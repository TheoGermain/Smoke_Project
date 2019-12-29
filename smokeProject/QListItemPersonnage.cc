#include "QListItemPersonnage.hh"


QListItemPersonnage::QListItemPersonnage(Civil*c, QListWidget *parent, int type) : QListWidgetItem(QString::fromStdString(c->toString()), parent, type), _c(c){

}

QListItemPersonnage::~QListItemPersonnage(){}

Civil* QListItemPersonnage::get_civil(void){
    return _c;
}
