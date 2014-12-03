#include "arrangement.h"

arrangement::arrangement()
{
    environment = new Arrangement_2();
    manipulator_diametre = 0;
    target_diametre = 0;
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
    /*
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
    */
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
}

void
arrangement::newProblem()
{
    // reset arrangement data
    environment = new Arrangement_2();
    // reset polygon data
    env = Polygon_2();
    obs.clear();
    inset.clear();
    offsets.clear();
    admissible.clear();

}

