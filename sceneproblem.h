#ifndef SCENEPROBLEM_H
#define SCENEPROBLEM_H

#include "mainwindow.h"

#include <string>

#include <QGraphicsScene>

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QPen>

class MainWindow;

class SceneProblem : public QGraphicsScene
{
public:
    // constructors
    SceneProblem(MainWindow *mw);

    // methods
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void newProblem();

public:
    MainWindow *mw;

    // for graphics render
    std::vector<QGraphicsEllipseItem *> pEllipses;
    std::vector<QGraphicsEllipseItem *> oEllipses;

    std::vector<QGraphicsLineItem *> pLines;
    std::vector<QGraphicsLineItem *> oLines;

    QGraphicsEllipseItem *mb;
    QGraphicsEllipseItem *me;
    QGraphicsEllipseItem *ob;
    QGraphicsEllipseItem *oe;

    QGraphicsLineItem *tLine;
    QGraphicsLineItem *oLine;

    QPen *pen;

    // data
    std::vector<QPoint> pEnv;
    std::vector<std::vector<QPoint> > pObs;

    QPoint manip_begin;
    QPoint manip_end;
    int manip_radius;

    QPoint obj_begin;
    QPoint obj_end;
    int obj_radius;
};

#endif // SCENEPROBLEM_H
