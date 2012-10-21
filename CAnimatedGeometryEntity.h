#ifndef CANIMATEDGEOMETRYENTITY_H
#define CANIMATEDGEOMETRYENTITY_H

#include "CEntity.h"
#include "CScene.h"
#include "QGraphicsAnimatedSprite.h"

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
    CResource* getResource() const;

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

protected:
    CResource* mResource;
    QGraphicsAnimatedSprite* mSprite;
};

#endif // CANIMATEDGEOMETRYENTITY_H
