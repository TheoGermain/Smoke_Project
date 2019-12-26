#pragma once
#include "Grille.hh"
#include <string>
#include <math.h>
#include <vector>

#define PDVMAX 100
#define PDMMAX (L_GRILLE + C_GRILLE)/2


class Civil{

public :
  Civil();
  Civil(int pv, int pm, int x, int y);
  virtual ~Civil();
  friend std::ostream& operator<<(std::ostream& out, const Civil& c);
  int deplacer(int x, int y);
  std::vector<int> get_pos();
  static int cpt;
protected :
  std::string _name;
  int _pdv;
  int _pdm;
  std::vector<int> _pos;
};
