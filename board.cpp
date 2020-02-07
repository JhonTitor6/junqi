#include "board.h"
#include <QTime>
#include <QDebug>
#include <QString>
#include <QApplication>
#include <QMessageBox>
Board::Board(QWidget *parent): QWidget(parent)
{
	init();
	resize(530,950);
	QPushButton *P1Surrender = new QPushButton(this);
	QPushButton *P2Surrender = new QPushButton(this);
	QPushButton *Reconciliation = new QPushButton(this);

	P1Surrender->setText("P1认输");
	P2Surrender->setText("P2认输");
	Reconciliation->setText("提和");

	P1Surrender->move(6*_d, 2*_d);
	P2Surrender->move(8*_d, 2*_d);
	connect(P1Surrender, &QPushButton::released, this, &Board::P1SurrenderDialog);
	connect(P2Surrender, &QPushButton::released, this, &Board::P1SurrenderDialog);
	connect(Reconciliation, &QPushButton::released, this, &Board::Reconciliation);

}
void Board::init()
{
	int chessBook[50];
	//初始化随机棋子
	_d = 40*1.3;
	_selectid=-1;
	_P1StepNum=0;
	_P2StepNum=0;


	_P1Turn = true;
	_colorflag = false;
	_colorflag1 = false;
	_colorflag2 = false;

	_redDileiNum=3;
	_yellowDileiNum=3;
	getRandomNumber(chessBook);
	for(int i=0; i<50; i++)
	{
		_s[i].init(i);
		if(chessBook[i]<12)
			_s[i]._red = true;
		else
			_s[i]._red = false;
		if(chessBook[i]==0||chessBook[i]==12)
		{
			_s[i]._type = Stone::JUNQI;
			_s[i]._eatPower = 0;
		}
		if(chessBook[i]==1||chessBook[i]==13)
		{
			_s[i]._type = Stone::SILING;
			_s[i]._eatPower = 9;
		}
		if(chessBook[i]==2||chessBook[i]==14)
		{
			_s[i]._type = Stone::JUNZHANG;
			_s[i]._eatPower = 8;
		}
		if(chessBook[i]==3||chessBook[i]==15)
		{
			_s[i]._type = Stone::SHIZHANG;
			_s[i]._eatPower = 7;
		}
		if(chessBook[i]==4||chessBook[i]==16)
		{
			_s[i]._type = Stone::LVZHANG;
			_s[i]._eatPower = 6;
		}
		if(chessBook[i]==5||chessBook[i]==17)
		{
			_s[i]._type = Stone::TUANZHANG;
			_s[i]._eatPower = 5;
		}
		if(chessBook[i]==6||chessBook[i]==18)
		{
			_s[i]._type = Stone::YINGZHANG;
			_s[i]._eatPower = 4;
		}
		if(chessBook[i]==7||chessBook[i]==19)
		{
			_s[i]._type = Stone::LIANZHANG;
			_s[i]._eatPower = 3;
		}
		if(chessBook[i]==8||chessBook[i]==20)
		{
			_s[i]._type = Stone::PAIZHANG;
			_s[i]._eatPower = 2;
		}
		if(chessBook[i]==9||chessBook[i]==21)
		{
			_s[i]._type = Stone::DILEI;
			_s[i]._eatPower = 200;
		}
		if(chessBook[i]==10||chessBook[i]==22)
		{
			_s[i]._type = Stone::GONGBING;
			_s[i]._eatPower = 1;
		}
		if(chessBook[i]==11||chessBook[i]==23)
		{
			_s[i]._type = Stone::ZHADAN;
			_s[i]._eatPower = 5;
		}
	}
}

bool Board::sleep(unsigned int msec)
{
	QTime dieTime = QTime::currentTime().addMSecs(msec);

	while (QTime::currentTime() < dieTime)
	{
		QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
	}
	return true;
}
//生成随机棋子排序
void Board::getRandomNumber(int chessBook[50])
{
	//JUNQI, SILING, JUNZHANG, SHIZHANG, LVZHANG, TUANZHANG,
	//YINGZHANG, LIANZHANG, PAIZHANG, DILEI, GONGBING, ZHADAN
	//随机选择的计数数组
	int book[24]={1,1,1,2,2,2,
				  2,3,3,3,3,2,
				  1,1,1,2,2,2,
				  2,3,3,3,3,2};
	int realbook[24]={0};
	int i=0;
	qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
	while(1)
	{
		//随机12种棋子 2种颜色
		int test =qrand()%24;
		if(realbook[test]<book[test])
		{
			chessBook[i]=test;
			realbook[test]++;
			i++;
		}
		if(i==50)
			break;
	}
}
void Board::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
	QPen pen;
	int d = _d;
	//画横线
	//空了2行，实际显示的15行,两边各6行放棋子
	for(int i=1; i<=17; i++)
	{
		if(i==8||i==10)
			continue;
		pen.setWidth(2);
		painter.setPen(pen);
		painter.drawLine(QPoint(d, i*d),QPoint(5*d, i*d));
		if(i==2||(i>=6&&i<=12)||i==16)
		{
			pen.setWidth(5);
			painter.setPen(pen);
			painter.drawLine(QPoint(d, i*d),QPoint(5*d, i*d));
		}
    }
    //画竖线
    for(int i=1; i<=5; i++)
    {
		if(i==1||i==5)
		{
			painter.drawLine(QPoint(i*d, d),QPoint(i*d, 17*d));
			pen.setWidth(5);
			painter.setPen(pen);
			painter.drawLine(QPoint(i*d, 2*d),QPoint(i*d, 16*d));
		}
		if(i==3)
		{
			pen.setWidth(5);
			painter.setPen(pen);

			painter.drawLine(QPoint(i*d, 6*d),QPoint(i*d, 12*d));
			pen.setWidth(2);
			painter.setPen(pen);
			painter.drawLine(QPoint(i*d, d),QPoint(i*d, 17*d));
		}
        else
        {
			pen.setWidth(2);
			painter.setPen(pen);
			painter.drawLine(QPoint(i*d, d),QPoint(i*d, 6*d));
			painter.drawLine(QPoint(i*d, 12*d),QPoint(i*d, 17*d));
        }
    }
	//画斜线
	pen.setWidth(1);
	painter.setPen(pen);
	for(int i=1; i<=5; i++)
	{
		for(int j=1; j<=17; j++)
		{
			if(i==1||i==3)
				if(j==2||j==4||j==12||j==14)
					painter.drawLine(i*d, j*d, i*d+2*d, j*d+2*d);
			if(i==3||i==5)
				if(j==2||j==4||j==12||j==14)
					painter.drawLine(i*d, j*d, i*d-2*d, j*d+2*d);
		}
	}
	//画圆圈
	pen.setWidth(2);
	painter.setPen(pen);
	for(int i=1; i<=17; i++)
		for(int j=1; j<=5; j++)
		{
			painter.setBrush(QBrush(QColor(255, 255, 255)));
			if(i==3||i==5||i==13||i==15)
			{
				if(j==2||j==4)
				painter.drawEllipse(QPointF(j*d,i*d),0.5*d,0.5*d);
			}
			if(i==4||i==14)
				painter.drawEllipse(QPointF(3*d,i*d),0.5*d,0.5*d);
		}
	//放棋子
	pen.setWidth(1);
	painter.setPen(pen);
	for(int i=0; i<50;i++)
	{
		drawStone(painter, i);
	}
	//画信息框
	painter.setFont(QFont("system", _d, 100));
	painter.drawText(6.4*_d, 1.1*_d, "P1");
	painter.drawText(8.4*_d, 1.1*_d, "P2");
	painter.drawText(6*_d, 3.1*_d, "P1步数:"+QString::number(_P1StepNum));
	painter.drawText(8*_d, 3.1*_d, "P2步数:"+QString::number(_P2StepNum));
	if(_colorflag)
	{
		if(_P1Turn)
		{
			QRect rect = QRect(6*_d, 0.7*_d, _d, 0.7*_d);
			if(_P1color)
				painter.setBrush(QBrush(QColor(255, 99, 71)));
			else
				painter.setBrush(QBrush(QColor(238, 238, 0)));
			painter.drawRoundRect(rect, 25, 25);
			painter.drawText(6.4*_d, 1.1*_d, "P1");
		}
		else
		{
			QRect rect = QRect(8*_d, 0.7*_d, _d, 0.7*_d);
			if(!_P1color)
				painter.setBrush(QBrush(QColor(255, 99, 71)));
			else
				painter.setBrush(QBrush(QColor(238, 238, 0)));
			painter.drawRoundRect(rect, 25, 25);
			painter.drawText(8.4*_d, 1.1*_d, "P2");
		}
	}
}


QPoint Board::lefttop(int row, int col)
{
	QPoint ret;
	ret.rx() = col *  _d - _d/2;
	ret.ry() = row *  _d - 0.35 * _d;
	return ret;
}
QPoint Board::lefttop(int id)
{
	return lefttop(_s[id]._row, _s[id]._col);
}
void Board::drawStone(QPainter& painter, int id)
{
	if(_s[id]._dead)
		return;
	QRect rect = QRect(lefttop(id).rx(), lefttop(id).ry(), _d, 0.7*_d);

	if(!_s[id]._showed)
	{
		painter.drawRoundRect(rect, 25, 25);
		painter.setBrush(QBrush(QColor(162, 205, 90)));
		painter.drawRoundRect(rect, 25, 25);
	}
	else
	{
		//画对应的背景颜色
		//被选中,变灰色
		if(id == _selectid)
			painter.setBrush(QBrush(Qt::gray));
		//不被选中，画对应的颜色
		if(_s[id]._red && id != _selectid)
			painter.setBrush(QBrush(QColor(255, 99, 71)));
		else if(id != _selectid)
			painter.setBrush(QBrush(QColor(238, 238, 0)));
		painter.drawRoundRect(rect, 25, 25);
		//画字
		painter.setFont(QFont("system", _d, 100));
		painter.drawText(rect, _s[id].getText(), QTextOption(Qt::AlignCenter));
	}
}
//基本正确
bool Board::getRowCol(QPoint pt, int &row, int &col)
{
	for(row=1; row<=17; row++)
	{
		for(col=1; col<=5; col++)
		{
			QPoint c = lefttop(row, col);
			int dx = abs(c.x()-pt.x());
			int dy = abs(c.y()-pt.y());
			int distx = dx * 100;
			int disty = dy * 100;
			if(distx < _d*100 && disty<0.7*_d*100)
				return true;
		}
	}
    return false;
}
int Board::whichKind(int row, int col)
{
	//1是铁路，2是行营，3是公路
	//铁路
	if(row==2||row==16||(row>=6&&row<=12))
	{
		return 1;
	}
	else if((col==1||col==5)&&(row>=2&&row<=16))
	{
		return 1;
	}
	//行营
	else if((row==3||row==5||row==13||row==15)&&(col==2||col==4))
	{
		return 2;
	}
	else if((row==4||row==14)&&col==3)
	{
		return 2;
	}
	else
	{
		return 3;
	}
}

int Board::getChessId(int row, int col)
{
	for(int i=0; i<50; i++)
	{
		if(_s[i]._row == row && _s[i]._col == col && !_s[i]._dead)
			return i;
	}
	return -1;
}

//深搜判断工兵是否能走
void Board::canMoveGongbing(int nowrow, int nowcol, int endrow, int endcol, int vis[18][6], int *flag)
{
	int dir[4][2]={{0,-1}, {1,0}, {0,1}, {-1,0}}; //左下右上,0123
	int tx,ty;
	if(nowrow == endrow && nowcol==endcol)
	{
		*flag = 1;
		return ;
	}
	if(!(*flag))
	{
		for(int i=0; i<4; i++)
		{
			tx = nowrow + dir[i][0];
			ty = nowcol + dir[i][1];
			//tx,ty修正
			if(tx==8||tx==10||((tx==7||tx==9||tx==11)&&(ty==2||ty==4)))
			{
				tx = tx + dir[i][0];
				ty = ty + dir[i][1];
			}
			if(i==1||i==3)
			{
				if((tx>=7&&tx<=11)&&(ty==2||ty==4))
					continue;
			}
			if(tx<1 || tx>17 || ty<1 || ty>5 || whichKind(tx,ty)!=1)
				continue;
			int yyy = getChessId(tx, ty);
			if((vis[tx][ty]!=1 && yyy==-1)||(tx == endrow && ty==endcol))
			{
				vis[tx][ty]=1;
				canMoveGongbing(tx, ty, endrow, endcol, vis, flag);
				vis[tx][ty]=0;
			}
		}
	}
	return ;
}

bool Board::canMove(int moveid, int row, int col, int killid)
{
	if(moveid == -1)
		return false;
	if(_s[moveid]._type == Stone::DILEI || _s[moveid]._type == Stone::JUNQI)
		return false;
	//挖掉空掉的位置
	if(row==8||row==10)
	{
		return false;
	}
	if((row==7||row==9||row==11)&&(col==2||col==4))
	{
		return false;
	}
	//选中的棋子或者目标是行营
	if(whichKind(_s[moveid]._row,_s[moveid]._col)==2||whichKind(row, col)==2)
	{
		int tx = abs(_s[moveid]._row-row);
		int ty = abs(_s[moveid]._col-col);
		if(tx>1||ty>1)
		{
			return false;
		}
	}
	//选中的棋子在铁路上，目标也在铁路上
	else if(whichKind(_s[moveid]._row,_s[moveid]._col)==1 && whichKind(row, col)==1)
	{
		//工兵特判
		//不管选棋和走棋终点，只用min和max保存。从
		if(_s[moveid]._type==Stone::GONGBING)
		{
			int vis[18][6];
			int flag = 0;
			canMoveGongbing(_s[moveid]._row, _s[moveid]._col, row, col, vis, &flag);
			if(!flag)
				return false;
		}
		//没点击直线
		else if(row-_s[moveid]._row!=0 && col-_s[moveid]._col!=0)
		{
			return false;
		}
		//点击了直线
		else
		{
			//如果中间有棋子阻挡，false
			//走竖,列不变
			if(col-_s[moveid]._col==0)
			{
				int minrow = _s[moveid]._row < row ? _s[moveid]._row:row;
				int maxrow = _s[moveid]._row > row ? _s[moveid]._row:row;
				for(int i = minrow+1; i<maxrow; i++)
				{
					if(whichKind(i,_s[moveid]._col)!=1)
						return false;
					if(i==8||i==10)
						continue;
					if((i==7||i==11)&&(_s[moveid]._col==2||_s[moveid]._col==4))
						return false;
					//遍历判断是否有棋子阻挡
					for(int j=0; j<50; j++)
					{
						if(_s[j]._dead)
							continue;
						else
						{
							if(_s[j]._row==i && _s[j]._col==col)
								return false;
						}
					}
				}
			}
			//走横，行不变
			if(row-_s[moveid]._row==0)
			{
				int mincol = _s[moveid]._col < col ? _s[moveid]._col:col;
				int maxcol = _s[moveid]._col > col ? _s[moveid]._col:col;
				for(int i = mincol+1; i<maxcol; i++)
				{
					if(whichKind(_s[moveid]._row,i)!=1)
						return false;
					//遍历判断是否有棋子阻挡
					for(int j=0; j<50; j++)
					{
						if(_s[j]._dead)
							continue;
						else
						{
							if(_s[j]._col==i && _s[j]._row==row)
								return false;
						}
					}
				}
			}
		}
	}
	//不在铁路上，走了大于1步，false
	else
	{
		int tx = abs(_s[moveid]._row-row);
		int ty = abs(_s[moveid]._col-col);
		if(tx+ty>1)
		{
			return false;
		}
	}
	//目标位置是棋子
	if(killid != -1)
	{
		//目标没翻开
		if(_s[killid]._showed == false)
			return false;
		//已选棋子和目标位置棋子颜色一样，
		if(_s[moveid]._red == _s[killid]._red)
		{
			return false;
		}
		//目标棋子在行营里，false
		if(whichKind(row, col)==2)
		{
			return false;
		}
		//地雷大于3不能吃军旗
		if(_s[moveid]._red && _yellowDileiNum!=0 && _s[killid]._type==Stone::JUNQI)
		{
			return false;
		}
		else if(!_s[moveid]._red && _redDileiNum!=0 && _s[killid]._type==Stone::JUNQI)
		{
			return false;
		}
		//moveid不是炸弹和地雷但是点击了地雷，false
		if(_s[moveid]._type!=Stone::ZHADAN && _s[moveid]._type!=Stone::GONGBING && _s[killid]._type==Stone::DILEI)
		{
			return false;
		}
		//工兵可以挖地雷
		else if(_s[moveid]._type == Stone::GONGBING&&_s[killid]._type == Stone::DILEI)
		{
			return true;
		}
	}
	return true;
}
void Board::confirmColor(int clickid)
{
	//轮到P1
	if(_P1Turn)
	{
		if(_colorflag1)
		{
			if(_P1lastcolor==_s[clickid]._red)
			{
				_P1color=_s[clickid]._red;
				_colorflag1=false;
				_colorflag2=false;
				_colorflag=true;
			}
		}
		else
		{
			_P1lastcolor=_s[clickid]._red;
			_colorflag1=true;
		}
	}
	//轮到P2
	else
	{
		if(_colorflag2)
		{
			if(_P2lastcolor==_s[clickid]._red)
			{
				_P1color=!_s[clickid]._red;
				_colorflag1=false;
				_colorflag2=false;
				_colorflag=true;
			}
		}
		else
		{
			_P2lastcolor=_s[clickid]._red;
			_colorflag2=true;
		}
	}
}

void Board::mouseReleaseEvent(QMouseEvent *ev)
{
	if(ev->button() != Qt::LeftButton)
	{
		return;
	}
	QPoint pt = ev->pos();
	//由getRowCol转化成棋子的行列
	//判断这个行列上有没有棋子
	//row,col为鼠标点击的坐标
	int row, col;
	bool bRet = getRowCol(pt, row, col);
	//点到棋盘外
	if(bRet == false)
	{
		if(_selectid!=-1)
		{
			_selectid = -1;
			update();
		}
		return;
	}
	int id = getChessId(row, col);
	click(id, row, col);
}
void Board::doShow(int clickid)
{
	_s[clickid]._showed = true;
	//还未确认双方颜色
	if(!_colorflag)
	{
		confirmColor(clickid);
	}
	_P1Turn=!_P1Turn;
	//if(_colorflag)
		//_P1color=!_P1color;
}
void Board::unmoveStone(int moveid, int row, int col)
{
	if(moveid == -1) return;
	_s[moveid]._row = row;
	_s[moveid]._col = col;
	_P1Turn = !_P1Turn;
}

void Board::moveStone(int moveid, int row, int col)
{
	if(moveid == -1) return;
	_s[moveid]._row = row;
	_s[moveid]._col = col;
	_P1Turn = !_P1Turn;
	//_P1color = !_P1color;
}
void Board::moveStone(int moveid, int row, int col, int killid)
{
	if(killid!=-1)
		eatStone(moveid, row, col, killid);
	else
		moveStone(moveid, row, col);
	_selectid = -1;
}
void Board::click(int clickid, int row, int col)
{
	//自己点自己取消选中
	if(_selectid == clickid && _s[clickid]._showed)
	{
		_selectid = -1;
	}
	//选中了棋子还去翻棋子，就把选中的取消，并且不翻开棋子
	else if(_selectid != -1 && clickid != -1 && _s[clickid]._showed == false)
	{
		_selectid = -1;
	}
	//点击了棋子并且没选中棋子和没翻开，执行翻开
	else if(clickid != -1 && _s[clickid]._showed==false && _selectid == -1)
	{
		doShow(clickid);
		if(!_P1Turn)
			_P1StepNum++;
	}
	//点击了棋子，且没有棋子变灰色,执行选中
	else if(_selectid == -1 && clickid != -1 && _s[clickid]._showed && _colorflag)
	{
		//当前走方的颜色和棋子颜色一致，true
		if(_P1Turn)
		{
			if(_P1color == _s[clickid]._red)
			{
				//无法选中地雷和军旗
				if(_s[clickid]._type!=Stone::JUNQI&&_s[clickid]._type!=Stone::DILEI)
					_selectid = clickid;
			}
		}
		else
		{
			if(!_P1color == _s[clickid]._red)
			{
				//无法选中地雷和军旗
				if(_s[clickid]._type!=Stone::JUNQI&&_s[clickid]._type!=Stone::DILEI)
					_selectid = clickid;
			}
		}
	}
	//选中棋子还点自己棋子，换选
	else if(_selectid!=-1 && _s[clickid]._red == _s[_selectid]._red)
	{
		if(_s[clickid]._type!=Stone::JUNQI && _s[clickid]._type!=Stone::DILEI && !_s[clickid]._dead)
			_selectid = clickid;
	}
	//有棋子被选中还点击了其他位置，执行移动
	else if(_selectid != -1)
	{
		if(canMove(_selectid, row, col, clickid))
		{
				moveStone(_selectid, row, col, clickid);
		}
		if(!_P1Turn)
			_P1StepNum++;
	}
	update();
}
void Board::uneatStone(int moveid, int row, int col, int killid)
{
	if(_s[moveid]._type == Stone::GONGBING && _s[killid]._type == Stone::DILEI)
	{
		_s[killid]._dead = false;
		if(_s[killid]._red==false)
			_redDileiNum++;
		else
			_yellowDileiNum++;
		unmoveStone(moveid, row, col);
	}
	else if(_s[moveid]._type == Stone::ZHADAN ||_s[killid]._type == Stone::ZHADAN||_s[moveid]._eatPower == _s[killid]._eatPower)
	{
		_s[moveid]._dead = false;
		_s[killid]._dead = false;
		_P1Turn=!_P1Turn;
		//_P1color=!_P1color;
	}
	else if(_s[moveid]._eatPower > _s[killid]._eatPower)
	{
		_s[killid]._dead=false;
		unmoveStone(moveid, row, col);
	}
	else if(_s[moveid]._eatPower < _s[killid]._eatPower)
	{
		_s[moveid]._dead = false;
		_selectid = -1;
		_P1Turn=!_P1Turn;
	}
}

void Board::eatStone(int moveid, int row, int col, int killid)
{
	if(_s[moveid]._type == Stone::GONGBING && _s[killid]._type == Stone::DILEI)
	{
		_s[killid]._dead = true;
		if(_s[killid]._red==true)
			_redDileiNum--;
		else
			_yellowDileiNum--;
		moveStone(moveid, row, col);
	}
	else if(_s[moveid]._type == Stone::ZHADAN ||_s[killid]._type == Stone::ZHADAN||_s[moveid]._eatPower == _s[killid]._eatPower)
	{
		_s[moveid]._dead = true;
		_s[killid]._dead = true;
		_P1Turn=!_P1Turn;
		//_P1color=!_P1color;
	}
	else if(_s[moveid]._eatPower > _s[killid]._eatPower)
	{
		_s[killid]._dead=true;
		moveStone(moveid, row, col);
		if(_s[killid]._type == Stone::JUNQI && _s[killid]._red == _P1color)
		{
			QMessageBox msg(this);
			msg.setText("P1输了");
			msg.setStandardButtons(QMessageBox::Yes);
			if(msg.exec()==QMessageBox::Yes)
			{
				Board::close();
			}
		}
		else if(_s[killid]._type == Stone::JUNQI && _s[killid]._red == !_P1color)
		{
			QMessageBox msg(this);
			msg.setText("P2输了");
			msg.setStandardButtons(QMessageBox::Yes);
			if(msg.exec()==QMessageBox::Yes)
			{
				Board::close();
			}
		}
	}
	else if(_s[moveid]._eatPower < _s[killid]._eatPower)
	{
		_s[moveid]._dead = true;
		_selectid = -1;
		_P1Turn=!_P1Turn;
	}
}

void Board::saveStep(int moveid, int row, int col, int killid, QVector<Step *> &steps)
{
	Step *step = new Step;
	step->_rowFrom = _s[moveid]._row;
	step->_colFrom = _s[moveid]._col;
	step->_rowTo = row;
	step->_colTo = col;
	step->_moveid = moveid;
	step->_killid = killid;

	steps.append(step);
}
void Board::P1SurrenderDialog()
{
	QMessageBox msg(this);
	msg.setText("P1认输");
	msg.setStandardButtons(QMessageBox::Ok);
	if(msg.exec()==QMessageBox::Ok)
	{
		Board::close();
	}
}
void Board::P2SurrenderDialog()
{
	QMessageBox msg(this);
	msg.setText("P2认输");
	msg.setStandardButtons(QMessageBox::Ok);
	if(msg.exec()==QMessageBox::Ok)
	{
		Board::close();
	}
}
void Board::Reconciliation()
{
	QMessageBox msg(this);
	msg.setText("请求和局");
	msg.setStandardButtons(QMessageBox::Yes| QMessageBox::No);
	if(msg.exec()==QMessageBox::Yes)
	{
		Board::close();
	}
}
