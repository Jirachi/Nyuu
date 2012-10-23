#ifndef CRESOURCE_H
#define CRESOURCE_H

#include <QString>
#include <QVariant>

class CResource
{
public:
    // ctor
    CResource(const QString& file);

    // dtor
    ~CResource();

    // Return a resource property
    QVariant& getProperty(const QString& key);

    // Return all the properties
    QVariantMap& getProperties();

    // Read the values from the resource file
    void load();

    // Save the values to the resource file
    void save();

protected:
    QString mFile;
    QVariantMap mProperties;
};

#endif // CRESOURCE_H
