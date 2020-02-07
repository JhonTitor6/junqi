#ifndef SINGLEGAME_H
#define SINGLEGAME_H

#include "board.h"
class Singlegame : public Board
{
	Q_OBJECT
public:
	Singlegame()
	{
		_level = 3;
	}
	int _level;

	virtual void click(int clickid, int row, int col);
	Step* getBestMove();
	void getAllPossibleMove(QVector<Step*>& steps);
	void randomShow();

	void fakeMove(Step* step);
	void unfakeMove(Step* step);
	int calcScore();
	int getMinScore(int level, int curMaxScore);
	int getMaxScore(int level, int curMinScore);
};

#endif // SINGLEGAME_H
