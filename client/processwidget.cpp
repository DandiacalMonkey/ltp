#include "processwidget.h"

using ltp::client::ProcessWidget;

ProcessWidget::ProcessWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

ProcessWidget::~ProcessWidget()
{

}

void ProcessWidget::onProcessFile(QString fileName)
{
	ui.filePreview_->openFile(fileName);
}
