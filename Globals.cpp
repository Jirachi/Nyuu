#include "Globals.h"
#include "CScene.h"

CScene* Globals::mCurrentScene = 0;
QGraphicsScene* Globals::mCurrentGraphicsScene = 0;
QString Globals::mProjectPath = "";

//-----------------------------------------------------
Globals::Globals()
{

}
//-----------------------------------------------------
void Globals::setCurrentScene(CScene *scene)
{
    if (mCurrentScene)
        delete mCurrentScene;

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
void Globals::setProjectPath(const QString &path)
{
    mProjectPath = path;
}
//-----------------------------------------------------
QString Globals::getProjectPath()
{
    return mProjectPath;
}
//-----------------------------------------------------
