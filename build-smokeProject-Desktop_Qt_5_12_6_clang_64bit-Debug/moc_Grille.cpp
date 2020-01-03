/****************************************************************************
** Meta object code from reading C++ file 'Grille.hh'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../smokeProject/Grille.hh"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Grille.hh' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Grille_t {
    QByteArrayData data[20];
    char stringdata0[262];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Grille_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Grille_t qt_meta_stringdata_Grille = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Grille"
QT_MOC_LITERAL(1, 7, 11), // "displayInfo"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 7), // "showMsg"
QT_MOC_LITERAL(4, 28, 10), // "boxClicked"
QT_MOC_LITERAL(5, 39, 9), // "gameStart"
QT_MOC_LITERAL(6, 49, 11), // "tourSuivant"
QT_MOC_LITERAL(7, 61, 14), // "displayActions"
QT_MOC_LITERAL(8, 76, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(9, 93, 4), // "item"
QT_MOC_LITERAL(10, 98, 18), // "cleanPossibilities"
QT_MOC_LITERAL(11, 117, 15), // "displayNextTurn"
QT_MOC_LITERAL(12, 133, 22), // "afficherPorteeArrosage"
QT_MOC_LITERAL(13, 156, 21), // "monterVehiculePressed"
QT_MOC_LITERAL(14, 178, 24), // "descendreVehiculePressed"
QT_MOC_LITERAL(15, 203, 15), // "conduirePressed"
QT_MOC_LITERAL(16, 219, 14), // "remplirPressed"
QT_MOC_LITERAL(17, 234, 7), // "quitter"
QT_MOC_LITERAL(18, 242, 7), // "rejouer"
QT_MOC_LITERAL(19, 250, 11) // "resizeRegle"

    },
    "Grille\0displayInfo\0\0showMsg\0boxClicked\0"
    "gameStart\0tourSuivant\0displayActions\0"
    "QListWidgetItem*\0item\0cleanPossibilities\0"
    "displayNextTurn\0afficherPorteeArrosage\0"
    "monterVehiculePressed\0descendreVehiculePressed\0"
    "conduirePressed\0remplirPressed\0quitter\0"
    "rejouer\0resizeRegle"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Grille[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x06 /* Public */,
       3,    0,   95,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    2,   96,    2, 0x0a /* Public */,
       5,    0,  101,    2, 0x0a /* Public */,
       6,    0,  102,    2, 0x0a /* Public */,
       7,    1,  103,    2, 0x0a /* Public */,
      10,    0,  106,    2, 0x0a /* Public */,
      11,    0,  107,    2, 0x0a /* Public */,
      12,    0,  108,    2, 0x0a /* Public */,
      13,    0,  109,    2, 0x0a /* Public */,
      14,    0,  110,    2, 0x0a /* Public */,
      15,    0,  111,    2, 0x0a /* Public */,
      16,    0,  112,    2, 0x0a /* Public */,
      17,    0,  113,    2, 0x0a /* Public */,
      18,    0,  114,    2, 0x0a /* Public */,
      19,    1,  115,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void Grille::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Grille *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->displayInfo(); break;
        case 1: _t->showMsg(); break;
        case 2: _t->boxClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->gameStart(); break;
        case 4: _t->tourSuivant(); break;
        case 5: _t->displayActions((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 6: _t->cleanPossibilities(); break;
        case 7: _t->displayNextTurn(); break;
        case 8: _t->afficherPorteeArrosage(); break;
        case 9: _t->monterVehiculePressed(); break;
        case 10: _t->descendreVehiculePressed(); break;
        case 11: _t->conduirePressed(); break;
        case 12: _t->remplirPressed(); break;
        case 13: _t->quitter(); break;
        case 14: _t->rejouer(); break;
        case 15: _t->resizeRegle((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Grille::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Grille::displayInfo)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Grille::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Grille::showMsg)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Grille::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_Grille.data,
    qt_meta_data_Grille,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Grille::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Grille::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Grille.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Grille::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void Grille::displayInfo()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Grille::showMsg()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
