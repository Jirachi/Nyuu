#ifndef QGRAPHICSANIMATEDSPRITE_H
#define QGRAPHICSANIMATEDSPRITE_H

#include <QGraphicsObject>

class QGraphicsAnimatedSprite : public QGraphicsObject
{
public:
    // ctor
    QGraphicsAnimatedSprite(QImage& spritesheet);

    // dtor
    ~QGraphicsAnimatedSprite();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    QImage mSpriteSheet;
};

#endif // QGRAPHICSANIMATEDSPRITE_H
