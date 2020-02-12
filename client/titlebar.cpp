#include "titlebar.h"

#include <QDateTime>

using ltp::client::TitleBar;

TitleBar::TitleBar(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

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