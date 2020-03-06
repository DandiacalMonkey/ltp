#include "selectaxisbar.h"
#include "machiningstates.h"
#include "base/systemvariables.hpp"
#include "remotevariables.hpp"
#include "common/rmi/globals.h"

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
	//按钮初始化
	const int checkDelay = 50;
	for each (auto x in axisButtons_)
	{
		var->setAutoExclusive(true);
		//默认为disable
		x->setEnabled(false);
		//按钮按下和延迟确认
		x->setAutoChecked(false);
		x->setClickDelayCheck(
			[this, x]()
			{
				base::getInstance<base::SystemVariables<RemoteVariables>>().
					setPlcVariable(rmi::G_AXIS, buttonsAxisEnumMap_.at(x) + 1);
			}, checkDelay,
			[this]()
			{
				base::getInstance<base::SystemVariables<RemoteVariables>>().
					setPlcVariable(rmi::G_AXIS, 0);
				updateInformation();
			});
	}
	normalDirectionAxisButton_->setAutoExclusive(true);

	normalDirectionAxisButton_->setEnabled(false);
	//设定有效轴
	connect(&base::getInstance<MachiningStates>(),
		SIGNAL(validAxesChanged(const std::vector<base::Axis>&)),
		SLOT(setValidAxes(const std::vector<base::Axis>&)));
	//刷新选中轴
	const int kUpdateInterval = 200;
	timer.start(kUpdateInterval);
	connect(&timer, SIGNAL(timeout()), SLOT(updateInformation()));
	connect(&base::getInstance<MachiningStates>(),
		SIGNAL(modeChanged(base::Mode)), SLOT(updateInformation()));
}

SelectAxisBar::~SelectAxisBar()
{



}

void SelectAxisBar::setValidAxes(const std::vector<ltp::base::Axis> validAxes)
{
	//先将所有按钮无效化
	for each (auto x in axisButtons_)
	{
		x->setEnabled(false);
	}
	//清空映射内容，需要重建
	buttonsAxisEnumMap_.clear();
	for (int i = 0; i < kMaxFeedAxes && i < validAxes.size(); i++)
	{
		axisButtons_[i]->setText(QChar(base::getInstance<MachiningStates>().
			axisEnumToAxisCharacter(validAxes[i])));
		buttonsAxisEnumMap_[axisButtons_[i]] = validAxes[i];
		axisButtons_[i]->setEnabled(true);
	}
}

void SelectAxisBar::updateInformation()
{
	auto& systemVariables = base::getInstance<base::SystemVariables<RemoteVariables>>();
	auto& machiningStates = base::getInstance<MachiningStates>();
	//处于手轮模式
	if (machiningStates.mode() == base::HANDLE)
	{
		//当前选中轴的轴地址
		auto remoteSelectedAxis = systemVariables.plcVariable(rmi::F_AXIS);
		for each (auto x in buttonsAxisEnumMap_)
		{
			//有效轴设置可点按
			x.first->setEnabled(true);
			//清空选中状态
			x.first->setChecked(false);
			//选中当前轴
			if (x.second + 1 == remoteSelectedAxis)
			{
				x.first->setChecked(true);
			}
		}
		ui.modeLabel_->setText(tr("手轮"));
		//手轮倍率显示
		int handwheelOverride = static_cast<int>(systemVariables.macroVariable(base::HANDWHEEL_OVERRIDE));
		ui.overrideLabel_->setText(QString::number(handwheelOverride) + "%");
	}
	else if (machiningStates.mode() == base::JOG)
	{
		
		for each (auto x in buttonsAxisEnumMap_)
		{
			//有效轴设置可点按
			x.first->setEnabled(true);
			//清空选中状态
			x.first->setChecked(false);
		}
		ui.modeLabel_->setText(tr("JOG"));
		//jog倍率显示
		int jogOverride = static_cast<int>(systemVariables.macroVariable(base::JOG_OVERRIDE) * 100);
		ui.overrideLabel_->setText(QString::number(jogOverride) + "%");
	}
	else
	{
		//非jog和手轮不能轴选
		for each (auto x in buttonsAxisEnumMap_)
		{
			//有效轴设置不可点按
			x.first->setEnabled(false);
			//清空选中状态
			x.first->setChecked(false);
		}
		ui.modeLabel_->setText("");
		ui.overrideLabel_->setText("");
	}
