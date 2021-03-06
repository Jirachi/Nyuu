#include "CStaticGeometryEntity.h"
#include <QGraphicsPixmapItem>
#include "CResource.h"
#include "Globals.h"
#include <QDebug>

const QString CStaticGeometryEntity::PROP_KEY_RESOURCE = "resource";

//----------------------------------------------------
CStaticGeometryEntity::CStaticGeometryEntity(long id, CResource* resource) :
    CEntity(id), mResource(resource), mSceneItem(0)
{
    QString filePath = resource->getProperty("file").toString();
    qDebug() << "File path: " << filePath;
    mTexturePixmap = QPixmap(Globals::getProjectPath() + "/" + filePath);
}
//----------------------------------------------------
CStaticGeometryEntity::~CStaticGeometryEntity()
{
    if (mSceneItem)
        delete mSceneItem;
}
//----------------------------------------------------
void CStaticGeometryEntity::addToScene(QGraphicsScene *scene)
{
    // Memory management is tough here so we have to be careful. We keep a pointer to the
    // PixmapItem generated when adding an element to renderView's QGraphicsView, so we make
    // sure we have no duplicates when (re)adding to the scene.
    if (mSceneItem)
        delete mSceneItem;

    mSceneItem = scene->addPixmap(mTexturePixmap);
    mSceneItem->setPos(mPosition.x, mPosition.y);
}
//----------------------------------------------------
void CStaticGeometryEntity::setAngle(float angle)
{
    CEntity::setAngle(angle);

    mSceneItem->setRotation(angle);
}
//-----------------------------------------------------
void CStaticGeometryEntity::setPosition(const Vector2D &pos)
{
    CEntity::setPosition(pos);

    mSceneItem->setPos(pos.x, pos.y);
}
//-----------------------------------------------------
QVariantMap CStaticGeometryEntity::getProperties()
{
    QVariantMap map = CEntity::getProperties();

    map.insert(PROP_KEY_RESOURCE, mResource->getRelativeFilePath());

    return map;
}
//-----------------------------------------------------
bool CStaticGeometryEntity::setProperty(const QString &key, const QVariant &value)
{
    return CEntity::setProperty(key,value);
}
//-----------------------------------------------------
void CStaticGeometryEntity::setZIndex(unsigned short layer)
{
    CEntity::setZIndex(layer);

    mSceneItem->setZValue(layer);
}
//-----------------------------------------------------
