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
ACScell::compareLabels(ACScell &cell)
{
    // if there is no rho_ in one labels
    bool myFlag = true;
    for (int a = 0; a < (int) labels.size(); ++a)
        if (labels[a].compare("rho_") == 0)
            myFlag = false;

    if (myFlag)
        return true;

    myFlag = true;

    for (int a = 0; a < (int) cell.labels.size(); ++a)
        if (cell.labels[a].compare("rho_") == 0)
            myFlag = false;

    if (myFlag)
        return true;

    // Compare circular labels
    if((cell.labels.size() <= labels.size() - 2 ) || cell.labels.size() >= labels.size() +2  )
        return false;
    else
    {
        int i, j, k;
        int cpt_error = 0;
        int l1 = (int) labels.size();
        int l2 = (int) cell.labels.size();
        bool flag = true;
        for(j = 0; j < (int) cell.labels.size(); ++j) // to retrieve a fixed point for comparison
        {
            if(cell.labels[j].compare(labels[0]) == 0)
            {
                k = ++j;
                cpt_error = 0;
                for(i = 1;i < (int) labels.size(); ++i)
                {
                    if(cell.labels[k%l2].compare(labels[i%l1]) != 0)
                    {
                        ++cpt_error;
                        if(cpt_error == 2)
                        {
                            flag = false;
                            break;
                        }

                        if(cell.labels[(k+1)%l2].compare(labels[i%l1]) == 0)
                            ++k;
                        else if(cell.labels[k%l2].compare(labels[(i+1)%l2]) == 0)
                            ++i;
                        else
                        {
                            flag = false;
                            break;
                        }
                    }
                    ++k;
                }
                if(flag)
                    return true;

                flag = true;
            }
        }
        return false;
    }
    return false;
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
