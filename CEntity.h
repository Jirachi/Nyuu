#ifndef CENTITY_H
#define CENTITY_H

#include "Maths.h"
#include <QGraphicsScene>

enum EntityType
{
    ENTITY_TYPE_DUMMY,
    ENTITY_TYPE_STATIC_GEOMETRY,
    ENTITY_TYPE_ANIMATED_GEOMETRY
};


class CEntity
{
protected:
    // ctor
    CEntity(long id);

    // dtor
    virtual ~CEntity();

public:
    // Set Entity Position
    virtual void setPosition(const Vector2D& pos);

    // Returns entity position
    Vector2D getPosition() const { return mPosition; }

    // Set entity angle
    virtual void setAngle(float angle);

    // Returns entity angle
    float getAngle() const { return mAngle; }

    // Apply the entity to the current scene
    virtual void addToScene(QGraphicsScene* scene);

    // Returns the type of this entity
    virtual EntityType getType() const { return ENTITY_TYPE_DUMMY; }

    // Returns the current RenderWidget item representation
    virtual QGraphicsItem* getSceneItem() const { return 0; }

protected:
    long mEntityId;
    Vector2D mPosition;
    float mAngle;
};

#endif // CENTITY_H
