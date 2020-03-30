#include "base/ltpmath.h"

using namespace ltp::base::Math;

double ltp::base::Math::operator*(const Point3D& point1, const Point3D& point2)
{
	double result = 0;
	for (int i = 0; i < point1.size(); i++)
	{
		result += point1[i] * point2[i];
	}
	return result;
}

Point3D ltp::base::Math::operator^(const Point3D& point1, const Point3D& point2)
{
	Point3D result = { point1[1] * point2[2] - point1[2] * point2[1],
		point1[2] * point2[0] - point1[0] * point2[2],
		point1[0] * point2[1] - point1[1] * point2[0] };
	return result;
}

Plane ltp::base::Math::pointsPlane(const std::vector<Point3D>& points, double tolerance)
{
	if (points.size() <= 1)
	{
		return NONE_PLANE;
	}
	for (int axis = 0; axis < points[0].size(); axis++)
	{
		bool ok = true;
		//两两计算平面，确定是否同一平面
		for (int i = 0; i < points.size(); i++)
		{
			for (int j = i + 1; j < points.size(); j++)
			{
				if (std::abs(points[i][axis] - points[j][axis]) > tolerance)
				{
					ok = false;
					break;
				}
			}
			if (ok == false)
			{
				break;
			}
		}
		if (ok == true)
		{
			switch (axis)
			{
			case 0:
				return YZ_PLANE;
			case 1:
				return XZ_PLANE;
			case 2:
				return XY_PLANE;
			default:
				return NONE_PLANE;
			}
		}
	}
		
	return NONE_PLANE;
}

bool ltp::base::Math::isCollinear(const std::vector<Point3D>& points, double tolerance)
{
	//共线需要至少三个点
	if (points.size() < 3)
	{
		return false;
	}
	//构造点1点2直线
	base::Math::Line<Point3D> line = { makePoint<Point3D>(points[0].begin()), makePoint<Point3D>(points[1].begin()) };
	for (int i = 2; i < points.size(); i++)
	{
		base::Math::Line<Point3D> tempLine = { makePoint<Point3D>(points[0].begin()), makePoint<Point3D>(points[i].begin()) };
		double dotValue = line.normalize() * tempLine.normalize();
		if (!(std::abs(dotValue) > 1 - base::Math::kDistanceTolerance_ && 
			std::abs(dotValue) < 1 + base::Math::kDistanceTolerance_))
		{
			return false;
		}
	}
	return true;
}
