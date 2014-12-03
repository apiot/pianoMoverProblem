#ifndef ARRANGEMENT_H
#define ARRANGEMENT_H

#include "mainwindow.h"

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
    void offset_of_polygon(Polygon_2 P, int diametre, std::vector<Offset_polygon_with_holes_2> &off);
    void inset_of_polygon(Polygon_2 P, int diametre, std::list<Offset_polygon_2> &in);
    void admissible_configuration(Op2_it pgn, std::vector<Offset_polygon_with_holes_2> &off, Pwh_list_2 &adm);
    void compute_admissible_configuration();
    void newProblem();

public:
    // computed arrangement data
    Arrangement_2 *environment;

    // compute polygon data
    Polygon_2 env;
    std::vector<Polygon_2> obs;
    std::list<Offset_polygon_2> inset;
    std::vector<Offset_polygon_with_holes_2> offsets;
    Pwh_list_2 admissible;
    std::list<Offset_polygon_2> inset_o;
    std::vector<Offset_polygon_with_holes_2> offsets_o;
    Pwh_list_2 admissible_o;



    // raw data
    std::vector<QPoint> frontier;
    std::vector<std::vector<QPoint> > obstacles;
    QPoint manipulator_centre;
    QPoint manipulator_centre_end;
    int manipulator_diametre;
    QPoint target_centre;
    QPoint target_centre_end;
    int target_diametre;
};

#endif // ARRANGEMENT_H
