#pragma once

#include <QLabel>
#include <QWidget>
#include <Qt>
#include <QMouseEvent>

class ClickableLabel : public QLabel {
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~ClickableLabel();

signals:
    void clicked(int, int);
    void clickedFeu(int, int);

protected:
    void mousePressEvent(QMouseEvent* event);

};
