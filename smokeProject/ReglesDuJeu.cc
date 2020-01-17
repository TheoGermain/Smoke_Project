#include "ReglesDuJeu.hh"

void clearLayout(QLayout *);

ReglesDuJeu::ReglesDuJeu(QWidget *parent): QDialog(parent), _state(-1){
    QFont font;
    font.setPixelSize(14);
    setWindowTitle("Règles");
    _mainLayout = new QVBoxLayout();
    _bodyLayout = new QVBoxLayout();
    _buttonLayout = new QHBoxLayout();
    _suivant = new QPushButton("SUIVANT");
    _passer = new QPushButton("PASSER");
    _suivant->setFont(font);
    _passer->setFont(font);
    _titre = new QLabel;
    _buttonLayout->addWidget(_suivant);
    _buttonLayout->addWidget(_passer);
    QFont fnt;
    fnt.setPixelSize(40);
    _titre->setFont(fnt);
    _mainLayout->addWidget(_titre);
    _mainLayout->addLayout(_bodyLayout);
    _mainLayout->addLayout(_buttonLayout);
    changeState();
    this->setLayout(_mainLayout);
    QObject::connect(_passer, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(_suivant, SIGNAL(clicked()), this, SLOT(changeState()));
}

ReglesDuJeu::~ReglesDuJeu(){
    delete _titre;
    delete _mainLayout;
    delete _suivant;
    delete _passer;

    for(auto it : objets){
        delete it;
    }
}

void ReglesDuJeu::changeState(){
    _state++;
    switch(_state){
        case 0 :
            displayStateZero();
        break;
        case 1 :
            displayStateOne();
        break;
        case 2 :
            displayStateTwo();
        break;
        case 3 :
            displayStateThree();
        break;
        case 4 :
            displayStateFour();
        break;
        case 5 :
            displayStateFive();
        break;
        case 6 :
            displayStateSix();
        break;
        default :
            _state = -1;
    }
    if(_state != -1)
        emit resize(_state);
}

void ReglesDuJeu::displayStateZero(void){
    clearLayout(_bodyLayout);
    QFont font;
    font.setPixelSize(14);
    QLabel *body = new QLabel("Avant de commencer la partie, voici les règles du jeu");
    objets.push_back(body);
    body->setFont(font);
    _bodyLayout->addWidget(body);
    _titre->setText("BIENVENU");
}

void ReglesDuJeu::displayStateOne(void){
    QFont font;
    font.setPixelSize(14);
    _titre->setText("PRINCIPE (1/6)");
    clearLayout(_bodyLayout);
    std::stringstream ss;
    ss << "Le but du jeu est d'éteindre toutes les cases en feu, en sauvant un maximum de civils" << std::endl
     << "Si tous les pompiers ou civils meurent, ou si toutes les cases qui ne sont pas en feu sont brulées, vous perdez la partie..." << std::endl;
    QLabel *body = new QLabel(QString::fromStdString(ss.str()));
    objets.push_back(body);
    body->setFont(font);


    // Images
    QLabel *civil = new QLabel;
    objets.push_back(civil);
    QLabel *pompier = new QLabel;
    objets.push_back(pompier);
    QLabel *pompierEnChef = new QLabel;
    objets.push_back(pompierEnChef);
    QHBoxLayout *imgLayout = new QHBoxLayout;
    objets.push_back(imgLayout);
    civil->setPixmap(QPixmap(QApplication::applicationDirPath() + "/imagesFolder/civil.png"));
    pompier->setPixmap(QPixmap(QApplication::applicationDirPath() + "/imagesFolder/pompier.png"));
    pompierEnChef->setPixmap(QPixmap(QApplication::applicationDirPath() + "/imagesFolder/pompier_en_chef.png"));
    imgLayout->addWidget(civil);
    imgLayout->addWidget(pompier);
    imgLayout->addWidget(pompierEnChef);

    // Texts
    QLabel *civilText = new QLabel("Civils");
    objets.push_back(civilText);
    civilText->setFont(font);
    QLabel *pompierText = new QLabel("Pompiers");
    objets.push_back(pompierText);
    pompierText->setFont(font);
    QLabel *pompierEnChefText = new QLabel("Pompiers en Chef");
    objets.push_back(pompierEnChefText);
    pompierEnChefText->setFont(font);
    QHBoxLayout *txtLayout = new QHBoxLayout;
    objets.push_back(txtLayout);
    txtLayout->addWidget(civilText);
    txtLayout->addWidget(pompierText);
    txtLayout->addWidget(pompierEnChefText);

    QLabel *body2 = new QLabel;
    objets.push_back(body2);
    std::stringstream ss2;
    ss2 << std::endl << "Les civils : sont autonomes, ils se déplacent aléatoirement à chaque tour, et meurent au contact du feu."
       << std::endl << std::endl << "Les pompiers : sont déplaçables par le joueur, possèdent un seau ou un extincteur pour éteindre le feu, peuvent conduire les mobylettes et monter dans le camion."
       << std::endl << std::endl << "Les pompiers en chef : sont déplaçables par le joueur, possèdent une puissante lance aux munitions illimitées pour éteindre le feu, peuvent conduire tous les véhicules."
       << std::endl << std::endl << "Les pompiers et pompiers en chef possèdent respectivement 2 et 4 PV, ils en perdent 1 au contact du feu et meurent si ce nombre atteint 0." << std::endl;
    body2->setText(QString::fromStdString(ss2.str()));
    body2->setFont(font);

    _bodyLayout->addWidget(body);
    _bodyLayout->addLayout(imgLayout);
    _bodyLayout->addLayout(txtLayout);
    _bodyLayout->addWidget(body2);

}

void ReglesDuJeu::displayStateTwo(void){
    QFont font;
    font.setPixelSize(14);
    _titre->setText("LES CASES (2/6)");
    clearLayout(_bodyLayout);
    QLabel *body1 = new QLabel("Voici les différents milieux :\n\n");
    objets.push_back(body1);
    body1->setFont(font);

    QHBoxLayout *imgLayout = new QHBoxLayout;
    objets.push_back(imgLayout);
    QLabel *foret = new QLabel;
    objets.push_back(foret);
    foret->setPixmap(QPixmap(QApplication::applicationDirPath() + "/imagesFolder/foret.png"));
    imgLayout->addWidget(foret);
    QLabel *plaine = new QLabel;
    objets.push_back(plaine);
    plaine->setPixmap(QPixmap(QApplication::applicationDirPath() + "/imagesFolder/plaine.png"));
    imgLayout->addWidget(plaine);
    QLabel *ville = new QLabel;
    objets.push_back(ville);
    ville->setPixmap(QPixmap(QApplication::applicationDirPath() + "/imagesFolder/ville.png"));
    imgLayout->addWidget(ville);
    QLabel *usine = new QLabel;
    objets.push_back(usine);
    usine->setPixmap(QPixmap(QApplication::applicationDirPath() + "/imagesFolder/usine.png"));
    imgLayout->addWidget(usine);
    QLabel *eau = new QLabel;
    objets.push_back(eau);
    eau->setPixmap(QPixmap(QApplication::applicationDirPath() + "/imagesFolder/eau.png"));
    imgLayout->addWidget(eau);
    QLabel *feu = new QLabel;
    objets.push_back(feu);
    feu->setPixmap(QPixmap(QApplication::applicationDirPath() + "/imagesFolder/feu.png"));
    imgLayout->addWidget(feu);
    QLabel *brule = new QLabel;
    objets.push_back(brule);
    brule->setPixmap(QPixmap(QApplication::applicationDirPath() + "/imagesFolder/cendre.png"));
    imgLayout->addWidget(brule);

    QHBoxLayout *txtLayout = new QHBoxLayout;
    objets.push_back(txtLayout);
    QLabel *foretTxt = new QLabel("foret");
    objets.push_back(foretTxt);
    foretTxt->setFont(font);
    txtLayout->addWidget(foretTxt);
    QLabel *plaineTxt = new QLabel("plaine");
    objets.push_back(plaineTxt);
    plaineTxt->setFont(font);
    txtLayout->addWidget(plaineTxt);
    QLabel *villeTxt = new QLabel("ville");
    objets.push_back(villeTxt);
    villeTxt->setFont(font);
    txtLayout->addWidget(villeTxt);
    QLabel *usineTxt = new QLabel("usine");
    objets.push_back(usineTxt);
    usineTxt->setFont(font);
    txtLayout->addWidget(usineTxt);
    QLabel *eauTxt = new QLabel("eau");
    objets.push_back(eauTxt);
    eauTxt->setFont(font);
    txtLayout->addWidget(eauTxt);
    QLabel *feuTxt = new QLabel("feu");
    objets.push_back(feuTxt);
    feuTxt->setFont(font);
    txtLayout->addWidget(feuTxt);
    QLabel *bruleTxt = new QLabel("brulé (cendre)");
    objets.push_back(bruleTxt);
    bruleTxt->setFont(font);
    txtLayout->addWidget(bruleTxt);

    QLabel *body2 = new QLabel;
    objets.push_back(body2);
    std::stringstream ss;
    ss << std::endl << std::endl << "Le feu se propage à chaque tour aux cases voisines, plus ou moins rapidemment en fonction du milieu."
       << std::endl << std::endl << "Le feu ne peux pas prendre sur des cases de type eau ou brulé."
       << std::endl << std::endl << "L'intensité du feu dépend du milieu de la case sur laquelle il se trouve."
       << std::endl << std::endl << "Exemple : Pour une case de type foret, le feu aura une intensité de 6, et pourra se propager à chaque tour jusqu'à 2 cases autour." << std::endl;

    body2->setText(QString::fromStdString(ss.str()));
    body2->setFont(font);
    _bodyLayout->addWidget(body1);
    _bodyLayout->addLayout(imgLayout);
    _bodyLayout->addLayout(txtLayout);
    _bodyLayout->addWidget(body2);
}

void ReglesDuJeu::displayStateThree(void){
    QFont font;
    font.setPixelSize(14);
    _titre->setText("LES INFORMATIONS DE CASES (3/6)");
    clearLayout(_bodyLayout);
    QLabel *body1 = new QLabel("Lors d'un clique sur une case, les informations suivantes apparaissent :\n\n");
    objets.push_back(body1);
    body1->setFont(font);
    QLabel *infoCase = new QLabel;
    objets.push_back(infoCase);
    infoCase->setPixmap(QPixmap(QApplication::applicationDirPath() + "/imagesFolder/info_case.png"));
    QLabel *body2 = new QLabel;
    objets.push_back(body2);
    std::stringstream ss;
    ss << std::endl << "Un clique sur un élément de la liste permettra de selectionner un personnage ou un véhicule."
       << std::endl << "Pour un Pompier ou Pompier en Chef, les information correspondent (de gauche à droite) à :"
       << std::endl << "Le nom, le nombre de point de vie, le nombre de 'munitions' restantes, et la puissance d'exctinction (voir après)." << std::endl;
    body2->setText(QString::fromStdString(ss.str()));
    body2->setFont(font);
    _bodyLayout->addWidget(body1);
    _bodyLayout->addWidget(infoCase);
    _bodyLayout->addWidget(body2);
}

void ReglesDuJeu::displayStateFour(void){
    QFont font;
    font.setPixelSize(14);
    _titre->setText("LES ACTIONS (4/6)");
    clearLayout(_bodyLayout);
    QLabel* body1 = new QLabel("Lors d'un clique sur un pompier ou un pompier en chef dans la liste d'une case, plusieurs actions sont possibles.\nLe personnage devient gris s'il à effectué toutes les actions qu'il pouvait faire pendant ce tour.\nChaque tour les personnages peuvent arroser un feu et au choix se déplacer ou monter dans un véhicule.\n");
    objets.push_back(body1);
    body1->setFont(font);

    QHBoxLayout *imgLayout = new QHBoxLayout;
    objets.push_back(imgLayout);
    QLabel *deplacement = new QLabel;
    objets.push_back(deplacement);
    deplacement->setPixmap(QPixmap(QApplication::applicationDirPath() + "/imagesFolder/regles_deplacement.png"));
    imgLayout->addWidget(deplacement);
    QLabel *boutonArroser = new QLabel;
    objets.push_back(boutonArroser);
    boutonArroser->setPixmap(QPixmap(QApplication::applicationDirPath() + "/imagesFolder/regles_arroser.png"));
    imgLayout->addWidget(boutonArroser);
    QLabel *boutonMonterVehicule = new QLabel;
    objets.push_back(boutonMonterVehicule);
    boutonMonterVehicule->setPixmap(QPixmap(QApplication::applicationDirPath() + "/imagesFolder/regles_monter_vehicule.png"));
    imgLayout->addWidget(boutonMonterVehicule);
    QLabel *casesRouges = new QLabel;
    objets.push_back(casesRouges);
    casesRouges->setPixmap(QPixmap(QApplication::applicationDirPath() + "/imagesFolder/regles_cases_rouges.png"));
    imgLayout->addWidget(casesRouges);

    QHBoxLayout *txtLayout = new QHBoxLayout;
    objets.push_back(txtLayout);
    std::stringstream ss;
    ss << "Quand un personnage est selectionné," << std::endl << "sa portée de déplacement se matérialise"
       << std::endl << "avec des cases bleues." << std::endl << "Il suffit alors de cliquer sur une de ces"
       << std::endl << "cases pour déplacer le personnage." << std::endl << "Un seul déplacement est autorisé" << std::endl << "par tour.";
    QLabel* txtDeplacement = new QLabel(QString::fromStdString(ss.str()));
    objets.push_back(txtDeplacement);
    txtDeplacement->setFont(font);
    txtLayout->addWidget(txtDeplacement);
    ss.clear();
    ss.str(std::string());
    ss << "En bas de l'écran, un bouton ARROSER" << std::endl << "apparait si un personnage est selectionné." << std::endl << "En pressant ce bouton, la porter de l'arrosage"
       << std::endl << "est affichée avec des cases bleues comme" << std::endl << "pour le déplacement."
       << std::endl << "Cette portée dépend du contenant du" << std::endl << "personnage (Seau, Extincteur ou Lance)." << std::endl << "Pour arroser une case en feu il suffit alors" << std::endl << "de cliquer sur une case." << std::endl << "Arroser un feu fait diminuer l'intensité du" << std::endl <<"feu du montant de la puissance d'extinction"
       << std::endl << "(Seau : 4, Extincteur : 5, Lance : 6)."
       << std::endl << std::endl << "Arroser une case arrose aussi les cases" << std::endl << "adjacentes (en croix)." << std::endl;
    QLabel* txtArroser = new QLabel(QString::fromStdString(ss.str()));
    objets.push_back(txtArroser);
    txtArroser->setFont(font);
    txtLayout->addWidget(txtArroser);
    ss.clear();
    ss.str(std::string());
    ss << "En plus du bouton arroser, un bouton 'Monter dans un véhicule' s'affiche en bas de l'écran." << std::endl << "Lorsque l'on clique sur ce bouton, les cases de portée deviennent rouge (photo ci-dessus)" << std::endl << "afin d'avertir le joueur qu'il peut maintenant cliquer sur un véhicule à sa portée pour" << std::endl << "embarquer dans ce-dernier.";
    QLabel* txtMonterVehicule = new QLabel(QString::fromStdString(ss.str()));
    objets.push_back(txtMonterVehicule);
    txtMonterVehicule->setFont(font);
    txtLayout->addWidget(txtMonterVehicule);

    _bodyLayout->addWidget(body1);
    _bodyLayout->addLayout(imgLayout);
    _bodyLayout->addLayout(txtLayout);
}

void ReglesDuJeu::displayStateFive(void){
    QFont font;
    font.setPixelSize(14);
    _titre->setText("LES VEHICULES (5/6)");
    clearLayout(_bodyLayout);
    QLabel* body1 = new QLabel("3 Véhicules sont disponibles, 2 mobylettes et 1 camion :\n");
    objets.push_back(body1);
    body1->setFont(font);
    _bodyLayout->addWidget(body1);

    QHBoxLayout* imgLayout = new QHBoxLayout;
    objets.push_back(imgLayout);
    QLabel *mobylette = new QLabel;
    objets.push_back(mobylette);
    mobylette->setPixmap(QPixmap(QApplication::applicationDirPath() + "/imagesFolder/regles_mobylette.png"));
    imgLayout->addWidget(mobylette);
    QLabel *camion = new QLabel;
    objets.push_back(camion);
    camion->setPixmap(QPixmap(QApplication::applicationDirPath() + "/imagesFolder/regles_camion.png"));
    imgLayout->addWidget(camion);
    QLabel *selection_vehicule = new QLabel;
    objets.push_back(selection_vehicule);
    selection_vehicule->setPixmap(QPixmap(QApplication::applicationDirPath() + "/imagesFolder/regles_selection_vehicule.png"));
    imgLayout->addWidget(selection_vehicule);
    QLabel *bouton_conduire = new QLabel;
    objets.push_back(bouton_conduire);
    bouton_conduire->setPixmap(QPixmap(QApplication::applicationDirPath() + "/imagesFolder/regles_bouton_conduire.png"));
    imgLayout->addWidget(bouton_conduire);

    QHBoxLayout* txtLayout = new QHBoxLayout;
    objets.push_back(txtLayout);
    std::stringstream ss;
    ss << "Les mobylettes permettent de se" << std::endl << "déplacer plus rapidemment" << std::endl << "(jusqu'à 7 cases)." << std::endl << "Elles peuvent embarquer jusqu'à" << std::endl << "deux personnages."
       << std::endl << "Pour pouvoir la conduire il faut" << std::endl << "qu'au moins un des passagers" << std::endl << "ne soit pas grisé" << std::endl << "(1 personnage ne peut donc" << std::endl << "pas conduire une mobylette le" << std::endl << "tour où il monte sur cette-dernière)." << std::endl;
    QLabel *mobyletteTxt = new QLabel(QString::fromStdString(ss.str()));
    objets.push_back(mobyletteTxt);
    mobyletteTxt->setFont(font);
    txtLayout->addWidget(mobyletteTxt);
    ss.clear();
    ss.str(std::string());
    ss << "Le camion peut se déplacer encore plus" << std::endl << "rapidement (jusqu'à 12 cases)." << std::endl << "Il peut embarqué jusqu'à 6 passagers."
       << std::endl << "Pour pouvoir le conduire il faut qu'au" << std::endl << "moins" << std::endl << "un passager soit un Pompier en Chef."
       << std::endl << "Un camion peut être conduit dès le" << std::endl <<  "tour où le pompier en chef embarque." << std::endl;
    QLabel *camionTxt = new QLabel(QString::fromStdString(ss.str()));
    objets.push_back(camionTxt);
    camionTxt->setFont(font);
    txtLayout->addWidget(camionTxt);
    ss.clear();
    ss.str(std::string());
    ss << "Lorsque des personnages sont dans un véhicule, ils s'affichent en italique (image ci-dessus)." << std::endl << "Pour déplacer un véhicule, il faut alors le sélectionner dans la liste," << std::endl << "et si les conditions précedentes sont remplies," << std::endl <<  "un bouton CONDUIRE apparaîtra en bas de l'écran."
       << std::endl << "Appuyer sur ce bouton affichera la portée du véhicule," << std::endl << "il suffit alors de cliquer sur une case pour le déplacer." << std::endl;
    QLabel *selectionVehiculeTxt = new QLabel(QString::fromStdString(ss.str()));
    objets.push_back(selectionVehiculeTxt);
    selectionVehiculeTxt->setFont(font);
    txtLayout->addWidget(selectionVehiculeTxt);

    _bodyLayout->addWidget(body1);
    _bodyLayout->addLayout(imgLayout);
    _bodyLayout->addLayout(txtLayout);
}

void ReglesDuJeu::displayStateSix(void){
    QFont font;
    font.setPixelSize(14);
    _titre->setText("LE RECHARGEMENT (6/6)");
    clearLayout(_bodyLayout);
    std::stringstream ss;
    ss << "Lorsque les 'munitions' du récipient d'un personnage est vide, il faut le remplir pour pouvoir arroser de nouveau."
       << std::endl << "Pour cela, les pompiers possédant un seau doivent se trouver à côté d'une case remplie d'eau, "
       << std::endl << "ceux possédant des extincteurs doivent se trouver à côté d'un véhicule."
       << std::endl << "Un bouton REMPLIR apparaît alors en bas de l'écran, appuyer dessus remplira le contenant."
       << std::endl << "Il est possible de remplir le contenant même si ce dernier n'est pas vide." << std::endl;
    QLabel* body = new QLabel(QString::fromStdString(ss.str()));
    objets.push_back(body);
    body->setFont(font);
    _bodyLayout->addWidget(body);
}

void clearLayout(QLayout *layout){
    QLayoutItem *item;
    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
           delete item->widget();
        }
    }
}
