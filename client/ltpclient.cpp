#include "ltpclient.h"
#include "hintwidgetproxy.h"
#include "../base/buttonprocessor.h"

using ltp::client::LtpClient;

LtpClient::LtpClient(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);
	HintWidgetProxy<HintBar>::getInstance().setHintWidget(ui.hintBar_);
	HintWidgetProxy<HintBar>::getInstance().setHint(tr("我是提示栏"));
	//模仿按钮处理指令由线程处理
	base::ButtonProcessor::getInstance().moveToThread(&buttonProcessorThread_);
	//线程启动
	buttonProcessorThread_.start();
}

LtpClient::~LtpClient()
{

}
