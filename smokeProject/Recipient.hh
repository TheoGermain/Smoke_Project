#pragma once
#include <string>

class Recipient{

public:
    Recipient(int puissance, int contenu, int portee, std::string name) : _puissance(puissance), _contenuRestant(contenu), _portee(portee), _name(name){}
    virtual ~Recipient(){};
    int get_puissance(void){if(!_contenuRestant){return 0;} else{return _puissance;}}
    int get_contenuRestant(void){return _contenuRestant;}
    int get_portee(void){return _portee;}
    std::string get_name(void){return _name;}
    void decrement_contenuRestant(void){_contenuRestant--;}

private:
    std::string _name;
    int _puissance;
    int _contenuRestant;
    int _portee;
};


class Seau : public Recipient{
public:
    Seau() : Recipient(2, 10, 3, "Seau"){}
    ~Seau(){};
};

class Extincteur : public Recipient{
public:
    Extincteur() : Recipient(4, 15, 4, "Extincteur"){}
    ~Extincteur(){};
};

class Lance : public Recipient{
public:
    Lance() : Recipient(6, 9999, 5, "Lance"){}
    ~Lance(){};
};
