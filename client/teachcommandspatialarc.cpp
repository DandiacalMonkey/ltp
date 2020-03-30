#include "teachcommandspatialarc.h"
#include <cassert>
#include <machiningstates.h>

ltp::client::TeachCommandSpatialArc::TeachCommandSpatialArc()
	: TeachCommand("G02.4", 3)
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
	//记录当前点
	reset();
}

bool ltp::client::TeachCommandSpatialArc::checkPoint() throw(RepeatPointException, PointCollinear)
{
	auto tempPosition = systemVariables_.teachPosition(1);
	switch (points_.size())
	{
	case 0:
	{
		//没有储存点时，直接写入当前点
		points_.push_back(tempPosition);
		break;
	}
	case 1:
	{
		//第二个点，需要判断是否有相同点
		if (hasSamePoint(tempPosition, base::X_AXIS, base::A_AXIS))
		{
			throw RepeatPointException();
		}
		//点不相同则写入当前点
		points_.push_back(tempPosition);
		break;
	}
	case 2:
	{
		//第三个点，需要判断是否有相同点
		if (hasSamePoint(tempPosition, base::X_AXIS, base::A_AXIS))
		{
			throw RepeatPointException();
		}
		//构造点xyz坐标点
		std::vector<base::Math::Point3D> points;
		points.push_back(base::Math::makePoint<base::Math::Point3D>(points_[0].begin()));
		points.push_back(base::Math::makePoint<base::Math::Point3D>(points_[1].begin()));
		points.push_back(base::Math::makePoint<base::Math::Point3D>(tempPosition.begin()));
		//确定三点是否共线
		if (base::Math::isCollinear(points) == true)
		{
			throw PointCollinear();
		}
		//写入当前点
		points_.push_back(tempPosition);
		break;
	}
	default:
		assert(false);
		break;
	}
	return points_.size() == kPointNumber_;
}

bool ltp::client::TeachCommandSpatialArc::hasPreviousPoint() const
{
	return points_.size() > 1;
}

QString ltp::client::TeachCommandSpatialArc::getCommand() const
{
	
	//中间点
	auto inArc = base::Math::makePoint<base::Math::Point3D>(points_[1].begin());
	//生成结果
	QString result = "G02.4";
	//终点
	auto end = base::Math::makePoint<base::Math::Point3D>(points_[2].begin());
	result += generateCommand(base::getInstance<MachiningStates>().validAxes(),
		points_[2], base::axisEnumToAxisChar);
	result += generateCommand(base::getInstance<MachiningStates>().validAxes(),
		points_[1], base::axisEnumToArcChar);
	return result;
}

bool ltp::client::TeachCommandSpatialArc::canChangeMode() const
{
	auto tempPosition = systemVariables_.teachPosition(1);
	if (points_.size() == 1 && base::Math::isSamePoint(points_[0].begin(), points_[0].end(), tempPosition.cbegin()) == true)
	{
		return true;
	}
	return false;
}

void ltp::client::TeachCommandSpatialArc::reset()
{
	points_.clear();
	checkPoint();
}
