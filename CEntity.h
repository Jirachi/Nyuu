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
    friend class CScene;

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

    // Set entity Z depth index
    virtual void setZIndex(unsigned short layer) { mZIndex = layer; }

    // Returns entity Z depth index
    unsigned short getZIndex() const { return mZIndex; }

    // Apply the entity to the current scene
    virtual void addToScene(QGraphicsScene* scene);

    // Returns the type of this entity
    virtual EntityType getType() const { return ENTITY_TYPE_DUMMY; }

    // Returns the current RenderWidget item representation
    virtual QGraphicsItem* getSceneItem() const { return 0; }

    // Returns the properties available for this entity
    virtual QVariantMap getProperties();

    // Defines a property for this entity
    // Returns if the property has been successfully set
    virtual bool setProperty(const QString& key, const QVariant& value);

    // Copies this entity's properties to the target specified
    virtual void copyPropertiesTo(CEntity* ent);

    // Return entity ID
    long getEntityId() const { return mEntityId; }

    ///////////////////////////////////
    // Properties key names
    static const QString PROP_KEY_REF_NAME;
    static const QString PROP_KEY_Z_INDEX;
    static const QString PROP_KEY_POSITION_X;
    static const QString PROP_KEY_POSITION_Y;
    ///////////////////////////////////

protected:
    long mEntityId;
    Vector2D mPosition;
    float mAngle;
    QString mReferenceName;
    unsigned short mZIndex;
};

#endif // CENTITY_H
