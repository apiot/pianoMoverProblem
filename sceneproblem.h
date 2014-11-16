#ifndef SCENEPROBLEM_H
#define SCENEPROBLEM_H

#include "mainwindow.h"

#include <string>

#include <QGraphicsScene>

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsEllipseItem>

class MainWindow;

class SceneProblem : public QGraphicsScene
{
public:
    // constructors
    SceneProblem(MainWindow *mw);

    // methods
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

public:
    MainWindow *mw;

    std::vector<QPoint> pEnv;
    std::vector<std::vector<QPoint> > pObs;

    QGraphicsEllipseItem *mb;
    QPoint manip_begin;
    QGraphicsEllipseItem *me;
    QPoint manip_end;
    int manip_radius;

    QGraphicsEllipseItem *ob;
    QPoint obj_begin;
    QGraphicsEllipseItem *oe;
    QPoint obj_end;
    int obj_radius;
};

#endif // SCENEPROBLEM_H
