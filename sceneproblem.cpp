#include "sceneproblem.h"

SceneProblem::SceneProblem(MainWindow *mw)
{
    this->mw = mw;

    int r = mw->manipulatorRadius;
    mb = new QGraphicsEllipseItem(-10000,-10000,r,r);
    addItem(mb);
    me = new QGraphicsEllipseItem(-10000,-10000,r,r);
    addItem(me);

    r = mw->targetRadius;
    ob = new QGraphicsEllipseItem(-10000,-10000,r,r);
    addItem(ob);
    oe = new QGraphicsEllipseItem(-10000,-10000,r,r);
    addItem(oe);

    std::vector<QPoint> foo;
    pObs.push_back(foo);
}

void
SceneProblem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPoint qp = event->scenePos().toPoint();
    int x = qp.x();
    int y = qp.y();
    QString qs = QString::fromStdString("  x : "+std::to_string(x)+"  y : "+std::to_string(y)+ "  ");
    mw->statusBarLeft->setText(qs);

    int r = mw->manipulatorRadius;
    int s = mw->targetRadius;

    if (!mw->env_close)
    {

    }
    else if (!mw->manipb_close && mw->activeManipulator)
    {
        mb->setRect(x-(r/2),y-(r/2),r,r);
    }
    else if (!mw->manipe_close && mw->activeEndManipulator)
    {
        me->setRect(x-(r/2),y-(r/2),r,r);
    }
    else if (!mw->targetb_close && mw->activeTarget)
    {
        ob->setRect(x-(s/2),y-(s/2),s,s);
    }
    else if (!mw->targete_close && mw->activeEndTarget)
    {
        oe->setRect(x-(s/2),y-(s/2),s,s);
    }

}

void
SceneProblem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QPoint qp = event->scenePos().toPoint();
    std::cout << "Clicked Point : " << qp.x() << " " << qp.y() << std::endl;

    int r = mw->manipulatorRadius;
    int s = mw->targetRadius;

    if (!mw->env_close && mw->activeFrontier)
    {
        pEnv.push_back(qp);

        QGraphicsEllipseItem *e = new QGraphicsEllipseItem(qp.x()-1,qp.y()-1,2,2);
        e->setBrush(Qt::black);
        addItem(e);

        if (pEnv.size() >= 2)
        {
            QPoint p1 = pEnv[pEnv.size()-2];
            QPoint p2 = pEnv[pEnv.size()-1];
            addLine(p1.x(),p1.y(),p2.x(),p2.y());
        }

    }
    else if (mw->activeObstacles)
    {
        pObs[pObs.size()-1].push_back(qp);
        QGraphicsEllipseItem *e = new QGraphicsEllipseItem(qp.x()-1,qp.y()-1,2,2);
        e->setBrush(Qt::black);
        addItem(e);

        if (pObs[pObs.size()-1].size() >= 2)
        {
            QPoint p1 = pObs[pObs.size()-1][pObs[pObs.size()-1].size()-2];
            QPoint p2 = pObs[pObs.size()-1][pObs[pObs.size()-1].size()-1];
            addLine(p1.x(),p1.y(),p2.x(),p2.y());
        }
    }
    else if (!mw->manipb_close && mw->activeManipulator)
    {
        QGraphicsEllipseItem *e = new QGraphicsEllipseItem(qp.x()-(r/2),qp.y()-(r/2),r,r);
        e->setBrush(QBrush(QColor(98,163,244)));
        addItem(e);
        manip_begin = qp;
        manip_radius = mw->manipulatorRadius;
        mb->setVisible(false);
        mw->manipb_close = true;
    }
    else if (!mw->manipe_close && mw->activeEndManipulator)
    {
        QGraphicsEllipseItem *e = new QGraphicsEllipseItem(qp.x()-(r/2),qp.y()-(r/2),r,r);
        e->setBrush(QBrush(QColor(130,184,251), Qt::Dense2Pattern));
        addItem(e);
        manip_end = qp;
        me->setVisible(false);
        mw->manipe_close = true;
    }
    else if (!mw->targetb_close && mw->activeTarget)
    {
        QGraphicsEllipseItem *e = new QGraphicsEllipseItem(qp.x()-(s/2),qp.y()-(s/2),s,s);
        e->setBrush(QBrush(QColor(250,68,136)));
        addItem(e);
        obj_begin = qp;
        obj_radius = mw->targetRadius;
        ob->setVisible(false);
        mw->targetb_close = true;
    }

    else if (!mw->targete_close && mw->activeEndTarget)
    {
        QGraphicsEllipseItem *e = new QGraphicsEllipseItem(qp.x()-(s/2),qp.y()-(s/2),s,s);
        e->setBrush(QBrush(QColor(251,113,165),Qt::Dense2Pattern));
        addItem(e);
        obj_end = qp;
        oe->setVisible(false);
        mw->targete_close = true;
    }


}
