#include "Pompier.hh"

int Pompier::cpt = 0;

Pompier::Pompier(Recipient* recip) : Civil(0, 0, 2, 5), _recip(recip), _deplacementEffectue(false), _arrosageEffectue(false){
    _name = "Pompier_" + std::to_string(cpt++);
}

Pompier::Pompier(int x, int y, Recipient* recip, int pv, int pm) : Civil(x, y, pv, pm), _recip(recip), _deplacementEffectue(false), _arrosageEffectue(false){
    _name = "Pompier_" + std::to_string(cpt++);
}

Pompier::~Pompier(){}

void Pompier::set_deplacementEffectue(bool b){
    _deplacementEffectue = b;
}

void Pompier::set_arrosageEffectue(bool b){
    _arrosageEffectue = b;
}

bool Pompier::get_deplacementEffectue(){
    return _deplacementEffectue;
}

bool Pompier::get_arrosageEffectue(){
    return _arrosageEffectue;
}

std::string Pompier::toString(void){
    std::stringstream ss;
    ss << Civil::toString() << " " << _recip->get_name() << '(' << _recip->get_contenuRestant() << ')' << " : " << _recip->get_puissance();
    return ss.str();
}

Recipient* Pompier::get_recip(){
    return _recip;
}
