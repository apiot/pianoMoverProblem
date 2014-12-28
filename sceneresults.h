#ifndef SCENERESULTS_H
#define SCENERESULTS_H

#include <QBrush>
#include <QColor>
#include <QGraphicsSimpleTextItem>
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
#include <CGAL/Arrangement_on_surface_with_history_2.h>
#include <CGAL/Arrangement_with_history_2.h>
#include <CGAL/Arr_extended_dcel.h>
#include <CGAL/Arr_walk_along_line_point_location.h>
#include <CGAL/Arr_observer.h>

#include <CGAL/offset_polygon_2.h>
#include <CGAL/Gps_traits_2.h>
#include <CGAL/Polygon_2.h>

#include <CGAL/Boolean_set_operations_2.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/General_polygon_2.h>


                                     /* basics */

typedef CGAL::CORE_algebraic_number_traits                           Nt_traits;
typedef Nt_traits::Rational                                          Rational;
typedef Nt_traits::Algebraic                                         Algebraic;

typedef CGAL::Cartesian<Rational>                                    Rat_kernel;
typedef CGAL::Cartesian<Algebraic>                                   Alg_kernel;

typedef Rat_kernel::Point_2                                          Rat_point_2;
typedef Rat_kernel::Segment_2                                        Rat_segment_2;
typedef Rat_kernel::Circle_2                                         Rat_circle_2;
typedef CGAL::Arr_conic_traits_2<Rat_kernel, Alg_kernel, Nt_traits>  Conic_traits_2;

//typedef Conic_traits_2::Point_2                                      Point_2;
//typedef Conic_traits_2::Curve_2                                      Conic_arc_2;

typedef Alg_kernel::FT                                               Algebraic_ft;


                                   /* for arrangement */

                                                 // vertex, edge, face
typedef CGAL::Arr_extended_dcel<Conic_traits_2, std::string, std::string, int> Dcel;
typedef CGAL::Arrangement_2<Conic_traits_2, Dcel>                    Arrangement_2;
typedef Arrangement_2::Face_handle                                   Face_handle;
typedef CGAL::Arr_naive_point_location<Arrangement_2>                Naive_pl;
typedef CGAL::Arr_walk_along_line_point_location<Arrangement_2>      Walk_pl;
// with history
/*
typedef CGAL::Arrangement_with_history_2<Conic_traits_2, Dcel>       Arr_with_hist_2;
typedef CGAL::Arr_walk_along_line_point_location<Arr_with_hist_2>    Hist_Walk_pl;
*/

                                      /* for polygon */
typedef CGAL::Polygon_2<Rat_kernel>                                  Polygon_2;
typedef CGAL::Gps_traits_2<Conic_traits_2>                           Gps_traits_2;
typedef Gps_traits_2::Polygon_2                                      Offset_polygon_2;
typedef Gps_traits_2::Polygon_with_holes_2                           Offset_polygon_with_holes_2;
typedef Polygon_2::Edge_const_iterator                               EdgeIterator;
typedef Polygon_2::Vertex_iterator                                   VertexIterator;
typedef std::list<Offset_polygon_2>::iterator                        Op2_it;
typedef std::vector<Offset_polygon_with_holes_2>                     Pwh_list_2;

                                   /* for conic arc */
typedef Conic_traits_2::X_monotone_curve_2                           X_monotone_curve_2;
typedef Conic_traits_2::Curve_2                                      Conic_curve_2;
typedef Conic_traits_2::Point_2                                      Conic_point_2;
typedef std::list<X_monotone_curve_2>                                X_monotone_curves_2;
typedef X_monotone_curves_2::iterator                                X_curve_2_it;

                                        /* others */
typedef std::pair<double, double>                                    approximated_point_2;



class sceneResults : public QGraphicsScene
{
public:

public:
    sceneResults();
    void paint_env(std::vector<QPoint> env);
    void paint_obstacles(std::vector<std::vector<QPoint> > obs);
    void paint_offset(std::vector<Offset_polygon_with_holes_2> offsets);
    void paint_inset(std::list<Offset_polygon_2> inset);
    void paint_convolution(Pwh_list_2 admis);
    void paint_cc_convolution(std::vector<Arrangement_2> arr);
    void paint_ccI(std::vector<Arrangement_2> ccI);
    void paint_ccII(std::vector<Arrangement_2> ccII);
    void paint_arrangement(Arrangement_2 arr, QColor color, bool displayText, QColor colorText);
    void paint_curves(X_curve_2_it curve, QColor color);
    void paint_face_id(std::vector<std::vector<double> > &point_in_faces);
    void newProblem();
};

#endif // SCENERESULTS_H
