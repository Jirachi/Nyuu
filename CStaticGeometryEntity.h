#ifndef CSTATICGEOMETRYENTITY_H
#define CSTATICGEOMETRYENTITY_H

#include "CEntity.h"
#include "CScene.h"
#include <QGraphicsPixmapItem>

class CStaticGeometryEntity : public CEntity
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

protected:
    QString mTextureFile;
    QPixmap mTexturePixmap;
    QGraphicsPixmapItem* mSceneItem;
};

#endif // CSTATICGEOMETRYENTITY_H
