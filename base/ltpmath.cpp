#include "base/ltpmath.h"

using namespace ltp::base::Math;

double ltp::base::Math::operator*(const Point3D& point1, const Point3D& point2)
{
	double result = 0;
	for (size_t i = 0; i < point1.size(); i++)
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
	for (size_t axis = 0; axis < points[0].size(); axis++)
	{
		bool ok = true;
		//两两计算平面，确定是否同一平面
		for (size_t i = 0; i < points.size(); i++)
		{
			for (size_t j = i + 1; j < points.size(); j++)
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
	base::Math::Line<Point3D> line = { points[0], points[1] };
	for (size_t i = 2; i < points.size(); i++)
	{
		base::Math::Line<Point3D> tempLine = { points[0], points[i] };
		//得到cos值
		double dotValue = line.normalize() * tempLine.normalize();
		//小角度时，sinθ ≈ θ，计算sin值，和容差比较
		if (std::sqrt(std::abs(1 - dotValue * dotValue)) > tolerance)
		{
			return false;
		}
	}
	return true;
}

template<>
Point2D Arc<Point2D>::calculateCenter(const Point2D& start, const Point2D& inArc, const Point2D& end)
{
	Point2D::value_type a = 2 * (inArc[0] - start[0]);
	Point2D::value_type b = 2 * (inArc[1] - start[1]);
	Point2D::value_type c = inArc[0] * inArc[0] + inArc[1] * inArc[1] - start[0] * start[0] - start[1] * start[1];
	Point2D::value_type d = 2 * (end[0] - inArc[0]);
	Point2D::value_type e = 2 * (end[1] - inArc[1]);
	Point2D::value_type f = end[0] * end[0] + end[1] * end[1] - inArc[0] * inArc[0] - inArc[1] * inArc[1];
	//除数不为0
	if (std::abs(b * d - e * a) < kPrecision)
	{
		throw std::runtime_error("can not calculate center");
	}
	Point2D center = { (b * f - e * c) / (b * d - e * a), (d * c - a * f) / (b * d - e * a) };
	return center;
}
