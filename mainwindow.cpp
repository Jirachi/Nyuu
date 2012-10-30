#include "mainwindow.h"
#include "aboutdialog.h"
#include "levelsettingsdialog.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>
#include <QDirIterator>
#include <QDebug>
#include <QMessageBox>
#include <QVariantMap>
#include <QSettings>
#include <cassert>

#include "CScene.h"
#include "CStaticGeometryEntity.h"
#include "CAnimatedGeometryEntity.h"
#include "Globals.h"
#include "Maths.h"
#include "CResourceManager.h"
#include "CResource.h"
#include "CEntity.h"

//-----------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mSelectedEntity(0), mCurrentScenePath("")
{
    ui->setupUi(this);

    // Connect all actions from UI
    connect(ui->actionA_propos, SIGNAL(triggered()), this, SLOT(onClick_APropos()));
    connect(ui->actionNouveau, SIGNAL(triggered()), this, SLOT(onClick_Nouveau()));
    connect(ui->actionSauvegarder, SIGNAL(triggered()), this, SLOT(onClick_Sauvegarder()));
    connect(ui->actionOuvrir, SIGNAL(triggered()), this, SLOT(onClick_Ouvrir()));
    connect(ui->actionD_finir_le_chemin_du_projet, SIGNAL(triggered()), this, SLOT(onClick_SetProjectPath()));
    connect(ui->actionQuitter, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionConfiguration_du_niveau, SIGNAL(triggered()), this, SLOT(onClick_ConfigNiveau()));

    connect(ui->tree_EntitiesAvailable, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(onDoubleClick_EntityTree(QTreeWidgetItem*,int)));
    connect(ui->tableProperties, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(onChange_Property(QTableWidgetItem*)));

    connect(ui->renderWidget, SIGNAL(itemSelected(QGraphicsItem*)), this, SLOT(onSelect_RenderItem(QGraphicsItem*)));
    connect(ui->renderWidget, SIGNAL(selectionCleared()), this, SLOT(onClear_RenderSelection()));
    connect(ui->renderWidget, SIGNAL(itemChanged()), this, SLOT(onUpdate_Properties()));

    // Reload the project path (if any)
    QSettings settings("Jirachi", "Nyuu");
    setProjectPath(settings.value("editor/ProjectPath", ".").toString());
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
    // Create a new scene and use it as current
    CScene* scene = new CScene();
    Globals::setCurrentScene(scene);
    ui->renderWidget->notifySceneChanged();

    ui->dock_Toolset->setEnabled(true);

   /* scene->createStaticGeometry("D:\\Projets\\Jirachi\\test-rsrc\\tree_0_med.png")->setPosition(Vector2D(50, 50));
    scene->createStaticGeometry("D:\\Projets\\Jirachi\\test-rsrc\\tree_0_med.png")->setPosition(Vector2D(150, 150));
    scene->createStaticGeometry("D:\\Projets\\Jirachi\\test-rsrc\\turret.svg")->setPosition(Vector2D(350, 150));*/

}
//-----------------------------------------------------
void MainWindow::setProjectPath(const QString &directory)
{
    Globals::setProjectPath(directory);
    QSettings settings("Jirachi", "Nyuu");
    settings.setValue("editor/ProjectPath", directory);

    // Load resources in that directory and update side tree
    ui->tree_EntitiesAvailable->clear();

    QDir dir(directory);
    QDirIterator iterator(dir.absolutePath(), QDirIterator::Subdirectories);
    while (iterator.hasNext()) {
        iterator.next();

        QStringList strs;
        strs.push_back(iterator.fileName());
        strs.push_back(iterator.filePath().right(iterator.filePath().size() - directory.size() - 1));

        // We filter only .rs files
        if ((!iterator.fileInfo().isDir() && !iterator.fileName().endsWith(".rs")) || iterator.fileName().startsWith("."))
            continue;

        // Folders are added as topLevelItems, files are children of them
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
void MainWindow::onClick_SetProjectPath()
{
    QString directory = QFileDialog::getExistingDirectory(this, "Répertoire projet...", ".");
    setProjectPath(directory);
}
//-----------------------------------------------------
void MainWindow::onDoubleClick_EntityTree(QTreeWidgetItem* item, int column)
{
    Q_UNUSED(column);

    // We grab a vector of the middle of the screen projected into scene-space
    QPoint midScene(ui->renderWidget->width()/2, ui->renderWidget->height()/2);
    QPointF projectedMidScene = ui->renderWidget->mapToScene(midScene);
    Vector2D midSceneVec(projectedMidScene.x(), projectedMidScene.y());

    CResource* resource = CResourceManager::getInstance()->get(item->text(1));

    // We make the right entity based on its type
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
void MainWindow::onClear_RenderSelection()
{
    // Disable the right panel
    ui->tab_2->setEnabled(false);
}
//-----------------------------------------------------
void MainWindow::onSelect_RenderItem(QGraphicsItem *item)
{
    CEntity* entity = Globals::getCurrentScene()->getEntityFromGraphicsView(item);
    onSelect_RenderItem(entity);
}
//-----------------------------------------------------
void MainWindow::onSelect_RenderItem(CEntity *item)
{
    if (!item)
    {
        onClear_RenderSelection();
        return;
    }

    // Enable the tab panel
    ui->tab_2->setEnabled(true);

    // Read properties and fill in the table
    ui->tableProperties->clearContents();

    mSelectedEntity = item;

    QVariantMap properties = item->getProperties();
    QList<QString> keys = properties.keys();
    ui->tableProperties->setRowCount(keys.size());

    int i = 0;
    for (QList<QString>::iterator it = keys.begin(); it != keys.end(); ++it)
    {
        QTableWidgetItem* propName = new QTableWidgetItem(*it);
        QTableWidgetItem* propValue = new QTableWidgetItem(properties[(*it)].toString());

        propName->setFlags(Qt::ItemIsEnabled);

        ui->tableProperties->setItem(i, 0, propName);
        ui->tableProperties->setItem(i, 1, propValue);
        i++;
    }
}
//-----------------------------------------------------
void MainWindow::onChange_Property(QTableWidgetItem *item)
{
    QString propName = ui->tableProperties->item(item->row(), 0)->text();

    assert(mSelectedEntity);

    if (item->text() != propName)
        mSelectedEntity->setProperty(propName, item->text());
}
//-----------------------------------------------------
void MainWindow::onUpdate_Properties()
{
    onSelect_RenderItem(mSelectedEntity);
}
//-----------------------------------------------------
void MainWindow::onClick_Sauvegarder()
{
    if (Globals::getCurrentScene())
    {
        if (mCurrentScenePath == "")
        {
            mCurrentScenePath = QFileDialog::getSaveFileName(this, "Fichier final", ".", "*.scn");
        }

        Globals::getCurrentScene()->save(mCurrentScenePath);
    }
}
//-----------------------------------------------------
void MainWindow::onClick_Ouvrir()
{
    QString path = QFileDialog::getOpenFileName(this, "Fichier scène", ".", "*.scn");

    if (path != "")
    {
        CScene* scene = new CScene();
        Globals::setCurrentScene(scene);
        ui->renderWidget->notifySceneChanged();

        scene->load(path);

        ui->dock_Toolset->setEnabled(true);
    }
}
//-----------------------------------------------------
void MainWindow::onClick_ConfigNiveau()
{
    if (!Globals::getCurrentScene())
    {
        QMessageBox::critical(this, "Impossible !", "Veuillez ouvrir un niveau.");
        return;
    }

    static LevelSettingsDialog* dlg = 0;
    if (!dlg)
    {
        dlg = new LevelSettingsDialog(this);
    }

    dlg->show();
}
//-----------------------------------------------------
