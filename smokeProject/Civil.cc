#include "Civil.hh"

//  DIRECTIONS
//  7   0   1
//  6   .   2
//  5   4   3

int Civil::cpt = 1;

Civil::Civil() : _name("Civil_" + std::to_string(cpt++)), _pdv(1), _pdm(4), _pos(2, 0){
}

Civil::Civil(int x, int y, int pv, int pm): _name("Civil_" + std::to_string(cpt++)), _pdv(pv), _pdm(pm){
  _pos.push_back(x);
  _pos.push_back(y);
}

Civil::~Civil(){}


void Civil::set_pos(int x, int y){
    _pos[0] = x;
    _pos[1] = y;
}

void Civil::set_pdv(int pdv){
    _pdv = pdv;
}

std::vector<int> Civil::get_pos(){
  return _pos;
}

int Civil::get_pdv(void){
    return _pdv;
}

int Civil::get_pdm(void){
    return _pdm;
}

void Civil::calcul_dest(int direction, int deplacement, int &x, int &y){
    switch (direction) {
        case 0:
            x = _pos[0];
            y = _pos[1] - deplacement;
        break;
        case 1:
            x = _pos[0] + deplacement;
            y = _pos[1] - deplacement;
        break;
        case 2:
            x = _pos[0] + deplacement;
            y = _pos[1];
        break;
        case 3:
            x = _pos[0] + deplacement;
            y = _pos[1] + deplacement;
        break;
        case 4:
            x = _pos[0];
            y = _pos[1] + deplacement;
        break;
        case 5:
            x = _pos[0] - deplacement;
            y = _pos[1] + deplacement;
        break;
        case 6:
            x = _pos[0] - deplacement;
            y = _pos[1];
        break;
        case 7:
            x = _pos[0] - deplacement;
            y = _pos[1] - deplacement;
        break;
        default:
            x = _pos[0];
            y = _pos[1];
    }
}

std::string Civil::get_name() const{
    return _name;
}

std::string Civil::toString(void){
    std::stringstream ss;
    ss << _name << "   " << "PV : " << _pdv << "   " << "PM " << _pdm;
    return ss.str();
}

/*int Civil::deplacer(int x, int y){
    if()
}*/

/*std::ostream& operator<<(std::ostream& out, const Civil& c){
  out << c._name << ", pos : (" << c._pos[0] << ',' << c._pos[1] << "), " << c._pdv << " PV, " << c._pdm << " PM";
  return out;
}*/
