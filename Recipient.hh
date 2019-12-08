#pragma once
#include "Milieu.hh"

class Recipient {
public:
  Recipient(int r);
  virtual ~Recipient();
  void arroser(Milieu& m);

private:
  int _contenant;
};
