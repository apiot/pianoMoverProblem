#ifndef GRAPHS_H
#define GRAPHS_H

#include "mainwindow.h"

class Graphs
{
public:
    Graphs();
    void retrieveData(std::vector<std::vector<int> > &voisins, std::vector<ACScell> &acscells, std::vector<GRASPcell> &graspcells, std::vector<std::vector<int> > &graspmanipcells,  std::vector<int> &source, std::vector<int> &target);
    void printNewNeighbours(std::vector<std::vector<int> > &item);
    void add_neighbours_ACS(int a, int b);
    void add_neighbours_GRASP(int a, int b);
    void compute_new_neighbours();
    void printGraph(std::vector<std::vector<int> > &graph);
    void printACScells();
    void printGRASPcells();
    void create_motion_graph();
    void create_contact_graph();
    void create_manip_graph();
    void resetVertices();
    template <typename T>
    int breadthFirstSearch(std::vector<T> &items, std::vector<std::vector<int> > &graph, int &source, std::vector<int> &target);
    std::list<int> getResult();
    void newProblem();
public:
    // raw data
    std::vector<std::vector<int> > neighbours;
    std::vector<ACScell> ACScells;
    std::vector<GRASPcell> GRASPcells;
    std::vector<std::vector<int> > GRASPManipCells;

    // for graphs : adjacency lists
    std::vector<std::vector<int> > neighboursACScells;
    std::vector<std::vector<int> > neighboursGRASPcells;

    std::vector<std::vector<int> > motion_graph;
    std::vector<std::vector<int> > contact_graph;
    std::vector<std::vector<int> > manip_graph;

    std::vector<int> source;
    std::vector<int> target;

    // result
    std::list<int> result;

};

#endif // GRAPHS_H
