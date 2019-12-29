#include "Pompier.hh"

int Pompier::cpt = 0;

Pompier::Pompier() : Civil(0, 0, 2, 5), _deplacementEffectue(false){
    _name = "Pompier_" + std::to_string(cpt++);
}

Pompier::Pompier(int x, int y, int pv, int pm) : Civil(x, y, pv, pm), _deplacementEffectue(false){
    _name = "Pompier_" + std::to_string(cpt++);
}

Pompier::~Pompier(){}

void Pompier::set_deplacementEffectue(bool b){
    _deplacementEffectue = b;
}

bool Pompier::get_deplacementEffectue(){
    return _deplacementEffectue;
}
