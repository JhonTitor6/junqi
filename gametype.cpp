#include "gametype.h"



/*                     作废                      */




GameType::GameType(QWidget *parent) : QWidget(parent)
{
	flag = -1;
	QPushButton *pve = new QPushButton(this);
	QPushButton *pvp = new QPushButton(this);

	pve->setText("人机对战");
	pve->move(100,100);

	pvp->setText("人人对战");
	pvp->move(100,200);

	connect(pve, &QPushButton::released, this, &GameType::sendPve);
	connect(pvp, &QPushButton::released, this, &GameType::sendPvp);
}
void GameType::sendPve()
{
	emit mySignal(1);
}
void GameType::sendPvp()
{
	emit mySignal(0);
}

int GameType::pve_clicked(int argc, char *argv[])
{
	QApplication a(argc, argv);
	flag = 1;
	Singlegame board;
	board.show();
	return a.exec();
}
int GameType::pvp_clicked(int argc, char *argv[])
{
	QApplication a(argc, argv);
	flag = 0;
	Board board;
	board.show();
	return a.exec();
}
