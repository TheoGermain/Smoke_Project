#pragma once
#include "Milieu.hh"
#include <vector>
#include <QWidget>
#include <time.h>
#include <iostream>
#include <QApplication>
#include <fstream>
#include <QPushButton>
#include <QBoxLayout>
#include "Clickablelabel.hh"

#define L_GRILLE 22
#define C_GRILLE 40

#define DEPART_FEU_START 4

class Grille : public QWidget{
    Q_OBJECT

public :
  Grille();
  virtual ~Grille();
  Milieu operator()(std::size_t L, std::size_t C) const;
  Milieu& operator()(std::size_t L, std::size_t C);
  friend std::ostream& operator<<(std::ostream& out, const Grille& g);
  static std::vector<int*> cases_en_feu;
  void turn_on_fire(int L, int C);
  void turn_off_fire(int L, int C);

public slots :
  void boxClicked(int L, int C);
  void gameStart();
  void propagation();

private :
  void propagation_feu(int, std::size_t, std::size_t);
  bool declaration_feu(std::size_t, std::size_t);
  void propagation_feu_ligne(int, std::size_t, std::size_t);
  void propagation_feu_colonne(int, std::size_t , std::size_t);
  void propagation_feu_diagonaleGD(int, std::size_t, std::size_t);
  void propagation_feu_diagonaleDG(int, std::size_t, std::size_t);
  Milieu **plateau;
  std::vector<std::vector<ClickableLabel*>> _imgFeu;
  ClickableLabel *_map;
  QPushButton *_start;
  QPushButton *_nextTurn;
};
