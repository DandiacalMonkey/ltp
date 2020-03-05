#include "operationpanel.h"
#include "base/systemvariables.hpp"
#include "hintwidgetproxy.h"
#include "remotevariables.hpp"
#include "hintbar.h"

using ltp::client::OperationPanel;

OperationPanel::OperationPanel(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//自动刷新间隔
	const int kAutoUpdateInterval = 200;
	//主动刷新间隔（按钮按下后，需要确认功能是否正常开启）
	const int kInitaltiveUpdateInterval = 50;
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
	timer_->start(kAutoUpdateInterval);
	//单节按钮
	auto singleSection = ui.singleSection_;
	static unsigned long singleSectionValue;
	ui.singleSection_->setCheckFunction(
		[singleSection]()
		{
			singleSection->setChecked(base::getInstance<Network>().plcVariable(rmi::F_SINGLE) == 1);
		}, kAutoUpdateInterval);
	ui.singleSection_->setClickDelayCheck(
		[singleSection]()
		{
			singleSectionValue = base::getInstance<Network>().plcVariable(rmi::F_SINGLE);
			base::getInstance<Network>().setPlcVariable(rmi::G_SINGLE, 1);
		}, kInitaltiveUpdateInterval,
		[singleSection]()
		{
			base::getInstance<Network>().setPlcVariable(rmi::G_SINGLE, 0);
			if (base::getInstance<Network>().plcVariable(rmi::F_SINGLE) != singleSectionValue)
			{
				singleSection->setChecked(singleSectionValue == 0);
			}
			else
			{
				base::getInstance<HintWidgetProxy<HintBar>>().setHint("单节设定失败");
			}
		});
}

OperationPanel::~OperationPanel()
{

}

void OperationPanel::onTimer()
{
	// 获取进给速度F
	double dSpeedF = ltp::base::getInstance<ltp::base::SystemVariables<ltp::client::RemoteVariables>>().macroVariable(ltp::base::FEED_SPEED);
	ui.speedF_->setText(QString::number(dSpeedF, 'f', 1));
	// 获取进给速率
	double dRateF = ltp::base::getInstance<ltp::base::SystemVariables<ltp::client::RemoteVariables>>().macroVariable(ltp::base::FEED_RATE);
	ui.speedFButton_->setValue(dRateF);
}

void OperationPanel::changeFeedRate(int value)
{
	double rate = double(value);
	ltp::base::getInstance<ltp::base::SystemVariables<ltp::client::RemoteVariables>>().setMacroVariable(ltp::base::FEED_RATE, rate);
}