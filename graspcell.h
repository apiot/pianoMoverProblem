#ifndef GRASPCELL_H
#define GRASPCELL_H

#include "stdio.h"
#include "stdlib.h"
#include <string>
#include "sceneresults.h"

class GRASPcell
{
public:
    GRASPcell();
    GRASPcell(int region);

public:
    std::string label1;
    std::string label2;
    int NCR;
    std::string id;
    std::vector<double> center; // not used for the moment

    // for graph
    int distance;
    int father;
    int mark;
};

#endif // GRASPCELL_H
