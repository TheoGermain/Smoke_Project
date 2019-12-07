#pragma once
#include "Milieu.hh"

class Grille{
public :
  Grille();
  virtual ~Grille();
  void jouerTour();
  void jouerPartie();

private :
  void propagation();
  static int cases_en_feu;
  Milieu **plateau;

};
