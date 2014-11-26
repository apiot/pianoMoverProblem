#include "arrangement.h"

arrangement::arrangement()
{
    environment = new Arrangement_2();
    manipulator = new Arrangement_2();
    target = new Arrangement_2();
}

void
arrangement::addSegment(Arrangement_2 *ar, int a, int b, int u, int v)
{
    // Insert the segment (a, b) -- (u, v).
    Rat_point_2 ps3 (a, b);
    Rat_point_2 pt3 (u, v);
    Conic_arc_2 c3 (Rat_segment_2 (ps3, pt3));
    insert (*ar, c3);
}

void
arrangement::addCircle(Arrangement_2 *ar, int a, int b, int rn, int rd)
{
    // Insert a full circle that is centered at (a, b) and radius (rn/rd)^2.
    Rat_circle_2 circ (Rat_point_2(a,b), Rational(rn,rd));
    Conic_arc_2 c (circ);
    insert (*ar, c);
}

void
arrangement::addCirclePart(Arrangement_2 *ar, int Ox, int Oy, int k, int l, int u, int v, int rn, int rd)
{
    // Insert the part of the circle centered at (Ox,Oy) whose radius
    // is (rn/rd)^2 and go throw point(k,l) and point(u,v)
    Rat_circle_2 circ (Rat_point_2(Ox, Oy), Rational(rn,rd));
    Point_2 ps (k, l);
    Point_2 pt (u, v);
    Conic_arc_2 c (circ, CGAL::CLOCKWISE, ps, pt);
    insert (*ar, c);
}

void
arrangement::printArrConsole()
{
   std::cout << "The environment :" << std::endl
   << " V = " << environment->number_of_vertices()
   << ", E = " << environment->number_of_edges()
   << ", F = " << environment->number_of_faces() << std::endl;

   std::cout << "The manipulator :" << std::endl
   << " V = " << manipulator->number_of_vertices()
   << ", E = " << manipulator->number_of_edges()
   << ", F = " << manipulator->number_of_faces() << std::endl;

   std::cout << "The target :" << std::endl
   << " V = " << target->number_of_vertices()
   << ", E = " << target->number_of_edges()
   << ", F = " << target->number_of_faces() << std::endl;
}

void
arrangement::retrieveData(std::vector<QPoint> env, std::vector<std::vector<QPoint> > obs,
                          QPoint mb,QPoint me,int mr,QPoint tb,QPoint te,int tr)
{
    int num;
    int den;
    toolbox tool;

    for (int i=0; i < (int) env.size()-1; ++i)
        addSegment(environment,env[i].x(),env[i].y(),env[i+1].x(),env[i+1].y());
    addSegment(environment,env.back().x(),env.back().y(),env[0].x(),env[0].y());

    for (int j=0; j < (int) obs.size()-1; ++j)
    {
        for (int i=0; i < obs[j].size()-1; ++i)
            addSegment(environment,obs[j][i].x(),obs[j][i].y(),obs[j][i+1].x(),obs[j][i+1].y());
        addSegment(environment,obs[j].back().x(),obs[j].back().y(),obs[j][0].x(),obs[j][0].y());
    }

    printArrConsole();
    //tool.getRationalFromDouble(num,den,var);

}
