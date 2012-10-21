#ifndef CANIMATEDGEOMETRYENTITY_H
#define CANIMATEDGEOMETRYENTITY_H

#include "CEntity.h"
#include "CScene.h"
#include <QGraphicsPixmapItem>

class CAnimatedGeometryEntity : public CEntity
{
protected:
    friend class CScene;

    // ctor
    CStaticGeometryEntity(long id, QString texture);

    // dtor
    ~CStaticGeometryEntity();

public:
    // Returns the texture file used by this entity
    QString getTexture() const;

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
    QString mTextureFile;
    QPixmap mTexturePixmap;
    QGraphicsPixmapItem* mSceneItem;
};

#endif // CANIMATEDGEOMETRYENTITY_H
