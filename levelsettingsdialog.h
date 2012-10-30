#ifndef LEVELSETTINGSDIALOG_H
#define LEVELSETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class LevelSettingsDialog;
}

class LevelSettingsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit LevelSettingsDialog(QWidget *parent = 0);
    ~LevelSettingsDialog();
    
private:
    Ui::LevelSettingsDialog *ui;
};

#endif // LEVELSETTINGSDIALOG_H
