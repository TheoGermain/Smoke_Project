#include <iostream>
#include <vector>
#include "Grille.hh"

using namespace NSRevetement;

std::ostream& operator<<(std::ostream& out, const NSRevetement::Revetement& r){
  switch (r){
    case foret:
      return out << "foret";
    case plaine:
      return out << "plaine";
    case eau:
      return out << "eau";
    case ville:
      return out << "ville";
    case usine:
      return out << "usine";
    case brule:
      return out << "brulé";
    default :
      return out;
  }
}

int main(){
  srand (time (NULL));
  Grille test;
  std::cout << test << std::endl;
  test(4,2).set_revetement(NSRevetement::foret);
  test(4,2).set_en_feu(true);
  int t[2] = {4,2};
  Grille::cases_en_feu.push_back(t);
  std::cout << std::endl << Grille::cases_en_feu[0][0] << ',' << Grille::cases_en_feu[0][1] << std::endl;
  std::cout << test << std::endl << Grille::cases_en_feu.size() << std::endl;
  test.propagation();
  std::cout << test << std::endl << Grille::cases_en_feu.size() << std::endl;
}
