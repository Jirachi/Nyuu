#ifndef CSTATICGEOMETRYENTITY_H
#define CSTATICGEOMETRYENTITY_H

#include "CEntity.h"
#include "CScene.h"
#include <QGraphicsPixmapItem>

class CResource;
class CStaticGeometryEntity : public CEntity
{
protected:
    friend class CScene;

    // ctor
    CStaticGeometryEntity(long id, CResource* resource);

    // dtor
    ~CStaticGeometryEntity();

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
    virtual EntityType getType() const { return ENTITY_TYPE_STATIC_GEOMETRY; }

    // Returns the current RenderWidget item representation
    virtual QGraphicsItem* getSceneItem() const { return mSceneItem; }

protected:
    CResource* mResource;
    QPixmap mTexturePixmap;
    QGraphicsPixmapItem* mSceneItem;
};

#endif // CSTATICGEOMETRYENTITY_H
