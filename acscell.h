#ifndef ACSCELL_H
#define ACSCELL_H

#include "mainwindow.h"

/* Admissible Configuration Set Cell */
class ACScell
{
public:
    ACScell();
    ACScell(int region);
    void addLabel(std::string label);
    void setRegion(int region);
    bool compareLabels(ACScell cell);
public:
    std::vector<std::string> labels;
    /* NCR = Non Critical Region (cell built with critical curves in object convolution */
    int NCR;
};

#endif // ACSCELL_H
