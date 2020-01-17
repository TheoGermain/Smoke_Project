#include "BoxDisplayInfo.hh"

BoxDisplayInfo::BoxDisplayInfo(QWidget *parent) : QDialog(parent){
    QFont font;
    font.setPixelSize(14);
    setWindowTitle("Info Case");
    _layout = new QVBoxLayout;
    _coordCase = new QLabel;
    _coordCase->setFont(font);
    _revCase = new QLabel;
    _revCase->setFont(font);
    _statusCase = new QLabel;
    _statusCase->setFont(font);
    _intensiteFeuCase = new QLabel;
    _intensiteFeuCase->setFont(font);
    _list = new QListWidget();
    QLabel *_contenu = new QLabel("Contenu de la case :");
    _contenu->setFont(font);
    _layout->addWidget(_coordCase);
    _layout->addWidget(_revCase);
    _layout->addWidget(_statusCase);
    _layout->addWidget(_intensiteFeuCase);
    _layout->addWidget(_contenu);
    _layout->addWidget(_list);
    this->setLayout(_layout);
}

BoxDisplayInfo::~BoxDisplayInfo(){
    delete _layout;
    delete _coordCase;
    delete _revCase;
    delete _statusCase;
    delete _intensiteFeuCase;
    delete _list;
}

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
