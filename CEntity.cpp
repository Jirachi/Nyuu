#include "CEntity.h"

const QString CEntity::PROP_KEY_REF_NAME = "ref_name";
const QString CEntity::PROP_KEY_POSITION_X = "pos_x";
const QString CEntity::PROP_KEY_POSITION_Y = "pos_y";

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
    map.insert(PROP_KEY_REF_NAME, mReferenceName);
    map.insert(PROP_KEY_POSITION_X, mPosition.x);
    map.insert(PROP_KEY_POSITION_Y, mPosition.y);

    return map;
}
//-----------------------------------------------------
bool CEntity::setProperty(const QString &key, const QVariant &value)
{
    if (key == PROP_KEY_REF_NAME)
    {
        mReferenceName = value.toString();
        return true;
    }

    if (key == PROP_KEY_POSITION_X)
    {
        mPosition.x = value.toInt();
        return true;
    }

    if (key == PROP_KEY_POSITION_Y)
    {
        mPosition.y = value.toInt();
        return true;
    }


    return false;
}
//-----------------------------------------------------
