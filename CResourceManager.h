#ifndef CRESOURCEMANAGER_H
#define CRESOURCEMANAGER_H

#include <QMap>
#include <QString>

class CResource;
class CResourceManager
{
protected:
    static CResourceManager* mSingleton;

    // ctor
    CResourceManager();

    // dtor
    ~CResourceManager();

public:
    // Returns singleton instance
    static CResourceManager* getInstance();

    // Returns or load an existing resource at specified path (relative to project directory)
    CResource* get(const QString& path);

protected:
    QMap<QString, CResource*> mResources;
};

#endif // CRESOURCEMANAGER_H
