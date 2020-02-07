#ifndef GAMETYPE_H
#define GAMETYPE_H

#include <QWidget>
#include "board.h"
#include "singlegame.h"
#include <QPushButton>
#include <QApplication>


/*                     作废                      */



class GameType : public QWidget
{
	Q_OBJECT
public:
	explicit GameType(QWidget *parent = nullptr);
	Singlegame single;
	Board board;
	void sendPve();
	void sendPvp();
	int flag;
signals:
	void mySignal(int);
public slots:
	int pvp_clicked(int argc, char *argv[]);
	int pve_clicked(int argc, char *argv[]);
};

#endif // GAMETYPE_H
