#include "filemanagerwidget.h"

using ltp::client::FileManagerWidget;

FileManagerWidget::FileManagerWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	// 左侧按钮栏设置
	ui.fileManagerButtonWidget_->setCommandButtonName(ltp::client::BUTTON1, QString(tr("用户盘")));
	ui.fileManagerButtonWidget_->setCommandButtonName(ltp::client::BUTTON5, QString(tr("执行")));
	ui.fileManagerButtonWidget_->setCommandButtonName(ltp::client::BUTTON6, QString(tr("打开")));
	enableButton(false);		// 初始禁用执行和打开功能，在选择文件后启用
	// 返回主界面
	connect(ui.fileManagerButtonWidget_, SIGNAL(signalReturnButtonClicked()), this, SIGNAL(onHome()));
	connect(ui.fileManagerButtonWidget_, SIGNAL(signalButtonClicked(int)), this, SLOT(onFileManagerModule(int)));
	// 上载文件
	connect(this, SIGNAL(signalSaved(QString)), ui.fileManagerBar_, SLOT(uploadFile(QString)));

	// 可以加载文件，即执行、打开功能是否使用
	connect(ui.fileManagerBar_, SIGNAL(downloadEnable(bool)), this, SLOT(enableButton(bool)));
}

FileManagerWidget::~FileManagerWidget()
{

}

void FileManagerWidget::enableButton(bool enable)
{
	// 初始禁用执行和打开功能，在选择文件后启用
	if (enable)
	{
		ui.fileManagerButtonWidget_->setButtonEnabled(ltp::client::BUTTON5, true);
		ui.fileManagerButtonWidget_->setButtonEnabled(ltp::client::BUTTON6, true);
	} 
	else
	{
		ui.fileManagerButtonWidget_->setButtonEnabled(ltp::client::BUTTON5, false);
		ui.fileManagerButtonWidget_->setButtonEnabled(ltp::client::BUTTON6, false);
	}
}

void FileManagerWidget::onFileManagerModule(int nModule)
{
	QString filename = "";
	if (nModule == BUTTON6 || nModule == BUTTON5)
	{
		// 获取当前选中文件名
		filename = ui.fileManagerBar_->getCurrentFileName();
		// 检查否下载，未下载需要先下载
		if(!ui.fileManagerBar_->checkDownload(filename))
		{
			return;
		}
	}	

	switch(nModule)
	{
	case ltp::client::BUTTON1:
		break;
	case ltp::client::BUTTON5:			// 执行
		emit onProcessFile(filename);
		break;
	case ltp::client::BUTTON6:			// 打开
		emit onOpenFile(filename);
		break;
	default:
		break;
	}
}

void FileManagerWidget::onStartPage()
{
	ui.fileManagerButtonWidget_->setCheckedButton(BUTTON1, true);
}