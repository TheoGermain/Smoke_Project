#include "Recipient.hh"

Recipient::Recipient(int r): _contenant(r){}
Recipient::~Recipient(){}

 void Recipient::arroser(Milieu& m){ //mettre à jour Grille en feu
  m.set_fire(m.get_fire()-_contenant);
  if( m.get_fire()<= 0){
      m.set_fire(0);
    m.set_en_feu(false);
  }
}
