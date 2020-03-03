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
	static unsigned long targetValue;
	ui.singleSection_->setCheckFunction(
		[]()
		{
			return base::getInstance<Network>().plcVariable(rmi::F_SINGLE) == 1;
		}, 200);
	ui.singleSection_->setClickDelayCheck(
		[singleSection]()
		{
			targetValue = singleSection->isChecked() ? 0 : 1;
			base::getInstance<Network>().setPlcVariable(rmi::G_SINGLE, targetValue);
		}, 50,
		[singleSection]()
		{
			if (base::getInstance<Network>().plcVariable(rmi::F_SINGLE) == targetValue)
			{
				singleSection->setChecked(targetValue == 1);
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
