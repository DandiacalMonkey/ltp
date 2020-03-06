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
	//״̬ˢ��
	const int kInterval = 200;
	timer_.start(kInterval);
	connect(&timer_, SIGNAL(timeout()), SLOT(updateState()));
	//��������ʱ��ȷ����Ч��
	connect(&base::getInstance<Network>(), SIGNAL(connected()), SLOT(updateAxesInformation()));
	//��ʼ����ö�ٵ����ַ�ӳ���ϵ
	axisEnumAxisCharacterMap_[base::X_AXIS] = 'X';
	axisEnumAxisCharacterMap_[base::Y_AXIS] = 'Y';
	axisEnumAxisCharacterMap_[base::Z_AXIS] = 'Z';
	axisEnumAxisCharacterMap_[base::A_AXIS] = 'A';
	axisEnumAxisCharacterMap_[base::B_AXIS] = 'B';
	axisEnumAxisCharacterMap_[base::C_AXIS] = 'C';
	axisEnumAxisCharacterMap_[base::U_AXIS] = 'U';
	axisEnumAxisCharacterMap_[base::V_AXIS] = 'V';
	axisEnumAxisCharacterMap_[base::W_AXIS] = 'W';
	//��ʼ�����ַ�����ö��ӳ���ϵ
	for each (auto x in axisEnumAxisCharacterMap_)
	{
		axisCharacterAxisEnumMap_[x.second] = x.first;
	}
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
	//PLC�о�����־
	if (systemVariables.plcVariable(rmi::F_READY) != 0)
	{
		return base::READY;
	}
	//PLC�о����־
	if (systemVariables.plcVariable(rmi::F_HOLDING) != 0)
	{
		return base::HOLD;
	}
	//PLC�����б�־
	if (systemVariables.plcVariable(rmi::F_RUNNING) != 0)
	{
		return base::BUSY;
	}
	//Ĭ��Ϊֹͣ״̬
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
	//CI������������󣬱�ʾ�б���
	if (systemVariables.plcVariable(rmi::F_CIERR) != 0 | 
		systemVariables.plcVariable(rmi::F_FATALERR) != 0)
	{
		return base::ERROR;
	}
	//PLC�ľ����־λ
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
	//ģʽ
	auto remoteMode = mode();
	if (mode_ != remoteMode)
	{
		mode_ = remoteMode;
		emit modeChanged(mode_);
	}
	//״̬
	auto remoteMachiningState = machiningState();
	if (machiningState_ != remoteMachiningState)
	{
		machiningState_ = remoteMachiningState;
		emit machiningStateChanged(machiningState_);
	}
	//����ȼ�
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
	//�������ϵ���Ч��
	auto remoteValidAxes = axesCharacterToAxesEnum(systemVariables.validFeedAxes());
	//�Ա���Ч��
	if (validAxes_ != remoteValidAxes)
	{
		validAxes_ = std::move(remoteValidAxes);
		emit validAxesChanged(validAxes_);
	}
	//�������ַ
	auto remoteAxesAddress = systemVariables.axesAddress();
	axesAddress_.clear();
	for each (auto x in remoteAxesAddress)
	{
		axesAddress_[axisCharacterToAxisEnum(x.first)] = x.second;
	}
}