#include "Milieu.hh"

std::map<NSRevetement::Revetement, int> Milieu::map_coeff_propagation = {{NSRevetement::foret,2} , {NSRevetement::plaine,3}, {NSRevetement::eau,0}, {NSRevetement::ville,1}, {NSRevetement::usine,5}, {NSRevetement::brule,0}};
std::map<NSRevetement::Revetement, int> Milieu::map_proba_feu = {{NSRevetement::foret,3} , {NSRevetement::plaine,4}, {NSRevetement::eau,0}, {NSRevetement::ville,5}, {NSRevetement::usine,1}, {NSRevetement::brule,0}};

Milieu::Milieu():_r(NSRevetement::foret), en_feu(false), _personnages(0), _vehicules(0), degre_de_feu(0){
}

Milieu::Milieu(NSRevetement::Revetement revet, bool en_feu) : _r(revet), en_feu(en_feu), _personnages(0), _vehicules(0){
  set_degre_de_feu();
}

Milieu::~Milieu(){

}

void Milieu::set_revetement(NSRevetement::Revetement r){
  this->_r = r;
  if(_r == NSRevetement::eau || _r == NSRevetement::brule)
    set_en_feu(false);
  else
    set_degre_de_feu();
}

NSRevetement::Revetement Milieu::get_revetement(void){
    return this->_r;
}

std::vector<Civil*> Milieu::get_personnages(void){
    return _personnages;
}

std::vector<Vehicule*> Milieu::get_vehicules(void){
    return _vehicules;
}

void Milieu::set_en_feu(bool b){
  if(this->_r != NSRevetement::eau && this->_r != NSRevetement::brule){
    this->en_feu = b;
  }
  else
    this->en_feu = false;
  set_degre_de_feu();
}

bool Milieu::get_en_feu() const{
  return this->en_feu;
}

NSRevetement::Revetement Milieu::get_revetement() const{
  return this->_r;
}


std::ostream& operator<<(std::ostream& out, const Milieu& m){
  return out << '(' << m._r << ", " << m.en_feu << ", " << "deg : " << m.degre_de_feu << ')';
}

void Milieu::set_degre_de_feu(){
  if(!this->en_feu)
    degre_de_feu = 0;
  else{
    switch(this->_r){
      case NSRevetement::foret :
        degre_de_feu = 6;
        break;
      case NSRevetement::plaine :
        degre_de_feu = 4;
        break;
      case NSRevetement::eau :
      case NSRevetement::brule :
        degre_de_feu = 0;
        en_feu = false;
        break;
      case NSRevetement::ville :
      degre_de_feu = 5;
      break;
      case NSRevetement::usine :
        degre_de_feu = 7;
        break;
      default :
        break;
    }
  }
}

void Milieu::ajouterPersonnage(Civil* c){
    _personnages.push_back(c);
}

void Milieu::supprimerPersonnage(const Civil* c){
    std::vector<Civil*>::iterator to_erase;
    for(auto it = _personnages.begin(); it != _personnages.end(); it++){
        if(!(*it)->get_name().compare(c->get_name()))
            to_erase = it;
    }
    _personnages.erase(to_erase);
}

void Milieu::ajouterVehicule(Vehicule* v){
    _vehicules.push_back(v);
}

void Milieu::supprimerVehicule(const Vehicule* v){
    for(auto it = _vehicules.begin(); it != _vehicules.end(); it++){
        if(*it == v){
            _vehicules.erase(it);
            break;
        }
    }
}

