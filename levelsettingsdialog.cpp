#include "levelsettingsdialog.h"
#include "ui_levelsettingsdialog.h"

LevelSettingsDialog::LevelSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LevelSettingsDialog)
{
    ui->setupUi(this);
}

LevelSettingsDialog::~LevelSettingsDialog()
{
    delete ui;
}
