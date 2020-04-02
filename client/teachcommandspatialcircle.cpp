#include "teachcommandspatialcircle.h"
#include <cassert>

bool ltp::client::TeachCommandSpatialCircle::checkPoint() throw(RepeatPointException, PointCollinear, PointCollinear)
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
			throw PointCollinear();
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
	return static_cast<int>(points_.size()) == kPointNumber_;
}

QString ltp::client::TeachCommandSpatialCircle::getCommand() const
{
	return TeachCommandSpatialArc::getCommand() + " R1";
}
