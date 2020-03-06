#include "titlebar.h"

#include <QDateTime>
#include "machiningstates.h"

using ltp::client::TitleBar;


TitleBar::TitleBar(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	ui.connectStateLabel_->setPixmap(QPixmap(":/LtpClient/image/net_connected.png"));
	// 初始隐藏错误提示栏
	ui.errorMessageLabel_->setText(tr(""));
	ui.errorMessageLabel_->setStyleSheet("QLabel{background:#F5F5F5;}");

	// 模式更新
	connect(&base::getInstance<MachiningStates>(), SIGNAL(modeChanged(base::Mode)), this, SLOT(setMode(base::Mode)));
	// 加工状态更新
	connect(&base::getInstance<MachiningStates>(), SIGNAL(machiningStateChanged(base::MachiningState)), this, SLOT(setMachiningState(base::MachiningState)));
	// 报错信息更新
	connect(&base::getInstance<MachiningStates>(), SIGNAL(errorLevelChanged(base::ErrorLevel)), this, SLOT(setErrorMessages(base::ErrorLevel)));
	// 文件名更新
	connect(&base::getInstance<MachiningStates>(), SIGNAL(machiningFileNameChanged(QString)), this, SLOT(setCurrentNCName(QString)));

	updateTimeTimer_ = new QTimer(this);			// 系统时间更新
	connect(updateTimeTimer_, SIGNAL(timeout()), this, SLOT(updateTime()));
	updateTimeTimer_->start(1000);
}

TitleBar::~TitleBar()
{
}

void TitleBar::updateTime()
{
	// 系统时间更新
	QDateTime now(QDateTime::currentDateTime());
	ui.timeLabel_->setText(now.toString("yyyy/MM/dd hh:mm"));
}

void TitleBar::setMode(ltp::base::Mode modeType)
{
	switch (modeType)
	{
	case ltp::base::HANDLE:			// 手轮
		ui.modeIconLabel_->setPixmap(QPixmap(":/LtpClient/image/mode_handwheel.png"));
		ui.modeNameLabel_->setText(tr("手轮"));
		break;
	case ltp::base::CODELESS:		// 快捷（少图）
		ui.modeIconLabel_->setPixmap(QPixmap(":/LtpClient/image/mode_auto.png"));
		ui.modeNameLabel_->setText(tr("CODELESS"));
		break;
	case ltp::base::JOG:			// JOG
		ui.modeIconLabel_->setPixmap(QPixmap(":/LtpClient/image/mode_JOG.png"));
		ui.modeNameLabel_->setText(tr("JOG"));
		break;
	case ltp::base::MEMORY:			// 自动
		ui.modeIconLabel_->setPixmap(QPixmap(":/LtpClient/image/mode_auto.png"));
		ui.modeNameLabel_->setText(tr("自动"));
		break;
	case ltp::base::HOME:			// 回原点
		ui.modeIconLabel_->setPixmap(QPixmap(":/LtpClient/image/mode_reference_point.png"));
		ui.modeNameLabel_->setText(tr("原点复归"));
		break;
	case ltp::base::MDI:			// MDI
		ui.modeIconLabel_->setPixmap(QPixmap(":/LtpClient/image/mode_MDI.png"));
		ui.modeNameLabel_->setText(tr("MDI"));
		break;
	default:
		break;
	}
}

void TitleBar::setModuleName(const QString &name)
{
	ui.moduleNameLabel_->setText(name);
}

void TitleBar::setMachiningState(ltp::base::MachiningState state)
{
	// 加工状态改变
	switch (state)
	{
	case ltp::base::READY:
		ui.machiningStateLabel_->setText(tr("就绪"));
		ui.machiningStateLabel_->setStyleSheet("QLabel{background:transparent; font:14px SIMHEI; color:black;}");
		break;
	case ltp::base::BUSY:
		ui.machiningStateLabel_->setText(tr("动作中"));
		ui.machiningStateLabel_->setStyleSheet("QLabel{background:#00AA4B; font:14px SIMHEI; color:white; border-radius:10px; padding:3px 2px 3px 2px;}");
		break;
	case ltp::base::HOLD:
		ui.machiningStateLabel_->setText(tr("暂停"));
		ui.machiningStateLabel_->setStyleSheet("QLabel{background:#FFBE0A; font:14px SIMHEI; color:white; border-radius:10px; padding:3px 9px 3px 9px;}");
		break;
	case ltp::base::STOP:
		ui.machiningStateLabel_->setText(tr("停止"));
		ui.machiningStateLabel_->setStyleSheet("QLabel{background:#FA3200; font:14px SIMHEI; color:white; border-radius:10px; padding:3px 9px 3px 9px;}");
		break;
	default:
		break;
	}
}

void TitleBar::setCurrentNCName(const QString &name)
{
	ui.currentNCNameLabel_->setText(name);
}

void TitleBar::setErrorMessages(ltp::base::ErrorLevel errlevel)
{
	switch (errlevel)
	{
	case base::NO_ERROR:				// 无报错
		ui.errorMessageLabel_->setText(tr(""));
		ui.errorMessageLabel_->setStyleSheet("QLabel{background:#F5F5F5;}");
		break;
	case base::WARNNING:				// 警告
		ui.errorMessageLabel_->show();
		ui.errorMessageLabel_->setText(tr(" 警告！"));
		ui.errorMessageLabel_->setStyleSheet("QLabel{background:rgb(255, 255, 0); font:14px SIMHEI; color:white;}");
		break;
	case base::ERROR:					// 错误
		ui.errorMessageLabel_->show();
		ui.errorMessageLabel_->setText(tr(" 错误！"));
		ui.errorMessageLabel_->setStyleSheet("QLabel{background:rgb(250, 50, 0); font:14px SIMHEI; color:white;}");
		break;
	default:
		break;
	}
}



