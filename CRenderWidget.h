#ifndef CRENDERWIDGET_H
#define CRENDERWIDGET_H

#include <QGraphicsView>
#include <QList>

class CRenderWidget : public QGraphicsView
{
    Q_OBJECT
public:
    explicit CRenderWidget(QWidget *parent = 0);
    ~CRenderWidget();
    
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);

    // Remove all the selection rectangles
    void clearSelection();

signals:
    // Signal sent when an item is picked in the render view
    void itemSelected(QGraphicsItem* item);

    // Signal sent when selection is cleared
    void selectionCleared();

public slots:
    void notifySceneChanged();

protected:
    QGraphicsScene mScene;

    QList<QGraphicsItem*> mSelectedItems;
    QList<QGraphicsItem*> mSelectionRects;

    bool mIsLeftMouseDown;
    QPoint mMouseDownPosition;
    
};

#endif // CRENDERWIDGET_H
