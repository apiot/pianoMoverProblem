#include "graphs.h"

Graphs::Graphs()
{
}

void
Graphs::retrieveData(std::vector<std::vector<int> > &voisins, std::vector<ACScell> &acscells, std::vector<GRASPcell> &graspcells)
{
    neighbours = voisins;
    ACScells = acscells;
    GRASPcells = graspcells;
}

void
Graphs::create_motion_graph()
{

}

void
Graphs::create_contact_graph()
{

}

void
Graphs::create_manip_graph()
{

}

void
Graphs::resetVertices()
{
    for (int i = 0; i < (int) ACScells.size(); ++i)
    {
        ACScells[i].distance = -1;
        ACScells[i].father = -1;
        ACScells[i].mark = -1;
    }
    for (int i = 0; i < (int) GRASPcells.size(); ++i)
    {
        GRASPcells[i].distance = -1;
        GRASPcells[i].father = -1;
        GRASPcells[i].mark = -1;
    }
}

template<typename T>
bool
Graphs::isConnexe(std::vector<std::vector<int> > &adjacencies, std::vector<T> &graph, int &source, int &target)
{
    resetVertices();

    // Depth first search
    std::vector<int> stack;
    graph[source].mark = 1;                // -1 free; 0 waiting; 1 visited


}

bool
Graphs::isNeighbour(std::vector<std::vector<int> > &adjacencies, int &source, int &target)
{
    for (int i = 0; i < (int)adjacencies[source].size(); ++i)
        if (adjacencies[source][i] == target)
            return true;

    return false;
}

template<typename T>
void
Graphs::dijkstra(std::vector<std::vector<int> > &adjacencies, std::vector<T> &graph, int &source, int &target)
{

}

std::vector<int>
Graphs::getResult()
{
    return result;
}

void
Graphs::newProblem()
{
    neighbours.clear();
    ACScells.clear();
    GRASPcells.clear();

    motion_graph.clear();
    contact_graph.clear();
    manip_graph.clear();
}
