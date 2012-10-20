#include "CScene.h"
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
