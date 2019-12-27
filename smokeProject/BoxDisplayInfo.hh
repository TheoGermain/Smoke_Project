#pragma once
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <string>
#include <QListWidget>

class BoxDisplayInfo : public QDialog{

public:
    BoxDisplayInfo();
    virtual ~BoxDisplayInfo();
    void set_coordCase(std::string str);
    void set_revCase(std::string str);
    void set_statusCase(std::string str);
    void set_intensiteFeuCase(std::string str);
    void addItem(std::string);
    void clear(void);


private:
    QVBoxLayout *_layout;
    QLabel *_coordCase;
    QLabel *_revCase;
    QLabel *_statusCase;
    QLabel *_intensiteFeuCase;
    QListWidget *_list;
};
