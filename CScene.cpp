#include "CScene.h"
#include "CEntity.h"
#include "CStaticGeometryEntity.h"
#include "CAnimatedGeometryEntity.h"
#include "Globals.h"
#include <QMessageBox>
#include <QFile>
#include "QJson/serializer.h"

//-----------------------------------------------------
CScene::CScene() : mFreeEntityId(0)
{
}
//-----------------------------------------------------
CScene::~CScene()
{

}
//-----------------------------------------------------
CStaticGeometryEntity* CScene::createStaticGeometry(CResource* resource)
{
    CStaticGeometryEntity* entity = new CStaticGeometryEntity(++mFreeEntityId, resource);
    entity->addToScene(Globals::getCurrentGraphicsScene());

    mEntities.push_back(entity);

    return entity;
}
//-----------------------------------------------------
CAnimatedGeometryEntity* CScene::createAnimatedGeometry(CResource* resource)
{
    CAnimatedGeometryEntity* entity = new CAnimatedGeometryEntity(++mFreeEntityId, resource);
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
        entities.insert(QString::number(ent->getEntityId()), ent->getProperties());
    }

    output.insert("entities", entities);


    QJson::Serializer serializer;
    QByteArray json = serializer.serialize(output);

    QFile file(filename);
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);   // we will serialize the data into the file
    out << json;  // serialize a string
}
//-----------------------------------------------------
