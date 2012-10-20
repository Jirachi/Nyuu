#include "CRenderWidget.h"
#include "Globals.h"
#include "CScene.h"
#include "CEntity.h"
#include <QGraphicsTextItem>
#include <QMouseEvent>
#include <QMessageBox>

//---------------------------------------------------------------------------
CRenderWidget::CRenderWidget(QWidget *parent) :
    QGraphicsView(parent), mIsLeftMouseDown(false)
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
        // We rebuild the scene out of the new elements.
        CScene* scene = Globals::getCurrentScene();

        scene->addAllElementsToScene(&mScene);
    }
    else
    {
        mScene.addText("Veuillez ouvrir ou créer un nouveau niveau.");
    }
}
//---------------------------------------------------------------------------
void CRenderWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        mIsLeftMouseDown = true;
        mMouseDownPosition = event->pos();

        QGraphicsItem* item = itemAt(event->pos());
        if (mSelectionRects.contains(item))
            return;

        clearSelection();

        if (!item)
            return;

        QPen dashedPen;
        dashedPen.setStyle(Qt::DashLine);

        if (!mSelectedItems.contains(item))
        {
            mSelectedItems.push_back(item);
            mSelectionRects.push_back(mScene.addRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height(), dashedPen));
        }
    }
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
            QMessageBox::critical(this, "Erreur!", "Impossible de retrouver l'entité attachée au graphique sélectionné!");
            return;
        }

        QPoint delta = event->pos() - mMouseDownPosition;

        // Move the entity
        entity->setPosition(entity->getPosition() + Vector2D(delta.x(), delta.y()));
        mMouseDownPosition = event->pos();

        // Move selection rects
        for (QList<QGraphicsItem*>::iterator it = mSelectionRects.begin(); it != mSelectionRects.end(); ++it)
        {
            QGraphicsItem* rect = (*it);
            rect->setPos(rect->pos() + delta);
        }
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
}
//---------------------------------------------------------------------------

