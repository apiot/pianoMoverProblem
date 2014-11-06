#ifndef SCENEPROBLEM_H
#define SCENEPROBLEM_H

#include <QGraphicsScene>
#include <QPoint>
#include <QGraphicsSceneMouseEvent>
#include <QLabel>
#include <QString>
#include <QObject>

class SceneProblem : public QGraphicsScene
{
public:
    SceneProblem(QLabel *st);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QObject *_parent;
    QLabel *_statusBar;

};

#endif // SCENEPROBLEM_H
