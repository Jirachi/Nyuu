#ifndef CSCENE_H
#define CSCENE_H

#include <QList>
#include <QGraphicsScene>

class CEntity;
class CStaticGeometryEntity;
class CAnimatedGeometryEntity;
class CResource;
class CScene
{
public:
    // ctor
    CScene();

    // dtor
    ~CScene();

    // Returns a list of all the scene's entities
    QList<CEntity*>& getEntities() const;

    // Add all the entities to the specified scene
    void addAllElementsToScene(QGraphicsScene* scene);

    // Create a Static Geometry entity
    CStaticGeometryEntity* createStaticGeometry(CResource* resource);

    // Create an Animated Geometry entity
    CAnimatedGeometryEntity* createAnimatedGeometry(CResource* resource);

    // Returns an entity whom QGraphicsItem representation is the specified pointer
    CEntity* getEntityFromGraphicsView(QGraphicsItem* element);

    // Clone the specified entity and returns the copied one
    CEntity* cloneEntity(CEntity* src);

    // Save the scene
    void save(const QString& filename);

protected:
    QList<CEntity*> mEntities;
    long mFreeEntityId;
};

#endif // CSCENE_H
