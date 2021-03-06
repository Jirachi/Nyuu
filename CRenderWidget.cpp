#include "CRenderWidget.h"
#include "Globals.h"
#include "CScene.h"
#include "CEntity.h"
#include <QGraphicsTextItem>
#include <QMouseEvent>
#include <QMessageBox>
#include <QMenu>
#include <QDebug>
#include <math.h>

//---------------------------------------------------------------------------
CRenderWidget::CRenderWidget(QWidget *parent) :
    QGraphicsView(parent),
    mIsCtrlKeyDown(false), mIsLeftMouseDown(false), mDoCopySelection(false)
{
    Globals::setCurrentGraphicsScene(&mScene);
    setScene(&mScene);
    setAlignment(Qt::AlignTop|Qt::AlignLeft);
    notifySceneChanged();
}
//---------------------------------------------------------------------------
CRenderWidget::~CRenderWidget()
{

}
//---------------------------------------------------------------------------
void CRenderWidget::notifySceneChanged()
{
    mScene.clear();

    if (Globals::getCurrentScene())
    {
        // Make background
        this->setBackgroundBrush(QBrush(QPixmap(Globals::getProjectPath() + "/backgrounds/01.jpg")));

        // We rebuild the scene out of the new elements.
        CScene* scene = Globals::getCurrentScene();

        scene->addAllElementsToScene(&mScene);
    }
    else
    {
        mScene.addText("Veuillez ouvrir ou cr�er un nouveau niveau.");
    }//
}
//---------------------------------------------------------------------------
void CRenderWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        mIsLeftMouseDown = true;
        mMouseDownPosition = event->pos();

        QGraphicsItem* item = itemAt(event->pos());

        // if we pressed control key, duplicate the selection
        // if user drags mouse
        if (mIsCtrlKeyDown)
        {
            mDoCopySelection = true;
        }

        selectEntity(item);
    }
}
//---------------------------------------------------------------------------
bool CRenderWidget::selectEntity(QGraphicsItem *item)
{
    if (mSelectionRects.contains(item))
    {
        return false;
    }

    clearSelection();

    if (!item)
    {
        return false;
    }

    QPen dashedPen;
    dashedPen.setStyle(Qt::DashLine);

    if (!mSelectedItems.contains(item))
    {
        mSelectedItems.push_back(item);
        mSelectionRects.push_back(mScene.addRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height(), dashedPen));

        emit itemSelected(item);

        CEntity* entity = Globals::getCurrentScene()->getEntityFromGraphicsView(mSelectedItems.first());

        if (entity)
        {
            mOriginalPosition = entity->getPosition();
        }


        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
void CRenderWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        mIsLeftMouseDown = false;
    }
}
//---------------------------------------------------------------------------
void CRenderWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (mIsLeftMouseDown && mSelectedItems.size() > 0)
    {
        // Lookup the entity
        CEntity* entity = Globals::getCurrentScene()->getEntityFromGraphicsView(mSelectedItems.first());

        if (!entity)
        {
            QMessageBox::critical(this, "Erreur!", "Impossible de retrouver l'entit� attach�e au graphique s�lectionn�!");
            return;
        }

        QPoint delta = event->pos() - mMouseDownPosition;

        if (mDoCopySelection)
        {
            // Hep, stop right there! We want to duplicate the selection, and switch our current pick to the copied
            // entity, and move it.
            entity = Globals::getCurrentScene()->cloneEntity(entity);
            selectEntity(entity->getSceneItem());

            mDoCopySelection = false;
        }

        // Move the entity
        QPoint gridDelta = delta;//QPoint(ceil(delta.x() / 16.f) * 16.f, ceil(delta.y() / 16.f) * 16.f);
        Vector2D finalPos = mOriginalPosition + Vector2D(gridDelta.x(), gridDelta.y());

        entity->setPosition(finalPos);

        emit itemChanged();

        // Move selection rects
        for (QList<QGraphicsItem*>::iterator it = mSelectionRects.begin(); it != mSelectionRects.end(); ++it)
        {
            QGraphicsItem* rect = (*it);
            rect->setPos(gridDelta);
        }
    }
}
//---------------------------------------------------------------------------
void CRenderWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Control:
        mIsCtrlKeyDown = true;
        break;

    case Qt::Key_Delete:
        if (mSelectedItems.size() > 0)
        {
            // Delete selected item
            CEntity* entity = Globals::getCurrentScene()->getEntityFromGraphicsView(mSelectedItems.first());
            Globals::getCurrentScene()->remove(entity);

            clearSelection();
        }
        break;
    }
}
//---------------------------------------------------------------------------
void CRenderWidget::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Control)
    {
        mIsCtrlKeyDown = false;
    }
}
//---------------------------------------------------------------------------
void CRenderWidget::clearSelection()
{
    for (QList<QGraphicsItem*>::iterator it = mSelectionRects.begin(); it != mSelectionRects.end(); ++it)
    {
        mScene.removeItem((*it));
    }

    mSelectionRects.clear();
    mSelectedItems.clear();

    emit selectionCleared();
}
//---------------------------------------------------------------------------
void CRenderWidget::contextMenuEvent(QContextMenuEvent *event)
{
    Q_UNUSED(event);
    //QMenu* ctxMenu = new QMenu(this);
}
//---------------------------------------------------------------------------
void CRenderWidget::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
}
//---------------------------------------------------------------------------
