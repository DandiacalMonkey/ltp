#include "ltpclient.h"
#include <QTextCodec>
#include "application.h"
#include "network.h"
#include "remotevariables.hpp"
#include "base/systemvariables.hpp"
#include "client/machiningstates.h"

int main(int argc, char *argv[])
{
#ifdef Q_OS_WIN
	QTextCodec* codec = QTextCodec::codecForName("gbk");
	QTextCodec::setCodecForCStrings(codec);
	QTextCodec::setCodecForTr(codec);
#else
	QTextCodec* codec = QTextCodec::codecForName("utf8");
	QTextCodec::setCodecForCStrings(codec);
	QTextCodec::setCodecForTr(codec);
#endif

	ltp::client::Application a(argc, argv);
	ltp::client::LtpClient w(nullptr);

	//TODO:测试代码
	ltp::base::getInstance<ltp::client::MachiningStates>();
	//网络连接需要最后执行，部分初始化依赖于网络连接信号
	ltp::base::getInstance<ltp::client::Network>().connect();

	w.resize(800, 600);
	w.show();
	return a.exec();
}
