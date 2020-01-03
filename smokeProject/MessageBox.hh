#pragma once
#include <QDialog>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>

class MessageBox : public QDialog{
    Q_OBJECT

public:
    MessageBox(QWidget *parent = nullptr);
    ~MessageBox();
    void set_msgPrincipal(std::string);
    void set_msgSecondaire(std::string);

signals:
    void rejouer();
    void quitter();

public slots:
    void rejouerClicked();
    void quitterClicked();

private:
    QLabel* _msgPrincipal;
    QLabel* _msgSecondaire;
    QPushButton* _rejouer;
    QPushButton* _quitter;
};
