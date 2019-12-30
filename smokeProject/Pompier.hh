#pragma once
#include "Civil.hh"
#include "Recipient.hh"

class Pompier : public Civil{

public :
  Pompier(Recipient* recip = new Seau());
  Pompier(int x, int y, Recipient* recip = new Seau(), int pv = 2, int pm = 5);
  ~Pompier();

  void set_deplacementEffectue(bool);
  void set_arrosageEffectue(bool);
  bool get_deplacementEffectue(void);
  bool get_arrosageEffectue(void);
  Recipient* get_recip(void);
  std::string toString(void);

  static int cpt;
protected :
  Recipient* _recip;
  bool _deplacementEffectue;
  bool _arrosageEffectue;
};
