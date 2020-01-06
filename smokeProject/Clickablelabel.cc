#include "Clickablelabel.hh"

ClickableLabel::ClickableLabel(QWidget* parent): QLabel(parent){
}

ClickableLabel::~ClickableLabel() {}

void ClickableLabel::mousePressEvent(QMouseEvent* event) {
    int mx = event->x()/PIX_CASE;
    int my = event->y()/PIX_CASE;
    emit clicked(my, mx);
    emit clickedImg(this->y()/PIX_CASE, this->x()/PIX_CASE);
}
