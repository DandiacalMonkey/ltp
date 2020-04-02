#ifndef LTP_BASE_MATH_H_
#define LTP_BASE_MATH_H_

#include <array>
#include <cmath>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include <type_traits>

namespace ltp
{
	namespace base
	{
		namespace Math
		{
			//定义二维和三维点
			typedef std::array<double, 2> Point2D;
			typedef std::array<double, 3> Point3D;
			//矢量和
			template <int Integer>
			std::array<double, Integer> operator+(const std::array<double, Integer>& point1, const std::array<double, Integer>& point2)
			{
				std::array<double, Integer> result;
				std::transform(point1.begin(), point1.end(), point2.begin(), std::plus<double>());
				return result;
			}
			//矢量差
			template <int Integer>
			std::array<double, Integer> operator-(const std::array<double, Integer>& point1, const std::array<double, Integer>& point2)
			{
				std::array<double, Integer> result;
				std::transform(point1.begin(), point1.end(), point2.begin(), std::minus<double>());
				return result;
			}
			//点乘
			double operator*(const Point3D& point1, const Point3D& point2);
			//叉乘
			Point3D operator^(const Point3D& point1, const Point3D& point2);
			//定义直线
			template <typename Point>
			struct Line
			{
				//直线长度
				typename Point::value_type length()
				{
					double sum = 0;
					for (size_t i = 0; i < start.size(); i++)
					{
						sum += (start[i] - end[i]) * (start[i] - end[i]);
					}
					return std::sqrt(sum);
				}
				//计算单位向量
				Point normalize()
				{
					//计算模
					typename Point::value_type tempLength = length();
					//归一化
					Point result;
					for (size_t i = 0; i < result.size(); i++)
					{
						result[i] = (end[i] - start[i]) / tempLength;
					}
					return result;
				}
				//直线起点
				Point start;
				//直线终点
				Point end;
			};
			//定义圆弧
			template <typename Point>
			struct Arc
			{
				//三点计算圆心
				static Point calculateCenter(const Point& start, const Point& inArc, const Point& end);
				//半径
				typename Point::value_type radius()
				{
					typename Point::value_type result = 0;
					for (size_t i = 0; i < start.size(); i++)
					{
						result += (start[i] - center[i]) * (start[i] - center[i]);
					}
					return std::sqrt(result);
				}
				//起点
				Point start;
				//圆心
				Point center;
				//终点
				Point end;
			};
			//平面
			enum Plane
			{
				NONE_PLANE,
				XY_PLANE,
				XZ_PLANE,
				YZ_PLANE
			};
			//距离容差
			const double kDistanceTolerance_ = 1e-3;
			//角度容差
			const double kAngleTolerance_ = 0.1;
			//计算精度
			const double kPrecision = 1e-6;
			//点是否重合，输入坐标的迭代器
			template <typename Iterator>
			bool isSamePoint(Iterator start1, Iterator end1, Iterator start2, double tolerance = kDistanceTolerance_)
			{
				for (auto it1 = start1, it2 = start2; it1 != end1; it1++, it2++)
				{
					if (std::fabs(*it1 - *it2) > tolerance)
					{
						return false;
					}
				}
				return true;
			}
			//点是否位于XY,YZ,XZ平面之一
			Plane pointsPlane(const std::vector<Point3D>& points, double tolerance = kDistanceTolerance_);
			//点是否共线
			bool isCollinear(const std::vector<Point3D>& points, double tolerance = kAngleTolerance_);
			//点转换
			template <typename Point, typename Iterator>
			Point makePoint(Iterator iterator)
			{
				Point point;
				std::copy_n(iterator, point.size(), point.begin());
				return point;
			}
			//三点计算圆心
			template <typename Point>
			Point Arc<Point>::calculateCenter(const Point& start, const Point& inArc, const Point& end)
			{
				static_assert(std::is_same<Point, Point2D>::value, "仅支持二维");
			}
			//二维计算圆心的特化
			template<>
			Point2D Arc<Point2D>::calculateCenter(const Point2D& start, const Point2D& inArc, const Point2D& end);
		};
	}
}

using ltp::base::Math::operator+;
using ltp::base::Math::operator-;
using ltp::base::Math::operator*;
using ltp::base::Math::operator^;

#endif // !LTP_BASE_MATH_H_
