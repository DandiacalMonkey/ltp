#include "ltpclient.h"
#include <QTextCodec>
#include <QtGui/QApplication>
#include "network.h"
#include "remotevariables.hpp"
#include "base/systemvariables.hpp"

int main(int argc, char *argv[])
{
	QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
	QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

	QApplication a(argc, argv);

	//TODO:需要修改，界面启动前，先初始化网络接口
	ltp::base::getInstance<ltp::client::Network>().setHost("192.168.6.194");
	ltp::base::getInstance<ltp::client::Network>().connect();
	//TODO:测试代码
	int tmp = ltp::base::getInstance<ltp::base::SystemVariables<ltp::client::RemoteVariables>>().macroVariable(7408);
	auto coord = ltp::base::getInstance<ltp::base::SystemVariables<ltp::client::RemoteVariables>>().mechanicalCoordinates(1);

	ltp::client::LtpClient w(nullptr);
	w.resize(800, 600);
	w.show();
	return a.exec();
}
