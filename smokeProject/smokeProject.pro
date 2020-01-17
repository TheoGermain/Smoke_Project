CONFIG += app_bundle

ICON = myIcon.icns

mySetOfExtraFiles.files = $$PWD/imagesFolder
mySetOfExtraFiles.path = Contents/MacOS
QMAKE_BUNDLE_DATA += mySetOfExtraFiles

QMAKE_CXXFLAGS += -std=c++0x

HEADERS += \
    BoxDisplayInfo.hh \
    Civil.hh \
    Clickablelabel.hh \
    Grille.hh \
    MessageBox.hh \
    Milieu.hh \
    Pompier.hh \
    PompierEnChef.hh \
    QListItemPersonnage.hh \
    QListItemVehicule.hh \
    Recipient.hh \
    ReglesDuJeu.hh \
    Revetement.hh \
    Vehicule.hh

SOURCES += \
    BoxDisplayInfo.cc \
    Civil.cc \
    Clickablelabel.cc \
    Grille.cc \
    MessageBox.cc \
    Milieu.cc \
    Pompier.cc \
    PompierEnChef.cc \
    QListItemPersonnage.cc \
    QListItemVehicule.cc \
    ReglesDuJeu.cc \
    Vehicule.cc \
    main.cc

QT += widgets
