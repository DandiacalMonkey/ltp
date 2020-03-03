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

	const int kAutoUpdateInterval = 200;
	const int kInitaltiveUpdateInterval = 50;

	//单节按钮
	auto singleSection = ui.singleSection_;
	static unsigned long singleSectionValue;
	ui.singleSection_->setCheckFunction(
		[]()
		{
			return base::getInstance<Network>().plcVariable(rmi::F_SINGLE) == 1;
		}, 200);
	ui.singleSection_->setClickDelayCheck(
		[singleSection]()
		{
			singleSectionValue = singleSection->isChecked() ? 0 : 1;
			base::getInstance<Network>().setPlcVariable(rmi::G_SINGLE, singleSectionValue);
		}, 50,
		[singleSection]()
		{
			if (base::getInstance<Network>().plcVariable(rmi::F_SINGLE) == singleSectionValue)
			{
				singleSection->setChecked(singleSectionValue == 1);
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