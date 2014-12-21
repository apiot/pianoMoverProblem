#include "acscell.h"

ACScell::ACScell()
{
}

ACScell::ACScell(int region)
{
    NCR = region;
}

void
ACScell::addLabel(std::string label)
{
    labels.push_back(label);
}

void
ACScell::setRegion(int region)
{
    NCR = region;
}

bool
ACScell::compareLabels(ACScell cell)
{
    // Compare circular labels
    // TODO

    return true;
}
