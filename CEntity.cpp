#include "CEntity.h"

//-----------------------------------------------------
CEntity::CEntity(long id) : mEntityId(id), mAngle(0), mPosition(0,0)
{

}
//-----------------------------------------------------
CEntity::~CEntity()
{

}
//-----------------------------------------------------
void CEntity::addToScene(QGraphicsScene *scene)
{
    Q_UNUSED(scene);
    // Nothing to do here.
}
//-----------------------------------------------------
void CEntity::setAngle(float angle)
{
    mAngle = angle;
}
//-----------------------------------------------------
void CEntity::setPosition(const Vector2D &pos)
{
    mPosition = pos;
}
//-----------------------------------------------------
QVariantMap CEntity::getProperties()
{
    QVariantMap map;

    // General properties for all entities
    map.insert("ref_name", mReferenceName);
    map.insert("pos_x", mPosition.x);
    map.insert("pos_y", mPosition.y);

    return map;
}
//-----------------------------------------------------
