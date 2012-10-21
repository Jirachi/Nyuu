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

    // Override paint event from QGraphicsObject
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // Override boundingRect calculation from QGraphicsObject
    // @note: Miscalculating boundingRect results in rendering glitches
    QRectF boundingRect() const;

    // Timer event for animation
    void timerEvent(QTimerEvent *evt);

    // Set whether or not to enable frame reverse (animation goes 1==>10 10==>1 1==>10.. instead of 1==>10 1==>10 1==>10)
    void setFrameReversion(bool reverse);

    // Set the number of lines and columns of the sheet
    void setSheetSize(int lines, int columns);

    // Set the size of one element of the sheet
    void setElementSize(int width, int height);

    // Set the animation frames to loop
    void setAnimationFrames(int start_col, int start_line, int end_col, int end_line);

    // Set time between each frame (100 = 100ms between each frame)
    void setSpeed(int timeMs);

protected:
    QImage mSpriteSheet;
    int mTimerId;

    int mCurrentColumn;
    int mCurrentLine;

    bool mReverseFrame;
    bool mReverseFrameEnabled;

    int mAnimationStartCol;
    int mAnimationStartLine;
    int mAnimationEndCol;
    int mAnimationEndLine;

    int mSheetLines;
    int mSheetColumns;
    int mElementWidth;
    int mElementHeight;
};

#endif // QGRAPHICSANIMATEDSPRITE_H
