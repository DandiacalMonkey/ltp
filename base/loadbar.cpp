#include "loadbar.h"
#include <QDebug>

using ltp::base::LoadBar;

LoadBar::LoadBar(QWidget *parent)
	: QProgressBar(parent)
{
	this->setStyleSheet("QProgressBar{border:none; background-color:#E1E1E1; text-align:right; margin-right:45px; margin-left:35px; margin-top:3px; margin-bottom:3px; font:14px Arial;}");
	this->setFixedSize(200, 14);

	connect(this, SIGNAL(valueChanged(int)), this, SLOT(colorChanged(int)));
}

LoadBar::~LoadBar()
{
}

void LoadBar::colorChanged(int value)
{
	QString styleSheet = "QProgressBar{border:none; background-color:#E1E1E1; text-align:right; margin-right:45px; margin-left:35px; margin-top:3px; margin-bottom:3px; font:14px Arial;} \
						  QProgressBar::chunk {background-color:%0}";
	if (value < 40)								// 绿色范围
	{
		this->setStyleSheet(styleSheet.arg("#00AA3C"));
	} 
	else if (value >= 40 && value < 70)			// 黄色范围
	{
		this->setStyleSheet(styleSheet.arg("#FFD524"));
	}
	else										// 红色警示范围
	{
		this->setStyleSheet(styleSheet.arg("#FA3200"));
	}
}
