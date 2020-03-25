#ifndef LTP_BASE_MATH_H_
#define LTP_BASE_MATH_H_

#include <array>
#include <cmath>
#include <algorithm>

namespace ltp
{
	namespace base
	{
		namespace Math
		{
			//定义二维和三维点
			typedef std::array<double, 2> Point2D;
			typedef std::array<double, 3> Point3D;
			//容差
			const double kDistanceTolerance_ = 1e-3;
			template <typename Point>
			bool isSamePoint(Point point1, Point point2)
			{
				for (int i = 0; i < point1.size(); i++)
				{
					if (std::fabs(point1[i] - point2[i]) > kDistanceTolerance_)
					{
						return false;
					}
				}
				return true;
			}
			//点转换
			template <typename Point, typename Iterator>
			Point makePoint(Iterator iterator)
			{
				Point point;
				std::copy_n(iterator, point.size(), point.begin());
				return point;
			}
		};
	}
}


#endif // !LTP_BASE_MATH_H_



