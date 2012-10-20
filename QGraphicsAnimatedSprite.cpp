#include "QGraphicsAnimatedSprite.h"
#include <QPainter>

//-----------------------------------------------------------
QGraphicsAnimatedSprite::QGraphicsAnimatedSprite(QImage &spritesheet) : mSpriteSheet(spritesheet)
{

}
//-----------------------------------------------------------
QGraphicsAnimatedSprite::~QGraphicsAnimatedSprite()
{

}
//-----------------------------------------------------------
void QGraphicsAnimatedSprite::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QRect sr = QRect(0, 0, 32, 32);
    painter->drawImage(pos(), mSpriteSheet, sr, Qt::AutoColor);
}
//-----------------------------------------------------------
