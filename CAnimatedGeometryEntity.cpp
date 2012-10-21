#include "CAnimatedGeometryEntity.h"
#include "QGraphicsAnimatedSprite.h"
#include "CResource.h"
#include "Globals.h"
#include <QDebug>

//----------------------------------------------------
CAnimatedGeometryEntity::CAnimatedGeometryEntity(long id, CResource* resource) :
    CEntity(id), mResource(resource)
{
    QString filePath = Globals::getProjectPath() + "/" + resource->getProperty("file").toString();
    qDebug() << "File path: " << filePath;
    mSprite = new QGraphicsAnimatedSprite(QImage(filePath));
}
//----------------------------------------------------
CAnimatedGeometryEntity::~CAnimatedGeometryEntity()
{
    if (mSprite)
        delete mSprite;
}
//----------------------------------------------------
void CAnimatedGeometryEntity::addToScene(QGraphicsScene *scene)
{
    scene->addItem(mSprite);
    mSprite->setPos(mPosition.x, mPosition.y);
}
//----------------------------------------------------
void CAnimatedGeometryEntity::setAngle(float angle)
{
    CEntity::setAngle(angle);

    mSprite->setRotation(angle);
}
//-----------------------------------------------------
void CAnimatedGeometryEntity::setPosition(const Vector2D &pos)
{
    CEntity::setPosition(pos);

    mSprite->setPos(pos.x, pos.y);
}
//-----------------------------------------------------
