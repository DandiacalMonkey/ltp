#ifndef LTP_CLIENT_LTPCLIENT_H_
#define LTP_CLIENT_LTPCLIENT_H_

#include <QtGui/QWidget>
#include <QThread>
#include "ui_ltpclient.h"

namespace ltp
{
namespace client
{
class LtpClient : public QWidget
{
	Q_OBJECT

public:
	LtpClient(QWidget* parent = 0, Qt::WFlags flags = 0);
	~LtpClient();

private:
	Ui::LtpClientClass ui;
	//ģ�°�ť����ָ����߳�
	QThread buttonProcessorThread_;

private slots:
	void setHintText(QString);
	void setErrorText(std::vector<std::string>);
};
}
}

#endif // LTP_CLIENT_LTPCLIENT_H_
