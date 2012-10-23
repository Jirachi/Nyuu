#include "CAnimatedGeometryEntity.h"
#include "QGraphicsAnimatedSprite.h"
#include "CResource.h"
#include "Globals.h"
#include <QDebug>
#include <QVariant>

const QString CAnimatedGeometryEntity::PROP_KEY_ANIMATION_NAME = "anim_name";

//----------------------------------------------------
CAnimatedGeometryEntity::CAnimatedGeometryEntity(long id, CResource* resource) :
    CEntity(id), mResource(resource)
{
    QString filePath = Globals::getProjectPath() + "/" + resource->getProperty("file").toString();
    qDebug() << "File path: " << filePath;
    mSprite = new QGraphicsAnimatedSprite(QImage(filePath));

    // Read resource file for settings
    QVariantMap rsrc_anim = mResource->getProperty("anim").toMap();
    mSprite->setSheetSize(rsrc_anim["lines"].toInt(), rsrc_anim["columns"].toInt());
    mSprite->setElementSize(rsrc_anim["width"].toInt(), rsrc_anim["height"].toInt());
    mSprite->setFrameReversion(rsrc_anim["reverse"].toBool());
    mSprite->setSpeed(rsrc_anim["speed"].toInt());

    _loadAnimations();

    // test
    playAnimation("idle");
}
//----------------------------------------------------
CAnimatedGeometryEntity::~CAnimatedGeometryEntity()
{
    if (mSprite)
        delete mSprite;
}
//----------------------------------------------------
void CAnimatedGeometryEntity::addToScene(QGraphicsScene *scene)
{
    scene->addItem(mSprite);
    mSprite->setPos(mPosition.x, mPosition.y);
}
//----------------------------------------------------
void CAnimatedGeometryEntity::setAngle(float angle)
{
    CEntity::setAngle(angle);

    mSprite->setRotation(angle);
}
//-----------------------------------------------------
void CAnimatedGeometryEntity::setPosition(const Vector2D &pos)
{
    CEntity::setPosition(pos);

    mSprite->setPos(pos.x, pos.y);
}
//-----------------------------------------------------
void CAnimatedGeometryEntity::_loadAnimations()
{
    // Read the "anims" array from resource file
    QVariantMap rsrc_anim = mResource->getProperty("anim").toMap();
    QVariantList anims = rsrc_anim["anims"].toList();

    for (QVariantList::iterator it = anims.begin(); it != anims.end(); ++it)
    {
        QVariantMap current_anim = (*it).toMap();
        Animation anim_struct;

        anim_struct.start_col = current_anim["start_col"].toInt();
        anim_struct.start_line = current_anim["start_line"].toInt();
        anim_struct.end_col = current_anim["end_col"].toInt();
        anim_struct.end_line = current_anim["end_line"].toInt();
        anim_struct.name = current_anim["name"].toString();

        mAnimations[anim_struct.name] = anim_struct;
    }
}
//-----------------------------------------------------
void CAnimatedGeometryEntity::playAnimation(const QString &name)
{
    Animation anim = mAnimations[name];
    mSprite->setAnimationFrames(anim.start_col, anim.start_line, anim.end_col, anim.end_line);
}
//-----------------------------------------------------
QVariantMap CAnimatedGeometryEntity::getProperties()
{
    QVariantMap map = CEntity::getProperties();

    return map;
}
//-----------------------------------------------------
bool CAnimatedGeometryEntity::setProperty(const QString &key, const QVariant &value)
{
    if (key == PROP_KEY_ANIMATION_NAME)
    {
        playAnimation(value.toString());
        return true;
    }

    // Fall back on parent class implementation
    return CEntity::setProperty(key,value);
}
//-----------------------------------------------------
