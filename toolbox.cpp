#include "toolbox.h"

toolbox::toolbox()
{

}

void
toolbox::getRationalFromDouble(int &num, int &den, double var)
{
    int precision = 6;
    double k = 0;
    double x = 0;
    while (k <= precision)
    {
        while (x*x < var)
            x = x + 1.0/pow(10,k);
        if (x*x == var)
            break;
        else
            x -= 1.0/pow(10,k++);
    }
    num = (int)(x*pow(10,precision));
    den = pow(10,precision);
    std::cout << "valeur : "<< num << "/" << den << std::endl;
}
