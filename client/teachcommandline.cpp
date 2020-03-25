#include "teachcommandline.h"
#include <QObject>
#include "machiningstates.h"

using ltp::client::TeachCommandLine;

TeachCommandLine::TeachCommandLine(const QString& command, const QString& schematicDiagramPath)
	: kCommand_(command), 
	  systemVariables_(base::getInstance<base::SystemVariables<RemoteVariables>>()),
	  TeachCommand(command, 2)
{
	//图例
	schematicDiagramsPath_.push_back("");
	schematicDiagramsPath_.push_back(schematicDiagramPath);
	//提示
	hints_.push_back(QObject::tr(""));
	hints_.push_back(QObject::tr("请移动到终点，点击确定完成示教"));
	//调用重置，执行初始化，会记录第一个点
	reset();
}

bool TeachCommandLine::checkPoint() throw (RepeatPointException)
{
	//当前位置
	auto currentPosition = systemVariables_.workpieceCoordinates(1);
	//当前位置的xyz坐标
	auto currentPoint = base::Math::makePoint<base::Math::Point3D>(currentPosition.begin());
	//如果已经记录过点，需要确认是否有重复点
	if (hasSamePoint(currentPoint))
	{
		throw RepeatPointException();
	}
	points_.push_back(systemVariables_.workpieceCoordinates(1));
	return points_.size() == kPointNumber_;
}

bool TeachCommandLine::hasPreviousPoint() const
{
	return points_.size() != 1;
}

QString TeachCommandLine::getCommand() const
{
	QString result;
	result += kCommand_;
	result += " ";
	result += generateCommand(base::getInstance<MachiningStates>().validAxes(), points_.back());
	return result;
}

void TeachCommandLine::reset()
{
	points_.clear();
	checkPoint();
}
