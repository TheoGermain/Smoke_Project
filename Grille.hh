#pragma once
#include "Milieu.hh"
#include <vector>

#define L_GRILLE 10
#define C_GRILLE 6

class Grille{
public :
  Grille();
  virtual ~Grille();
  //void jouerTour();
  //void jouerPartie();
  Milieu operator()(std::size_t L, std::size_t C) const;
  Milieu& operator()(std::size_t L, std::size_t C);
  friend std::ostream& operator<<(std::ostream& out, const Grille& g);
  void propagation();
  static std::vector<int*> cases_en_feu;

private :
  void propagation_feu(int, std::size_t, std::size_t);
  bool declaration_feu(std::size_t, std::size_t);
  Milieu **plateau;
};
