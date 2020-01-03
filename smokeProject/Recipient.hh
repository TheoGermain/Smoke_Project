#pragma once
#include <string>

class Recipient{

public:
    Recipient(int puissance, int contenu, int portee, std::string name) :_name(name), _puissance(puissance), _contenuRestant(contenu), _portee(portee), _contenuMax(contenu){}
    virtual ~Recipient(){};
    int get_puissance(void) const {if(!_contenuRestant){return 0;} else{return _puissance;}}
    int get_contenuRestant(void) const {return _contenuRestant;}
    int get_portee(void) const {return _portee;}
    int get_contenuMax(void) const {return _contenuMax;}
    std::string get_name(void){return _name;}
    void decrement_contenuRestant(void){_contenuRestant--;}
    void set_contenuRestant(int val){_contenuRestant = val;}

protected:
    std::string _name;
    int _puissance;
    int _contenuRestant;
    int _portee;
    const int _contenuMax;
};


class Seau : public Recipient{
public:
    Seau() : Recipient(4, 10, 3, "Seau"){}
    ~Seau(){};
};

class Extincteur : public Recipient{
public:
    Extincteur() : Recipient(5, 15, 4, "Extincteur"){}
    ~Extincteur(){};
};

class Lance : public Recipient{
public:
    Lance() : Recipient(6, 99999, 5, "Lance"){}
    ~Lance(){};
};
