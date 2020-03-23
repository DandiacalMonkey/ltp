#include "teachcommand.h"

using ltp::client::TeachCommand;

TeachCommand::TeachCommand(const QString& teachTitle, int pointNumber)
	: kTeachTitle_(teachTitle),
	  kPointNumber_(pointNumber)
{

}

bool ltp::client::TeachCommand::previousPoint()
{
	points_.pop_back();
	return points_.size() != 1;
}

bool ltp::client::TeachCommand::isLastPoint()
{
	return points_.size() == kPointNumber_ - 1;
}
