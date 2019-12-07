#include "Milieu.hh"

std::map<NSRevetement::Revetement, int> Milieu::map_coeff_propagation = {{NSRevetement::foret,2} , {NSRevetement::plaine,3}, {NSRevetement::eau,0}, {NSRevetement::ville,1}, {NSRevetement::usine,5}, {NSRevetement::brule,0}};
std::map<NSRevetement::Revetement, int> Milieu::map_proba_feu = {{NSRevetement::foret,3} , {NSRevetement::plaine,4}, {NSRevetement::eau,0}, {NSRevetement::ville,5}, {NSRevetement::usine,1}, {NSRevetement::brule,0}};


Milieu::Milieu(){
  r = NSRevetement::foret;
  en_feu = false;
  degre_de_feu = 0;
}

Milieu::Milieu(NSRevetement::Revetement revet, bool en_feu) : r(revet), en_feu(en_feu){
  set_degre_de_feu();
}

Milieu::~Milieu(){

}


void Milieu::set_revetement(NSRevetement::Revetement r){
  this->r = r;
  if(r == NSRevetement::eau || r == NSRevetement::brule)
    set_en_feu(false);
  else
    set_degre_de_feu();
}

void Milieu::set_en_feu(bool b){
  if(this->r != NSRevetement::eau && this->r != NSRevetement::brule){
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
  return this->r;
}


std::ostream& operator<<(std::ostream& out, const Milieu& m){
  return out << '(' << m.r << ", " << m.en_feu << ", " << "deg : " << m.degre_de_feu << ')';
}

void Milieu::set_degre_de_feu(){
  if(!this->en_feu)
    degre_de_feu = 0;
  else{
    switch(this->r){
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
