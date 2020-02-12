#include "ltpclient.h"
#include <QTextCodec>
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
	QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
	QApplication a(argc, argv);
	ltp::client::LtpClient w(nullptr);
	w.resize(800, 600);
	w.show();
	return a.exec();
}
