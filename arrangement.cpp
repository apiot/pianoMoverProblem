#include "arrangement.h"

arrangement::arrangement()
{

}

void
arrangement::addSegment(int a, int b, int u, int v)
{
    // Insert the segment (a, b) -- (u, v).
    Rat_point_2 ps3 (a, b);
    Rat_point_2 pt3 (u, v);
    Conic_arc_2 c3 (Rat_segment_2 (ps3, pt3));
    insert (arr, c3);
}

void
arrangement::addCircle(int a, int b, int rn, int rd)
{
    // Insert a full circle that is centered at (a, b) and radius (rn/rd)^2.
    Rat_circle_2 circ (Rat_point_2(a,b), Rational(rn,rd));
    Conic_arc_2 c (circ);
    insert (arr, c);
}

void
arrangement::addCirclePart(int Ox, int Oy, int k, int l, int u, int v, int rn, int rd)
{
    // Insert the part of the circle centered at (Ox,Oy) whose radius
    // is (rn/rd)^2 and go throw point(k,l) and point(u,v)
    Rat_circle_2 circ (Rat_point_2(Ox, Oy), Rational(rn,rd));
    Point_2 ps (k, l);
    Point_2 pt (u, v);
    Conic_arc_2 c (circ, CGAL::CLOCKWISE, ps, pt);
    insert (arr, c);
}

void
arrangement::printArrConsole()
{
   // Print out the size of the resulting arrangement.
   std::cout << "The arrangement size:" << std::endl
   << " V = " << arr.number_of_vertices()
   << ", E = " << arr.number_of_edges()
   << ", F = " << arr.number_of_faces() << std::endl;
}
