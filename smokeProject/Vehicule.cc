#include "Vehicule.hh"

Vehicule::Vehicule(std::string name, int deplacement, int capacite) : _capaciteMax(capacite), _deplacementMax(deplacement), _name(name), _passagers(std::vector<Pompier*>(0)), _pos(2, 0), _deplacementEffectue(false){

}

Vehicule::~Vehicule(){}

std::string Vehicule::get_name() const{
    return _name;
}

size_t Vehicule::get_deplacementMax() const{
    return _deplacementMax;
}

size_t Vehicule::get_capaciteMax() const{
    return _capaciteMax;
}

std::string Vehicule::toString() const{
    std::stringstream ss;
    ss << _name << " (" << _passagers.size() << '/' << _capaciteMax << ')';
    return ss.str();
}

void Vehicule::ajouterPassager(Pompier* p){
    _passagers.push_back(p);
}

void Vehicule::supprimerPassager(Pompier* p){
    for(auto it = _passagers.begin(); it != _passagers.end(); it++){
        if(*it == p){
            _passagers.erase(it);
            break;
        }
    }
}

std::vector<Pompier*> Vehicule::get_passagers(void){
    return _passagers;
}

void Vehicule::set_pos(int x, int y){
    _pos[0] = x;
    _pos[1] = y;
}

std::vector<int> Vehicule::get_pos(){
  return _pos;
}

bool Vehicule::get_deplacementEffectue(void){
    return _deplacementEffectue;
}

void Vehicule::set_deplacementEffectue(bool b){
    _deplacementEffectue = b;
}
