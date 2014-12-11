#include "sceneproblem.h"

SceneProblem::SceneProblem(MainWindow *mw)
{
    this->mw = mw;

    pen = new QPen(QColor(238,233,233));

    tLine = new QGraphicsLineItem(-10000,-10000,-10000,-10000);
    tLine->setPen(*pen);
    addItem(tLine);

    oLine = new QGraphicsLineItem(-10000,-10000,-10000,-10000);
    oLine->setPen(*pen);
    addItem(oLine);

    int r = mw->manipulatorRadius;
    mb = new QGraphicsEllipseItem(-10000,-10000,r,r);
    mb->setBrush(QBrush(QColor(98,163,244)));
    addItem(mb);

    r = mw->targetRadius;
    ob = new QGraphicsEllipseItem(-10000,-10000,r,r);
    ob->setBrush(QBrush(QColor(250,68,136)));
    addItem(ob);

    r = mw->manipulatorRadius;
    me = new QGraphicsEllipseItem(-10000,-10000,r,r);
    me->setBrush(QBrush(QColor(130,184,251), Qt::Dense2Pattern));
    addItem(me);

    r = mw->targetRadius;
    oe = new QGraphicsEllipseItem(-10000,-10000,r,r);
    oe->setBrush(QBrush(QColor(251,113,165),Qt::Dense2Pattern));
    addItem(oe);

    pObs.push_back(std::vector<QPoint>());
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

    if (!mw->env_close && mw->activeFrontier && pEnv.size() > 0)
    {
        QPoint p1 = pEnv.back();
        tLine->setLine(p1.x(),p1.y(),x,y);
    }
    else if (mw->activeObstacles)
    {
        if (pObs.back().size() > 0)
        {
            QPoint p1 = pObs.back().back();
            oLine->setLine(p1.x(),p1.y(),x,y);
        }
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
    //std::cout << "Clicked Point : " << qp.x() << " " << qp.y() << std::endl;

    if (!mw->env_close && mw->activeFrontier)
    {
        pEnv.push_back(qp);

        QGraphicsEllipseItem *e = new QGraphicsEllipseItem(qp.x()-1,qp.y()-1,2,2);
        e->setBrush(Qt::black);
        pEllipses.push_back(e);
        addItem(e);

        tLine->setVisible(true);

        if (pEnv.size() >= 2)
        {
            QPoint p1 = pEnv[pEnv.size()-2];
            QPoint p2 = pEnv[pEnv.size()-1];
            QGraphicsLineItem *l = new QGraphicsLineItem(p1.x(),p1.y(),p2.x(),p2.y());
            pLines.push_back(l);
            addItem(l);
        }

    }
    else if (mw->activeObstacles)
    {
        pObs[pObs.size()-1].push_back(qp);
        QGraphicsEllipseItem *e = new QGraphicsEllipseItem(qp.x()-1,qp.y()-1,2,2);
        e->setBrush(Qt::black);
        oEllipses.push_back(e);
        addItem(e);

        oLine->setVisible(true);

        if (pObs[pObs.size()-1].size() >= 2)
        {
            QPoint p1 = pObs[pObs.size()-1][pObs[pObs.size()-1].size()-2];
            QPoint p2 = pObs[pObs.size()-1][pObs[pObs.size()-1].size()-1];
            QGraphicsLineItem *l = new QGraphicsLineItem(p1.x(),p1.y(),p2.x(),p2.y());
            oLines.push_back(l);
            addItem(l);
        }
    }
    else if (!mw->manipb_close && mw->activeManipulator)
    {
        manip_begin = qp;
        manip_radius = mw->manipulatorRadius;
        mw->manipb_close = true;
    }
    else if (!mw->manipe_close && mw->activeEndManipulator)
    {
        manip_end = qp;
        mw->manipe_close = true;
    }
    else if (!mw->targetb_close && mw->activeTarget)
    {
        obj_begin = qp;
        obj_radius = mw->targetRadius;
        mw->targetb_close = true;
    }

    else if (!mw->targete_close && mw->activeEndTarget)
    {
        obj_end = qp;
        mw->targete_close = true;
    }    
}

void
SceneProblem::newProblem()
{
    pEnv.clear();
    pObs.clear();
    pObs.push_back(std::vector<QPoint>());
    for (int i = 0; i < (int)pEllipses.size(); ++i)
        removeItem(pEllipses[i]);
    for (int i = 0; i < (int)oEllipses.size(); ++i)
        removeItem(oEllipses[i]);
    for (int i = 0; i < (int)pLines.size(); ++i)
        removeItem(pLines[i]);
    for (int i = 0; i < (int)oLines.size(); ++i)
        removeItem(oLines[i]);
    pEllipses.clear();
    oEllipses.clear();
    pLines.clear();
    oLines.clear();
    mb->setRect(-10000,-10000,1,1);
    me->setRect(-10000,-10000,1,1);
    ob->setRect(-10000,-10000,1,1);
    oe->setRect(-10000,-10000,1,1);
}

