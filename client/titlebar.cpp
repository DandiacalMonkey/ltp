#include "titlebar.h"

#include <QDateTime>

using ltp::client::TitleBar;

TitleBar::TitleBar(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
		 
	ui.m_moduleNameLabel->setGeometry(7, 13, 32, 16);			// 模块标签 
	ui.m_moduleNameLabel->setStyleSheet("font: 16px SIMHEI");
	 
	ui.m_modeIconLabel->setGeometry(108, 8, 22, 22);			// 模式图标

	ui.m_modeNameLabel->setGeometry(145, 13, 28, 14);			// 模式标签
	ui.m_modeNameLabel->setStyleSheet("font: 14px SIMHEI");

	ui.m_machiningStateLabel->setGeometry(206, 13, 28, 14);			// 状态标签
	ui.m_machiningStateLabel->setStyleSheet("font: 14px SIMHEI");

	ui.m_currentNCNameLabel->setGeometry(270, 13, 280, 16);			// 文件名标签
	ui.m_currentNCNameLabel->setStyleSheet("font: 14px Arial");

	ui.m_connectStateLabel->setGeometry(620, 6, 24, 24);			// 连接状态标签

	ui.m_timeLabel->setGeometry(680, 13, 115, 16);			// 系统时间标签
	ui.m_timeLabel->setStyleSheet("font: 14px Arial");

	m_updateTimer = new QTimer(this);			// 系统时间更新
	connect(m_updateTimer, SIGNAL(timeout()), this, SLOT(updateTime()));
	m_updateTimer->start(1000);
}

TitleBar::~TitleBar()
{
}

void TitleBar::updateTime()
{
	// 系统时间更新
	QDateTime now(QDateTime::currentDateTime());
	ui.m_timeLabel->setText(now.toString("yyyy/MM/dd hh:mm"));
}