#include "Civil.hh"
static int cpt =1;

Civil::Civil(){
    _name = "Civil"+std::to_string(cpt);
    cpt++;
    _pdv = rand()%PDVMAX +1;
    _pdm = rand()%PDMMAX +1;
    pos[0] = rand()%L_GRILLE;
    pos[1] = rand()%C_GRILLE;
}

Civil::Civil(int pv, int pm,int x, int y): Civil(){
  _pdv = pv;
  _pdm = pm;
  pos[0] = x;
  pos[1] = y;
}

Civil::~Civil(){}

std::vector<int> Civil::get_pos(){
  std::vector<int> res;
  res.push_back(pos[0]);
  res.push_back(pos[1]);
  return res;
}
int Civil::deplacer(int x, int y){
  if(x >= L_GRILLE || y >= C_GRILLE) { return -1;}
  if(sqrt(pow(this->pos[0]-x,2))+ sqrt(pow(this->pos[1]-y,2)) <= this-> _pdm) {
    this->pos[0] = x;
    this->pos[1] = y;
    return 0;
    }
  return -1;
}
