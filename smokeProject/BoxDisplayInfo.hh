#pragma once
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <string>
#include <QListWidget>
#include <QCloseEvent>

class BoxDisplayInfo : public QDialog{
    Q_OBJECT

public:
    BoxDisplayInfo(QWidget *parent = nullptr);
    ~BoxDisplayInfo();
    void set_coordCase(std::string str);
    void set_revCase(std::string str);
    void set_statusCase(std::string str);
    void set_intensiteFeuCase(std::string str);
    void addItem(QListWidgetItem*);
    void clear(void);
    QListWidget* get_list(void);
    void reject();

signals:
    void close();


private:
    QVBoxLayout *_layout;
    QLabel *_coordCase;
    QLabel *_revCase;
    QLabel *_statusCase;
    QLabel *_intensiteFeuCase;
    QListWidget *_list;
};
