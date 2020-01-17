#include "QListItemVehicule.hh"


QListItemVehicule::QListItemVehicule(Vehicule *v, QListWidget *parent, int type) : QListWidgetItem(QString::fromStdString(v->toString()), parent, type), _v(v){

}

QListItemVehicule::~QListItemVehicule(){
    delete _v;
}

Vehicule* QListItemVehicule::get_vehicule(void){
    return _v;
}
