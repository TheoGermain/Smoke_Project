#pragma once
#include <vector>
#include <string>
#include "Pompier.hh"

class Vehicule{

public:
    Vehicule(std::string, int, int);
    ~Vehicule();

    std::string get_name(void) const;
    size_t get_deplacementMax(void) const;
    size_t get_capaciteMax(void) const;
    std::string toString(void) const;
    void ajouterPassager(Pompier*);
    void supprimerPassager(Pompier*);
    std::vector<Pompier*> get_passagers(void);
    void set_pos(int, int);
    std::vector<int> get_pos(void);
    bool get_deplacementEffectue(void);
    void set_deplacementEffectue(bool);

protected:
    size_t _capaciteMax;
    size_t _deplacementMax;
    std::string _name;
    std::vector<Pompier*> _passagers;
    std::vector<int> _pos;
    bool _deplacementEffectue;
};


class Camion : public Vehicule{
public:
    Camion():Vehicule("Camion", 12, 6){}
};

class Mobylette : public Vehicule{
public:
    Mobylette():Vehicule("Mobylette", 7, 2){}
};
