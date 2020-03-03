#include "ltpclient.h"
#include "hintwidgetproxy.h"

using ltp::client::LtpClient;

LtpClient::LtpClient(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);
	base::getInstance<HintWidgetProxy<HintBar>>().setHintWidget(ui.hintBar_);

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
	base::getInstance<HintWidgetProxy<HintBar>>().setHint(str);
}

void LtpClient::setErrorText(std::vector<std::string> errorMessages)
{
	// 显示保存信息
	//ui.titleBar_->setErrorMessages(errorMessages);
}