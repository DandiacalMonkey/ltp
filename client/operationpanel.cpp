#include "operationpanel.h"
#include "base/systemvariables.hpp"
#include "remotevariables.hpp"

using ltp::client::OperationPanel;

OperationPanel::OperationPanel(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	// 按钮设置
	ui.singleSection_->setButtonPicture(QPixmap(":/LtpClient/image/single_block.png"));
	ui.singleSection_->setButtonText(tr("单  节"));
	ui.handleWheelSimulation_->setButtonPicture(QPixmap(":/LtpClient/image/handwheel_simulation_rest.png"));
	ui.handleWheelSimulation_->setButtonText(tr("手轮模拟"));
	ui.skip_->setButtonPicture(QPixmap(":/LtpClient/image/skip_rest.png"));
	ui.skip_->setButtonText(tr("跳  过"));

	// 进给倍率修改
	connect(ui.speedFButton_, SIGNAL(valueChanged(int)), this, SLOT(changeFeedRate(int)));

	// 定时器循环更新
	QTimer *timer_ = new QTimer();
	connect(timer_, SIGNAL(timeout()), this, SLOT(onTimer()));
	timer_->start(500);
}

OperationPanel::~OperationPanel()
{

}

void OperationPanel::onTimer()
{
	// 获取进给速度F
	double dSpeedF = ltp::base::getInstance<ltp::base::SystemVariables<ltp::client::RemoteVariables>>().macroVariable(ltp::base::FEEDSPEED);
	ui.speedF_->setText(QString::number(dSpeedF, 'f', 1));
	// 获取进给速率
	double dRateF = ltp::base::getInstance<ltp::base::SystemVariables<ltp::client::RemoteVariables>>().macroVariable(ltp::base::FEEDRATE);
	ui.speedFButton_->setValue(dRateF);
}

void OperationPanel::changeFeedRate(int value)
{
	double rate = double(value);
	ltp::base::getInstance<ltp::base::SystemVariables<ltp::client::RemoteVariables>>().setMacroVariable(ltp::base::FEEDRATE, rate);
}