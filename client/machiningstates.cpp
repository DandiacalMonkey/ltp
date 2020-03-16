#include "machiningstates.h"
#include "network.h"
#include "base/systemvariables.hpp"
#include "remotevariables.hpp"
#include "physicalbuttonsprocessor.h"
#include "base/globals.h"

using ltp::client::MachiningStates;

MachiningStates::MachiningStates(QObject* parent)
	: QObject(parent),
	  mode_(base::CODELESS),
	  machiningState_(base::READY),
	  errorLevel_(base::NO_ERROR)
{
	//状态刷新
	const int kInterval = 200;
	timer_.start(kInterval);
	connect(&timer_, SIGNAL(timeout()), SLOT(updateState()));
	//网络连接时，确认有效轴
	connect(&base::getInstance<Network>(), SIGNAL(connected(const std::string&)), SLOT(updateAxesInformation()));
	// 下排外设按钮响应
	connect(&base::getInstance<PhysicalButtonsProcessor>(),SIGNAL(bottomButtonModeClicked(int)), this, SLOT(modeChanged(int)));
	connect(&base::getInstance<PhysicalButtonsProcessor>(),SIGNAL(bottomButtonRateClicked(int)), this, SLOT(rateChanged(int)));
	//初始化轴枚举到轴字符映射关系
	axisEnumAxisCharacterMap_[base::X_AXIS] = 'X';
	axisEnumAxisCharacterMap_[base::Y_AXIS] = 'Y';
	axisEnumAxisCharacterMap_[base::Z_AXIS] = 'Z';
	axisEnumAxisCharacterMap_[base::A_AXIS] = 'A';
	axisEnumAxisCharacterMap_[base::B_AXIS] = 'B';
	axisEnumAxisCharacterMap_[base::C_AXIS] = 'C';
	axisEnumAxisCharacterMap_[base::U_AXIS] = 'U';
	axisEnumAxisCharacterMap_[base::V_AXIS] = 'V';
	axisEnumAxisCharacterMap_[base::W_AXIS] = 'W';
	//初始化轴字符到轴枚举映射关系
	for each (auto x in axisEnumAxisCharacterMap_)
	{
		axisCharacterAxisEnumMap_[x.second] = x.first;
	}
}

MachiningStates::~MachiningStates()
{

}

void MachiningStates::rateChanged(int buttonID)
{
	switch (buttonID)
	{
	case base::BOTTOMBUTTON6:			// X1 5%
		break;
	case base::BOTTOMBUTTON7:			// X10 25%
		break;
	case base::BOTTOMBUTTON8:			// X100 50%
		break;
	case base::BOTTOMBUTTON9:			// X200 100%
		break;
	default:
		break;
	}
}

void MachiningStates::modeChanged(int buttonID)
{
	switch (buttonID)
	{
	case base::BOTTOMBUTTON1:			// 自动
		break;
	case base::BOTTOMBUTTON2:			// JOG
		break;
	case base::BOTTOMBUTTON3:			// 手轮
		break;
	default:
		break;
	}
}

ltp::base::Mode MachiningStates::mode() const
{
	return static_cast<base::Mode>(static_cast<int>(
		base::getInstance<base::SystemVariables<RemoteVariables>>().macroVariable(base::SYSTEM_MODE)));
}

ltp::base::MachiningState MachiningStates::machiningState() const
{
	auto& systemVariables = base::getInstance<base::SystemVariables<RemoteVariables>>();
	//PLC中就绪标志
	if (systemVariables.plcVariable(rmi::F_READY) != 0)
	{
		return base::READY;
	}
	//PLC中警告标志
	if (systemVariables.plcVariable(rmi::F_HOLDING) != 0)
	{
		return base::HOLD;
	}
	//PLC中运行标志
	if (systemVariables.plcVariable(rmi::F_RUNNING) != 0)
	{
		return base::BUSY;
	}
	//默认为停止状态
	return base::STOP;
}

QString MachiningStates::machiningFilePath() const
{
	return QString();
}

QString MachiningStates::machiningFileName() const
{
	return QString();
}

ltp::base::ErrorLevel MachiningStates::errorLevel() const
{
	auto& systemVariables = base::getInstance<base::SystemVariables<RemoteVariables>>();
	//CI错误和致命错误，表示有报错
	if (systemVariables.plcVariable(rmi::F_CIERR) != 0 | 
		systemVariables.plcVariable(rmi::F_FATALERR) != 0)
	{
		return base::ERROR;
	}
	//PLC的警告标志位
	else if (systemVariables.plcVariable(rmi::F_WARN) != 0)
	{
		return base::WARNNING;
	}
	return base::NO_ERROR;
}

const std::vector<ltp::base::Axis>& ltp::client::MachiningStates::validAxes() const
{
	return validAxes_;
}

char MachiningStates::axisEnumToAxisCharacter(ltp::base::Axis axisEnum) const
{
	return axisEnumAxisCharacterMap_.at(axisEnum);
}

std::vector<char> ltp::client::MachiningStates::axesEnumToAxesCharacter(const std::vector<base::Axis>& axesEnum) const
{
	std::vector<char> result;
	for each (auto x in axesEnum)
	{
		result.push_back(axisEnumToAxisCharacter(x));
	}
	return std::move(result);
}

ltp::base::Axis ltp::client::MachiningStates::axisCharacterToAxisEnum(char axisCharacter) const
{
	return axisCharacterAxisEnumMap_.at(axisCharacter);
}

std::vector<ltp::base::Axis> ltp::client::MachiningStates::axesCharacterToAxesEnum(const std::vector<char>& axesCharacter) const
{
	std::vector<base::Axis> result;
	for each (auto x in axesCharacter)
	{
		result.push_back(axisCharacterToAxisEnum(x));
	}
	return std::move(result);
}

int ltp::client::MachiningStates::axisEnumToAxisAddress(base::Axis axisEnum) const
{
	return axesAddress_.at(axisEnum);
}

void MachiningStates::updateState()
{
	//模式
	auto remoteMode = mode();
	if (mode_ != remoteMode)
	{
		mode_ = remoteMode;
		emit modeChanged(mode_);
	}
	//状态
	auto remoteMachiningState = machiningState();
	if (machiningState_ != remoteMachiningState)
	{
		machiningState_ = remoteMachiningState;
		emit machiningStateChanged(machiningState_);
	}
	//报错等级
	auto remoteErrorLevel = errorLevel();
	if (errorLevel_ != remoteErrorLevel)
	{
		errorLevel_ = remoteErrorLevel;
		emit errorLevelChanged(errorLevel_);
	}
}

void MachiningStates::updateAxesInformation()
{
	auto& systemVariables = base::getInstance<base::SystemVariables<RemoteVariables>>();
	//控制器上的有效轴
	auto remoteValidAxes = axesCharacterToAxesEnum(systemVariables.validFeedAxes());
	//对比有效轴
	if (validAxes_ != remoteValidAxes)
	{
		validAxes_ = std::move(remoteValidAxes);
		emit validAxesChanged(validAxes_);
	}
	//更新轴地址
	auto remoteAxesAddress = systemVariables.axesAddress();
	axesAddress_.clear();
	for each (auto x in remoteAxesAddress)
	{
		axesAddress_[axisCharacterToAxisEnum(x.first)] = x.second;
	}
}