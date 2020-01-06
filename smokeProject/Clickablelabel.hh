#pragma once

#include <QLabel>
#include <QWidget>
#include <Qt>
#include <QMouseEvent>

#define PIX_CASE 35

class ClickableLabel : public QLabel {
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget* parent = Q_NULLPTR);
    ~ClickableLabel();

signals:
    void clicked(int, int);
    void clickedImg(int, int);

protected:
    void mousePressEvent(QMouseEvent* event);

};
