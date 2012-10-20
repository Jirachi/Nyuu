#include "Globals.h"
#include "CScene.h"

CScene* Globals::mCurrentScene = 0;
QGraphicsScene* Globals::mCurrentGraphicsScene = 0;

//-----------------------------------------------------
Globals::Globals()
{

}
//-----------------------------------------------------
void Globals::setCurrentScene(CScene *scene)
{
    mCurrentScene = scene;
}
//-----------------------------------------------------
CScene* Globals::getCurrentScene()
{
    return mCurrentScene;
}
//-----------------------------------------------------
void Globals::setCurrentGraphicsScene(QGraphicsScene *scene)
{
    mCurrentGraphicsScene = scene;
}
//-----------------------------------------------------
QGraphicsScene* Globals::getCurrentGraphicsScene()
{
    return mCurrentGraphicsScene;
}
//-----------------------------------------------------
