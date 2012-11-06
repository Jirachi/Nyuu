#ifndef CRENDERWIDGET_H
#define CRENDERWIDGET_H

#include <QGraphicsView>
#include <QList>
class QPixmap;
class CRenderWidget : public QGraphicsView
{
    Q_OBJECT
public:
    explicit CRenderWidget(QWidget *parent = 0);
    ~CRenderWidget();
    
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);
    void resizeEvent(QResizeEvent *event);

    // Remove all the selection rectangles
    void clearSelection();

    // Try to select the specified entity
    // Returns true if the entity really got selected
    bool selectEntity(QGraphicsItem *item);

signals:
    // Signal sent when an item is picked in the render view
    void itemSelected(QGraphicsItem* item);

    // Signal sent when selection is cleared
    void selectionCleared();

    // Signal sent when a rendered element is changed by user action
    void itemChanged();

public slots:
    void notifySceneChanged();

protected:
    QGraphicsScene mScene;

    QList<QGraphicsItem*> mSelectedItems;
    QList<QGraphicsItem*> mSelectionRects;

    bool mIsCtrlKeyDown;
    bool mIsLeftMouseDown;
    QPoint mMouseDownPosition;

    bool mDoCopySelection;
    
};

#endif // CRENDERWIDGET_H
