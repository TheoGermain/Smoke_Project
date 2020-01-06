#include "Grille.hh"

bool flag_rejouer = false;
bool flag_deplacement = false;
bool flag_arroser = false;
bool flag_monterVehicule = false;
bool flag_conduire = false;
int nbCivilMort = 0;
int nbTour = -1;
int nbCaseBrule = 0;
int nbPompier = DEPART_POMPIER;
std::pair<Civil*, ClickableLabel*> currentlySelected;
std::pair<Vehicule*, ClickableLabel*> currentlySelectedVehicule;

std::vector<int*> Grille::cases_en_feu;

Grille::Grille() : _imgFeu(L_GRILLE, std::vector<ClickableLabel*>()), _imgAction(L_GRILLE, std::vector<ClickableLabel*>()), _civilList(DEPART_CIVIL), _pompierList(DEPART_POMPIER), _vehiculeList(DEPART_VEHICULE){
  flag_rejouer = false;
  int pos_l = 0;
  int pos_c = 0;
  std::string path = QApplication::applicationDirPath().toUtf8().constData();
  std::cout << path << std::endl;
  setFixedSize(1400, 820);

  // Afficher un message
  _msg = new MessageBox(this);

  // Plateau
  plateau = new Milieu*[L_GRILLE];
  for(std::size_t j = 0; j < L_GRILLE; j++)
    plateau[j] = new Milieu[C_GRILLE];

  // MAP
  _map = new ClickableLabel(this);
  _map->setPixmap(QPixmap(QApplication::applicationDirPath() + "/imagesFolder/map1.png"));
  std::ifstream mapDescriptor(path + "/imagesFolder/mapDescriptor.txt");

  initSymboles();
  initListes();
  initBoutons();

  // Initialisation du plateau grace au map descriptor
  while(!mapDescriptor.eof()){
    int i;
    char c;
    char str_tmp[5];
    NSRevetement::Revetement rev;
    mapDescriptor >> str_tmp;
    sscanf(str_tmp, "%c", &c);
    mapDescriptor >> str_tmp;
    sscanf(str_tmp, "%d", &i);

    switch(c){
        case 'F':
            rev = NSRevetement::foret;
        break;
        case 'P':
            rev = NSRevetement::plaine;
        break;
        case 'E':
            rev = NSRevetement::eau;
        break;
        case 'V':
            rev = NSRevetement::ville;
        break;
        case 'U':
            rev = NSRevetement::usine;
        break;
        default:
            rev = NSRevetement::brule;
    }
    for(int j = pos_c; j < pos_c + i; j++)
        plateau[pos_l][j].set_revetement(rev);

    pos_c += i;
    if(pos_c == C_GRILLE){
        pos_c = 0;
        pos_l++;
    }
  }
  affichageNombres();

  // Fenetre pour l'affichage des informations d'une case
  _fenetreInfoCase = new BoxDisplayInfo(this);

  // Affichages règles du jeu
  _regles = new ReglesDuJeu(this);

  connexionSignaux();
}

Grille::~Grille(){
  for(std::size_t i = 0; i < L_GRILLE; i++)
    delete[] plateau[i];
  delete[] plateau;
  for(auto it = Grille::cases_en_feu.begin(); it != Grille::cases_en_feu.end(); it++){
      delete[] *it;
  }
}

Milieu Grille::operator()(std::size_t L, std::size_t C) const{
  return plateau[L][C];
}

Milieu& Grille::operator()(std::size_t L, std::size_t C){
  return plateau[L][C];
}

std::ostream& operator<<(std::ostream& out, const Grille& g){
  for(std::size_t i = 0; i < L_GRILLE; i++){
    for(std::size_t j = 0; j < C_GRILLE; j++){
      out << g(i,j) << '\t';
    }
    out << std::endl;
  }
  return out;
}

void Grille::propagation(){
  auto v = Grille::cases_en_feu;
  for(const auto& it : v){
      propagation_feu(Milieu::map_coeff_propagation[(*this)(it[0], it[1]).get_revetement()], it[0], it[1]);
    }
}

void Grille::propagation_feu(int coeff_propagation, std::size_t L, std::size_t C){
  propagation_feu_ligne(coeff_propagation, L, C);
  propagation_feu_colonne(coeff_propagation, L, C);
  propagation_feu_diagonaleGD(coeff_propagation, L, C);
  propagation_feu_diagonaleDG(coeff_propagation, L, C);
}

bool Grille::declaration_feu(std::size_t i, std::size_t j){
  int proba_declaration = Milieu::map_proba_feu[(*this)(i,j).get_revetement()];
  if(!proba_declaration)
    return false;
  if(!(rand() % proba_declaration)) // 1 chance /proba_declaration que ça soit true
    return true;
  return false;
}

void Grille::turn_on_fire(int L, int C){
  (*this)(L,C).set_en_feu(true);
  int *tmp = new int[2];
  tmp[0] = L;
  tmp[1] = C;
  Grille::cases_en_feu.push_back(tmp);
  _imgFeu[L][C]->setVisible(true);
}

void Grille::turn_off_fire(int L, int C){
  (*this)(L,C).set_en_feu(false);
  (*this)(L,C).set_revetement(NSRevetement::brule);
  for(auto it = Grille::cases_en_feu.begin(); it != Grille::cases_en_feu.end(); it++){
    if(((*it)[0] == L) && ((*it)[1] == C)){
      Grille::cases_en_feu.erase(it);
      break;
    }
  }
  _nbFeu->setText(QString::fromStdString(std::to_string(cases_en_feu.size())));
}

void Grille::propagation_feu_ligne(int coeff_propagation, std::size_t L, std::size_t C){
  int min = C - coeff_propagation;
  int max = C + coeff_propagation;
  if(min < 0)
    min = 0;
  if(max >= C_GRILLE)
    max = C_GRILLE - 1;

  for(int i = min; i <= max; i++){
    if((size_t)i == C || (*this)(L,i).get_en_feu())
      continue;
    if(declaration_feu(L, i))
      turn_on_fire((int)L,i);
  }
}

void Grille::propagation_feu_colonne(int coeff_propagation, std::size_t L, std::size_t C){
  int min = L - coeff_propagation;
  int max = L + coeff_propagation;
  if(min < 0)
    min = 0;
  if(max >= L_GRILLE)
    max = L_GRILLE - 1;

  for(int i = min; i <= max; i++){
    if((size_t)i == L || (*this)(i,C).get_en_feu())
      continue;
    if(declaration_feu(i, C))
      turn_on_fire(i,(int)C);
  }
}

void Grille::propagation_feu_diagonaleGD(int coeff_propagation, std::size_t L, std::size_t C){
  int min_L = L - coeff_propagation + 1;
  int min_C = C - coeff_propagation + 1;
  int max_L = L + coeff_propagation - 1;
  int max_C = C + coeff_propagation - 1;
  if(min_L < 0)
    min_L = 0;
  if(min_C < 0)
    min_C = 0;
  if(max_L >= L_GRILLE)
    max_L = L_GRILLE - 1;
  if(max_C >= C_GRILLE)
    max_C = C_GRILLE - 1;
  while(min_L <= max_L && min_C <= max_C){
    if(((size_t)min_L == L && (size_t)min_C == C) || ((*this)(min_L, min_C).get_en_feu())){
      min_L++;
      min_C++;
      continue;
    }
    if(declaration_feu(min_L, min_C))
      turn_on_fire(min_L,min_C);

    min_L++;
    min_C++;
  }
}

void Grille::propagation_feu_diagonaleDG(int coeff_propagation, std::size_t L, std::size_t C){
  int min_L = L - coeff_propagation + 1;
  int min_C = C + coeff_propagation - 1;
  int max_L = L + coeff_propagation - 1;
  int max_C = C - coeff_propagation + 1;
  if(min_L < 0)
    min_L = 0;
  if(min_C >= C_GRILLE)
    min_C = C_GRILLE - 1;
  if(max_L >= L_GRILLE)
    max_L = L_GRILLE - 1;
  if(max_C < 0)
    max_C = 0;

  while(min_L != (max_L+1) && min_C != (max_C-1)){
    if(((size_t)min_L == L && (size_t)min_C == C) || ((*this)(min_L, min_C).get_en_feu())){
      min_L++;
      min_C--;
      continue;
    }
    if(declaration_feu(min_L, min_C))
      turn_on_fire(min_L, min_C);

    min_L++;
    min_C--;
  }
}

void Grille::boxClicked(int L, int C){
    Pompier *p;
    p = static_cast<Pompier*>(currentlySelected.first);
    if(flag_conduire){
        conduire(L,C);
    }
    else if(flag_deplacement){
        if(_imgAction[L][C]->isVisible()){
            deplacer_personnage(currentlySelected.first->get_pos(), C, L, &currentlySelected);
            flag_deplacement = false;
            _monterVehicule->setVisible(false);
            if(p != NULL)
                p->set_deplacementEffectue(true);
        }
    }
    else if(flag_arroser){
        arroser(L,C,p);
    }
    else if(flag_monterVehicule){
        if(_imgAction[L][C]->isVisible() && !plateau[L][C].get_vehicules().empty() && (plateau[L][C].get_vehicules()[0]->get_passagers().size() < plateau[L][C].get_vehicules()[0]->get_capaciteMax())){
            deplacer_personnage(currentlySelected.first->get_pos(), C, L, &currentlySelected);
            p->set_dansUnVehicule(true);
            plateau[L][C].get_vehicules()[0]->ajouterPassager(p);
            p->set_arrosageEffectue(true);
            p->set_deplacementEffectue(true);
        }
    }
    if(p != NULL && p->get_arrosageEffectue() && p->get_deplacementEffectue()){
        if(dynamic_cast<PompierEnChef*>(currentlySelected.first))
            currentlySelected.second->setPixmap(QApplication::applicationDirPath() + "/imagesFolder/pompier_en_chef_fini.png");
        else
            currentlySelected.second->setPixmap(QApplication::applicationDirPath() + "/imagesFolder/pompier_fini.png");
    }
    fillFenetreInfoCase(L,C);
    emit displayInfo();
    cleanPossibilities();

}

void Grille::gameStart(){
    nbTour = 0;
    _start->setVisible(false);
    _nextTurn->setVisible(true);
    _nbCivil->setVisible(true);
    _nbPompier->setVisible(true);
    _afficherRegles->setVisible(false);

    // Initialisation des cases en feu
    initCaseFeu();

    // Initialisation des civils
    initCivils();

    // Initialisation des pompiers
    initPompiers();

    // Initialisation des véhicules
    initVehicules();
}

void Grille::tourSuivant(){
    nbTour++;
    propagation();
    for(auto &it : _vehiculeList){
        it.first->set_deplacementEffectue(false);
        if(plateau[it.first->get_pos()[1]][it.first->get_pos()[0]].get_en_feu() && it.second->isVisible()){
            it.second->setVisible(false);
            plateau[it.first->get_pos()[1]][it.first->get_pos()[0]].supprimerVehicule(it.first);
            for(auto &it2 : it.first->get_passagers())
                it2->set_pdv(1);
        }
    }
    baisse_pdv();
    if(nbCivilMort != DEPART_CIVIL)
        deplacement_civils();
    _nbFeu->setText(QString::fromStdString(std::to_string(cases_en_feu.size())));
    for(auto &it : _pompierList){
        if(it.first->get_pdv() <= 0)
            continue;
        it.first->set_deplacementEffectue(false);
        if(it.first->get_recip()->get_contenuRestant() != 0)
            it.first->set_arrosageEffectue(false);
        it.second->setPixmap(QApplication::applicationDirPath() + "/imagesFolder/pompier.png");
        if(dynamic_cast<PompierEnChef*>(it.first))
            it.second->setPixmap(QApplication::applicationDirPath() + "/imagesFolder/pompier_en_chef.png");
    }
    if(nbCivilMort == DEPART_CIVIL || nbPompier == 0 || (nbCaseBrule + cases_en_feu.size() == 808))
        msgPerdu();
    else if(cases_en_feu.empty())
        msgGagne();
}

void Grille::deplacement_civils(void){
    for(auto it = _civilList.begin(); it != _civilList.end(); it++){
        int direction;
        int deplacement;
        bool ok;
        int x, y;
        int nb_boucle = 0;
        do{
            nb_boucle++;
            ok = false;
            direction = rand() % 8;
            deplacement = rand() % (it->first->get_pdm() + 1);
            it->first->calcul_dest(direction, deplacement, x, y);
            if(x >= C_GRILLE)
                x = C_GRILLE - 1;
            else if(x < 0)
                x = 0;
            if(y >= L_GRILLE)
                y = L_GRILLE - 1;
            else if(y < 0)
                y = 0;

            if((plateau[y][x].get_revetement() != NSRevetement::eau) && ((!plateau[y][x].get_en_feu()) || (nb_boucle >= 1000))){
                nb_boucle = 0;
                ok = true;
            }

        }while(!ok);
        deplacer_personnage(it->first->get_pos(), x, y, &(*it));
    }
}

void Grille::deplacer_personnage(std::vector<int> former_pos, int new_x, int new_y, std::pair<Civil*, ClickableLabel*> *c){
    plateau[former_pos[1]][former_pos[0]].supprimerPersonnage(c->first);
    plateau[new_y][new_x].ajouterPersonnage(c->first);
    c->first->set_pos(new_x, new_y);
    c->second->move(new_x*PIX_CASE, new_y*PIX_CASE);
}

void Grille::deplacer_vehicule(std::vector<int> former_pos, int new_x, int new_y, std::pair<Vehicule*, ClickableLabel*> *c){
    plateau[former_pos[1]][former_pos[0]].supprimerVehicule(c->first);
    plateau[new_y][new_x].ajouterVehicule(c->first);
    c->first->set_pos(new_x, new_y);
    c->second->move(new_x*PIX_CASE, new_y*PIX_CASE);
}

void Grille::baisse_pdv(){
    for(auto it = _civilList.begin(); it != _civilList.end(); it++){
        if(it->first->get_pdv() == 0)
            continue;
        std::vector<int> v_tmp = it->first->get_pos();
        if(plateau[v_tmp[1]][v_tmp[0]].get_fire()){
            nbCivilMort++;
            _nbCivil->setText(QString::fromStdString(std::to_string(DEPART_CIVIL - nbCivilMort)));
            it->first->set_pdv(0);
            it->second->setVisible(false);
        }
    }
    for(auto it = _pompierList.begin(); it != _pompierList.end(); it++){
        if(it->first->get_pdv() == 0)
            continue;
        if(plateau[it->first->get_pos()[1]][it->first->get_pos()[0]].get_fire()){
            it->first->set_pdv(it->first->get_pdv() - 1);
            if(it->first->get_pdv() == 0){
                nbPompier--;
                it->second->setVisible(false);
            }
        }
    }
    _nbPompier->setText(QString::fromStdString(std::to_string(nbPompier)));
}

void Grille::displayActions(QListWidgetItem *item){
    cleanPossibilities();
    _nextTurn->setVisible(false);
    if(QListItemPersonnage *item_tmp = dynamic_cast<QListItemPersonnage*>(item)){
        if(Pompier *p = dynamic_cast<Pompier*>(item_tmp->get_civil())){
            for(auto &it : _pompierList){
                if(it.first == p){
                    currentlySelected.first = it.first;
                    currentlySelected.second = it.second;
                    break;
                }
            }
            displayActionsPersonnages(p);
        }
    }
    else if(QListItemVehicule *item_tmp = dynamic_cast<QListItemVehicule*>(item)){
        Vehicule* v = item_tmp->get_vehicule();
        for(const auto &it : _vehiculeList){
            if(it.first == v){
                currentlySelectedVehicule = it;
                break;
            }
        }
        displayActionsVehicules(v);
    }
}

void Grille::displayPossibilities(std::vector<int> pos, int portee, bool vehicule){
    int n = portee;
    for(int i = (pos[1] - portee); i <= (pos[1] + portee); i++){
        for(int j = (pos[0] - portee + n); j < (pos[0] + portee - n + 1); j++){
            if(i == pos[1] && j == pos[0])
                continue;
            else if(i >= 0 && i < L_GRILLE && j >= 0 && j < C_GRILLE && plateau[i][j].get_revetement() != NSRevetement::eau){
                if(vehicule)
                    _imgAction[i][j]->setPixmap(QApplication::applicationDirPath() + "/imagesFolder/action_vehicule.png");
                _imgAction[i][j]->setVisible(true);
            }
        }
        if(i < pos[1])
            n--;
        else
            n++;
    }
}

void Grille::cleanPossibilities(void){
    flag_arroser = false;
    flag_deplacement = false;
    flag_monterVehicule = false;
    flag_conduire = false;
    _conduire->setVisible(false);
    _arroser->setVisible(false);
    _monterVehicule->setVisible(false);
    _descendreVehicule->setVisible(false);
    _remplir->setVisible(false);
    for(auto &it : _imgAction){
        for(auto &it2 : it){
            it2->setVisible(false);
            it2->setPixmap(QApplication::applicationDirPath() + "/imagesFolder/action.png");
        }
    }
}

void Grille::displayNextTurn(){
    if(nbTour >= 0)
        _nextTurn->setVisible(true);
}

void Grille::afficherPorteeArrosage(){
    cleanPossibilities();
    _arroser->setVisible(false);
    flag_arroser = true;
    flag_deplacement = false;
    displayPossibilities(currentlySelected.first->get_pos(), dynamic_cast<Pompier*>(currentlySelected.first)->get_recip()->get_portee(), false);
}

void Grille::monterVehiculePressed(void){
    flag_monterVehicule = true;
    flag_arroser = false;
    flag_deplacement = false;
    _arroser->setVisible(false);
    _monterVehicule->setVisible(false);
    displayPossibilities(currentlySelected.first->get_pos(), dynamic_cast<Pompier*>(currentlySelected.first)->get_pdm(), true);
}

void Grille::descendreVehiculePressed(void){
    _descendreVehicule->setVisible(false);
    flag_deplacement = true;
    dynamic_cast<Pompier*>(currentlySelected.first)->set_dansUnVehicule(false);
    plateau[currentlySelected.first->get_pos()[1]][currentlySelected.first->get_pos()[0]].get_vehicules()[0]->supprimerPassager(dynamic_cast<Pompier*>(currentlySelected.first));
    displayPossibilities(currentlySelected.first->get_pos(), dynamic_cast<Pompier*>(currentlySelected.first)->get_pdm(), false);
}

void Grille::conduirePressed(void){
    _conduire->setVisible(false);
    _nextTurn->setVisible(false);
    displayPossibilities(currentlySelectedVehicule.first->get_pos(), currentlySelectedVehicule.first->get_deplacementMax(), false);
    flag_conduire = true;
}

void Grille::remplirPressed(void){
    _remplir->setVisible(false);
    dynamic_cast<Pompier*>(currentlySelected.first)->get_recip()->set_contenuRestant(dynamic_cast<Pompier*>(currentlySelected.first)->get_recip()->get_contenuMax());
    fillFenetreInfoCase(currentlySelected.first->get_pos()[1], currentlySelected.first->get_pos()[0]);
    emit displayInfo();
}

void Grille::fillFenetreInfoCase(int L, int C){
    QFont font;
    font.setPointSize(13);
    if((C < C_GRILLE/2))
        _fenetreInfoCase->move(3*(_map->width()/4) - _fenetreInfoCase->width()/2, _map->height()/2 - _fenetreInfoCase->height()/2);
    else if(C >= C_GRILLE/2)
        _fenetreInfoCase->move(_map->width()/4 - _fenetreInfoCase->width()/2, _map->height()/2 - _fenetreInfoCase->height()/2);

    std::stringstream ss;
    ss << "CASE " << '(' << std::to_string(L) << ',' << std::to_string(C) << ')';
    _fenetreInfoCase->set_coordCase(ss.str());
    ss.clear();
    ss.str(std::string());
    ss << plateau[L][C].get_revetement();
    _fenetreInfoCase->set_revCase(ss.str());
    ss.clear();
    ss.str(std::string());
    if(plateau[L][C].get_en_feu())
        ss << "En feu";
    else
        ss << "Pas en feu";
    _fenetreInfoCase->set_statusCase(ss.str());
    ss.clear();
    ss.str(std::string());
    ss << "Intensité du feu : " << std::to_string( plateau[L][C].get_fire());
    _fenetreInfoCase->set_intensiteFeuCase(ss.str());
    _fenetreInfoCase->clear();
    std::vector<Civil*> v_c = plateau[L][C].get_personnages();
    for(std::vector<Civil*>::iterator it = v_c.begin(); it != v_c.end(); it++){
        if((*it)->get_pdv() <= 0)
            continue;
        if(Pompier *p_tmp = dynamic_cast<Pompier*>(*it)){
            if(p_tmp->get_dansUnVehicule())
                    continue;
        }
        QListItemPersonnage *item = new QListItemPersonnage(*it, _fenetreInfoCase->get_list());
        item->setFont(font);
        _fenetreInfoCase->addItem(item);
    }
    std::vector<Vehicule*> v_v = plateau[L][C].get_vehicules();
    for(std::vector<Vehicule*>::iterator it = v_v.begin(); it != v_v.end(); it++){
        QListItemVehicule *item = new QListItemVehicule(*it, _fenetreInfoCase->get_list());
        item->setFont(font);
        _fenetreInfoCase->addItem(item);
        std::vector<Pompier*> v_p = (*it)->get_passagers();
        if(!v_p.empty())
        {
            for(std::vector<Pompier*>::iterator it2 = v_p.begin(); it2 != v_p.end(); it2++){
                QListItemPersonnage *item_2 = new QListItemPersonnage(*it2, _fenetreInfoCase->get_list());
                font.setItalic(true);
                item_2->setFont(font);
                _fenetreInfoCase->addItem(item_2);
            }
        }
    }
}

void Grille::initCaseFeu(void){
    while(Grille::cases_en_feu.size() != DEPART_FEU_START){
        int x_alea = rand() % 40;
        int y_alea = rand() % 10;
        if(plateau[y_alea][x_alea].get_revetement() == NSRevetement::eau || plateau[y_alea][x_alea].get_en_feu())
            continue;
        turn_on_fire(y_alea, x_alea);
    }
    _nbFeu->setText(QString::fromStdString(std::to_string(cases_en_feu.size())));
    _nbFeu->setVisible(true);
}

void Grille::initCivils(void){
    for(auto it = _civilList.begin(); it != _civilList.end(); it++){
        int x_alea;
        int y_alea;
        do{
            x_alea = rand() % 30;
            y_alea = (rand() % 13) + 9;
        }while(plateau[y_alea][x_alea].get_revetement() == NSRevetement::eau || plateau[y_alea][x_alea].get_en_feu());
        it->first->set_pos(x_alea, y_alea);
        plateau[y_alea][x_alea].ajouterPersonnage(it->first);
        it->second->move(x_alea*PIX_CASE, y_alea*PIX_CASE);
        it->second->setVisible(true);
    }
}

void Grille::initPompiers(void){
    for(auto it = _pompierList.begin(); it != _pompierList.end(); it++){
        int x_alea;
        int y_alea;
        do{
            x_alea = (rand() % 8) + 22;
            y_alea = (rand() % 6) + 11;
        }while(plateau[y_alea][x_alea].get_revetement() == NSRevetement::eau || plateau[y_alea][x_alea].get_en_feu());
        it->first->set_pos(x_alea, y_alea);
        plateau[y_alea][x_alea].ajouterPersonnage(it->first);
        it->second->move(x_alea*PIX_CASE, y_alea*PIX_CASE);
        it->second->setVisible(true);
    }
}

void Grille::initVehicules(void){
    _vehiculeList[0].second->move(23*PIX_CASE, 18*PIX_CASE);
    _vehiculeList[0].first->set_pos(23, 18);
    _vehiculeList[0].second->setVisible(true);
    plateau[18][23].ajouterVehicule(_vehiculeList[0].first);
    _vehiculeList[1].second->move(24*PIX_CASE, 18*PIX_CASE);
    _vehiculeList[1].first->set_pos(24, 18);
    _vehiculeList[1].second->setVisible(true);
    plateau[18][24].ajouterVehicule(_vehiculeList[1].first);
    _vehiculeList[2].second->move(22*PIX_CASE, 18*PIX_CASE);
    _vehiculeList[2].first->set_pos(22, 18);
    _vehiculeList[2].second->setVisible(true);
    plateau[18][22].ajouterVehicule(_vehiculeList[2].first);
}

void Grille::initBoutons(void){
    QFont font;
    font.setPointSize(13);

    // Bouton START
    _start = new QPushButton("START", this);
    _start->move(this->frameSize().width()/2 - _start->frameSize().width()/2, 780);
    _start->setFont(font);

    std::cout << _start->font().pointSize() << std::endl;

    // Bouton Afficher Règles
    _afficherRegles = new QPushButton("REGLES DU JEU", this);
    _afficherRegles->move(this->width()/2 - 2*_start->width(), 780);
    _afficherRegles->setFont(font);

    // Bouton TOUR SUIVANT
    _nextTurn = new QPushButton("Tour Suivant", this);
    _nextTurn->move(this->frameSize().width()/2 - _nextTurn->frameSize().width()/2, 780);
    _nextTurn->setFont(font);
    _nextTurn->setVisible(false);

    // Bouton ARROSER
    _arroser = new QPushButton("ARROSER", this);
    _arroser->move(this->frameSize().width()/4 - _arroser->frameSize().width()/2, 780);
    _arroser->setFont(font);
    _arroser->setVisible(false);

    // Bouton MONTER VEHICULE
    _monterVehicule = new QPushButton("Monter dans un véhicule", this);
    _monterVehicule->move(this->frameSize().width()/2 - _monterVehicule->frameSize().width()/2, 780);
    _monterVehicule->setFont(font);
    _monterVehicule->setVisible(false);

    // Bouton DESCENDRE VEHICULE
    _descendreVehicule = new QPushButton("Descendre du véhicule", this);
    _descendreVehicule->move(this->frameSize().width()/2 - _descendreVehicule->frameSize().width()/2, 780);
    _descendreVehicule->setFont(font);
    _descendreVehicule->setVisible(false);

    // Bouton CONDUIRE
    _conduire = new QPushButton("CONDUIRE", this);
    _conduire->move(this->frameSize().width()/3 - _conduire->frameSize().width()/2, 780);
    _conduire->setFont(font);
    _conduire->setVisible(false);

    // Bouton REMPLIR
    _remplir = new QPushButton("REMPLIR", this);
    _remplir->move(this->frameSize().width()/3 - _remplir->frameSize().width()/2, 780);
    _remplir->setFont(font);
    _remplir->setVisible(false);
}

void Grille::initSymboles(void){
    // Symboles FEU non affichés
    for(int j = 0; j < L_GRILLE; j++){
        for(int k = 0; k < C_GRILLE; k++){
            ClickableLabel *imgFeu = new ClickableLabel(this);
            imgFeu->setPixmap(QPixmap(QApplication::applicationDirPath() + "/imagesFolder/feu.png"));
            imgFeu->setGeometry(k*PIX_CASE, j*PIX_CASE, PIX_CASE, PIX_CASE);
            imgFeu->setVisible(false);
            _imgFeu[j].push_back(imgFeu);
            QObject::connect(imgFeu, SIGNAL(clickedImg(int, int)), this, SLOT(boxClicked(int, int)));
        }
    }

    // Symboles 'ACTION' non affichés
    for(int j = 0; j < L_GRILLE; j++){
        for(int k = 0; k < C_GRILLE; k++){
            ClickableLabel *imgAction = new ClickableLabel(this);
            imgAction->setPixmap(QPixmap(QApplication::applicationDirPath() + "/imagesFolder/action.png"));
            imgAction->setGeometry(k*PIX_CASE, j*PIX_CASE, PIX_CASE, PIX_CASE);
            imgAction->setVisible(false);
            _imgAction[j].push_back(imgAction);
            QObject::connect(imgAction, SIGNAL(clickedImg(int, int)), this, SLOT(boxClicked(int, int)));
        }
    }
}

void Grille::initListes(void){
    // Affichage caché des civils
    for(auto &it : _civilList){
        ClickableLabel *nCivil = new ClickableLabel(this);
        nCivil->setPixmap(QPixmap(QApplication::applicationDirPath() + "/imagesFolder/civil.png"));
        nCivil->setVisible(false);
        it.first = new Civil;
        it.second = nCivil;
        QObject::connect(nCivil, SIGNAL(clickedImg(int, int)), this, SLOT(boxClicked(int, int)));
    }

    // Affichage caché des pompiers
    int n = 0;
    for(auto &it : _pompierList){
        ClickableLabel *nPompier = new ClickableLabel(this);
        if(n == 0 || n == 1 || n == 2){
            nPompier->setPixmap(QPixmap(QApplication::applicationDirPath() + "/imagesFolder/pompier.png"));
            it.first = new Pompier;
        }
        else if(n == 3 || n == 4){
            it.first = new PompierEnChef;
            nPompier->setPixmap(QPixmap(QApplication::applicationDirPath() + "/imagesFolder/pompier_en_chef.png"));
        }
        else
        {
            nPompier->setPixmap(QPixmap(QApplication::applicationDirPath() + "/imagesFolder/pompier.png"));
            it.first = new Pompier(new Extincteur);
        }

        nPompier->setVisible(false);
        it.second = nPompier;
        QObject::connect(nPompier, SIGNAL(clickedImg(int, int)), this, SLOT(boxClicked(int, int)));
        n++;
    }

    // Affichage caché des véhicules
    int k = 0;
    for(auto &it : _vehiculeList){
        ClickableLabel *nVehicule = new ClickableLabel(this);
        if(k == 0){
             it.first = new Camion();
             nVehicule->setPixmap(QPixmap(QApplication::applicationDirPath() + "/imagesFolder/camion.png"));
        }
        else{
            it.first = new Mobylette();
            nVehicule->setPixmap(QPixmap(QApplication::applicationDirPath() + "/imagesFolder/mobylette.png"));
        }
        nVehicule->setVisible(false);
        it.second = nVehicule;
        QObject::connect(nVehicule, SIGNAL(clickedImg(int, int)), this, SLOT(boxClicked(int, int)));
        k++;
    }
}

void Grille::affichageNombres(void){
    // Affichage nombre de civils
    QLabel *blackRect = new QLabel(this);
    QLabel *logoCivil = new QLabel(this);
    _nbCivil = new QLabel(this);
    QFont font = _nbCivil->font();
    font.setPixelSize(26);
    _nbCivil->setFont(font);
    _nbCivil->setText(QString::fromStdString(std::to_string(DEPART_CIVIL - nbCivilMort)));
    blackRect->setPixmap(QApplication::applicationDirPath() + "/imagesFolder/blackRect.png");
    logoCivil->setPixmap(QApplication::applicationDirPath() + "/imagesFolder/civil.png");
    _nbCivil->move(1050, 780);
    blackRect->move(1000, 777);
    logoCivil->move(1000, 777);
    _nbCivil->setVisible(false);

    // Affichage nombre de cases en feu
    QLabel *blackRect2 = new QLabel(this);
    QLabel *logoFeu = new QLabel(this);
    _nbFeu = new QLabel(this);
    _nbFeu->setFixedSize(100, _nbFeu->height());
    _nbFeu->setFont(font);
    blackRect2->setPixmap(QApplication::applicationDirPath() + "/imagesFolder/blackRect.png");
    logoFeu->setPixmap(QApplication::applicationDirPath() + "/imagesFolder/feu.png");
    _nbFeu->move(1150, 780);
    logoFeu->move(1100, 777);
    _nbFeu->setVisible(false);

    // Affichage nombre de pompier
    QLabel *logoPompier = new QLabel(this);
    _nbPompier = new QLabel(QString::fromStdString(std::to_string(nbPompier)), this);
    _nbPompier->setFixedSize(100, _nbPompier->height());
    _nbPompier->setFont(font);
    logoPompier->setPixmap(QApplication::applicationDirPath() + "/imagesFolder/pompier.png");
    _nbPompier->move(1250, 780);
    blackRect2->move(1200, 777);
    logoPompier->move(1200, 777);
    _nbPompier->setVisible(false);

}

void Grille::connexionSignaux(void){
    // Connexion des signaux et slots
    QObject::connect(_map, SIGNAL(clicked(int, int)), this, SLOT(boxClicked(int, int)));
    QObject::connect(_start, SIGNAL(clicked()), this, SLOT(gameStart()));
    QObject::connect(_nextTurn, SIGNAL(clicked()), this, SLOT(tourSuivant()));
    QObject::connect(this, SIGNAL(displayInfo()), _fenetreInfoCase, SLOT(show()));
    QObject::connect(_fenetreInfoCase->get_list(), SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(displayActions(QListWidgetItem *)));
    QObject::connect(_fenetreInfoCase, SIGNAL(close()), this, SLOT(cleanPossibilities()));
    QObject::connect(_fenetreInfoCase, SIGNAL(close()), this, SLOT(displayNextTurn()));
    QObject::connect(_arroser, SIGNAL(clicked()), this, SLOT(afficherPorteeArrosage()));
    QObject::connect(_monterVehicule, SIGNAL(clicked()), this, SLOT(monterVehiculePressed()));
    QObject::connect(_descendreVehicule, SIGNAL(clicked()), this, SLOT(descendreVehiculePressed()));
    QObject::connect(_conduire, SIGNAL(clicked()), this, SLOT(conduirePressed()));
    QObject::connect(_remplir, SIGNAL(clicked()), this, SLOT(remplirPressed()));
    QObject::connect(this, SIGNAL(showMsg()), _msg, SLOT(exec()));
    QObject::connect(_msg, SIGNAL(quitter()), this, SLOT(quitter()));
    QObject::connect(_msg, SIGNAL(rejouer()), this, SLOT(rejouer()));
    QObject::connect(_afficherRegles, SIGNAL(clicked()), _regles, SLOT(exec()));
    QObject::connect(_regles, SIGNAL(resize(int)), this, SLOT(resizeRegle(int)));
}

void Grille::conduire(int L, int C){
    if(_imgAction[L][C]->isVisible()){
        deplacer_vehicule(currentlySelectedVehicule.first->get_pos(), C, L, &currentlySelectedVehicule);
        currentlySelectedVehicule.first->set_deplacementEffectue(true);
        for(const auto &it : currentlySelectedVehicule.first->get_passagers()){
            for(const auto &it2 : _pompierList){
                if(it2.first == it){
                    std::pair<Civil*, ClickableLabel*> tmp;
                    tmp.first = dynamic_cast<Civil*>(it);
                    tmp.second = it2.second;
                    deplacer_personnage(it->get_pos(), C, L, &tmp);
                }
            }
        }
    }
}

void Grille::arroser(int L, int C, Pompier* p){
    if(_imgAction[L][C]->isVisible() && plateau[L][C].get_en_feu()){
        p->set_arrosageEffectue(true);
        int n = 1;
        for(int i = L - 1; i <= L + 1; i ++){
            for(int j = C - 1 + n; j <= C + 1 - n; j++){
                if(j == p->get_pos()[0] && i == p->get_pos()[1])
                    continue;
                if(i < 0 || i >= L_GRILLE || j < 0 || j >= C_GRILLE)
                    continue;
                if(plateau[i][j].get_en_feu()){
                    plateau[i][j].set_fire(plateau[i][j].get_fire() - p->get_recip()->get_puissance());

                    if(plateau[i][j].get_fire() <= 0){
                        _imgFeu[i][j]->setPixmap(QApplication::applicationDirPath() + "/imagesFolder/cendre.png");
                        nbCaseBrule++;
                        turn_off_fire(i, j);
                        if(cases_en_feu.empty())
                            msgGagne();
                    }
                }
            }
            if(i < L)
                n--;
            else
                n++;
        }
        if(p->get_recip()->get_contenuRestant() != 0)
            p->get_recip()->decrement_contenuRestant();
        cleanPossibilities();
    }
}

void Grille::afficherRemplir(Pompier* p){
    if(dynamic_cast<Seau*>(p->get_recip())){
        std::vector<int> pos_tmp = p->get_pos();
        if(((pos_tmp[1] - 1 >= 0) && (plateau[pos_tmp[1] - 1][pos_tmp[0]].get_revetement() == NSRevetement::eau))
                || ((pos_tmp[1] + 1 < L_GRILLE) && (plateau[pos_tmp[1] + 1][pos_tmp[0]].get_revetement() == NSRevetement::eau))
                || ((pos_tmp[0] - 1 >= 0) && (plateau[pos_tmp[1]][pos_tmp[0] - 1].get_revetement() == NSRevetement::eau))
                || ((pos_tmp[0] + 1 < C_GRILLE) && (plateau[pos_tmp[1]][pos_tmp[0] + 1].get_revetement() == NSRevetement::eau)))
        {
            _remplir->setVisible(true);
        }
    }
    else if(dynamic_cast<Extincteur*>(p->get_recip())){
        std::vector<int> pos_tmp = p->get_pos();
        if(((pos_tmp[1] - 1 >= 0) && !plateau[pos_tmp[1] - 1][pos_tmp[0]].get_vehicules().empty())
                || ((pos_tmp[1] + 1 < L_GRILLE) && !plateau[pos_tmp[1] + 1][pos_tmp[0]].get_vehicules().empty())
                || ((pos_tmp[0] - 1 >= 0) && !plateau[pos_tmp[1]][pos_tmp[0] - 1].get_vehicules().empty())
                || ((pos_tmp[0] + 1 < C_GRILLE) && !plateau[pos_tmp[1]][pos_tmp[0] + 1].get_vehicules().empty()))
        {
            _remplir->setVisible(true);
        }
    }
}

void Grille::displayActionsVehicules(Vehicule* v){
    if(v->get_name().compare("Mobylette") == 0){
        bool conducteur = false;
        for(const auto &it : v->get_passagers()){
            if(it->get_deplacementEffectue() == false){
                conducteur = true;
                break;
            }
        }
        if(conducteur && !v->get_deplacementEffectue())
            _conduire->setVisible(true);
    }
    else if(v->get_name().compare("Camion") == 0){
        bool conducteur = false;
        for(const auto &it : v->get_passagers()){
            if(dynamic_cast<PompierEnChef*>(it)){
                conducteur = true;
                break;
            }
        }
        if(conducteur && !v->get_deplacementEffectue())
            _conduire->setVisible(true);
    }
}

void Grille::displayActionsPersonnages(Pompier* p){
    if(!p->get_dansUnVehicule() && (p->get_recip()->get_contenuRestant() < p->get_recip()->get_contenuMax())){
        afficherRemplir(p);
    }
    if(!p->get_deplacementEffectue())
        _monterVehicule->setVisible(true);
    if(!p->get_arrosageEffectue()  && !p->get_dansUnVehicule()){
        _arroser->setVisible(true);
    }
    if(!p->get_deplacementEffectue() && !p->get_dansUnVehicule()){
        flag_deplacement = true;
        displayPossibilities(p->get_pos(), p->get_pdm(), false);
    }
    if(p->get_dansUnVehicule() && !p->get_deplacementEffectue()){
        _monterVehicule->setVisible(false);
        _descendreVehicule->setVisible(true);
    }
}

void Grille::msgPerdu(){
    cleanPossibilities();
    _msg->set_msgPrincipal("Vous avez perdu ...");
    if(nbCivilMort == DEPART_CIVIL)
        _msg->set_msgSecondaire("Vous n'avez pas réussi à sauver les civils");
    else if(nbPompier == 0 || true)
        _msg->set_msgSecondaire("Tous vos pompiers ne sont plus parmis nous");
    else if(nbCaseBrule + cases_en_feu.size() == 808)
        _msg->set_msgSecondaire("Le village est ravagé par les flammes !");
    emit showMsg();
}

void Grille::msgGagne(){
    cleanPossibilities();
    _msg->set_msgPrincipal("Vous avez gagné !");
    std::stringstream ss;
    ss << "Vous avez sauvé " << (DEPART_CIVIL - nbCivilMort) << " civils" << std::endl << "Il vous reste " << nbPompier << " pompiers"<< std::endl << "En " << nbTour << " tours" << std::endl << "Avec " << nbCaseBrule << " cases brulées";
    _msg->set_msgSecondaire(ss.str());
    emit showMsg();
}

void Grille::quitter(void){
    close();
}

void Grille::rejouer(void){
    flag_rejouer = true;
    cases_en_feu.clear();
    Civil::cpt = 0;
    Pompier::cpt = 0;
    PompierEnChef::cpt = 0;
    flag_deplacement = false;
    flag_arroser = false;
    flag_monterVehicule = false;
    flag_conduire = false;
    nbCivilMort = 0;
    nbTour = 0;
    nbCaseBrule = 0;
    nbPompier = DEPART_POMPIER;
    close();
}

void Grille::resizeRegle(int n){
    switch(n){
        case 0 :
            _regles->setFixedSize(400,200);
        break;
        case 1 :
            _regles->setFixedSize(1070,450);
        break;
        case 2 :
            _regles->setFixedSize(1070,450);
        break;
        case 3 :
            _regles->setFixedSize(750,600);
        break;
        case 4 :
            _regles->setFixedSize(1200,700);
        break;
        case 5 :
            _regles->setFixedSize(1070,700);
        break;
        case 6 :
            _regles->setFixedSize(800,250);
        break;
    }
    _regles->move((_map->width() - _regles->width())/2, (_map->height() - _regles->height())/2);
}
