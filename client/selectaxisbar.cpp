#include "selectaxisbar.h"
#include "machiningstates.h"
#include "base/systemvariables.hpp"
#include "remotevariables.hpp"
#include "common/rmi/globals.h"
#include "physicalbuttonsprocessor.h"
#include "base/globals.h"

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
	//按钮初始化
	const int checkDelay = 50;
	for (int i = 0; i < axisButtons_.size(); ++i)
	{
		auto x = axisButtons_.at(i);
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
	// 外设按钮响应
	connect(&base::getInstance<PhysicalButtonsProcessor>(),SIGNAL(rightButtonPlusPress(int)), this, SLOT(plusButtonClicked(int)));
	connect(&base::getInstance<PhysicalButtonsProcessor>(),SIGNAL(rightButtonMinusPress(int)), this, SLOT(minusButtonClicked(int)));
	connect(&base::getInstance<PhysicalButtonsProcessor>(),SIGNAL(rightButtonPlusRealease(int)), this, SLOT(plusButtonRealeased(int)));
	connect(&base::getInstance<PhysicalButtonsProcessor>(),SIGNAL(rightButtonMinusRealease(int)), this, SLOT(minusButtonRealeased(int)));
	connect(&base::getInstance<PhysicalButtonsProcessor>(),SIGNAL(rightButtonStart()), this, SLOT(startButtonClicked()));
	connect(&base::getInstance<PhysicalButtonsProcessor>(),SIGNAL(rightButtonStop()), this, SLOT(stopButtonClicked()));
	connect(&base::getInstance<PhysicalButtonsProcessor>(),SIGNAL(rightButtonReset()), this, SLOT(resetButtonClicked()));
	connect(&base::getInstance<PhysicalButtonsProcessor>(),SIGNAL(rightButtonStartRealease()), this, SLOT(startButtonRealeased()));
	connect(&base::getInstance<PhysicalButtonsProcessor>(),SIGNAL(rightButtonStopRealease()), this, SLOT(stopButtonRealeased()));
	connect(&base::getInstance<PhysicalButtonsProcessor>(),SIGNAL(rightButtonResetRealease()), this, SLOT(resetButtonRealeased()));
}

SelectAxisBar::~SelectAxisBar()
{

}

void SelectAxisBar::plusButtonClicked(int key)
{
	// 轴选jog+，按键在显示轴范围内有对应，将相应plc置位
	if (key - base::RIGHTBUTTON1 < base::getInstance<MachiningStates>().validAxes().size())
	{
		base::getInstance<Network>().setPlcVariable(rmi::G_JMPLUS, 1 << base::getInstance<MachiningStates>().validAxes().at(key - base::RIGHTBUTTON1));
	}
}

void SelectAxisBar::minusButtonClicked(int key)
{
	// 轴选jog-，按键在显示轴范围内有对应，将相应plc置位
	if (key - base::RIGHTBUTTON1 < base::getInstance<MachiningStates>().validAxes().size())
	{
		base::getInstance<Network>().setPlcVariable(rmi::G_JMMINUS, 1 << base::getInstance<MachiningStates>().validAxes().at(key - base::RIGHTBUTTON1));
	}
}

void SelectAxisBar::plusButtonRealeased(int key)
{
	// jog+按钮松开，将plc移轴位置0
	base::getInstance<Network>().setPlcVariable(rmi::G_JMPLUS, 0);
}

void SelectAxisBar::minusButtonRealeased(int key)
{
	// jog-按钮松开，将plc移轴位置0
	base::getInstance<Network>().setPlcVariable(rmi::G_JMMINUS, 0);
}

void SelectAxisBar::startButtonClicked()
{
	// 启动按钮按下
	base::getInstance<Network>().setPlcVariable(rmi::G_CYCLESTART, 1);
}

void SelectAxisBar::startButtonRealeased()
{
	// 启动按钮松开
	base::getInstance<Network>().setPlcVariable(rmi::G_CYCLESTART, 0);
}

void SelectAxisBar::stopButtonClicked()
{
	// 停止按钮按下
	base::getInstance<Network>().setPlcVariable(rmi::G_PROGSTOP, 1);
}

void SelectAxisBar::stopButtonRealeased()
{
	// 停止按钮松开
	base::getInstance<Network>().setPlcVariable(rmi::G_PROGSTOP, 0);
}

void SelectAxisBar::resetButtonClicked()
{
	// 重置按钮按下
	base::getInstance<Network>().setPlcVariable(rmi::G_RESET, 1);
}

void SelectAxisBar::resetButtonRealeased()
{
	// 重置按钮松开
	base::getInstance<Network>().setPlcVariable(rmi::G_RESET, 0);
}

void SelectAxisBar::setValidAxes(const std::vector<ltp::base::Axis> validAxes)
{
	//先将所有按钮无效化
	for (int i = 0; i < axisButtons_.size(); ++i)
	{
		axisButtons_[i]->setEnabled(false);
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
		for (auto it = buttonsAxisEnumMap_.begin(); it != buttonsAxisEnumMap_.end(); ++it)
		{
			//有效轴设置可点按
			it->first->setEnabled(true);
			//清空选中状态
			it->first->setChecked(false);
			//选中当前轴
			if (it->second + 1 == remoteSelectedAxis)
			{
				it->first->setChecked(true);
			}
		}
		ui.modeLabel_->setText(tr("手轮"));
		//手轮倍率显示
		int handwheelOverride = static_cast<int>(systemVariables.macroVariable(base::HANDWHEEL_OVERRIDE));
		ui.overrideLabel_->setText(QString::number(handwheelOverride) + "%");
	}
	else if (machiningStates.mode() == base::JOG)
	{
		for (auto it = buttonsAxisEnumMap_.begin(); it != buttonsAxisEnumMap_.end(); ++it)
		{
			//有效轴设置可点按
			it->first->setEnabled(true);
			//清空选中状态
			it->first->setChecked(false);
		}
		ui.modeLabel_->setText(tr("JOG"));
		//jog倍率显示
		int jogOverride = static_cast<int>(systemVariables.macroVariable(base::JOG_OVERRIDE) * 100);
		ui.overrideLabel_->setText(QString::number(jogOverride) + "%");
	}
	else
	{
		//非jog和手轮不能轴选
		for (auto it = buttonsAxisEnumMap_.begin(); it != buttonsAxisEnumMap_.end(); ++it)
		{
			//有效轴设置不可点按
			it->first->setEnabled(false);
			//清空选中状态
			it->first->setChecked(false);
		}
		ui.modeLabel_->setText("");
		ui.overrideLabel_->setText("");
	}
}