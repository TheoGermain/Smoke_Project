#include "Clickablelabel.hh"

ClickableLabel::ClickableLabel(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent) {

}

ClickableLabel::~ClickableLabel() {}

void ClickableLabel::mousePressEvent(QMouseEvent* event) {
    int mx = event->x()/35;
    int my = event->y()/35;
    emit clicked(my, mx);
}
