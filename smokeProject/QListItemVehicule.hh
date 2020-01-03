#pragma once
#include<QListWidgetItem>
#include "Vehicule.hh"

class QListItemVehicule : public QListWidgetItem{

public:
    QListItemVehicule(Vehicule*, QListWidget *parent = nullptr, int type = Type);
    ~QListItemVehicule();

    Vehicule* get_vehicule(void);

private:
    Vehicule *_v;
};
