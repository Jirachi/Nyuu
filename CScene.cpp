#include "CScene.h"
#include "CEntity.h"
#include "CStaticGeometryEntity.h"
#include "Globals.h"

//-----------------------------------------------------
CScene::CScene() : mFreeEntityId(0)
{
}
//-----------------------------------------------------
CScene::~CScene()
{

}
//-----------------------------------------------------
CStaticGeometryEntity* CScene::createStaticGeometry(const QString &texture)
{
    CStaticGeometryEntity* entity = new CStaticGeometryEntity(++mFreeEntityId, texture);
    entity->addToScene(Globals::getCurrentGraphicsScene());

    return entity;
}
//-----------------------------------------------------
void CScene::addAllElementsToScene(QGraphicsScene *scene)
{
    for (QList<CEntity*>::iterator it = mEntities.begin(); it != mEntities.end(); ++it)
    {
        (*it)->addToScene(scene);
    }
}
//-----------------------------------------------------
