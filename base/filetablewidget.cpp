#include "filetablewidget.h"

#include <QButtonGroup>
#include <QScrollBar>
#include <QHeaderView>
#include <QDir>
#include <QDateTime>
#include <QDebug>
#include <QColor>

using ltp::base::FileTableWidget;

FileTableWidget::FileTableWidget(QWidget* parent)
	: QTableWidget(parent)
{
	this->setStyleSheet("QTableWidget QHeaderView:section{background:#FFFFFF; border:0px; border-right:1px solid #E6E6E6; font:13px SIMHEI; min-height:30px;} \
						 QTableWidget{font:13px Arial; color:black; border:none;} \
						 QTableWidget::item{min-height:30px;} \
						 QTableWidget::item::selected{background:#CDE1F5; color:black;} \
						 QTableWidget QScrollBar::vertical {margin:16px 0px 16px 0px; background-color:#E6E6E6; border: 0px; width: 16px;} \
						 QTableWidget QScrollBar::handle:vertical{background:rgba(0,0,0,51);} \
						 QTableWidget QScrollBar::handle:vertical:pressed{background:rgba(0,0,0,153);} \
						 QTableWidget QScrollBar::add-line:vertical{height:16px;width:16px;subcontrol-position:bottom left;subcontrol-origin: margin; image:url(:/LtpClient/image/bottom.png); background-color:#E6E6E6;} \
						 QTableWidget QScrollBar::add-line:vertical:pressed{height:16px;width:16px;subcontrol-position:bottom left;subcontrol-origin: margin; image:url(:/LtpClient/image/bottom.png); background-color:rgba(0,0,0,153);} \
						 QTableWidget QScrollBar::sub-line:vertical{image:url(:/LtpClient/image/top.png);background-color:#E6E6E6;} \
						 QTableWidget QScrollBar::sub-line:vertical:pressed{image:url(:/LtpClient/image/top.png);background-color:rgba(0,0,0,153);} \
						");

	this->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft|Qt::AlignVCenter);	// 表头左对齐
	this->setEditTriggers(QAbstractItemView::NoEditTriggers);		// 只读
	this->setShowGrid(false);										// 取消网格显示
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);		// 垂直滚动条常开
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);		// 水平滚动条常闭
	this->setSelectionMode(QAbstractItemView::SingleSelection);		// 单选模式
	this->setSelectionBehavior(QAbstractItemView::SelectRows);		// 单击选中一行

	connect(this->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(headerClicked(int)));
}

FileTableWidget::~FileTableWidget()
{

}

void FileTableWidget::headerClicked(int column)
{
	static bool bSort = true;
	if (bSort)
	{
		this->sortItems(column, Qt::AscendingOrder);
	} 
	else
	{
		this->sortItems(column, Qt::DescendingOrder);
	}

	bSort = !bSort;
	this->setCurrentCell(0, 0);
	this->clearSelection();
}

void FileTableWidget::tableWidgetClear()
{
	this->clear();

	// 初始化
	this->setEditTriggers(QAbstractItemView::NoEditTriggers);		// 只读
	// 五列
	this->selectColumn(5);
	this->setRowCount(0);

	// 插入表头
	QStringList qList;
	qList<<tr("名称")<<tr("大小")<<tr("类型")<<tr("权限")<<tr("更新日期");
	this->setHorizontalHeaderLabels(qList);
}

void FileTableWidget::showAllFiles(QString path)
{
	QDir qDir(path);
	if (!qDir.exists() || path == "")		// 路径不存在则清空返回
	{
		return;
	}

	tableWidgetClear();						// 更新文件信息前先清除之前信息
	qDir.setSorting(QDir::DirsFirst);		// 以文件名排序为初始排序

	QString qSuffix		   = "";
	QString qstrFileSize   = "";
	QString qfilename	   = "";
	QString qfileDate	   = "";
	QString qfileAuthority = "";
	int     nfileSize	   = 0;
	double  dfileSize	   = 0.0;

	QFileInfoList fileInfoList = qDir.entryInfoList();
	foreach(QFileInfo fileInfo, fileInfoList)
	{
		if(fileInfo.fileName() == "." || fileInfo.fileName() == ".." )
		{
			continue;
		}

		qfilename = fileInfo.fileName();			// 文件名
		qSuffix   = fileInfo.suffix();				// 文件后缀，文件类型
		qfileDate = fileInfo.lastModified().toString("yyyy-MM-dd hh:mm");		// 创建时间
		nfileSize = fileInfo.size();

		if (fileInfo.isDir() == false)				// 获取文件大小
		{
			if (nfileSize < 1024)					// 字节
			{
				qstrFileSize = QString::number(nfileSize) + QString(tr(" B"));
			}
			else if (nfileSize >= 1024)
			{
				nfileSize /= 1024;
				if (nfileSize < 1024)				// KB
				{
					qstrFileSize = QString::number(nfileSize) + QString(tr(" KB"));
				}
				else								// MB
				{
					dfileSize = nfileSize / 1024.0;
					qstrFileSize = QString::number(dfileSize, 'f', 1) + QString(tr(" MB"));
				}
			}
		}

		if (fileInfo.isReadable() && fileInfo.isWritable())			// 获取文件的读写权限
		{
			qfileAuthority = "读写";
		} 
		else if (fileInfo.isWritable())
		{
			qfileAuthority = "写";
		}
		else if (fileInfo.isReadable())
		{
			qfileAuthority = "读";
		}

		// 添加新的表格项目
		QTableWidgetItem *fileName = new QTableWidgetItem(qfilename);
		QTableWidgetItem *fileSize = new QTableWidgetItem(qstrFileSize);
		QTableWidgetItem *fileType = new QTableWidgetItem(qSuffix);
		QTableWidgetItem *fileDate = new QTableWidgetItem(qfileDate);
		QTableWidgetItem *filePermission = new QTableWidgetItem(qfileAuthority);

		// 插入表格
		int row = this->rowCount();
		this->insertRow(row);
		this->setItem(row, 0, fileName);
		this->setItem(row, 1, fileSize);
		this->setItem(row, 2, fileType);
		this->setItem(row, 3, filePermission);
		this->setItem(row, 4, fileDate);
	}
}

void FileTableWidget::getInformation(QString path, int &fileNumbers)
{
	QDir qDir(path);
	if (!qDir.exists() || path == "")		// 路径不存在则清空返回
	{
		return;
	}

	QList<QFileInfo> *fileInfo=new QList<QFileInfo>(qDir.entryInfoList());
	fileNumbers = fileInfo->count();		// 文件个数
}