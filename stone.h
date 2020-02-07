#ifndef STONE_H
#define STONE_H

#include <QString>
#include <QTime>
#include <QDebug>

class Stone
{
public:
    Stone();

	enum TYPE{
		JUNQI, SILING, JUNZHANG, SHIZHANG, LVZHANG, TUANZHANG,
		YINGZHANG, LIANZHANG, PAIZHANG, DILEI, GONGBING, ZHADAN};

    int _row;
    int _col;
	TYPE _type;

    int _id;
	int _eatPower;
    bool _dead;
	bool _red;	//1=红色，0=黄色
	bool _showed;

	void init(int id);

	QString getText()
	{
		switch (this->_type) {
		case JUNQI:
			return "军旗";
		case SILING:
			return "司令";
		case JUNZHANG:
			return "军长";
		case SHIZHANG:
			return "师长";
		case LVZHANG:
			return "旅长";
		case TUANZHANG:
			return "团长";
		case YINGZHANG:
			return "营长";
		case LIANZHANG:
			return "连长";
		case PAIZHANG:
			return "排长";
		case DILEI:
			return "地雷";
		case GONGBING:
			return "工兵";
		case ZHADAN:
			return "炸弹";
		}
		return "错误";
	}
};

#endif // STONE_H
