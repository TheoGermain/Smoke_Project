#include <QApplication>
#include "Grille.hh"
#include <time.h>

using namespace NSRevetement;

std::ostream& operator<<(std::ostream& out, const Revetement& r){
  switch (r){
    case foret:
      return out << "foret";
    case plaine:
      return out << "plaine";
    case eau:
      return out << "eau";
    case ville:
      return out << "ville";
    case usine:
      return out << "usine";
    case brule:
      return out << "brulé";
    default :
      return out;
  }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication app(argc, argv);
    Grille g;
    g.showFullScreen();

    return app.exec();
}
