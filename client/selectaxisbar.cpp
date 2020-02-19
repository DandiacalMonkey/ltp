#include "selectaxisbar.h"

using ltp::client::SelectAxisBar;

SelectAxisBar::SelectAxisBar(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	// 按钮建立互斥性
	ui.axisButton1_->setAutoExclusive(true);
	ui.axisButton2_->setAutoExclusive(true);
	ui.axisButton3_->setAutoExclusive(true);
	ui.axisButton4_->setAutoExclusive(true);
	ui.axisButton5_->setAutoExclusive(true);
	ui.axisButton6_->setAutoExclusive(true);
}

SelectAxisBar::~SelectAxisBar()
{

}