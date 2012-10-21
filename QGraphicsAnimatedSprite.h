#ifndef QGRAPHICSANIMATEDSPRITE_H
#define QGRAPHICSANIMATEDSPRITE_H

#include <QGraphicsObject>
#include <QTime>

class QGraphicsAnimatedSprite : public QGraphicsObject
{
public:
    // ctor
    QGraphicsAnimatedSprite(QImage& spritesheet);

    // dtor
    ~QGraphicsAnimatedSprite();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QRectF boundingRect() const;

    void timerEvent(QTimerEvent *evt);

protected:
    QImage mSpriteSheet;
    int mCurrentFrame;
    bool mReverseFrame;
};

#endif // QGRAPHICSANIMATEDSPRITE_H
