#ifndef STATUSBOX_H
#define STATUSBOX_H

#include <QWidget>
#include "board.h"

class StatusBox : public QWidget
{
public:
	StatusBox();
	explicit StatusBox(QWidget *parent = 0);
	void paintEvent(QPaintEvent *);

	void updateTurn(bool ,bool );
	void updateEated();
	void Timer();

};

#endif // STATUSBOX_H
