#include "arrangement.h"

arrangement::arrangement()
{
    manipulator_diametre = 0;
    target_diametre = 0;
}

void
arrangement::printArrConsole(Arrangement_2 *a)
{
   std::cout << " ======= Arrangement =======" << std::endl
   << " V = " << a->number_of_vertices()
   << ", E = " << a->number_of_edges()
   << ", F = " << a->number_of_faces() << std::endl;
}

void
arrangement::retrieveData(std::vector<QPoint> env, std::vector<std::vector<QPoint> > obs,
                          QPoint mb,QPoint me,int mr,QPoint tb,QPoint te,int tr)
{
    // copy raw data
    frontier = env;
    obstacles = obs;

    // copy manipulator and target
    manipulator_centre = mb;
    manipulator_centre_end = me;
    manipulator_diametre = mr;
    target_centre = tb;
    target_centre_end = te;
    target_diametre = tr;
    r1r2 = (tr+mr)/2.0;
}

void
arrangement::offset_of_polygon(Polygon_2 P, int diametre, std::vector<Offset_polygon_with_holes_2> &off)
{
   Conic_traits_2 traits;
   const Rational radius = Rational(diametre,2);
   Offset_polygon_with_holes_2 offset;
   offset = offset_polygon_2 (P, radius, traits);
   off.push_back(offset);
}

void
arrangement::inset_of_polygon(Polygon_2 P, int diametre, std::list<Offset_polygon_2> &in)
{
   Conic_traits_2 traits;
   const Rational radius = Rational(diametre,2);
   inset_polygon_2 (P, radius, traits, std::back_inserter (in));
}

void
arrangement::admissible_configuration(Op2_it pgn, std::vector<Offset_polygon_with_holes_2> &off,Pwh_list_2 &adm)
{
    Offset_polygon_with_holes_2 poly(*pgn);
    std::vector<Offset_polygon_with_holes_2> polys;
    polys.push_back(poly);

    for (int i =0; i< (int) polys.size(); ++i)
    if (polys[i].outer_boundary().orientation() == -1)
            polys[i].outer_boundary().reverse_orientation();

    for (int i =0; i< (int)polys.size(); ++i)
    {
        int before;
        bool flag = false;
        for (int k = 0; k < (int)off.size(); ++k)
        {
            if (off[k].outer_boundary().orientation() == -1)
                off[k].outer_boundary().reverse_orientation();

            if (CGAL::do_intersect(polys[i], off[k]))
            {
                flag = true;
                before = (int) adm.size();
                CGAL::difference(polys[i], off[k],std::back_inserter(adm));
                polys.pop_back();
                int cpt_tmp = (int)adm.size();
                for (int j = before; j < cpt_tmp; ++j)
                {
                    polys.push_back(adm.back());
                    adm.pop_back();
                }
            }
        }
        if (flag)
            --i;
    }
    for (int k = 0; k < (int)polys.size(); ++k)
        adm.push_back(polys[k]);
}

void
arrangement::compute_admissible_configuration()
{
    // transform environment into polygons
    std::list<Rat_point_2> pts;
    for (int i=0;i<(int)frontier.size();++i)
        pts.push_back(Rat_point_2(frontier[i].x(), frontier[i].y()));
    env.insert(env.vertices_circulator(), pts.begin(), pts.end());

    // compute inset
    inset_of_polygon(env, manipulator_diametre, inset);
    inset_of_polygon(env, target_diametre, inset_o);

    // transform and compute offset of obstacles
    std::vector<std::list<Rat_point_2> > pts2;
    pts2.resize((int)obstacles.size());
    obs.resize((int)obstacles.size());
    for(int k = 0; k < (int)obstacles.size()-1; ++k)
    {
        for (int i=0;i<(int)obstacles[k].size();++i)
            pts2[k].push_back(Rat_point_2(obstacles[k][i].x(),obstacles[k][i].y()));
        obs[k].insert(obs[k].vertices_circulator(), pts2[k].begin(), pts2[k].end());
        offset_of_polygon(obs[k],manipulator_diametre, offsets);
        offset_of_polygon(obs[k],target_diametre, offsets_o);
    }

    // compute admissible configuration
    for (Op2_it pgn=inset.begin(); pgn != inset.end(); ++pgn)
        admissible_configuration(pgn, offsets, admissible);
    for (Op2_it pgn=inset_o.begin(); pgn != inset_o.end(); ++pgn)
        admissible_configuration(pgn, offsets_o, admissible_o);

    // add all curves of admissible_O space in arrangement
    for (int i = 0; i < (int) admissible_o.size(); ++i)
    {
        Arrangement_2 arr;
        for (X_curve_2_it curve = admissible_o[i].outer_boundary().curves_begin(); curve != admissible_o[i].outer_boundary().curves_end(); ++curve)
            insert(arr, *curve);
        if (admissible_o[i].has_holes())
            for(Op2_it hol = admissible_o[i].holes_begin(); hol != admissible_o[i].holes_end(); ++hol)
                for (X_curve_2_it curve = hol->curves_begin(); curve != hol->curves_end(); ++curve)
                    insert(arr, *curve);
        convolutions.push_back(arr);
    }

    // save environment vertex
    for (int i = 0; i < (int)frontier.size(); ++i)
        env_points.push_back(frontier[i]);
    for (int i = 0; i < (int) obstacles.size(); ++i)
        for (int j = 0; j < (int) obstacles[i].size(); ++j)
            env_points.push_back(obstacles[i][j]);
}

std::string
arrangement::getLabel(std::vector<std::string> &labels, X_monotone_curve_2 &curve, int &cpt, double &r)
{
    int n = 2; // number of segments for the approximation
    double d1, d2, d3;
    double p0x, p0y, p1x, p1y, p2x, p2y, p3x, p3y;
    approximated_point_2* points = new approximated_point_2[n + 1];
    curve.polyline_approximation(n, points); // there is 3 points
    p1x = points[0].first;
    p1y = points[0].second;
    p2x = points[1].first;
    p2y = points[1].second;
    p3x = points[2].first;
    p3y = points[2].second;

    for (int i = 0; i < (int) env_points.size(); ++i)
    {
        p0x = env_points[i].x();
        p0y = env_points[i].y();

        d1 = sqrt((p0x-p1x)*(p0x-p1x)+(p0y-p1y)*(p0y-p1y));
        d2 = sqrt((p0x-p2x)*(p0x-p2x)+(p0y-p2y)*(p0y-p2y));
        d3 = sqrt((p0x-p3x)*(p0x-p3x)+(p0y-p3y)*(p0y-p3y));
        if (d1 > (r-1.0) && d1 < (r+1.0) && d2 > (r-1.0) && d2 < (r+1.0) && d3 > (r-1.0) && d3 < (r+1.0))
        {
            if (labels[i].compare("none") == 0)
            {
                labels[i] = "a"+std::to_string(cpt++);
                return labels[i];
            }
            else
                return labels[i];
        }
    }
    return "Error";
}

void
arrangement::compute_convolutionLabels()
{
    // initialize variables
    int compteur_wall = 0;
    int compteur_arc = 0;
    std::vector<std::string > labels;
    for (int i = 0; i < (int) env_points.size(); ++i)
        labels.push_back("none");

    double r = target_diametre/2;

    // compute
    for (int i = 0; i < (int) convolutions.size(); ++i)
    {
        for (Arrangement_2::Edge_iterator edge = convolutions[i].edges_begin(); edge != convolutions[i].edges_end(); ++edge)
        {
            if (edge->curve().orientation() == CGAL::COLLINEAR)
            {
                edge->set_data("w"+std::to_string(compteur_wall));
                edge->twin()->set_data("w"+std::to_string(compteur_wall++));
            }
            else // if it is an arc
            {
                std::string l = getLabel(labels, edge->curve(), compteur_arc, r);
                edge->set_data(l);
                edge->twin()->set_data(l);
            }
        }

        // print results
        /*
        std::cout << "edge label : "  << std::endl;
        for (Arrangement_2::Edge_iterator edge = convolutions[i].edges_begin(); edge != convolutions[i].edges_end(); ++edge)
        {
            std::cout << edge->data() << " ";
        }
        std::cout << std::endl;
        */
    }
}

void
arrangement::compute_criticalCurves_type_I()
{

    for (int i = 0; i < (int) convolutions.size(); ++i)
    {
        double radius_1 = manipulator_diametre/2.0;
        double radius_2 = target_diametre/2.0;
        Arrangement_2 arrangement;
        // Add the critical curves of type I.
        for (Arrangement_2::Edge_iterator edge = convolutions[i].edges_begin(); edge != convolutions[i].edges_end(); ++edge)
        {
            if (CGAL::COLLINEAR == edge->curve().orientation())
            {
                // Displaced a segment.
                Nt_traits nt_traits;
                Algebraic_ft factor = nt_traits.convert(Rational(radius_1) + Rational(radius_2));
                Conic_point_2 source = edge->curve().source();
                Conic_point_2 target = edge->curve().target();
                Algebraic_ft delta_x = target.x() - source.x();
                Algebraic_ft delta_y = target.y() - source.y();
                Algebraic_ft length = nt_traits.sqrt(delta_x * delta_x + delta_y * delta_y);
                Algebraic_ft translation_x = factor * delta_y / length;
                Algebraic_ft translation_y = - factor * delta_x / length;
                Conic_point_2 point_1(source.x() + translation_x, source.y() + translation_y);
                Conic_point_2 point_2(target.x() + translation_x, target.y() + translation_y);
                Algebraic_ft a = - delta_y;
                Algebraic_ft b = delta_x;
                Algebraic_ft c = factor * length - (source.y() * target.x() - source.x() * target.y());
                X_monotone_curve_2 x_monotone_curve(a, b, c, point_1, point_2);
                insert(arrangement, x_monotone_curve);
            }
            else
            {
                // Displaces an arc.
                Rational two(2);
                Rational four(4);

                Rational r = edge->curve().r();
                Rational s = edge->curve().s();
                Rational t = edge->curve().t();
                Rational u = edge->curve().u();
                Rational v = edge->curve().v();
                Rational w = edge->curve().w();

                Nt_traits nt_traits;
                Rational x_center = - u / (two * r);
                Rational y_center = - v / (two * r);
                Rat_point_2 rat_center(x_center, y_center);
                Conic_point_2 center(nt_traits.convert(x_center), nt_traits.convert(y_center));

                Rational radius = Rational(radius_1) + two * Rational(radius_2);

                Algebraic_ft coefficient = nt_traits.convert(radius / Rational(radius_2));

                Conic_point_2 source_1 = edge->curve().source();
                Algebraic_ft x_source_2 = center.x() + coefficient * (source_1.x() - center.x());
                Algebraic_ft y_source_2 = center.y() + coefficient * (source_1.y() - center.y());
                Conic_point_2 source_2(x_source_2, y_source_2);

                Conic_point_2 target_1 = edge->curve().target();
                Algebraic_ft x_target_2 = center.x() + coefficient * (target_1.x() - center.x());
                Algebraic_ft y_target_2 = center.y() + coefficient * (target_1.y() - center.y());
                Conic_point_2 target_2(x_target_2, y_target_2);

                Rat_circle_2 circle(rat_center, radius * radius);

                Conic_curve_2 conic_arc(circle, CGAL::CLOCKWISE, source_2, target_2);

                insert(arrangement, conic_arc);
            }
        }
        ccI.push_back(arrangement);
    }

}

void
arrangement::compute_criticalCurves_type_II()
{

    for (int i = 0; i < (int) convolutions.size(); ++i)
    {


        Arrangement_2 arr;
        for (Arrangement_2::Edge_iterator edge = convolutions[i].edges_begin(); edge != convolutions[i].edges_end(); ++edge)
        {
            double x = CGAL::to_double(edge->curve().source().x());
            double y = CGAL::to_double(edge->curve().source().y());
            double radius = r1r2;
            Rat_point_2 center(x, y);
            Rat_circle_2 circle(center, radius * radius);
            Conic_curve_2 conic_arc(circle);
            insert(arr, conic_arc);
        }

        // Remove the curves which are not include in the faces.
        /*
        Objects objects;
        Face_handle face;
        for (Arrangement_2::Edge_iterator edge = tmp.edges_begin(); edge != tmp.edges_end(); ++edge)
        {
            CGAL::zone(convolutions[i], edge->curve(), std::back_inserter(objects));
            for (Object_iterator object = objects.begin(); object != objects.end(); ++object)
            {
                if (assign(face, *object))
                {
                    if (face->is_unbounded())
                    {
                        //remove_edge(arrangement, edge);
                    }
                    else
                        insert(arr, edge->curve());
                }
            }
            objects.clear();
        }
        */
        ccII.push_back(arr);

    }
}

void
arrangement::newProblem()
{
    // reset arrangement data
    convolutions.clear();
    ccI.clear();
    ccII.clear();
    // reset polygon data
    env = Polygon_2();
    obs.clear();
    inset.clear();
    offsets.clear();
    admissible.clear();
    inset_o.clear();
    offsets_o.clear();
    admissible_o.clear();
    env_points.clear();

}

