#pragma once
#include "Civil.hh"

class Pompier : public Civil{

public :
  Pompier();
  Pompier(int x, int y, int pv = 2, int pm = 5);
  ~Pompier();

  void set_deplacementEffectue(bool);
  bool get_deplacementEffectue(void);

  static int cpt;
protected :
  //recipient _recip;
  bool _deplacementEffectue;

};
