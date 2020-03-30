#include "teachcommandpoint.h"
#include "machiningstates.h"

using ltp::client::TeachCommandPoint;

TeachCommandPoint::TeachCommandPoint()
	: TeachCommand(QObject::tr("点坐标"), 1)
{
	//图例
	schematicDiagramsPath_.push_back("");
	//提示
	hints_.push_back(QObject::tr("请移动到目标点，点击确定完成示教"));
	//上一点的标签
	previousPointLabel_.push_back(QObject::tr(""));
	//调用重置，执行初始化，清空记录的点
	reset();
}

bool TeachCommandPoint::checkPoint()
{
	// 当前位置
	auto currentPosition = systemVariables_.teachPosition(1);
	points_.push_back(currentPosition);
	return points_.size() == kPointNumber_;
}

bool TeachCommandPoint::hasPreviousPoint() const
{
	return false;
}

QString TeachCommandPoint::getCommand() const
{
	QString result;;
	//此处不管上一点坐标，全部输出
	result += generateCommand(base::getInstance<MachiningStates>().validAxes(),
		points_[0], base::axisEnumToAxisChar);
	return result;
}

bool TeachCommandPoint::canChangeMode() const
{
	return true;
}

void TeachCommandPoint::reset()
{
	points_.clear();
}
