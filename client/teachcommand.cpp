#include "teachcommand.h"
#include <algorithm>

using ltp::client::TeachCommand;

TeachCommand::TeachCommand(const QString& teachTitle, int pointNumber)
	: kTeachTitle_(teachTitle),
	  kPointNumber_(pointNumber), 
	  systemVariables_(base::getInstance<base::SystemVariables<RemoteVariables>>())
{

}

void ltp::client::TeachCommand::previousPoint()
{
	points_.pop_back();
}

bool ltp::client::TeachCommand::changeMode() throw (ChangeTeachModeFail, CannotChangeTeachMode)
{
	if (canChangeMode() == true)
	{
		auto temp = systemVariables_.macroVariable(base::TEACH_MODE);
		//修改当前示教模式
		systemVariables_.setMacroVariable(base::TEACH_MODE, temp == 0 ? 1 : 0);
		//等待50ms，模式修改完成
		QEventLoop eventloop;
		QTimer::singleShot(50, &eventloop, SLOT(quit()));
		eventloop.exec();
		//确认示教模式修改成功
		if (temp == systemVariables_.macroVariable(base::TEACH_MODE))
		{
			throw ChangeTeachModeFail();
		}
		reset();
		return true;
	}
	else
	{
		throw CannotChangeTeachMode();
		return false;
	}
}

bool ltp::client::TeachCommand::isLastPoint() const
{
	return points_.size() == kPointNumber_ - 1;
}

TeachCommand::Point TeachCommand::previousPointPosition() const
{
	//有上一点时返回上一点
	if (points_.size() > 0)
	{
		return points_.back();
	}
	//没有时返回0
	else
	{
		Point temp;
		std::fill(temp.begin(), temp.end(), 0);
		return temp;
	}
}

QString ltp::client::TeachCommand::generateCommand(const std::vector<base::Axis> axes, const Point& point, int precision) const
{
	QString result;
	double tolerance = std::pow(1.0, -precision);
	for (int i = 0; i < axes.size(); i++)
	{
		result += base::axisEnumToAxisChar(axes[i]);
		result += QString::number(point[i], 'f', precision);
		//空格
		result += " ";
	}
	//去掉最后一个空格
	if (result.length() > 0)
	{
		result.remove(result.length() - 1, 1);
	}
	return result;
}

QString ltp::client::TeachCommand::generateCommand(const std::vector<base::Axis> axes, const base::Math::Line<Point>& line, int precision) const
{
	QString result;
	double tolerance = std::pow(1.0, -precision);
	for (int i = 0; i < axes.size(); i++)
	{
		if (std::fabs(line.start[i] - line.end[i]) >= tolerance)
		{
			result += base::axisEnumToAxisChar(axes[i]);
			result += QString::number(line.end[axes[i]], 'f', precision);
			//空格
			result += " ";
		}
	}
	//去掉最后一个空格
	if (result.length() > 0)
	{
		result.remove(result.length() - 1, 1);
	}
	return result;
}
