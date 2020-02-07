#ifndef BOARD_H
#define BOARD_H

#include <QVector>
#include <QPainter>
#include <QMouseEvent>
#include <QWidget>
#include <QString>
#include <QPushButton>
#include <QMessageBox>

#include "stone.h"
#include "step.h"

class Board : public QWidget
{
	Q_OBJECT

public:
	Board(QWidget *parent = 0);
	Stone _s[50];
	QVector<Step*> _steps;
	int _d;
	int _selectid;
	void init();
	int _P1StepNum;
	int _P2StepNum;
	//轮流规则
	bool _P1Turn;  //1=轮到P1,0=轮到P2，P1先
	bool _P1color; //用于开局确认P1的颜色,1=红色，0=黄色，它的非就是P2的.也表示目前走方的颜色
	bool _P1lastcolor;
	bool _P2lastcolor;
	bool _colorflag; //是否已经确认了颜色，0=没，1=确认了
	bool _colorflag1;//是否已经确认了第一个颜色,第一个和第二个比较,
	bool _colorflag2;
	void confirmColor(int );
	//剩余地雷数目
	int _redDileiNum;
	int _yellowDileiNum;
	//返回象棋的左上角坐标
	QPoint lefttop(int r4ow, int col);
	QPoint lefttop(int id);
	//函数
	bool getRowCol(QPoint pt, int& row, int & col);
	void drawStone(QPainter& painter, int id);
	void drawStatusBox(QPainter& painter);
	void paintEvent(QPaintEvent *);

	void mouseReleaseEvent(QMouseEvent *);
	virtual void click(int clickid, int row, int col);
	int getChessId(int row, int col);
	void doShow(int clickid);
	void tryMoveStone(int moveid, int row, int col);
	void moveStone(int moveid, int row, int col);
	void moveStone(int moveid, int row, int col, int killid);
	void eatStone(int moveid, int row, int col, int killid);
	void unmoveStone(int moveid, int row, int col);
	void uneatStone(int moveid, int row, int col, int killid);
	void saveStep(int moveid, int row, int col, int killid, QVector<Step*>& steps);
	//判断
	bool canMove(int moveid, int row, int col, int killid);
	void canMoveGongbing(int nowrow, int nowcol, int endrow, int endcol, int vis[18][6], int *flag);
	int whichKind(int row, int col);
	//弹窗等功能
	void P1SurrenderDialog();
	void P2SurrenderDialog();
	void Reconciliation();
	//延时功能
	bool sleep(unsigned int msec);
	void getRandomNumber(int *);


};

#endif // BOARD_H
