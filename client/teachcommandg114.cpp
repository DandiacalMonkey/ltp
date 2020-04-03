#include "teachcommandg114.h"
#include "machiningstates.h"

using ltp::client::TeachCommandG114;

TeachCommandG114::TeachCommandG114()
	: TeachCommand("G114", 3)
{
	//图例
	schematicDiagramsPath_.push_back(":/LtpClient/image/teach_command_g114_P1.png");
	schematicDiagramsPath_.push_back(":/LtpClient/image/teach_command_g114_P2.png");
	schematicDiagramsPath_.push_back(":/LtpClient/image/teach_command_g114_P3.png");
	//提示
	hints_.push_back(QObject::tr("请移动到P1，并记录点"));
	hints_.push_back(QObject::tr("请移动到P2，并记录点"));
	hints_.push_back(QObject::tr("请移动到P3，点击确定完成示教"));
	//上一点的标签
	previousPointLabel_.push_back(QObject::tr(""));
	previousPointLabel_.push_back(QObject::tr("P1"));
	previousPointLabel_.push_back(QObject::tr("P2"));
}

bool TeachCommandG114::checkPoint() throw(RepeatPointException)
{
	//当前位置
	auto currentPosition = systemVariables_.teachPosition(1);
	//如果已经记录过点，需要确认是否有重复点
	if (hasSamePoint(currentPosition, base::X_AXIS, base::AXIS_COUNT))
	{
		throw RepeatPointException();
	}
	points_.push_back(systemVariables_.teachPosition(1));
	return static_cast<int>(points_.size()) == kPointNumber_;
}

bool TeachCommandG114::hasPreviousPoint() const
{
	return points_.size() > 0;
}

QString TeachCommandG114::getCommand() const
{
	QString result;
	result += "G114";
	for (size_t i = 0; i < points_.size(); i++)
	{
		result += QString(" P%0 ").arg(i + 1);
		result += generateCommand(base::getInstance<MachiningStates>().validAxes(), 
			points_[i], base::axisEnumToAxisChar);
	}
	return result;
}

bool TeachCommandG114::canChangeMode() const
{
	return points_.size() == 0;
}

void TeachCommandG114::reset()
{
	points_.clear();
}
