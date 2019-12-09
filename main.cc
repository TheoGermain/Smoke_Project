#include <iostream>
#include <vector>
#include "Grille.hh"
#include "Civil.hh"
#include "Recipient.hh"
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
  // Grille test;
  // //std::cout << test << std::endl;
  // //test(4,2).set_revetement(NSRevetement::foret);
  // test.turn_on_fire(4,2);
  //
  // std::cout << test << std::endl << Grille::cases_en_feu.size() << std::endl;
  // test.propagation();
  // std::cout << test << std::endl << Grille::cases_en_feu.size() << std::endl;
  // test.propagation();
  // std::cout << test << std::endl << Grille::cases_en_feu.size() << std::endl;
  // // test.propagation();
  // // test.propagation();
  // // test.propagation();
  // // test.propagation();
  // test.turn_off_fire(4,2);
  // std::cout << test << std::endl << Grille::cases_en_feu.size() << std::endl;

  std::cout<<"test Civil"<<std::endl;
  Civil a;
  std::vector<int> temp = a.get_pos();
  //std::cout << temp[0] << "," << temp[1] << std::endl;
  std::cout << a << std::endl;
  Civil b = Civil(100,4,2,2);
  std::cout << b << std::endl;
  std::cout<<b.deplacer(3,3)<<std::endl;
  std::cout<<b.deplacer(5,9)<<std::endl;
  std::cout<<b.deplacer(26,19)<<std::endl;
  std::cout << b << std::endl;
  std::vector<int> temp2 = b.get_pos();

    std::cout<<"test Recipient"<<std::endl;
    Recipient r = Recipient(5);
    r.arroser(test(4,2));
    std::cout << test << std::endl << Grille::cases_en_feu.size() << std::endl;
    r.arroser(test(4,2));//La fonction cases_en_feu ne met pas à jours cases_en_feu
    std::cout << test << std::endl << Grille::cases_en_feu.size() << std::endl;
}
