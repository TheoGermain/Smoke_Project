#pragma once
#include "Civil.hh"
#include "Recipient.hh"

#define PV_POMPIER 2
#define PM_POMPIER 4

class Pompier : public Civil{

public :
  Pompier(Recipient* recip = new Seau(), int pv = PV_POMPIER, int pm = PM_POMPIER);
  ~Pompier();

  void set_deplacementEffectue(bool);
  void set_arrosageEffectue(bool);
  void set_dansUnVehicule(bool b);
  bool get_deplacementEffectue(void) const;
  bool get_arrosageEffectue(void) const;
  bool get_dansUnVehicule(void) const;
  Recipient* get_recip(void);
  std::string toString(void) const;

  static int cpt;
protected :
  Recipient* _recip;
  bool _deplacementEffectue;
  bool _arrosageEffectue;
  bool _dansUnVehicule;
};
