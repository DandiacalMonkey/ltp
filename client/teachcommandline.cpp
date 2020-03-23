#include "teachcommandline.h"
#include <QObject>

using ltp::client::TeachCommandLine;

TeachCommandLine::TeachCommandLine(const QString& command, const QString& schematicDiagramPath)
	: kCommand_(command), 
	  systemVariables_(base::getInstance<base::SystemVariables<RemoteVariables>>()),
	  TeachCommand(command, 2)
{
	//图例
	schematicDiagramsPath_.push_back("");
	schematicDiagramsPath_.push_back(schematicDiagramPath);
	//提示
	hints_.push_back(QObject::tr(""));
	hints_.push_back(QObject::tr("请移动到终点并确认"));
	//调用重置，执行初始化，会记录第一个点
	reset();
}

bool TeachCommandLine::checkPoint()
{
	points_.push_back(systemVariables_.workpieceCoordinates(1));
	return points_.size() == kPointNumber_;
}

QString TeachCommandLine::getCommand()
{
	return QString("");
}

void TeachCommandLine::reset()
{
	points_.clear();
	checkPoint();
}
