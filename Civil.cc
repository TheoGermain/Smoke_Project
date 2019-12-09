#include "Civil.hh"

int Civil::cpt = 1;

Civil::Civil(){
    _name = "Civil_" + std::to_string(cpt++);
    _pdv = rand()%PDVMAX + 1;
    _pdm = rand()%PDMMAX + 1;
    _pos.push_back(rand()%L_GRILLE);
    _pos.push_back(rand()%C_GRILLE);
}

Civil::Civil(int pv, int pm,int x, int y): _pdv(pv), _pdm(pm){
  _name = "Civil_" + std::to_string(cpt++);
  _pos.push_back(x);
  _pos.push_back(y);
}

Civil::~Civil(){}

std::vector<int> Civil::get_pos(){
  return _pos;
}
int Civil::deplacer(int x, int y){
  if(x >= L_GRILLE || y >= C_GRILLE) { return -1;}
  if(sqrt(pow(this->_pos[0]-x,2))+ sqrt(pow(this->_pos[1]-y,2)) <= this->_pdm) {
    this->_pos[0] = x;
    this->_pos[1] = y;
    return 0;
    }
  return -1;
}

std::ostream& operator<<(std::ostream& out, const Civil& c){
  out << c._name << ", pos : (" << c._pos[0] << ',' << c._pos[1] << "), " << c._pdv << " PV, " << c._pdm << " PM";
  return out;
}
