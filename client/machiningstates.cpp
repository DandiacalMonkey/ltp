#include "machiningstates.h"
#include "network.h"
#include "base/systemvariables.hpp"
#include "remotevariables.hpp"

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
	connect(&base::getInstance<Network>(), SIGNAL(connected()), SLOT(checkValidAxes()));
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
	axisCharacterAxisEnumMap_['X'] = base::X_AXIS;
	axisCharacterAxisEnumMap_['Y'] = base::Y_AXIS;
	axisCharacterAxisEnumMap_['Z'] = base::Z_AXIS;
	axisCharacterAxisEnumMap_['A'] = base::A_AXIS;
	axisCharacterAxisEnumMap_['B'] = base::B_AXIS;
	axisCharacterAxisEnumMap_['C'] = base::C_AXIS;
	axisCharacterAxisEnumMap_['U'] = base::U_AXIS;
	axisCharacterAxisEnumMap_['V'] = base::V_AXIS;
	axisCharacterAxisEnumMap_['W'] = base::W_AXIS;
}

MachiningStates::~MachiningStates()
{

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

void MachiningStates::checkValidAxes()
{
	auto& systemVariables = base::getInstance<base::SystemVariables<RemoteVariables>>();
	auto remoteValidAxes = axesCharacterToAxesEnum(systemVariables.validFeedAxes());
	if (validAxes_ != remoteValidAxes)
	{
		validAxes_ = std::move(remoteValidAxes);
		emit validAxesChanged(validAxes_);
	}
}