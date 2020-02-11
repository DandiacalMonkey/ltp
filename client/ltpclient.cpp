#include "ltpclient.h"
#include "hintwidgetproxy.h"

using ltp::client::LtpClient;

LtpClient::LtpClient(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);
	HintWidgetProxy<HintBar>::getInstance().setHintWidget(ui.hintBar_);
	HintWidgetProxy<HintBar>::getInstance().setHint(tr("我是"));
}

LtpClient::~LtpClient()
{

}
