#ifndef ARRANGEMENT_H
#define ARRANGEMENT_H

#include <CGAL/basic.h>
#include <CGAL/Cartesian.h>
#include <CGAL/CORE_algebraic_number_traits.h>
#include <CGAL/Arr_conic_traits_2.h>
#include <CGAL/Arrangement_2.h>


typedef CGAL::CORE_algebraic_number_traits Nt_traits;
typedef Nt_traits::Rational Rational;
typedef Nt_traits::Algebraic Algebraic;
typedef CGAL::Cartesian<Rational> Rat_kernel;
typedef Rat_kernel::Point_2 Rat_point_2;
typedef Rat_kernel::Segment_2 Rat_segment_2;
typedef Rat_kernel::Circle_2 Rat_circle_2;
typedef CGAL::Cartesian<Algebraic> Alg_kernel;
typedef CGAL::Arr_conic_traits_2<Rat_kernel, Alg_kernel, Nt_traits> Traits_2;
typedef Traits_2::Point_2 Point_2;
typedef Traits_2::Curve_2 Conic_arc_2;
typedef CGAL::Arrangement_2<Traits_2> Arrangement_2;


class arrangement
{
public:
    arrangement();
    void addSegment(int a, int b, int u, int v);
    void addCircle(int a, int b, int rn, int rd);
    void addCirclePart(int Ox, int Oy, int k, int l, int u, int v, int rn, int rd);
    void printArrConsole();
private:
    Arrangement_2 arr;

};

#endif // ARRANGEMENT_H
