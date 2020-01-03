#pragma once
#include "Pompier.hh"

#define PV_POMPIER_CHEF 4
#define PM_POMPIER_CHEF 3

class PompierEnChef : public Pompier{
public:
    PompierEnChef();
    ~PompierEnChef();
    static int cpt;
};
