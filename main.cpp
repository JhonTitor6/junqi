#include "gametype.h"
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <stdio.h>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Singlegame board;
	board.show();

	return a.exec();
}

