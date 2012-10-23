#include "QGraphicsAnimatedSprite.h"
#include <QPainter>
#include <QDebug>

//-----------------------------------------------------------
QGraphicsAnimatedSprite::QGraphicsAnimatedSprite(QImage &spritesheet) : mSpriteSheet(spritesheet),
    mCurrentColumn(0), mCurrentLine(0), mReverseFrame(false)
{
    mTimerId = startTimer(100);
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

    QRect sr = QRect(mCurrentColumn * mElementWidth, mCurrentLine * mElementHeight, mElementWidth, mElementHeight);
    painter->drawImage(QPoint(0,0), mSpriteSheet, sr, Qt::AutoColor);
}
//-----------------------------------------------------------
QRectF QGraphicsAnimatedSprite::boundingRect() const
{
    return QRectF(0, 0, mElementWidth, mElementHeight);
}
//-----------------------------------------------------------
void QGraphicsAnimatedSprite::timerEvent(QTimerEvent *evt)
{
    // Check if we are at the end or at the beginning of the animation
    if (mCurrentColumn == mAnimationEndCol && mCurrentLine == mAnimationEndLine)
    {
        if (mReverseFrameEnabled)
        {
            mReverseFrame = true;
        }
        else
        {
            mCurrentColumn = mAnimationStartCol;
            mCurrentLine = mAnimationStartLine;
        }
    }
    else if (mCurrentColumn == mAnimationStartCol && mCurrentLine == mAnimationStartLine)
    {
        if (mReverseFrameEnabled)
        {
            mReverseFrame = false;
        }
    }

    // Progress through the frames
    if (!mReverseFrame) // Progress forward
    {
        if (mCurrentColumn == mSheetColumns-1)
        {
            mCurrentLine++;
            mCurrentColumn = 0;
        }
        else
        {
            mCurrentColumn++;
        }
    }
    else // Progress backwards
    {
        if (mCurrentColumn == 0)
        {
            mCurrentLine--;
            mCurrentColumn = mSheetColumns-1;
        }
        else
        {
            mCurrentColumn--;
        }
    }

    // Force redraw
    this->update();
}
//-----------------------------------------------------------
void QGraphicsAnimatedSprite::setAnimationFrames(int start_col, int start_line, int end_col, int end_line)
{
    mAnimationStartCol = start_col;
    mAnimationStartLine = start_line;
    mAnimationEndCol = end_col;
    mAnimationEndLine = end_line;

    // Reset animation state to avoid to go out of range
    mReverseFrame = false;
    mCurrentColumn = mAnimationStartCol;
    mCurrentLine = mAnimationStartLine;
}
//-----------------------------------------------------------
void QGraphicsAnimatedSprite::setFrameReversion(bool reverse)
{
    mReverseFrameEnabled = reverse;
}
//-----------------------------------------------------------
void QGraphicsAnimatedSprite::setSheetSize(int lines, int columns)
{
    mSheetLines = lines;
    mSheetColumns = columns;
}
//-----------------------------------------------------------
void QGraphicsAnimatedSprite::setElementSize(int width, int height)
{
    mElementWidth = width;
    mElementHeight = height;
}
//-----------------------------------------------------------
void QGraphicsAnimatedSprite::setSpeed(int timeMs)
{
    killTimer(mTimerId);
    mTimerId = startTimer(timeMs);
}
//-----------------------------------------------------------
