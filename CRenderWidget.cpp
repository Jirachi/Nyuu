#include "CRenderWidget.h"
#include "Globals.h"
#include <QGraphicsTextItem>

//---------------------------------------------------------------------------
CRenderWidget::CRenderWidget(QWidget *parent) :
    QGraphicsView(parent)
{
    Globals::setCurrentGraphicsScene(&mScene);
    setScene(&mScene);
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


    }
    else
    {
        mScene.addText("Veuillez ouvrir ou créer un nouveau niveau.");
    }
}
//---------------------------------------------------------------------------
