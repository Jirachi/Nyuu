#include "mainwindow.h"
#include "aboutdialog.h"
#include "ui_mainwindow.h"

#include "CScene.h"
#include "CStaticGeometryEntity.h"
#include "Globals.h"
#include "Maths.h"

//-----------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionA_propos, SIGNAL(triggered()), this, SLOT(onClick_APropos()));
    connect(ui->actionNouveau, SIGNAL(triggered()), this, SLOT(onClick_Nouveau()));
}
//-----------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}
//-----------------------------------------------------
void MainWindow::onClick_APropos()
{
    static AboutDialog* dlg = 0;

    if (!dlg)
        dlg = new AboutDialog();

    dlg->show();
}
//-----------------------------------------------------
void MainWindow::onClick_Nouveau()
{
    CScene* scene = new CScene();
    Globals::setCurrentScene(scene);
    ui->renderWidget->notifySceneChanged();

    scene->createStaticGeometry("D:\\Projets\\Jirachi\\test-rsrc\\tree_0_med.png")->setPosition(Vector2D(50, 50));
    scene->createStaticGeometry("D:\\Projets\\Jirachi\\test-rsrc\\tree_0_med.png")->setPosition(Vector2D(150, 150));
    scene->createStaticGeometry("D:\\Projets\\Jirachi\\test-rsrc\\turret.svg")->setPosition(Vector2D(350, 150));

}
//-----------------------------------------------------
