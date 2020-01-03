#include "Pompier.hh"

int Pompier::cpt = 0;

Pompier::Pompier(Recipient* recip, int pv, int pm) : Civil(0, 0, pv, pm), _recip(recip), _deplacementEffectue(false), _arrosageEffectue(false), _dansUnVehicule(false){
    _name = "Pompier_" + std::to_string(cpt++);
    Civil::cpt--;
}

Pompier::~Pompier(){}

void Pompier::set_deplacementEffectue(bool b){
    _deplacementEffectue = b;
}

void Pompier::set_arrosageEffectue(bool b){
    _arrosageEffectue = b;
}

void Pompier::set_dansUnVehicule(bool b){
    _dansUnVehicule = b;
}

bool Pompier::get_deplacementEffectue() const{
    return _deplacementEffectue;
}

bool Pompier::get_arrosageEffectue() const{
    return _arrosageEffectue;
}

bool Pompier::get_dansUnVehicule() const{
    return _dansUnVehicule;
}

std::string Pompier::toString(void) const{
    std::stringstream ss;
    std::string cont;
    if(dynamic_cast<Lance*>(_recip))
        cont = "inf";
    else
        cont = std::to_string(_recip->get_contenuRestant());
    ss << Civil::toString() << " " << _recip->get_name() << '(' << cont << ')' << " : " << _recip->get_puissance();
    return ss.str();
}

Recipient* Pompier::get_recip(){
    return _recip;
}
