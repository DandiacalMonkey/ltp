#include "processwidget.h"
#include "machiningstates.h"

using ltp::client::ProcessWidget;

ProcessWidget::ProcessWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//加载正在加工的文件
	connect(&base::getInstance<MachiningStates>(), SIGNAL(localMachiningFileChanged(const QString&)),
		SLOT(onProcessFile(const QString&)));
}

ProcessWidget::~ProcessWidget()
{

}

void ProcessWidget::onProcessFile(const QString& filePath)
{
	ui.filePreview_->openFile(filePath);
}
