#ifndef LTPCLIENT_H
#define LTPCLIENT_H

#include <QtGui/QWidget>
#include "ui_ltpclient.h"

class LtpClient : public QWidget
{
	Q_OBJECT

public:
	LtpClient(QWidget *parent = 0, Qt::WFlags flags = 0);
	~LtpClient();

private:
	Ui::LtpClientClass ui;
};

#endif // LTPCLIENT_H
