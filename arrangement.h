#ifndef ARRANGEMENT_H
#define ARRANGEMENT_H

#include "mainwindow.h"

#include <QPoint>

#include <CGAL/basic.h>
#include <CGAL/Cartesian.h>
#include <CGAL/CORE_algebraic_number_traits.h>
#include <CGAL/Arr_conic_traits_2.h>
#include <CGAL/Arrangement_2.h>

// to compute offset and inset
#include <CGAL/offset_polygon_2.h>
#include <CGAL/Timer.h>

// for conics
typedef CGAL::CORE_algebraic_number_traits                           Nt_traits;
typedef Nt_traits::Rational                                          Rational;
typedef Nt_traits::Algebraic                                         Algebraic;
typedef CGAL::Cartesian<Rational>                                    Rat_kernel;
typedef Rat_kernel::Point_2                                          Rat_point_2;
typedef Rat_kernel::Segment_2                                        Rat_segment_2;
typedef Rat_kernel::Circle_2                                         Rat_circle_2;
typedef CGAL::Cartesian<Algebraic>                                   Alg_kernel;
typedef CGAL::Arr_conic_traits_2<Rat_kernel, Alg_kernel, Nt_traits>  Traits_2;
typedef Traits_2::Point_2                                            Point_2;
typedef Traits_2::Curve_2                                            Conic_arc_2;
typedef CGAL::Arrangement_2<Traits_2>                                Arrangement_2;

// to compute offset and inset
struct Conic_traits_2 : public CGAL::Arr_conic_traits_2<Rat_kernel,Alg_kernel,Nt_traits> {};
typedef CGAL::Polygon_2<Rat_kernel>                                  Polygon_2;
typedef CGAL::Gps_traits_2<Conic_traits_2>                           Gps_traits_2;
typedef Gps_traits_2::Polygon_2                                      Offset_polygon_2;
typedef Gps_traits_2::Polygon_with_holes_2                 Offset_polygon_with_holes_2;

class MainWindow;

class arrangement
{
public:
    arrangement();
    void addSegment(Arrangement_2 *ar, int a, int b, int u, int v);
    void addCircle(Arrangement_2 *ar, int a, int b, int rn, int rd);
    void addCirclePart(Arrangement_2 *ar, int Ox, int Oy, int k, int l, int u, int v, int rn, int rd);
    void printArrConsole();
    void retrieveData(std::vector<QPoint> env, std::vector<std::vector<QPoint> > obs,
                      QPoint mb,QPoint me,int mr,QPoint tb,QPoint te,int tr);
    Offset_polygon_with_holes_2 offset_of_polygon(Polygon_2 P, int rayon);
    Offset_polygon_with_holes_2 compute_offset();
    void inset_of_polygon(Polygon_2 P, int rayon);
public:
    Arrangement_2 *environment;
    QPoint manipulator_centre;
    QPoint manipulator_centre_end;
    int manipulator_radius;
    QPoint target_centre;
    QPoint target_centre_end;
    int target_radius;
};

#endif // ARRANGEMENT_H
