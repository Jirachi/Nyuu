#ifndef CSCENE_H
#define CSCENE_H

#include <QList>

class CEntity;
class CStaticGeometryEntity;
class CScene
{
public:
    // ctor
    CScene();

    // dtor
    ~CScene();

    // Returns a list of all the scene's entities
    QList<CEntity*>& getEntities() const;

    // Create a Static Geometry entity
    CStaticGeometryEntity* createStaticGeometry(const QString& texture);

protected:
    QList<CEntity*> mEntities;
    long mFreeEntityId;
};

#endif // CSCENE_H
