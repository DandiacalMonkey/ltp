#include "teachcommand.h"

using ltp::client::TeachCommand;

TeachCommand::TeachCommand(const QString& teachTitle, int pointNumber)
	: kTeachTitle_(teachTitle),
	  kPointNumber_(pointNumber)
{

}

void ltp::client::TeachCommand::previousPoint()
{
	points_.pop_back();
}

bool ltp::client::TeachCommand::isLastPoint() const
{
	return points_.size() == kPointNumber_ - 1;
}

QString ltp::client::TeachCommand::generateCommand(const std::vector<base::Axis> axes, 
	std::array<double, base::AXIS_MAX> position, int precision) const
{
	QString result;
	for (int i = 0; i < axes.size(); i++)
	{
		result += base::axisEnumToAxisChar(axes[i]);
		result += QString::number(position[axes[i]], 'f', precision);
		//最后一个不添加空格
		if (i != axes.size() - 1)
		{
			result += " ";
		}
	}
	return result;
}
