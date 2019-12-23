#pragma once
#include "Milieu.hh"
#include <vector>
#include <QWidget>
#include "Clickablelabel.hh"

#define L_GRILLE 22
#define C_GRILLE 40

class Grille : public QWidget{
    Q_OBJECT

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
  void turn_on_fire(int L, int C);
  void turn_off_fire(int L, int C);

public slots :
  void boxClicked(int L, int C);

private :
  void propagation_feu(int, std::size_t, std::size_t);
  bool declaration_feu(std::size_t, std::size_t);
  void propagation_feu_ligne(int, std::size_t, std::size_t);
  void propagation_feu_colonne(int, std::size_t , std::size_t);
  void propagation_feu_diagonaleGD(int, std::size_t, std::size_t);
  void propagation_feu_diagonaleDG(int, std::size_t, std::size_t);
  Milieu **plateau;
  ClickableLabel *_map;
};
