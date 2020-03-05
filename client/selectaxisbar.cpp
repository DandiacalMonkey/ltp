#include "selectaxisbar.h"

using ltp::client::SelectAxisBar;

SelectAxisBar::SelectAxisBar(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//进给轴
	axisButtons_[0] = ui.axisButton1_;
	axisButtons_[1] = ui.axisButton2_;
	axisButtons_[2] = ui.axisButton3_;
	axisButtons_[3] = ui.axisButton4_;
	axisButtons_[4] = ui.axisButton5_;
	//法向轴
	normalDirectionAxisButton_ = ui.axisButton6_;
	//按钮建立互斥性
	for each (auto var in axisButtons_)
	{
		var->setAutoExclusive(true);
	}
	normalDirectionAxisButton_->setAutoExclusive(true);

}

SelectAxisBar::~SelectAxisBar()
{

}