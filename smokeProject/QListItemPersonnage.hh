#pragma once
#include<QListWidgetItem>
#include "Civil.hh"

class QListItemPersonnage : public QListWidgetItem{

public:
    QListItemPersonnage(Civil*, QListWidget *parent = nullptr, int type = Type);
    ~QListItemPersonnage();

    Civil* get_civil(void);

private:
    Civil *_c;
};
