#include "Grille.hh"

std::vector<int*> Grille::cases_en_feu;
int Grille::nbCivilMort = 0;

Grille::Grille() : _imgFeu(L_GRILLE, std::vector<ClickableLabel*>()), _civilList(DEPART_CIVIL){
  int pos_l = 0;
  int pos_c = 0;
  std::string path = QApplication::applicationDirPath().toUtf8().constData();
  setFixedSize(1400, 820);

  // Bouton START
  _start = new QPushButton("START", this);
  _start->move(this->frameSize().width()/2 - _start->frameSize().width()/2, 780);

  // Bouton TOUR SUIVANT
  _nextTurn = new QPushButton("Tour Suivant", this);
  _nextTurn->move(this->frameSize().width()/2 - _start->frameSize().width()/2, 780);
  _nextTurn->setVisible(false);

  // Plateau
  plateau = new Milieu*[L_GRILLE];
  for(std::size_t j = 0; j < L_GRILLE; j++)
    plateau[j] = new Milieu[C_GRILLE];

  // MAP
  _map = new ClickableLabel(this);
  _map->setPixmap(QPixmap(QApplication::applicationDirPath() + "/../../../map1.png"));
  std::ifstream mapDescriptor(path + "/../../../mapDescriptor.txt");

  // Symboles FEU non affichés
  for(int j = 0; j < L_GRILLE; j++){
      for(int k = 0; k < C_GRILLE; k++){
          ClickableLabel *imgFeu = new ClickableLabel(this);
          imgFeu->setPixmap(QPixmap(QApplication::applicationDirPath() + "/../../../feu.png"));
          imgFeu->setGeometry(k*35, j*35, 35, 35);
          imgFeu->setVisible(false);
          _imgFeu[j].push_back(imgFeu);
          QObject::connect(imgFeu, SIGNAL(clickedImg(int, int)), this, SLOT(boxClicked(int, int)));
      }
  }

  // Affichage caché des civils
  for(auto &it : _civilList){
      ClickableLabel *nCivil = new ClickableLabel(this);
      nCivil->setPixmap(QPixmap(QApplication::applicationDirPath() + "/../../../civil.png"));
      nCivil->setVisible(false);
      it.first = new Civil;
      it.second = nCivil;
      QObject::connect(nCivil, SIGNAL(clickedImg(int, int)), this, SLOT(boxClicked(int, int)));
  }

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

  // Affichage nombre de civils morts
  QLabel *blackRect = new QLabel(this);
  QLabel *logoCivil = new QLabel(this);
  _nbCivil = new QLabel(this);
  QFont font = _nbCivil->font();
  font.setPixelSize(26);
  _nbCivil->setFont(font);
  _nbCivil->setText(QString::fromStdString(std::to_string(DEPART_CIVIL - nbCivilMort)));
  blackRect->setPixmap(QApplication::applicationDirPath() + "/../../../blackRect.png");
  logoCivil->setPixmap(QApplication::applicationDirPath() + "/../../../civil.png");
  _nbCivil->move(1050, 780);
  blackRect->move(1000, 777);
  logoCivil->move(1000, 777);
  _nbCivil->setVisible(false);

  // Connexion des signaux et slots
  QObject::connect(_map, SIGNAL(clicked(int, int)), this, SLOT(boxClicked(int, int)));
  QObject::connect(_start, SIGNAL(clicked()), this, SLOT(gameStart()));
  QObject::connect(_nextTurn, SIGNAL(clicked()), this, SLOT(tourSuivant()));
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
}

void Grille::propagation_feu_ligne(int coeff_propagation, std::size_t L, std::size_t C){
  int min = C - coeff_propagation;
  int max = C + coeff_propagation;
  if(min < 0)
    min = 0;
  if(max >= C_GRILLE)
    max = C_GRILLE - 1;

  for(int i = min; i <= max; i++){
    if(i == C || (*this)(L,i).get_en_feu())
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
    if(i == L || (*this)(i,C).get_en_feu())
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
    if((min_L == L && min_C == C) || ((*this)(min_L, min_C).get_en_feu())){
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
    if((min_L == L && min_C == C) || ((*this)(min_L, min_C).get_en_feu())){
      min_L++;
      min_C--;
      continue;
    }
    if(declaration_feu(min_L, min_C))
      turn_on_fire(min_L,min_C);

    min_L++;
    min_C--;
  }
}

void Grille::boxClicked(int L, int C){
    std::cout << '(' << L << ',' << C << ',' << (*this)(L,C) << ')' << std::endl;
}

void Grille::gameStart(){
    _start->setVisible(false);
    _nextTurn->setVisible(true);
    _nbCivil->setVisible(true);

    // Initialisation des cases en feu
    while(Grille::cases_en_feu.size() != DEPART_FEU_START){
        int x_alea = rand() % 40;
        int y_alea = rand() % 10;
        if(plateau[y_alea][x_alea].get_revetement() == NSRevetement::eau || plateau[y_alea][x_alea].get_en_feu())
            continue;
        turn_on_fire(y_alea, x_alea);
        //std::cout << '(' << y_alea << ',' << x_alea << ')' << (*this)(y_alea, x_alea) << std::endl; // /////
    }

    // Initialisation des civils
    for(auto it = _civilList.begin(); it != _civilList.end(); it++){
        int x_alea;
        int y_alea;
        do{
            x_alea = rand() % 30;
            y_alea = (rand() % 13) + 9;
        }while(plateau[y_alea][x_alea].get_revetement() == NSRevetement::eau || plateau[y_alea][x_alea].get_en_feu());
        it->first->set_pos(x_alea, y_alea);
        plateau[y_alea][x_alea].ajouterCivil(it->first);
        it->second->move(x_alea*35, y_alea*35);
        it->second->setVisible(true);
    }
}

void Grille::tourSuivant(){
    propagation();
    baisse_pdv();
    if(nbCivilMort != DEPART_CIVIL)
        deplacement_personnages();
}



void Grille::deplacement_personnages(void){
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
    plateau[former_pos[1]][former_pos[0]].supprimerCivil(c->first);
    plateau[new_y][new_x].ajouterCivil(c->first);
    c->first->set_pos(new_x, new_y);
    c->second->move(new_x*35, new_y*35);
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
}

