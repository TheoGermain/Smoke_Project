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
  for(auto it = Grille::cases_en_feu.begin(); it != Grille::cases_en_feu.end(); it++){
      delete[] *it;
  }
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
  auto v = Grille::cases_en_feu;
  for(const auto& it : v){
      propagation_feu(Milieu::map_coeff_propagation[(*this)(it[0], it[1]).get_revetement()], it[0], it[1]);
    }
}

void Grille::propagation_feu(int coeff_propagation, std::size_t L, std::size_t C){
  propagation_feu_ligne(coeff_propagation, L, C);
  propagation_feu_colonne(coeff_propagation, L, C);
  propagation_feu_diagonaleGD(coeff_propagation, L, C);
  propagation_feu_diagonaleDG(coeff_propagation, L, C);
}

bool Grille::declaration_feu(std::size_t i, std::size_t j){
  int proba_declaration = Milieu::map_proba_feu[(*this)(i,j).get_revetement()];
  if(!proba_declaration)
    return false;
  if(!(rand() % proba_declaration))
    return true;
  return false;
}

void Grille::turn_on_fire(int L, int C){
  (*this)(L,C).set_en_feu(true);
  int *tmp = new int[2];
  tmp[0] = L;
  tmp[1] = C;
  Grille::cases_en_feu.push_back(tmp);
}

void Grille::propagation_feu_ligne(int coeff_propagation, std::size_t L, std::size_t C){
  int min = C - coeff_propagation;
  int max = C + coeff_propagation;
  if(min < 0)
    min = 0;
  if(max >= C_GRILLE)
    max = C_GRILLE - 1;

  for(int i = min; i <= max; i++){
    if(i == C || (*this)(L,i).get_en_feu())
      continue;
    if(declaration_feu(L, i))
      turn_on_fire((int)L,i);
  }
}

void Grille::propagation_feu_colonne(int coeff_propagation, std::size_t L, std::size_t C){
  int min = L - coeff_propagation;
  int max = L + coeff_propagation;
  if(min < 0)
    min = 0;
  if(max >= L_GRILLE)
    max = L_GRILLE - 1;

  for(int i = min; i <= max; i++){
    if(i == L || (*this)(i,C).get_en_feu())
      continue;
    if(declaration_feu(i, C))
      turn_on_fire(i,(int)C);
  }
}

void Grille::propagation_feu_diagonaleGD(int coeff_propagation, std::size_t L, std::size_t C){
  int min_L = L - coeff_propagation + 1;
  int min_C = C - coeff_propagation + 1;
  int max_L = L + coeff_propagation - 1;
  int max_C = C + coeff_propagation - 1;
  if(min_L < 0)
    min_L = 0;
  if(min_C < 0)
    min_C = 0;
  if(max_L >= L_GRILLE)
    max_L = L_GRILLE - 1;
  if(max_C >= C_GRILLE)
    max_C = C_GRILLE - 1;


  while(min_L <= max_L && min_C <= max_C){
    if((min_L == L && min_C == C) || ((*this)(min_L, min_C).get_en_feu())){
      min_L++;
      min_C++;
      continue;
    }
    if(declaration_feu(min_L, min_C))
      turn_on_fire(min_L,min_C);

    min_L++;
    min_C++;
  }
}

void Grille::propagation_feu_diagonaleDG(int coeff_propagation, std::size_t L, std::size_t C){
  int min_L = L - coeff_propagation + 1;
  int min_C = C + coeff_propagation - 1;
  int max_L = L + coeff_propagation - 1;
  int max_C = C - coeff_propagation + 1;
  if(min_L < 0)
    min_L = 0;
  if(min_C >= C_GRILLE)
    min_C = C_GRILLE - 1;
  if(max_L >= L_GRILLE)
    max_L = L_GRILLE - 1;
  if(max_C < 0)
    max_C = 0;

  while(min_L != (max_L+1) && min_C != (max_C-1)){
    if((min_L == L && min_C == C) || ((*this)(min_L, min_C).get_en_feu())){
      min_L++;
      min_C--;
      continue;
    }
    if(declaration_feu(min_L, min_C))
      turn_on_fire(min_L,min_C);

    min_L++;
    min_C--;
  }
}
