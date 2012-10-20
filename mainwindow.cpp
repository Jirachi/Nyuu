#include "mainwindow.h"
#include "aboutdialog.h"
#include "ui_mainwindow.h"

#include "CScene.h"
#include "Globals.h"

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
    scene->createStaticGeometry("C:\\Users\\Guigui\\Downloads\\test.jpg");
}
//-----------------------------------------------------
