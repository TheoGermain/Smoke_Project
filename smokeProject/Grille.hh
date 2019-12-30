#pragma once
#include "Milieu.hh"
#include <vector>
#include <QWidget>
#include <iostream>
#include <QApplication>
#include <fstream>
#include <QPushButton>
#include <sstream>
#include "Clickablelabel.hh"
#include "BoxDisplayInfo.hh"
#include "Pompier.hh"
#include "QListItemPersonnage.hh"

#define L_GRILLE 22
#define C_GRILLE 40

#define DEPART_FEU_START 4
#define DEPART_CIVIL 7
#define DEPART_POMPIER 10

class Grille : public QWidget{
    Q_OBJECT

public :
  Grille();
  virtual ~Grille();
  static std::vector<int*> cases_en_feu;
  Milieu operator()(std::size_t L, std::size_t C) const;
  Milieu& operator()(std::size_t L, std::size_t C);
  friend std::ostream& operator<<(std::ostream& out, const Grille& g);
  void turn_on_fire(int L, int C);
  void turn_off_fire(int L, int C);


public slots :
  void boxClicked(int, int);
  void gameStart();
  void tourSuivant();
  void displayActions(QListWidgetItem *item);
  void cleanPossibilities(void);
  void displayNextTurn();
  void afficherPorteeArrosage(void);

signals:
  void displayInfo();

private :
  void propagation_feu(int, std::size_t, std::size_t);
  bool declaration_feu(std::size_t, std::size_t);
  void propagation_feu_ligne(int, std::size_t, std::size_t);
  void propagation_feu_colonne(int, std::size_t, std::size_t);
  void propagation_feu_diagonaleGD(int, std::size_t, std::size_t);
  void propagation_feu_diagonaleDG(int, std::size_t, std::size_t);
  void deplacer_personnage(std::vector<int>, int, int, std::pair<Civil*, ClickableLabel*>*);
  void baisse_pdv();
  void propagation();
  void deplacement_civils(void);
  void displayPossibilities(std::vector<int>, int);


  Milieu **plateau;
  std::vector<std::vector<ClickableLabel*>> _imgFeu;
  std::vector<std::vector<ClickableLabel*>> _imgAction;
  std::vector<std::pair<Civil*, ClickableLabel*>> _civilList;
  std::vector<std::pair<Pompier*, ClickableLabel*>> _pompierList;
  ClickableLabel *_map;
  QPushButton *_start;
  QPushButton *_nextTurn;
  QPushButton *_arroser;
  QLabel *_nbCivil;
  QLabel *_nbFeu;
  QLabel *_nbPompier;
  BoxDisplayInfo *_fenetreInfoCase;
};
