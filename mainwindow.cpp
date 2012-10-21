#include "mainwindow.h"
#include "aboutdialog.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>
#include <QDirIterator>
#include <QDebug>
#include <QMessageBox>

#include "CScene.h"
#include "CStaticGeometryEntity.h"
#include "CAnimatedGeometryEntity.h"
#include "Globals.h"
#include "Maths.h"
#include "CResourceManager.h"
#include "CResource.h"

//-----------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionA_propos, SIGNAL(triggered()), this, SLOT(onClick_APropos()));
    connect(ui->actionNouveau, SIGNAL(triggered()), this, SLOT(onClick_Nouveau()));
    connect(ui->actionD_finir_le_chemin_du_projet, SIGNAL(triggered()), this, SLOT(onClick_SetProjectPath()));

    connect(ui->tree_EntitiesAvailable, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(onDoubleClick_EntityTree(QTreeWidgetItem*,int)));
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

    ui->dock_Toolset->setEnabled(true);

   /* scene->createStaticGeometry("D:\\Projets\\Jirachi\\test-rsrc\\tree_0_med.png")->setPosition(Vector2D(50, 50));
    scene->createStaticGeometry("D:\\Projets\\Jirachi\\test-rsrc\\tree_0_med.png")->setPosition(Vector2D(150, 150));
    scene->createStaticGeometry("D:\\Projets\\Jirachi\\test-rsrc\\turret.svg")->setPosition(Vector2D(350, 150));*/

}
//-----------------------------------------------------
void MainWindow::onClick_SetProjectPath()
{
    QString directory = QFileDialog::getExistingDirectory(this, "Répertoire projet...", ".");

    Globals::setProjectPath(directory);

    // Load resources in that directory and update side tree
    ui->tree_EntitiesAvailable->clear();

    QDir dir(directory);
    QDirIterator iterator(dir.absolutePath(), QDirIterator::Subdirectories);
    while (iterator.hasNext()) {
        iterator.next();

        QStringList strs;
        strs.push_back(iterator.fileName());
        strs.push_back(iterator.filePath().right(iterator.filePath().size() - directory.size() - 1));

        if ((!iterator.fileInfo().isDir() && !iterator.fileName().endsWith(".rs")) || iterator.fileName().startsWith("."))
            continue;

        if (!iterator.fileInfo().isDir())
        {
            QString topElement = strs.at(1).left(strs.at(1).indexOf("/"));
            ui->tree_EntitiesAvailable->findItems(topElement, Qt::MatchExactly).first()->addChild(new QTreeWidgetItem(strs));
        }
        else
        {
            ui->tree_EntitiesAvailable->addTopLevelItem(new QTreeWidgetItem(strs));
        }
    }
}
//-----------------------------------------------------
void MainWindow::onDoubleClick_EntityTree(QTreeWidgetItem* item, int column)
{
    QPoint midScene(ui->renderWidget->width()/2, ui->renderWidget->height()/2);
    QPointF projectedMidScene = ui->renderWidget->mapToScene(midScene);
    Vector2D midSceneVec(projectedMidScene.x(), projectedMidScene.y());

    CResource* resource = CResourceManager::getInstance()->get(item->text(1));

    if (resource->getProperty("type").toString() == "animated")
    {
        Globals::getCurrentScene()->createAnimatedGeometry(resource)->setPosition(midSceneVec);
    }
    else if (resource->getProperty("type").toString() == "static")
    {
        Globals::getCurrentScene()->createStaticGeometry(resource)->setPosition(midSceneVec);
    }
    else
    {
        QMessageBox::critical(this, "Erreur de ressource", "Le type n'est pas renseigné ou invalide (" + resource->getProperty("type").toString() + ")");
    }

}
//-----------------------------------------------------
