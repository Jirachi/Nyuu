#include "QGraphicsAnimatedSprite.h"
#include <QPainter>
#include <QDebug>

//-----------------------------------------------------------
QGraphicsAnimatedSprite::QGraphicsAnimatedSprite(QImage &spritesheet) : mSpriteSheet(spritesheet),
    mCurrentFrame(0), mReverseFrame(false)
{
    startTimer(100);
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

    QRect sr = QRect(mCurrentFrame * 56, 0, 56, 80);
    painter->drawImage(QPoint(0,0), mSpriteSheet, sr, Qt::AutoColor);
}
//-----------------------------------------------------------
QRectF QGraphicsAnimatedSprite::boundingRect() const
{
    return QRectF(0, 0, 56, 80);
}
//-----------------------------------------------------------
void QGraphicsAnimatedSprite::timerEvent(QTimerEvent *evt)
{
    if (mCurrentFrame == 2)
    {
        mReverseFrame = true;
    }
    else if (mCurrentFrame == 0)
    {
        mReverseFrame = false;
    }

    if (mReverseFrame)
        mCurrentFrame--;
    else
        mCurrentFrame++;

    this->update();
}
//-----------------------------------------------------------
