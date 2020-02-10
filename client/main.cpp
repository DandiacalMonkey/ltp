#include "ltpclient.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	LtpClient w(nullptr, Qt::FramelessWindowHint);
	w.show();
	return a.exec();
}
