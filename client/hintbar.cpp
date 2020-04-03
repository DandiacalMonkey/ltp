#include "hintbar.h"

using ltp::client::HintBar;

HintBar::HintBar(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//每0.5s检查一次是否清空
	int kCheckInterval = 500;
	hintClearTimer_.start(kCheckInterval);
	connect(&hintClearTimer_, SIGNAL(timeout()), SLOT(hintClear()));
}

HintBar::~HintBar()
{

}

void HintBar::setHint(const QString& hint)
{
	ui.hintLabel_->setText(hint);
	//储存设定提示的时间
	hintTime_ = QTime::currentTime();
}

void HintBar::hintClear()
{
	if (hintTime_.secsTo(QTime::currentTime()) >= kHintSurvivalSeconds_)
	{
		ui.hintLabel_->clear();
	}
}