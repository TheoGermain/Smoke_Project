#pragma once
#include <string>
#include <math.h>
#include <vector>
#include <sstream>

class Civil{

public :
  Civil();
  Civil(int x, int y, int pv = 1, int pm = 4);
  virtual ~Civil();
  std::vector<int> get_pos() const;
  void set_pos(int, int);
  void set_pdv(int pdv);
  int get_pdv(void) const;
  int get_pdm(void) const;
  std::string get_name() const;
  void calcul_dest(int direction, int deplacement, int &x, int &y);
  virtual std::string toString(void) const;

  static int cpt;

protected :
  std::string _name;
  int _pdv;
  int _pdm;
  std::vector<int> _pos;
};
