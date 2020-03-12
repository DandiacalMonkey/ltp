#include "filemanager.h"

using ltp::base::FileManager;

FileManager::FileManager(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	// tablewidgetÿ����ռ��������
	ui.tableWidget_->horizontalHeader()->resizeSection(0, 323);
	ui.tableWidget_->horizontalHeader()->resizeSection(1, 100);
	ui.tableWidget_->horizontalHeader()->resizeSection(2, 50);
	ui.tableWidget_->horizontalHeader()->resizeSection(3, 50);
	ui.tableWidget_->horizontalHeader()->resizeSection(4, 130);

	// ˫���¼�
	connect(ui.tableWidget_, SIGNAL(itemActivated(QTableWidgetItem*)), this, SLOT(openItem(QTableWidgetItem*)));
}

FileManager::~FileManager()
{

}
