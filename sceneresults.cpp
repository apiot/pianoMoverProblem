#include "sceneresults.h"



sceneResults::sceneResults()
{
    setBackgroundBrush(QColor(190,190,190)); // light gray
}

void
sceneResults::paint_env(std::vector<QPoint> env)
{
    QPolygonF *p = new QPolygonF();
    p->resize((int)env.size());
    for (int i=0; i < (int)env.size(); ++i)
        (*p)[i] = QPointF(env[i].x(),env[i].y());

    addPolygon(*p, QPen(Qt::black), QBrush(Qt::white));
}

void
sceneResults::paint_obstacles(std::vector<std::vector<QPoint> > obs)
{
    for (int k=0; k<(int)obs.size()-1; ++k)
    {
        QPolygonF *p = new QPolygonF();
        p->resize((int)obs[k].size());
        for (int i=0; i < (int)obs[k].size(); ++i)
            (*p)[i] = QPointF(obs[k][i].x(),obs[k][i].y());

        addPolygon(*p, QPen(Qt::black), QBrush(QColor(190,190,190)));
    }
}

void
sceneResults::paint_offset(std::vector<Offset_polygon_with_holes_2> offsets)
{
    for (int i = 0; i < (int)offsets.size(); ++i)
    {
        for (X_curve_2_it curve = offsets[i].outer_boundary().curves_begin(); curve != offsets[i].outer_boundary().curves_end(); ++curve)
            paint_curves(curve);

        if (offsets[i].has_holes())
            for (Op2_it pit = offsets[i].holes_begin(); pit != offsets[i].holes_end(); ++pit)
                for (X_curve_2_it curve = pit->curves_begin(); curve != pit->curves_end(); ++curve)
                    paint_curves(curve);
    }
}

void
sceneResults::paint_inset(std::list<Offset_polygon_2> inset)
{
    for (Op2_it iit = inset.begin(); iit != inset.end(); ++iit)
        for (X_curve_2_it curve = iit->curves_begin(); curve != iit->curves_end(); ++curve)
            paint_curves(curve);
}

void
sceneResults::paint_convolution(Pwh_list_2 admis)
{
    for (int i =0; i<(int)admis.size(); ++i)
    {
        /*
        QPolygonF *p = new QPolygonF();
        p->resize((int)obs[k].size());
        for (int i=0; i < (int)obs[k].size(); ++i)
            (*p)[i] = QPointF(obs[k][i].x(),obs[k][i].y());

        addPolygon(*p, QPen(Qt::black), QBrush(QColor(209,242,234)));
        */
        for (X_curve_2_it curve = admis[i].outer_boundary().curves_begin(); curve != admis[i].outer_boundary().curves_end(); ++curve)
            paint_curves(curve);
        if (admis[i].has_holes())
            for (Op2_it pit = admis[i].holes_begin(); pit != admis[i].holes_end(); ++pit)
                for (X_curve_2_it curve = pit->curves_begin(); curve != pit->curves_end(); ++curve)
                    paint_curves(curve);

    }
}

void
sceneResults::paint_curves(X_curve_2_it curve)
{
    // TODO: improve the number of points used for the approximation..
    int n = 25;
    approximated_point_2* points = new approximated_point_2[n + 1];
    curve->polyline_approximation(n, points);
    if (CGAL::COLLINEAR == curve->orientation())
    {
        // Draw a segment.
        QPointF p1 = QPointF(points[0].first, points[0].second);
        QPointF p2 = QPointF(points[1].first, points[1].second);
        addLine(p1.x(),p1.y(),p2.x(),p2.y());
    }
    else
    {
        // Draw an approximation of the conic arc.
        for (int i = 1; i < n + 1; ++i)
        {
            QPointF p1 = QPointF(points[i-1].first, points[i-1].second);
            QPointF p2 = QPointF(points[i].first, points[i].second);
            addLine(p1.x(),p1.y(),p2.x(),p2.y());
        }
    }
}

void sceneResults::newProblem()
{
    clear();
}
