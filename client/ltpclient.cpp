#include "ltpclient.h"
#include "hintwidgetproxy.h"
#include "base/buttonprocessor.h"

using ltp::client::LtpClient;

LtpClient::LtpClient(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);
	HintWidgetProxy<HintBar>::getInstance().setHintWidget(ui.hintBar_);
	//HintWidgetProxy<HintBar>::getInstance().setHint(tr("我是提示栏"));
	//模仿按钮处理指令由线程处理
	base::getInstance<base::ButtonProcessor>().moveToThread(&buttonProcessorThread_);
	//线程启动
	buttonProcessorThread_.start();

	// 提示信息
	connect(ui.mainContainer, SIGNAL(signalTips(QString)), this, SLOT(setHintText(QString)));
	// 当前加工文件名修改
	connect(ui.mainContainer, SIGNAL(signalChangeProcessFileName(QString)), ui.titleBar_, SLOT(setCurrentNCName(QString)));
	// 修改当前模块名
	connect(ui.mainContainer, SIGNAL(signalChangeModules(QString)), ui.titleBar_, SLOT(setModuleName(QString)));
}

LtpClient::~LtpClient()
{

}

void LtpClient::setHintText(QString str)
{
	str += "  ";
	// 提示栏信息设置
	HintWidgetProxy<HintBar>::getInstance().setHint(str);
}

void LtpClient::setErrorText(std::vector<std::string> errorMessages)
{
	// 显示保存信息
	//ui.titleBar_->setErrorMessages(errorMessages);
}