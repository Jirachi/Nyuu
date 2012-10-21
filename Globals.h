#ifndef GLOBALS_H
#define GLOBALS_H

#include <QGraphicsScene>

class CScene;

class Globals
{
protected:
    static CScene* mCurrentScene;
    static QGraphicsScene* mCurrentGraphicsScene;
    static QString mProjectPath;

public:
    Globals();

    static void setCurrentScene(CScene* scene);
    static CScene* getCurrentScene();

    static void setCurrentGraphicsScene(QGraphicsScene* scene);
    static QGraphicsScene* getCurrentGraphicsScene();

    static void setProjectPath(const QString& path);
    static QString getProjectPath();
};

#endif // GLOBALS_H
