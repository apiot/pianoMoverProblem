#include "graphs.h"

Graphs::Graphs()
{
}

void
Graphs::retrieveData(std::vector<std::vector<int> > &voisins, std::vector<ACScell> &acscells, std::vector<GRASPcell> &graspcells, std::vector<std::vector<int> > &graspmanipcells, std::vector<int> &source, std::vector<int> &target)
{
    neighbours = voisins;
    ACScells = acscells;
    GRASPcells = graspcells;
    GRASPManipCells = graspmanipcells;
    this->source = source;
    this->target = target;
    compute_new_neighbours();
}

void
Graphs::printNewNeighbours(std::vector<std::vector<int> > &item)
{
    std::cout << "************** New Neighbours ****************" << std::endl;
    for (int i = 0; i < (int)item.size(); ++i)
    {
        std::cout << "Vertex : " << std::to_string(i) << " - Neigbours : ";
        for (int j = 0; j < (int)item[i].size(); ++j)
        {
            std::cout << std::to_string(item[i][j]) << " ";
        }
        std::cout << std::endl;
    }
}

void
Graphs::add_neighbours_ACS(int a, int b)
{
    for (int i = 0; i < (int)ACScells.size(); ++i)
        if (ACScells[i].NCR == a)
            for (int j = 0; j < (int) ACScells.size(); ++j)
                if (ACScells[j].NCR == b)
                    neighboursACScells[i].push_back(j);
}

void
Graphs::add_neighbours_GRASP(int a, int b)
{
    for (int i = 0; i < (int)GRASPcells.size(); ++i)
        if (GRASPcells[i].NCR == a)
            for (int j = 0; j < (int) GRASPcells.size(); ++j)
                if (GRASPcells[j].NCR == b)
                    neighboursGRASPcells[i].push_back(j);
}

void
Graphs::compute_new_neighbours()
{
    neighboursACScells.resize(ACScells.size());
    neighboursGRASPcells.resize(GRASPcells.size());
    for (int i = 0; i < (int) neighbours.size(); ++i)
        for (int j = 0; j < (int) neighbours[i].size(); ++j)
        {
            // for ACScells
            add_neighbours_ACS(i,neighbours[i][j]);
            // for GRASPcells
            add_neighbours_GRASP(i,neighbours[i][j]);
        }

    printNewNeighbours(neighboursACScells);
    printNewNeighbours(neighboursGRASPcells);
}

void
Graphs::printGraph(std::vector<std::vector<int> > &graph)
{
    std::cout << "**************** Graph *****************" << std::endl;
    std::cout << "nb sommets : " << std::to_string((int)graph.size()) << std::endl;
    for (int i = 0; i < (int)graph.size(); ++i)
    {
        std::cout << "Vertex : " << std::to_string(i) << " - Neighbours :";
        for (int j = 0; j < (int)graph[i].size(); ++j)
        {
            std::cout << " " << std::to_string(graph[i][j]);
        }
        std::cout << std::endl;
    }

}

void
Graphs::printACScells()
{
    int cpt = 0;
    std::cout << std::endl;
    std::cout << "**************** ACScells ****************" << std::endl;
    for (int i = 0; i < (int) ACScells.size(); ++i)
    {
        std::cout << cpt << " - " << ACScells[i].id << " - Labels : ";
        for (int j = 0; j < (int) ACScells[i].labels.size(); ++j)
            std::cout << ACScells[i].labels[j] << " ";
        std::cout << std::endl;
        cpt++;
    }
    std::cout << std::endl;
}

void
Graphs::printGRASPcells()
{
    int cpt = 0;
    std::cout << std::endl;
    std::cout << "**************** GRASPcells ****************" << std::endl;
    for (int i = 0; i < (int) GRASPcells.size(); ++i)
    {
        std::cout << cpt << " - " << GRASPcells[i].id << " - Labels : ";
        std::cout << GRASPcells[i].label1 << " rho_ " << GRASPcells[i].label2 << std::endl;
        cpt++;
    }
    std::cout << std::endl;
}

void
Graphs::create_motion_graph()
{
    motion_graph.resize((int)ACScells.size());

    for(int i = 0; i < (int)neighboursACScells.size(); ++i)
       for(int j = 0; j < (int)neighboursACScells[i].size(); ++j)
            if(ACScells[i].compareLabels(ACScells[neighboursACScells[i][j]]))
                motion_graph[i].push_back(neighboursACScells[i][j]);

    printGraph(motion_graph);
}

void
Graphs::create_contact_graph()
{
    contact_graph.resize((int)GRASPcells.size());

    for(int i = 0; i< (int)neighboursGRASPcells.size(); ++i)
        for(int j = 0; j < (int)neighboursGRASPcells[i].size(); ++j)
        {
            bool a = (GRASPcells[i].label1.compare(GRASPcells[neighboursGRASPcells[i][j]].label1) == 0);
            bool b = (GRASPcells[i].label2.compare(GRASPcells[neighboursGRASPcells[i][j]].label2) == 0);
            if ((GRASPcells[i].label1.compare("joker")==0) || (GRASPcells[neighboursGRASPcells[i][j]].label1.compare("joker")==0))
                a = true;
            if( (!a && b) || (a && !b) || (a && b))
                contact_graph[i].push_back(neighboursGRASPcells[i][j]);
        }

    printGraph(contact_graph);
}

void
Graphs::create_manip_graph()
{
    // just add liaison edges
    manip_graph = contact_graph; // do a copy
    for (int i = 0; i < (int) GRASPManipCells.size(); ++i)
    {
        if ((int) GRASPManipCells[i].size() > 1)
        for (int j = 0; j < (int) GRASPManipCells[i].size(); ++j)
        {
            for (int k = 0; k < (int) GRASPManipCells[i].size(); ++k)
            if (k != j)
            {
                manip_graph[GRASPManipCells[i][j]].push_back(GRASPManipCells[i][k]);
            }
        }
    }

    printGraph(manip_graph);
}

void
Graphs::resetVertices()
{
    for (int i = 0; i < (int) ACScells.size(); ++i)
    {
        ACScells[i].distance = 0;
        ACScells[i].father = -1;
        ACScells[i].mark = 0; // 0 : not visited ; 1 : visited
    }
    for (int i = 0; i < (int) GRASPcells.size(); ++i)
    {
        GRASPcells[i].distance = 0;
        GRASPcells[i].father = -1;
        GRASPcells[i].mark = 0;
    }
}

// parcours en largeur
template <typename T>
int
Graphs::breadthFirstSearch(std::vector<T> &items, std::vector<std::vector<int> > &graph, int &source, std::vector<int> &target)
{
    resetVertices();

    std::list<int> file;
    int current = source;
    items[current].mark = 1;
    file.push_back(current);
    while (!file.empty())
    {
        current = file.front();
        file.pop_front();

        for (int i = 0; i < (int) graph[current].size(); ++i)
        {
            if (items[graph[current][i]].mark == 0)
            {
                items[graph[current][i]].mark = 1;
                items[graph[current][i]].father = current;
                items[graph[current][i]].distance = items[current].distance + 1;

                file.push_back(graph[current][i]);
            }
        }

        // test if vertex is among targets
        for (int k = 0; k < (int) target.size(); ++k)
            if (current == target[k])
                return current;

    }
    return -1;
}

std::list<int>
Graphs::getResult()
{
    // find solution
    int solution = -1;
    bool flag = false;
    for (int i = 0; i < (int) source.size(); ++i)
    {
        solution = breadthFirstSearch(GRASPcells, manip_graph, source[i], target);
        if (solution != -1)
        {
            flag = true;
            break;
        }
    }

    // just print source and target
    std::cout << "************** SOURCES **********" << std::endl;
    for (int i = 0; i < (int) source.size(); ++i)
        std::cout << " " << std::to_string(source[i]);
    std::cout << std::endl;

    std::cout << "************** TARGETS **********" << std::endl;
    for (int i = 0; i < (int) target.size(); ++i)
        std::cout << " " << std::to_string(target[i]);
    std::cout << std::endl;


    if (flag) // if there is a result
    {
        // retrieve solution
        int current = solution;
        do {
            result.push_back(current);
            current = GRASPcells[current].father;
        }
        while (current != -1);

        result.reverse();

        // print it
        std::cout << "************ SOLUTION IS (GRASP Cells) *************" << std::endl;
        for (std::list<int>::iterator it = result.begin(); it != result.end(); ++it)
        {
            std::cout << " >> " << *it;
        }
        std::cout << std::endl;
    }
    else
    {
        std::cout << "************ THERE IS NO SOLUTION *************" << std::endl;
    }


    std::cout << std::endl << "************ Liaison edges *************" << std::endl;
    for (int i = 0; i < (int) GRASPManipCells.size(); ++i)
    {
        if ((int) GRASPManipCells[i].size() > 1)
        {
            for (int j = 0; j < (int) GRASPManipCells[i].size(); ++j)
            {
                std::cout << " " << GRASPManipCells[i][j];
            }
            std::cout << std::endl;
        }

    }

    return result;
}

void
Graphs::newProblem()
{
    neighbours.clear();
    ACScells.clear();
    GRASPcells.clear();
    GRASPManipCells.clear();

    motion_graph.clear();
    contact_graph.clear();
    manip_graph.clear();

    neighboursACScells.clear();
    neighboursGRASPcells.clear();

    source.clear();
    target.clear();

    result.clear();
}
