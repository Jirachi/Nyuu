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
