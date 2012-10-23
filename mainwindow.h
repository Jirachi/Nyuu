#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>

class QGraphicsItem;
class QTableWidgetItem;
class CEntity;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void onClick_APropos();
    void onClick_Nouveau();
    void onClick_SetProjectPath();
    void onDoubleClick_EntityTree(QTreeWidgetItem* item, int column);
    void onSelect_RenderItem(QGraphicsItem* item);
    void onClear_RenderSelection();
    void onChange_Property(QTableWidgetItem* item);

private:
    Ui::MainWindow *ui;
    CEntity* mSelectedEntity;
};

#endif // MAINWINDOW_H
