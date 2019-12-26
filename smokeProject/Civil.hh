#pragma once
#include <string>
#include <math.h>
#include <vector>

class Civil{

public :
  Civil();
  Civil(int x, int y, int pv = 1, int pm = 4);
  virtual ~Civil();
  //friend std::ostream& operator<<(std::ostream& out, const Civil& c);
  //void deplacer(int x, int y);
  std::vector<int> get_pos();
  void set_pos(int, int);
  void set_pdv(int pdv);
  int get_pdv(void);
  int get_pdm(void);
  std::string get_name() const;
  void calcul_dest(int direction, int deplacement, int &x, int &y);

  static int cpt;

protected :
  std::string _name;
  int _pdv;
  int _pdm;
  std::vector<int> _pos;
};
