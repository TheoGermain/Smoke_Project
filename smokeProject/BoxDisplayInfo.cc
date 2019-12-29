#include "BoxDisplayInfo.hh"

BoxDisplayInfo::BoxDisplayInfo(QWidget *parent) : QDialog(parent){
    _layout = new QVBoxLayout;
    _coordCase = new QLabel;
    _revCase = new QLabel;
    _statusCase = new QLabel;
    _intensiteFeuCase = new QLabel;
    _list = new QListWidget();
    QLabel *_contenu = new QLabel("Contenu de la case :");
    _layout->addWidget(_coordCase);
    _layout->addWidget(_revCase);
    _layout->addWidget(_statusCase);
    _layout->addWidget(_intensiteFeuCase);
    _layout->addWidget(_contenu);
    _layout->addWidget(_list);
    this->setLayout(_layout);

}

BoxDisplayInfo::~BoxDisplayInfo(){}

void BoxDisplayInfo::set_coordCase(std::string str){
    _coordCase->setText(QString::fromStdString(str));
}

void BoxDisplayInfo::set_revCase(std::string str){
    _revCase->setText(QString::fromStdString(str));
}

void BoxDisplayInfo::set_statusCase(std::string str){
    _statusCase->setText(QString::fromStdString(str));
}

void BoxDisplayInfo::set_intensiteFeuCase(std::string str){
    _intensiteFeuCase->setText(QString::fromStdString(str));
}

void BoxDisplayInfo::addItem(QListWidgetItem *item){
    _list->addItem(item);
}

void BoxDisplayInfo::clear(void){
    _list->clear();
}

QListWidget* BoxDisplayInfo::get_list(void){
    return _list;
}

void BoxDisplayInfo::reject(){
    QDialog::reject();
    emit close();
}
