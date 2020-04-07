#include "teachcommandspatialcircle.h"
#include <cassert>

bool ltp::client::TeachCommandSpatialCircle::checkPoint()
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
		//旋转轴坐标是否变化
		if (isCoordinateChanged(tempPosition, base::A_AXIS, base::U_AXIS) == true)
		{
			throw RevolvingAxisPositionChanged();
		}
		//写入当前点
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
		//旋转轴坐标是否变化
		if (isCoordinateChanged(tempPosition, base::A_AXIS, base::U_AXIS) == true)
		{
			throw RevolvingAxisPositionChanged();
		}
		//写入当前点
		points_.push_back(tempPosition);
		break;
	}
	default:
		assert(false);
		break;
	}
	return static_cast<int>(points_.size()) == kPointNumber_;
}

QString ltp::client::TeachCommandSpatialCircle::getCommand() const
{
	//生成结果
	QString result = "G02.4 ";
	//空间整圆只需要写XYZ轴
	std::vector<base::Axis> tempAxes;
	tempAxes.push_back(base::X_AXIS);
	tempAxes.push_back(base::Y_AXIS);
	tempAxes.push_back(base::Z_AXIS);
	//终点
	result += generateCommand(tempAxes, points_[2], base::axisEnumToAxisChar) + " ";
	//中间点
	result += generateCommand(tempAxes, points_[1], base::axisEnumToArcChar);
	return result + " R1";
}
