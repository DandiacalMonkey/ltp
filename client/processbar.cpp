#include "processbar.h"

using ltp::client::ProcessBar;

ProcessBar::ProcessBar(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

ProcessBar::~ProcessBar()
{
}
