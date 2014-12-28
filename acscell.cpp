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

void
ACScell::cleanLabels()
{
    // erase sames consecutive labels
    std::string previous = "";
    bool flag = true;
    for (int i = 0; i < (int)labels.size(); ++i)
    {
        if (flag)
        {
            previous = labels[i];
            flag = false;
            continue;
        }

        if (previous.compare(labels[i]) == 0)
        {
            labels.erase(labels.begin() + i);
            --i;
        }
        else
            previous = labels[i];
    }

    // erase if first and last are same
    if ((int)labels.size() > 1 && labels[0].compare(labels[((int)labels.size())-1]) == 0)
        labels.erase(labels.begin() + (((int)labels.size())+1));

}
