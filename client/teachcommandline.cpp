#include "teachcommandline.h"
#include <QObject>
#include "machiningstates.h"

using ltp::client::TeachCommandLine;

TeachCommandLine::TeachCommandLine(const QString& command, const QString& schematicDiagramPath)
	: kCommand_(command), 
	  TeachCommand(command, 2)
{
	//图例
	schematicDiagramsPath_.push_back("");
	schematicDiagramsPath_.push_back(schematicDiagramPath);
	//提示
	hints_.push_back(QObject::tr(""));
	hints_.push_back(QObject::tr("请移动到终点，点击确定完成示教"));
	//上一点的标签
	previousPointLabel_.push_back(QObject::tr(""));
	previousPointLabel_.push_back(QObject::tr("起点"));
	//调用重置，执行初始化，会记录第一个点
	reset();
}

bool TeachCommandLine::checkPoint() throw (RepeatPointException)
{
	//当前位置
	auto currentPosition = systemVariables_.teachPosition(1);
	//如果已经记录过点，需要确认是否有重复点
	if (hasSamePoint(currentPosition))
	{
		throw RepeatPointException();
	}
	points_.push_back(systemVariables_.teachPosition(1));
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
	base::Math::Line<Point> line = { points_[0], points_[1] };
	result += generateCommand(base::getInstance<MachiningStates>().validAxes(), 
		line);
	return result;
}

bool ltp::client::TeachCommandLine::canChangeMode() const
{
	auto tempPosition = systemVariables_.teachPosition(1);
	if (points_.size() == 1 && base::Math::isSamePoint(points_[0], tempPosition) == true)
	{
		return true;
	}
	return false;
}

void TeachCommandLine::reset()
{
	points_.clear();
	checkPoint();
}
