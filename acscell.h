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
    bool compareLabels(ACScell &cell);
    void cleanLabels();
public:
    std::vector<std::string> labels;
    int NCR; // non critical region
    std::string id;
    Arrangement_2 arr;

    // for graph
    int distance;
    int father;
    int mark;
};

#endif // ACSCELL_H
