#include "MessageBox.hh"

MessageBox::MessageBox(QWidget *parent):QDialog(parent){
    setFixedSize(310, 200);
    QVBoxLayout* layout = new QVBoxLayout();
    QHBoxLayout* layoutBoutons = new QHBoxLayout();
    _msgPrincipal = new QLabel(this);
    _msgSecondaire = new QLabel(this);
    layout->addWidget(_msgPrincipal);
    layout->addWidget(_msgSecondaire);
    _rejouer = new QPushButton("REJOUER");
    _quitter = new QPushButton("QUITTER");
    layoutBoutons->addWidget(_rejouer);
    layoutBoutons->addWidget(_quitter);
    layout->addLayout(layoutBoutons);
    QObject::connect(_rejouer, SIGNAL(clicked()), this, SLOT(rejouerClicked()));
    QObject::connect(_quitter, SIGNAL(clicked()), this, SLOT(quitterClicked()));
    this->setLayout(layout);
}

MessageBox::~MessageBox(){
}

void MessageBox::set_msgPrincipal(std::string str)
{
    _msgPrincipal->setText(QString::fromStdString(str));
    QFont font;
    font.setPixelSize(30);
    _msgPrincipal->setFont(font);
}

void MessageBox::set_msgSecondaire(std::string str)
{
    _msgSecondaire->setText(QString::fromStdString(str));
}

void MessageBox::rejouerClicked(){
    emit rejouer();
}

void MessageBox::quitterClicked(){
    emit quitter();
}
