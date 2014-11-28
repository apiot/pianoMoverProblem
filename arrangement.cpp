#include "arrangement.h"

arrangement::arrangement()
{
    environment = new Arrangement_2();
    manipulator_radius = 0;
    target_radius = 0;
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
   std::cout << " ======= Arrangement =======" << std::endl;
   std::cout << "The environment :" << std::endl
   << " V = " << environment->number_of_vertices()
   << ", E = " << environment->number_of_edges()
   << ", F = " << environment->number_of_faces() << std::endl;
}

void
arrangement::retrieveData(std::vector<QPoint> env, std::vector<std::vector<QPoint> > obs,
                          QPoint mb,QPoint me,int mr,QPoint tb,QPoint te,int tr)
{
    // add frontier
    for (int i=0; i < (int) env.size()-1; ++i)
        addSegment(environment,env[i].x(),env[i].y(),env[i+1].x(),env[i+1].y());
    addSegment(environment,env.back().x(),env.back().y(),env[0].x(),env[0].y());

    // add obstacles
    for (int j=0; j < (int) obs.size()-1; ++j)
    {
        for (int i=0; i < (int)obs[j].size()-1; ++i)
            addSegment(environment,obs[j][i].x(),obs[j][i].y(),obs[j][i+1].x(),obs[j][i+1].y());
        addSegment(environment,obs[j].back().x(),obs[j].back().y(),obs[j][0].x(),obs[j][0].y());
    }

    // copy manipulator and target
    manipulator_centre = mb;
    manipulator_centre_end = me;
    manipulator_radius = mr;
    target_centre = tb;
    target_centre_end = te;
    target_radius = tr;
}

Offset_polygon_with_holes_2
arrangement::offset_of_polygon(Polygon_2 P, int rayon)
{
    // Compute the offset polygon.
   Conic_traits_2 traits;
   const Rational radius = rayon;
   Offset_polygon_with_holes_2 offset;
   CGAL::Timer timer;

   timer.start();
   offset = offset_polygon_2 (P, radius, traits);
   timer.stop();

   std::cout << "The offset polygon has " << offset.outer_boundary().size() << " vertices, " << offset.number_of_holes() << " holes." << std::endl;
   std::cout << "Offset computation took " << timer.time() << " seconds." << std::endl;
}

Offset_polygon_with_holes_2
arrangement::compute_offset()
{

}

void
arrangement::inset_of_polygon(Polygon_2 P, int rayon)
{
    // Compute the inner offset of the polygon.
   Conic_traits_2 traits;
   const Rational radius = rayon;
   std::list<Offset_polygon_2> inset_polygons;
   std::list<Offset_polygon_2>::iterator iit;
   CGAL::Timer timer;

   timer.start();
   inset_polygon_2 (P, radius, traits, std::back_inserter (inset_polygons));
   timer.stop();

   std::cout << "The inset comprises " << inset_polygons.size() << " polygon(s)." << std::endl;
   for (iit = inset_polygons.begin(); iit != inset_polygons.end(); ++iit)
   {
       std::cout << " Polygon with " << iit->size() << " vertices." << std::endl;
   }
   std::cout << "Inset computation took " << timer.time() << " seconds." << std::endl;
}
