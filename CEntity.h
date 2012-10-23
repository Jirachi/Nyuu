#ifndef CENTITY_H
#define CENTITY_H

#include "Maths.h"
#include <QGraphicsScene>
#include <QVariantMap>

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
    // Set Entity reference name (optional)
    void setReferenceName(const QString& name) { mReferenceName = name; }

    // Return Entity reference name (can be empty)
    QString getReferenceName() const { return mReferenceName; }

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

    // Returns the properties available for this entity
    virtual QVariantMap getProperties();

protected:
    long mEntityId;
    Vector2D mPosition;
    float mAngle;
    QString mReferenceName;
};

#endif // CENTITY_H
