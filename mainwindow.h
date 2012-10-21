#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>

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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
