#include "statusbox.h"

StatusBox::StatusBox(QWidget *parent) : QWidget(parent)
{
	int w = Board::getStatusboxWidth();
	int h = Board::getStatusboxHeigh();
	setFixedSize(w, h);
}

void StatusBox::paintEvent(QPaintEvent *)
{

}
