#ifndef CANIMATEDGEOMETRYENTITY_H
#define CANIMATEDGEOMETRYENTITY_H

#include "CEntity.h"
#include "CScene.h"
#include "QGraphicsAnimatedSprite.h"

struct Animation
{
    int start_line;
    int start_col;
    int end_line;
    int end_col;
    QString name;
};

class CResource;
class CAnimatedGeometryEntity : public CEntity
{
protected:
    friend class CScene;

    // ctor
    CAnimatedGeometryEntity(long id, CResource* resource);

    // dtor
    ~CAnimatedGeometryEntity();

public:
    // Returns the resource used by this entity
    CResource* getResource() const { return mResource; }

    // Apply the entity to the current scene
    virtual void addToScene(QGraphicsScene* scene);

    // Set Entity Position
    virtual void setPosition(const Vector2D& pos);

    // Set entity angle
    virtual void setAngle(float angle);

    // Returns the type of this entity
    virtual EntityType getType() const { return ENTITY_TYPE_ANIMATED_GEOMETRY; }

    // Returns the current RenderWidget item representation
    virtual QGraphicsItem* getSceneItem() const { return mSprite; }

    // Play the specified animation name
    void playAnimation(const QString& name);

    // Returns the properties available for this entity
    virtual QVariantMap getProperties();

    // Defines a property for this entity
    // Returns if the property has been successfully set
    virtual bool setProperty(const QString& key, const QVariant& value);

    // Set entity Z depth index
    virtual void setZIndex(unsigned short layer);

    // Copies this entity's properties to the target specified
    virtual void copyPropertiesTo(CEntity* ent);

    ///////////////////////////////////
    // Properties key names
    static const QString PROP_KEY_ANIMATION_NAME;
    static const QString PROP_KEY_RESOURCE;
    ///////////////////////////////////

protected:
    void _loadAnimations();

protected:
    CResource* mResource;
    QGraphicsAnimatedSprite* mSprite;
    QMap<QString, Animation> mAnimations;
    QString mCurrentAnimation;
};

#endif // CANIMATEDGEOMETRYENTITY_H
