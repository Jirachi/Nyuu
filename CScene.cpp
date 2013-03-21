#include "CScene.h"
#include "CEntity.h"
#include "CStaticGeometryEntity.h"
#include "CAnimatedGeometryEntity.h"
#include "CResourceManager.h"
#include "Globals.h"
#include <QMessageBox>
#include <QFile>
#include <QDebug>
#include "QJson/serializer.h"
#include "QJson/parser.h"

//-----------------------------------------------------
CScene::CScene() : mFreeEntityId(0)
{
}
//-----------------------------------------------------
CScene::~CScene()
{

}
//-----------------------------------------------------
CStaticGeometryEntity* CScene::createStaticGeometry(CResource* resource, int entityId)
{
    int finalId = (entityId == -1 ? ++mFreeEntityId : entityId);

    if (entityId != -1 && entityId > mFreeEntityId)
        mFreeEntityId = entityId+1;

    CStaticGeometryEntity* entity = new CStaticGeometryEntity(finalId, resource);
    entity->addToScene(Globals::getCurrentGraphicsScene());

    mEntities.push_back(entity);

    return entity;
}
//-----------------------------------------------------
CAnimatedGeometryEntity* CScene::createAnimatedGeometry(CResource* resource, int entityId)
{
    int finalId = (entityId == -1 ? ++mFreeEntityId : entityId);

    if (entityId != -1 && entityId > mFreeEntityId)
        mFreeEntityId = entityId+1;

    CAnimatedGeometryEntity* entity = new CAnimatedGeometryEntity(finalId, resource);
    entity->addToScene(Globals::getCurrentGraphicsScene());

    mEntities.push_back(entity);

    return entity;
}
//-----------------------------------------------------
void CScene::addAllElementsToScene(QGraphicsScene *scene)
{
    for (QList<CEntity*>::iterator it = mEntities.begin(); it != mEntities.end(); ++it)
    {
        (*it)->addToScene(scene);
    }
}
//-----------------------------------------------------
CEntity* CScene::getEntityFromGraphicsView(QGraphicsItem *element)
{
    for (QList<CEntity*>::iterator it = mEntities.begin(); it != mEntities.end(); ++it)
    {
        if ((*it)->getSceneItem() == element)
        {
            return (*it);
        }
    }

    return 0;
}
//-----------------------------------------------------
CEntity* CScene::cloneEntity(CEntity *src)
{
    switch (src->getType())
    {
    case ENTITY_TYPE_STATIC_GEOMETRY:
    {
        CStaticGeometryEntity* ent = static_cast<CStaticGeometryEntity*>(src);
        CStaticGeometryEntity* clone = createStaticGeometry(ent->getResource());
        ent->copyPropertiesTo(clone);
        return clone;
    }

    case ENTITY_TYPE_ANIMATED_GEOMETRY:
    {
        CAnimatedGeometryEntity* ent = static_cast<CAnimatedGeometryEntity*>(src);
        CAnimatedGeometryEntity* clone = createAnimatedGeometry(ent->getResource());
        ent->copyPropertiesTo(clone);
        return clone;
    }


    default:
        QMessageBox::critical(0, "Erreur", "Clonage de ce type d'entité non supporté!!! CScene::cloneEntity");
        break;
    }

    return 0;
}
//-----------------------------------------------------
void CScene::save(const QString &filename)
{
    // Serialize the scene
    QVariantMap output;

    // Serialize scene settings
    // TODO: Background, name, etc
    output.insert("settings", QVariantMap());

    // Serialize scene elements
    QVariantMap entities;
    for (QList<CEntity*>::iterator it = mEntities.begin(); it != mEntities.end(); ++it)
    {
        CEntity* ent = (*it);
        QVariantMap props;
        props.insert("properties", ent->getProperties());
        props.insert("type", ent->getType());
        entities.insert(QString::number(ent->getEntityId()), props);
    }


    output.insert("entities", entities);


    QJson::Serializer serializer;
    QByteArray json = serializer.serialize(output);

    // Write data
    QFile file(filename);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QDataStream out(&file);
    out << json;  // serialize as string
    file.flush();
    file.close();
}
//-----------------------------------------------------
void CScene::load(const QString &filename)
{
    // Read the scene status
    // Read raw scene file
    qDebug() << "Starting loading scene " << filename;
    QFile file(filename);
    QString jsonData;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        while (!in.atEnd())
        {
            //!!!! WARNING HAAAAAX
            // Somehow, I get \0 as the very first character of the saved scene file,
            // meaning that the whole JSON data is cut at the first character (which is pretty
            // embarrassing!) - so I'm manually overriding this here. I'll take a closer look
            // at this another time.
            QString line = in.readLine().trimmed(); //.replace('\0', ' ');
            jsonData.append(line);
        }
    }
    else
    {
        QMessageBox::critical(0, "Erreur", "Erreur lors de l'ouverture du fichier!");
        return;
    }

    // Parse all teh JSONz!
    QJson::Parser parser;
    bool ok;

    QVariantMap result = parser.parse (jsonData.toAscii(), &ok).toMap();
    if (!ok)
    {
        QMessageBox::critical(0, "Erreur" ,"Erreur lors du décodage: " + parser.errorString() + " at line " + QString::number(parser.errorLine()));
        return;
    }

    // Read JSON data
    // TODO: Background, name, etc... (see save())

    // De-serialize scene elements
    QVariantMap entities = result["entities"].toMap();
    for (QVariantMap::iterator it = entities.begin(); it != entities.end(); ++it)
    {
        int entityId = it.key().toInt();
        QVariantMap entityValue = it.value().toMap();

        // Read the types and the properties
        EntityType entityType = (EntityType)entityValue["type"].toInt();
        QVariantMap entityProps = entityValue["properties"].toMap();

        CEntity* entity = 0;

        // Create the right entity based on the type stored
        switch (entityType)
        {
        case ENTITY_TYPE_STATIC_GEOMETRY:
            entity = createStaticGeometry(CResourceManager::getInstance()->get(entityProps[CStaticGeometryEntity::PROP_KEY_RESOURCE].toString()), entityId);
            break;

        case ENTITY_TYPE_ANIMATED_GEOMETRY:
            entity = createAnimatedGeometry(CResourceManager::getInstance()->get(entityProps[CAnimatedGeometryEntity::PROP_KEY_RESOURCE].toString()), entityId);
            break;

        default:
            QMessageBox::critical(0, "Erreur!", "Type d'entité non supportée: " + QString::number(entityType));
            continue;
            break; // weirdness ahead!
        }

        // Re-apply all properties
        for (QVariantMap::iterator propsIt = entityProps.begin(); propsIt != entityProps.end(); ++propsIt)
        {
            QString propKey = propsIt.key();
            QVariant propValue = propsIt.value();

            entity->setProperty(propKey, propValue);
        }

        // Cave Johnson, we're done here.
    }
}
//-----------------------------------------------------
void CScene::remove(CEntity *ent)
{
    delete ent;
    mEntities.removeAll(ent);
}
//-----------------------------------------------------
