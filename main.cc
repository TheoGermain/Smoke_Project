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
  //std::cout << test << std::endl;
  //test(4,2).set_revetement(NSRevetement::foret);
  test.turn_on_fire(4,2);

  std::cout << test << std::endl << Grille::cases_en_feu.size() << std::endl;
  test.propagation();
  std::cout << test << std::endl << Grille::cases_en_feu.size() << std::endl;
  test.propagation();
  std::cout << test << std::endl << Grille::cases_en_feu.size() << std::endl;
  test.propagation();
  test.propagation();
  test.propagation();
  test.propagation();
  std::cout << test << std::endl << Grille::cases_en_feu.size() << std::endl;
}
