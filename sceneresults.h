#ifndef SCENERESULTS_H
#define SCENERESULTS_H


#include <QBrush>
#include <QGraphicsScene>
#include <QPen>
#include <QPoint>
#include <QPointF>
#include <QPolygon>
#include <QVector>

#include <CGAL/basic.h>
#include <CGAL/Cartesian.h>
#include <CGAL/CORE_algebraic_number_traits.h>
#include <CGAL/Arr_conic_traits_2.h>
#include <CGAL/Arrangement_2.h>

// to compute offset and inset
#include <CGAL/offset_polygon_2.h>
#include <CGAL/Gps_traits_2.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/Arr_extended_dcel.h>

#include <CGAL/Boolean_set_operations_2.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/General_polygon_2.h>

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
struct Rat_kernel_p: public CGAL::Cartesian<Rational> {};
struct Alg_kernel_p: public CGAL::Cartesian<Algebraic> {};
struct Conic_traits_2 : public CGAL::Arr_conic_traits_2<Rat_kernel_p,Alg_kernel_p,Nt_traits> {};
typedef CGAL::Polygon_2<Rat_kernel_p>                                Polygon_2;
typedef CGAL::Gps_traits_2<Conic_traits_2>                           Gps_traits_2;
typedef Gps_traits_2::Polygon_2                                      Offset_polygon_2;
typedef Gps_traits_2::Polygon_with_holes_2                           Offset_polygon_with_holes_2;



// for printing env
typedef Polygon_2::Edge_const_iterator                               EdgeIterator;
typedef Polygon_2::Vertex_iterator                                   VertexIterator;

// for printing inset
typedef std::list<Offset_polygon_2>::iterator                        Op2_it;
typedef Conic_traits_2::X_monotone_curve_2                           X_monotone_curve_2;
typedef std::list<X_monotone_curve_2>                                X_monotone_curves_2;
typedef X_monotone_curves_2::iterator                                X_curve_2_it;
typedef std::pair<double, double>                                    approximated_point_2;

// for polygons difference
typedef std::vector<Offset_polygon_with_holes_2>                       Pwh_list_2;




class sceneResults : public QGraphicsScene
{
public:
    sceneResults();
    void paint_env(std::vector<QPoint> env);
    void paint_obstacles(std::vector<std::vector<QPoint> > obs);
    void paint_offset(std::vector<Offset_polygon_with_holes_2> offsets);
    void paint_inset(std::list<Offset_polygon_2> inset);
    void paint_convolution(Pwh_list_2 admis);
    void paint_curves(X_curve_2_it curve);
    void newProblem();

public:

};

#endif // SCENERESULTS_H
