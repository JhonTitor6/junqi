#include "singlegame.h"
#include <QTimer>
#include <QTime>
void Singlegame::click(int clickid, int row, int col)
{
	if(!this->_P1Turn)
		return;
	Board::click(clickid, row, col);
	if(!this->_P1Turn)
	{
		// 启动0.1秒定时器，在0.1秒后电脑再思考
		sleep(100);
		Step* step = NULL;
		step = getBestMove();
		if(step)
		{
			moveStone(step->_moveid, step->_rowTo, step->_colTo, step->_killid);
		}
		else
		{
			randomShow();
		}
		delete step;
		_P2StepNum++;
		update();
	}
}
void Singlegame::randomShow()
{
	qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
	while(1)
	{
		int test =qrand()%50;
		if(_s[test]._showed)
			continue;
		else
		{
			doShow(test);
			update();
			break;
		}
	}
}

void Singlegame::getAllPossibleMove(QVector<Step *> &steps)
{
	//假想选中一个棋子
	for(int i=0; i<50; i++)
	{
		if(!_colorflag) break;
		if(_s[i]._dead) continue;
		if(!_s[i]._showed) continue;
		if(_s[i]._type==Stone::DILEI || _s[i]._type==Stone::JUNQI) continue;
		if(!_P1Turn)	//P2的
		{
			if(_s[i]._red != !_P1color) continue;
			//假想遍历移动到目的地
			for(int row=1; row<=17; row++)
			{
				for(int col=1; col<=5; col++)
				{
					int killid = getChessId(row, col);
					if(_s[killid]._red == !_P1color) continue;

					if(canMove(i, row, col, killid))
					{
						saveStep(i, row, col, killid, steps);
					}
				}
			}
		}
		else	//P1的
		{
			if(_s[i]._red != _P1color) continue;
			for(int row=1; row<=17; row++)
			{
				for(int col=1; col<=5; col++)
				{
					int killid = getChessId(row, col);
					if(_s[killid]._red == _P1color) continue;

					if(canMove(i, row, col, killid))
					{
						saveStep(i, row, col, killid, steps);
					}
				}
			}
		}
	}
}

void Singlegame::fakeMove(Step* step)
{
	if(step->_killid!=-1)
	{
		eatStone(step->_moveid, step->_rowTo, step->_colTo, step->_killid);
	}
	else
	{
		moveStone(step->_moveid,step->_rowTo, step->_colTo);
	}
}
void Singlegame::unfakeMove(Step* step)
{
	if(step->_killid!=-1)
	{
		uneatStone(step->_moveid, step->_rowFrom, step->_colFrom, step->_killid);
	}
	else
	{
		unmoveStone(step->_moveid, step->_rowFrom, step->_colFrom);
	}
}
int Singlegame::calcScore()
{
	//JUNQI, SILING, JUNZHANG, SHIZHANG, LVZHANG, TUANZHANG,
	//YINGZHANG, LIANZHANG, PAIZHANG, DILEI, GONGBING, ZHADAN};
	static int chessScore[] = {1000, 200, 70, 60, 50, 40,
							  30, 20, 10, 300, 150, 50};
	int P1TotalScore = 0;
	int P2TotalScore = 0;
	for(int i=0; i<50; i++)
	{
		if(_s[i]._dead) continue;
		if(!_s[i]._showed) continue;
		if(_s[i]._red == _P1color && _colorflag)
			P1TotalScore += chessScore[_s[i]._type];
		else if(_s[i]._red == !_P1color && _colorflag)
			P2TotalScore += chessScore[_s[i]._type];
	}
	return P2TotalScore - P1TotalScore;
}
int Singlegame::getMaxScore(int level, int curMinScore)
{
	if(level==0)
		return calcScore();
	QVector<Step*> steps;
	getAllPossibleMove(steps);	//P2的AllPossibleMove
	int maxScore = -99999;
	while(steps.count())
	{
		Step* step = steps.back();
		steps.removeLast();

		fakeMove(step);
		int score = getMinScore(level-1, maxScore);
		unfakeMove(step);
		delete step;

		if(score >= curMinScore)
		{
			while(steps.count())
			{
				Step* step = steps.back();
				steps.removeLast();
				delete step;
			}
			return score;
		}
		if(score > maxScore)
		{
			maxScore = score;
		}
	}
	return maxScore;
}

int Singlegame::getMinScore(int level, int curMaxScore)
{
	if(level==0)
		return calcScore();
	QVector<Step*> steps;
	getAllPossibleMove(steps);    //P1的getAllPossibleMove
	int minScore = 99999;
	while(steps.count())
	{
		Step* step = steps.back();
		steps.removeLast();

		fakeMove(step);
		int score = getMaxScore(level-1, minScore);
		unfakeMove(step);
		delete step;

		if(score <= curMaxScore)
		{
			while(steps.count())
			{
				Step* step = steps.back();
				steps.removeLast();
				delete step;
			}
			return score;
		}
		if(score < minScore)
		{
			minScore = score;
		}
	}
	return minScore;
}

Step* Singlegame::getBestMove()
{
	QVector<Step*> steps;
	getAllPossibleMove(steps);
	int maxScore = -99999;
	Step* ret=NULL;
	while(steps.count())
	{
		Step* step = steps.back();
		steps.removeLast();

		fakeMove(step);
		int score = getMinScore(_level-1, maxScore);
		unfakeMove(step);

		if(score > maxScore)
		{
			maxScore = score;
			if(ret) delete ret;
			ret = step;
		}
		else
		{
			delete step;
		}
	}
	return ret;
}
