#ifndef ACSCELL_H
#define ACSCELL_H

#include "stdio.h"
#include "stdlib.h"
#include <string>
#include "sceneresults.h"

/* Admissible Configuration Set Cell */
class ACScell
{
public:
    ACScell();
    ACScell(int region);
    void addLabel(std::string label);
    void setRegion(int region);
    bool compareLabels(ACScell cell);
    void cleanLabels();
public:
    std::vector<std::string> labels;
    /* NCR = Non Critical Region (cell built with critical curves in object convolution */
    int NCR;
    std::string id;
    Arrangement_2 arr; // not used for the moment

    // for graph
    int distance;
    int father;
    int mark;
};

#endif // ACSCELL_H
