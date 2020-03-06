#include "selectaxisbar.h"

#include "machiningstates.h"

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

	// 模式更新
	connect(&base::getInstance<MachiningStates>(), SIGNAL(modeChanged(base::Mode)), this, SLOT(setMode(base::Mode)));

}

SelectAxisBar::~SelectAxisBar()
{

}

void SelectAxisBar::setMode(ltp::base::Mode mode)
{
	switch (mode)
	{
	case ltp::base::HANDLE:			// 手轮
		ui.modeLabel_->setText(tr("手轮"));
		break;
	case ltp::base::JOG:			// JOG
		ui.modeLabel_->setText(tr("JOG"));
		break;
	default:						// 其他模式不支持模式，倍率显示
		ui.modeLabel_->setText(tr(""));
		ui.rateLabel_->setText(tr(""));
		break;
	}
};

void SelectAxisBar::setRate(int rate)
{
	if (ui.modeLabel_->text() != "")			// 是手轮或JOG模式，支持倍率显示
	{
		QString str = QString::number(rate) + QString("%");
		ui.rateLabel_->setText(str);
	}
}