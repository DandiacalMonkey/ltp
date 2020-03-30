#include "teachcommandplanararc.h"
#include <cassert>
#include <QLineF>

using ltp::client::TeachCommandPlanarArc;

TeachCommandPlanarArc::TeachCommandPlanarArc()
	: TeachCommand("G02/G03", 3)
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

bool TeachCommandPlanarArc::checkPoint() throw(RepeatPointException, PlaneError, PointCollinear)
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
		//确认三点是否位于XY,YZ,XZ三平面之一
		if (base::Math::pointsPlane(points) == base::Math::NONE_PLANE)
		{
			throw PlaneError();
		}
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

bool TeachCommandPlanarArc::hasPreviousPoint() const
{
	return points_.size() > 1;
}

QString TeachCommandPlanarArc::getCommand() const
{
	//构造点xyz坐标点
	std::vector<base::Math::Point3D> points;
	points.push_back(base::Math::makePoint<base::Math::Point3D>(points_[0].begin()));
	points.push_back(base::Math::makePoint<base::Math::Point3D>(points_[1].begin()));
	points.push_back(base::Math::makePoint<base::Math::Point3D>(points_[2].begin()));
	//三点的平面
	base::Math::Plane plane = base::Math::pointsPlane(points);
	if (plane == base::Math::NONE_PLANE)
	{
		throw PlaneError();
	}
	//将三维坐标压缩为二维坐标
	base::Axis index1 = base::X_AXIS;
	base::Axis index2 = base::X_AXIS;
	switch (plane)
	{
	case base::Math::XY_PLANE:
		index1 = base::X_AXIS;
		index2 = base::Y_AXIS;
		break;
	case base::Math::XZ_PLANE:
		index1 = base::Z_AXIS;
		index2 = base::X_AXIS;
		break;
	case base::Math::YZ_PLANE:
		index1 = base::Y_AXIS;
		index2 = base::Z_AXIS;
		break;
	default:
		break;
	}
	//储存示教后的三点的二维坐标
	std::array<base::Math::Point2D, 3> threePoints;
	std::transform(points_.begin(), points_.end(), threePoints.begin(),
		[index1, index2](Point p) -> base::Math::Point2D
		{
			base::Math::Point2D result = { p[index1], p[index2] };
			return result;
		});
	base::Math::Arc<base::Math::Point2D> planarArc;
	planarArc.start = threePoints[0];
	planarArc.center = base::Math::Arc<base::Math::Point2D>::calculateCenter(
		threePoints[0], threePoints[1], threePoints[2]);
	planarArc.end = threePoints[2];
	//储存指令
	QString result;
	//判断平面
	switch (plane)
	{
	case ltp::base::Math::XY_PLANE:
		result += "G17 ";
		break;
	case ltp::base::Math::XZ_PLANE:
		result += "G18 ";
		break;
	case ltp::base::Math::YZ_PLANE:
		result += "G19 ";
		break;
	default:
		break;
	}
	//圆心指向起点和终点的方向向量
	QLineF lineStart(0, 0, threePoints[0][0] - planarArc.center[0],
		threePoints[0][1] - planarArc.center[1]);
	QLineF lineInArc(0, 0, threePoints[1][0] - planarArc.center[0],
		threePoints[1][1] - planarArc.center[1]);
	QLineF lineEnd(0, 0, threePoints[2][0] - planarArc.center[0],
		threePoints[2][1] - planarArc.center[1]);
	//判断圆弧加工方向
	bool isClockwise = lineStart.angleTo(lineInArc) < lineStart.angleTo(lineEnd);
	if (isClockwise)
	{
		result += "G02 ";
	}
	else
	{
		result += "G03 ";
	}
	//终点坐标，ZX平面时需要先写X坐标，因此增加判断
	result += base::axisEnumToAxisChar(index1 > index2 ? index2 : index1);
	result += QString::number(planarArc.end[index1 > index2 ? 1 : 0], 'f', kPrecision_);
	result += " ";
	result += base::axisEnumToAxisChar(index1 > index2 ? index1 : index2);
	result += QString::number(planarArc.end[index1 > index2 ? 0 : 1], 'f', kPrecision_);
	result += " ";
	//半径
	double radius = planarArc.radius();
	double angle = lineStart.angleTo(lineEnd);
	//判断优弧劣弧
	if ((angle > 180 && isClockwise) || (angle <= 180 && !isClockwise))
	{
		radius = -radius;
	}
	result += "R";
	result += QString::number(radius, 'f', kPrecision_);
	return result;
}

bool TeachCommandPlanarArc::canChangeMode() const
{
	auto tempPosition = systemVariables_.teachPosition(1);
	if (points_.size() == 1 && base::Math::isSamePoint(points_[0].begin(), points_[0].end(), tempPosition.cbegin()) == true)
	{
		return true;
	}
	return false;
}

void TeachCommandPlanarArc::reset()
{
	points_.clear();
	checkPoint();
}
