#pragma once
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>
#include <sstream>
#include <QApplication>
#include <QDesktopWidget>
#include <QDialog>

class ReglesDuJeu : public QDialog{
    Q_OBJECT

public:
    ReglesDuJeu(QWidget *parent = nullptr);
    ~ReglesDuJeu();

public slots:
    void changeState(void);

signals:
    void resize(int);

private:
    void displayStateZero(void);
    void displayStateOne(void);
    void displayStateTwo(void);
    void displayStateThree(void);
    void displayStateFour(void);
    void displayStateFive(void);
    void displayStateSix(void);
    QLabel* _titre;
    QVBoxLayout* _mainLayout;
    QVBoxLayout* _bodyLayout;
    QHBoxLayout* _buttonLayout;
    QPushButton* _suivant;
    QPushButton* _passer;
    std::vector<QObject*> objets;
    int _state;
};
