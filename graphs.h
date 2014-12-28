#ifndef GRAPHS_H
#define GRAPHS_H

#include "mainwindow.h"

class Graphs
{
public:
    Graphs();
    void retrieveData(std::vector<std::vector<int> > &voisins, std::vector<ACScell> &acscells, std::vector<GRASPcell> &graspcells);
    void create_motion_graph();
    void create_contact_graph();
    void create_manip_graph();
    void resetVertices();
    template<typename T>
    bool isConnexe(std::vector<std::vector<int> > &adjacencies, std::vector<T> &graph, int &source, int &target);
    bool isNeighbour(std::vector<std::vector<int> > &adjacencies, int &source, int &target);
    template<typename T>
    void dijkstra(std::vector<std::vector<int> > &adjacencies, std::vector<T> &graph, int &source, int &target);
    std::vector<int> getResult();
    void newProblem();
public:
    // raw data
    std::vector<std::vector<int> > neighbours;
    std::vector<ACScell> ACScells;
    std::vector<GRASPcell> GRASPcells;

    // for graphs : adjacency lists
    std::vector<std::vector<int> > motion_graph;
    std::vector<std::vector<int> > contact_graph;
    std::vector<std::vector<int> > manip_graph;

    // result
    std::vector<int> result;

};

#endif // GRAPHS_H
