#include "CRenderWidget.h"
#include "Globals.h"
#include "CScene.h"
#include "CEntity.h"
#include <QGraphicsTextItem>
#include <QMouseEvent>
#include <QMessageBox>
#include <QMenu>

//---------------------------------------------------------------------------
CRenderWidget::CRenderWidget(QWidget *parent) :
    QGraphicsView(parent), mIsLeftMouseDown(false),
    mBackground(0)
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

    if (mBackground)
        mBackground = 0;

    if (Globals::getCurrentScene())
    {
        // Make background
        mBackgroundImage = QPixmap("D:\\Projets\\Jirachi\\test-rsrc\\backgrounds\\01.jpg");
        mBackground = mScene.addPixmap(mBackgroundImage);
        mBackground->setPos(0,0);
        mBackground->setScale(std::max<float>((float)height() / (float)mBackgroundImage.height(), (float)width() / (float)mBackgroundImage.width()));

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

        if (!item || mBackground == item)
            return;

        QPen dashedPen;
        dashedPen.setStyle(Qt::DashLine);

        if (!mSelectedItems.contains(item))
        {
            mSelectedItems.push_back(item);
            mSelectionRects.push_back(mScene.addRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height(), dashedPen));

            emit itemSelected(item);
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

        emit itemChanged();

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

    if (mBackground)
        mBackground->setScale(std::max<float>((float)height() / (float)mBackgroundImage.height(), (float)width() / (float)mBackgroundImage.width()));
}
//---------------------------------------------------------------------------
