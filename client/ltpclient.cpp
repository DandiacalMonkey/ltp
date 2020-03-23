#include "ltpclient.h"
#include "hintwidgetproxy.h"
#include "machiningstates.h"
#include "network.h"

using ltp::client::LtpClient;

LtpClient::LtpClient(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);
	//提示栏
	base::getInstance<HintWidgetProxy<HintBar>>().setHintWidget(ui.hintBar_);
	// 修改当前模块名
	connect(ui.mainContainer, SIGNAL(signalChangeModules(QString)), ui.titleBar_, SLOT(setModuleName(QString)));
	// 模式更新
	connect(&base::getInstance<MachiningStates>(), SIGNAL(modeChanged(base::Mode)), ui.titleBar_, SLOT(setMode(base::Mode)));
	// 加工状态更新
	connect(&base::getInstance<MachiningStates>(), SIGNAL(machiningStateChanged(base::MachiningState)), ui.titleBar_, SLOT(setMachiningState(base::MachiningState)));
	// 报错信息更新
	connect(&base::getInstance<MachiningStates>(), SIGNAL(errorLevelChanged(base::ErrorLevel)), ui.titleBar_, SLOT(setErrorMessages(base::ErrorLevel)));
	// 文件名更新
	connect(&base::getInstance<MachiningStates>(), SIGNAL(machiningFileChanged(const QString&)), ui.titleBar_, SLOT(setCurrentNCName(QString)));
	// 网络连接更新
	connect(&base::getInstance<Network>(), SIGNAL(connected(const std::string&)), ui.titleBar_, SLOT(setConnected()));
	connect(&base::getInstance<Network>(), SIGNAL(disconnected()), ui.titleBar_, SLOT(setDisconnected()));
}

LtpClient::~LtpClient()
{

}

void LtpClient::setErrorText(std::vector<std::string> errorMessages)
{
	// 显示保存信息
	//ui.titleBar_->setErrorMessages(errorMessages);
}