#include "MessageBox.hh"

MessageBox::MessageBox(QWidget *parent):QDialog(parent){
    QFont font;
    font.setPixelSize(14);
    setFixedSize(350, 200);
    setWindowTitle("Message");
    QVBoxLayout* layout = new QVBoxLayout();
    QHBoxLayout* layoutBoutons = new QHBoxLayout();
    _msgPrincipal = new QLabel(this);
    _msgSecondaire = new QLabel(this);
    _msgPrincipal->setFont(font);
    _msgSecondaire->setFont(font);
    layout->addWidget(_msgPrincipal);
    layout->addWidget(_msgSecondaire);
    _rejouer = new QPushButton("REJOUER");
    _quitter = new QPushButton("QUITTER");
    _rejouer->setFont(font);
    _quitter->setFont(font);
    layoutBoutons->addWidget(_rejouer);
    layoutBoutons->addWidget(_quitter);
    layout->addLayout(layoutBoutons);
    QObject::connect(_rejouer, SIGNAL(clicked()), this, SLOT(rejouerClicked()));
    QObject::connect(_quitter, SIGNAL(clicked()), this, SLOT(quitterClicked()));
    this->setLayout(layout);
}

MessageBox::~MessageBox(){
    delete _msgPrincipal;
    delete _msgSecondaire;
    delete _rejouer;
    delete _quitter;
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
