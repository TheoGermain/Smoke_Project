#pragma once

typedef enum{
  foret,
  plaine,
  eau,
  ville,
  usine,
  brule
}Revetement;

class Milieu{
public :
  Milieu(Revetement r, bool en_feu);
  virtual ~Milieu();

private :
  Revetement r;
  bool en_feu;
  vector<Civil> personnages;
  int degre_de_feu;
};
