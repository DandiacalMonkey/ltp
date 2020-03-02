#include "titlebar.h"

#include <QDateTime>

using ltp::client::TitleBar;


TitleBar::TitleBar(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	ui.connectStateLabel_->setPixmap(QPixmap(":/LtpClient/image/net_connected.png"));

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
	case ltp::base::CODELESS:		// 自动
		ui.modeIconLabel_->setPixmap(QPixmap(":/LtpClient/image/mode_auto.png"));
		ui.modeNameLabel_->setText(tr("自动"));
		break;
	case ltp::base::JOG:			// JOG
		ui.modeIconLabel_->setPixmap(QPixmap(":/LtpClient/image/mode_JOG.png"));
		ui.modeNameLabel_->setText(tr("JOG"));
		break;
	case ltp::base::MEMORY:			// 参考点
		ui.modeIconLabel_->setPixmap(QPixmap(":/LtpClient/image/mode_reference_point.png"));
		ui.modeNameLabel_->setText(tr("参考点"));
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
	switch (state)
	{
	case(ltp::base::READY):
		ui.machiningStateLabel_->setText(tr("就绪"));
		break;
	case(ltp::base::BUSY):
		ui.machiningStateLabel_->setText(tr("加工"));
		break;
	case(ltp::base::HOLD):
		ui.machiningStateLabel_->setText(tr("暂停"));
		break;
	case(ltp::base::STOP):
		ui.machiningStateLabel_->setText(tr("停止"));
		break;
	default:
		break;
	}
}

void TitleBar::setCurrentNCName(const QString &name)
{
	ui.currentNCNameLabel_->setText(name);
}

void TitleBar::setErrorMessages(const std::vector<std::string> &errorMessages)
{

}



