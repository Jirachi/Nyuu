#ifndef GLOBALS_H
#define GLOBALS_H

#include <QGraphicsScene>

class CScene;

class Globals
{
protected:
    static CScene* mCurrentScene;
    static QGraphicsScene* mCurrentGraphicsScene;

public:
    Globals();

    static void setCurrentScene(CScene* scene);
    static CScene* getCurrentScene();

    static void setCurrentGraphicsScene(QGraphicsScene* scene);
    static QGraphicsScene* getCurrentGraphicsScene();
};

#endif // GLOBALS_H
