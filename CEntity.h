#ifndef CENTITY_H
#define CENTITY_H

#include "Maths.h"
#include <QGraphicsScene>

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

    // Set entity angle
    virtual void setAngle(float angle);

    // Apply the entity to the current scene
    virtual void addToScene(QGraphicsScene* scene);

protected:
    long mEntityId;
    Vector2D mPosition;
    float mAngle;
};

#endif // CENTITY_H
