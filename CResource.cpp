#include "CResource.h"
#include "Globals.h"
#include "QJson/json_parser.hh"
#include <QFile>
#include <QMessageBox>

//-------------------------------------------------
CResource::CResource(const QString &file) :
    mFile(file)
{
    load();
}
//-------------------------------------------------
CResource::~CResource()
{

}
//-------------------------------------------------
void CResource::load()
{
    qDebug() << "Loading resource at " << Globals::getProjectPath() + "/" + mFile;

    // We read the rs file (which is under JSON format)
    QFile file(Globals::getProjectPath() + "/" + mFile);
    file.open(QFile::ReadOnly);
    QByteArray fileContents = file.readAll();

    qDebug() << "File contents: " << fileContents;

    // We parse it
    QJson::Parser parser;
    bool ok;

    QVariantMap result = parser.parse(fileContents, &ok).toMap();

    if (!ok)
    {
        QMessageBox::critical(0, "Erreur de lecture JSON", "Le fichier " + mFile + " n'est pas au format JSON, ou possède une erreur de syntaxe!\nLigne: " + QString::number(parser.errorLine()) + "\nErreur: " + parser.errorString());
        return;
    }

    qDebug() << "Read resource file";

    mProperties = result;
}
//-------------------------------------------------
void CResource::save()
{

}
//-------------------------------------------------
QVariant& CResource::getProperty(const QString &key)
{
    return mProperties[key];
}
//-------------------------------------------------
