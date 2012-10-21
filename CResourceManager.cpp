#include "CResourceManager.h"
#include "CResource.h"

CResourceManager* CResourceManager::mSingleton = 0;

//----------------------------------------------
CResourceManager::CResourceManager()
{
}
//----------------------------------------------
CResourceManager::~CResourceManager()
{

}
//----------------------------------------------
CResourceManager* CResourceManager::getInstance()
{
    if (!mSingleton)
    {
        mSingleton = new CResourceManager;
    }

    return mSingleton;
}
//----------------------------------------------
CResource* CResourceManager::get(const QString &path)
{
    CResource* rsrc = mResources[path];

    if (!rsrc)
    {
        rsrc = new CResource(path);
        mResources[path] = rsrc;
    }

    return rsrc;
}
//----------------------------------------------
