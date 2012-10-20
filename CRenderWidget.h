#ifndef CRENDERWIDGET_H
#define CRENDERWIDGET_H

#include <QGraphicsView>

class CRenderWidget : public QGraphicsView
{
    Q_OBJECT
public:
    explicit CRenderWidget(QWidget *parent = 0);
    ~CRenderWidget();
    
signals:
    
public slots:
    void notifySceneChanged();

protected:
    QGraphicsScene mScene;
    
};

#endif // CRENDERWIDGET_H
