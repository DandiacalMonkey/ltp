#include "filemanager.h"

using ltp::base::FileManager;

FileManager::FileManager(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	// tablewidget每列所占比例设置
	ui.tableWidget_->horizontalHeader()->resizeSection(0, 323);
	ui.tableWidget_->horizontalHeader()->resizeSection(1, 100);
	ui.tableWidget_->horizontalHeader()->resizeSection(2, 50);
	ui.tableWidget_->horizontalHeader()->resizeSection(3, 50);
	ui.tableWidget_->horizontalHeader()->resizeSection(4, 130);

	// 双击事件
	connect(ui.tableWidget_, SIGNAL(itemActivated(QTableWidgetItem*)), this, SLOT(openItem(QTableWidgetItem*)));
}

FileManager::~FileManager()
{

}
