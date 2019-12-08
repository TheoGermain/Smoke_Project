#include "Grille.hh"
#include <time.h>
#include <iostream>

std::vector<int*> Grille::cases_en_feu;

Grille::Grille(){
  plateau = new Milieu*[L_GRILLE];
  for(std::size_t i = 0; i < L_GRILLE; i++)
    plateau[i] = new Milieu[C_GRILLE];
}

Grille::~Grille(){
  for(std::size_t i = 0; i < L_GRILLE; i++)
    delete[] plateau[i];
  delete[] plateau;
}

Milieu Grille::operator()(std::size_t L, std::size_t C) const{
  return plateau[L][C];
}

Milieu& Grille::operator()(std::size_t L, std::size_t C){
  return plateau[L][C];
}


std::ostream& operator<<(std::ostream& out, const Grille& g){
  for(std::size_t i = 0; i < L_GRILLE; i++){
    for(std::size_t j = 0; j < C_GRILLE; j++){
      out << g(i,j) << '\t';
    }
    out << std::endl;
  }
  return out;
}

void Grille::propagation(){
  for(const auto& it : Grille::cases_en_feu){
    if((*this)(it[0],it[1]).get_en_feu()){
      propagation_feu(Milieu::map_coeff_propagation[(*this)(it[0],it[1]).get_revetement()], it[0], it[1]);
    }
  }
}

/// A REVOIR
void Grille::propagation_feu(int coeff_propagation, std::size_t L, std::size_t C){
  if(L - coeff_propagation >= 0 && L + coeff_propagation < L_GRILLE && C - coeff_propagation >= 0 && C + coeff_propagation < C_GRILLE){
    for(std::size_t i = L - coeff_propagation + 1; i < L + coeff_propagation; i++){
      for(std::size_t j = C - coeff_propagation; j <= C + coeff_propagation; j++){
        if(i == L && j == C)
          continue;
        if(declaration_feu(i,j)) {
          (*this)(i,j).set_en_feu(true);
          int t[2] = {(int)i,(int)j};// modif
          Grille::cases_en_feu.push_back(t);//mise à jour de case en feu
        }
      }
    }
  }
}

bool Grille::declaration_feu(std::size_t i, std::size_t j){
  int proba_declaration = Milieu::map_proba_feu[(*this)(i,j).get_revetement()];
  if(!proba_declaration)
    return false;
  if(!(rand() % proba_declaration)) //(proba_declaration-1)/proba_declaration chance que ça soit true
    return true;
  return false;
}
