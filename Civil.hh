#pragma once

class Civil{

public :
  Civil();
  virtual ~Civil();


protected :
  std::string _name;
  int _pdv;
  int _pdm;
  int pos[2];
};
