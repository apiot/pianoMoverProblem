#ifndef ARRANGEMENT_H
#define ARRANGEMENT_H

#include "mainwindow.h"

class MainWindow;

class arrangement
{
public:
    arrangement();
    void printArrConsole(Arrangement_2 *a);
    void retrieveData(std::vector<QPoint> env, std::vector<std::vector<QPoint> > obs,
                      QPoint mb,QPoint me,int mr,QPoint tb,QPoint te,int tr);
    void offset_of_polygon(Polygon_2 P, int diametre, std::vector<Offset_polygon_with_holes_2> &off);
    void inset_of_polygon(Polygon_2 P, int diametre, std::list<Offset_polygon_2> &in);
    void admissible_configuration(Op2_it pgn, std::vector<Offset_polygon_with_holes_2> &off, Pwh_list_2 &adm);
    void compute_admissible_configuration();
    std::string getLabel(std::vector<std::string> &labels, X_monotone_curve_2 &curve, int &cpt, double &r);
    void compute_convolutionLabels();
    void keep_arc(Arrangement_2::Edge_iterator &e, Arrangement_2 &copy, Walk_pl &walk_pl);
    void compute_criticalCurves_type_I();
    void compute_criticalCurves_type_II();
    std::vector<double> getPointMiddle(Arrangement_2::Ccb_halfedge_circulator &edge);
    void compute_pointInCells(Arrangement_2 &arr, std::vector<std::vector<double> > &points);
    void print_neighbours();
    void compute_neighbours();
    void compute_ACScell();
    void compute_GRASPcell();
    void compute_ACScellBeginEnd();
    void newProblem();

public:

    // raw data
    std::vector<QPoint> frontier;
    std::vector<std::vector<QPoint> > obstacles;
    std::vector<QPoint> env_points;
    QPoint manipulator_centre;
    QPoint manipulator_centre_end;
    int manipulator_diametre;
    QPoint target_centre;
    QPoint target_centre_end;
    int target_diametre;
    double r1r2;

    // compute polygon data
    Polygon_2 env;
    std::vector<Polygon_2> obs;

    std::list<Offset_polygon_2> inset;
    std::vector<Offset_polygon_with_holes_2> offsets;
    Pwh_list_2 admissible;

    std::list<Offset_polygon_2> inset_o;
    std::vector<Offset_polygon_with_holes_2> offsets_o;
    Pwh_list_2 admissible_o;

    // computed arrangement data
    std::vector<Arrangement_2> convolutions; // robot
    std::vector<Arrangement_2> convolutions_o;
    //std::vector<Arrangement_2> ccI;
    //std::vector<Arrangement_2> ccII;

    // for Graphs
    Arrangement_2 nonCriticalRegions;
    //Arrangement_2 convolution_r_all;
    std::vector<std::vector<double> > point_in_faces;
    std::vector<std::vector<int> > neighbours;

    int AcscellBegin;
    int AcscellEnd;

    std::vector<ACScell> ACScells;
    std::vector<GRASPcell> GRASPcells;
    std::vector<std::vector<int> > GRASPManipCells;
    std::vector<int> source;
    std::vector<int> target;
};

#endif // ARRANGEMENT_H
