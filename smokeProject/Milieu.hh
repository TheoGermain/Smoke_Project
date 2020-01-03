#pragma once
#include "Revetement.hh"
#include <vector>
#include <iostream>
#include "Civil.hh"
#include "Vehicule.hh"

class Milieu{
public :
  Milieu();
  Milieu(NSRevetement::Revetement r, bool en_feu);
  virtual ~Milieu();
  friend std::ostream& operator<<(std::ostream& out, const Milieu& m);
  void set_revetement(NSRevetement::Revetement r);
  NSRevetement::Revetement get_revetement(void);
  void set_en_feu(bool b);
  bool get_en_feu() const;
  void set_fire(int n){degre_de_feu = n;}
  int get_fire(){return degre_de_feu;}
  std::vector<Civil*> get_personnages(void);
  NSRevetement::Revetement get_revetement() const;
  void ajouterPersonnage(Civil*);
  void supprimerPersonnage(const Civil*);
  std::vector<Vehicule*> get_vehicules(void);
  void ajouterVehicule(Vehicule*);
  void supprimerVehicule(const Vehicule*);

  static std::map<NSRevetement::Revetement, int> map_coeff_propagation;
  static std::map<NSRevetement::Revetement, int> map_proba_feu;

private :
  NSRevetement::Revetement _r;
  bool en_feu;
  std::vector<Civil*> _personnages;
  std::vector<Vehicule*> _vehicules;
  int degre_de_feu;
  void set_degre_de_feu();
};
