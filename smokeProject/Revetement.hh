#pragma once
#include <iostream>
#include <map>

namespace NSRevetement{
  typedef enum{
    foret,
    plaine,
    eau,
    ville,
    usine,
    brule
  }Revetement;

}

std::ostream& operator<<(std::ostream& out, const NSRevetement::Revetement& r);
