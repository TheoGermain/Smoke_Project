#include "PompierEnChef.hh"

int PompierEnChef::cpt = 0;

PompierEnChef::PompierEnChef():Pompier(new Lance(), PV_POMPIER_CHEF, PM_POMPIER_CHEF){
    _name = "Pompier_en_Chef_" + std::to_string(cpt++);
    Pompier::cpt--;
}

PompierEnChef::~PompierEnChef(){}

