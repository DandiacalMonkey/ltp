#include "ftpfilemanager.h"
#include <QUrl>
#include <QTextCodec>

using ltp::base::FtpFileManager;

FtpFileManager::FtpFileManager(QWidget *parent)
	: FileManager(parent),
	  editTemporaryFilePath_("./NCFiles/edit_file.nc")
{
	ui.cdToParentButton_->setEnabled(false);
	ui.locationLabel_->setText(tr("控制器") + ":/" + tr("用户盘"));
	//返回上一级按钮
	connect(ui.cdToParentButton_, SIGNAL(clicked()), SLOT(cdToParent()));
	//刷新按钮
	connect(ui.refreshButton_, SIGNAL(clicked()), SLOT(refreshList()));
	//发送项目被选中信号
	connect(ui.tableWidget_, SIGNAL(currentItemChanged(QTableWidgetItem*, QTableWidgetItem*)), SLOT(selectedItemChanged()));
}

FtpFileManager::~FtpFileManager()
{

}

void FtpFileManager::openCurrentItem()
{
	openItem(ui.tableWidget_->currentItem());	
}

void FtpFileManager::executeCurrentItem()
{
	executeItem(ui.tableWidget_->currentItem());
}

void ltp::base::FtpFileManager::connectToFtp()
{
	// 重连下载器
	ftpTransmissionManager_.connect(ip_);
	//先尝试断开旧连接
	if (ftp_)
	{
		ftp_->close();
	}
	ftp_.reset(new QFtp());
	connect(ftp_.get(), SIGNAL(commandFinished(int, bool)), SLOT(ftpCommandFinished(int, bool)));
	connect(ftp_.get(), SIGNAL(listInfo(QUrlInfo)), SLOT(addToList(QUrlInfo)));

	// 更新路径信息，表格信息
	ui.tableWidget_->tableWidgetClear();
	currentPath_.clear();
	isDirectory_.clear();
	//路径变化
	ui.pathLabel_->setText(currentPath_);
	QUrl url(QString::fromStdString(ip_));
	ftp_->connectToHost(url.toString(), 21);
	ftp_->login();
}

void FtpFileManager::connectToFtp(const std::string& ip)
{
	ip_ = ip;
	connectToFtp();
}

void FtpFileManager::uploadFile(const QString& filePath)
{
	ftpTransmissionManager_.uploadFile(filePath, lastOpenedRemoteFilePath_);
}

void FtpFileManager::refreshList()
{
	// 清除表格信息
	ui.tableWidget_->tableWidgetClear();
	isDirectory_.clear();
	// 重新获取列表
	if (ftp_)
	{
		ftp_->list();
	}
}

void FtpFileManager::cdToParent()
{
	// 清除表格信息
	ui.tableWidget_->tableWidgetClear();
	isDirectory_.clear();
	// 返回上一级目录
	currentPath_ = currentPath_.left(currentPath_.lastIndexOf('/'));
	if (currentPath_.isEmpty())
	{
		//禁用返回上一级按钮
		ui.cdToParentButton_->setEnabled(false);
		ftp_->cd("/");
	}
	else
	{
		ftp_->cd(currentPath_);
	}
	//路径变化
	ui.pathLabel_->setText(currentPath_);
	ftp_->list();
}

void FtpFileManager::openItem(QTableWidgetItem* tableItem)
{
	// 获取所在行第一列name，即文件名
	QTableWidgetItem* tempItem = ui.tableWidget_->item(tableItem->row(), 0);
	QString name = tempItem->text();

	// 是文件夹
	if (isDirectory_.value(name))
	{
		ui.tableWidget_->tableWidgetClear();
		isDirectory_.clear();
		currentPath_ += '/';
		currentPath_ += name;
		ftp_->cd(name);
		ftp_->list();
		//启用返回上一级按钮
		ui.cdToParentButton_->setEnabled(true);
		//路径变化
		ui.pathLabel_->setText(currentPath_);
		return;
	}
	else
	{
		lastOpenedRemoteFilePath_ = currentPath_ + "/" + name;
		ftpTransmissionManager_.downloadFile(lastOpenedRemoteFilePath_, editTemporaryFilePath_);
		emit openFtpFile(editTemporaryFilePath_, lastOpenedRemoteFilePath_);
	}
}

void ltp::base::FtpFileManager::executeItem(QTableWidgetItem* tableItem)
{
	// 获取所在行第一列name，即文件名
	QTableWidgetItem* tempItem = ui.tableWidget_->item(tableItem->row(), 0);
	QString name = tempItem->text();

	// 是文件夹
	if (isDirectory_.value(name))
	{
		return;
	}
	else
	{
		emit executeFtpFile(currentPath_ + "/" + name);
	}
}

void ltp::base::FtpFileManager::executeLastOpenedFile()
{
	emit executeFtpFile(lastOpenedRemoteFilePath_);
}

void ltp::base::FtpFileManager::selectedItemChanged()
{
	//获取所在行的文件名
	QTableWidgetItem* current = ui.tableWidget_->currentItem();
	if (current)				// 当前目录下有内容
	{
		QTableWidgetItem* tempItem = ui.tableWidget_->item(current->row(), 0);
		QString currentFile = tempItem->text();
		if (isDirectory_.value(currentFile) == true)
		{
			emit selectedFolder();
		}
		else
		{
			emit selectedFile();
		}
	}
	else
	{
		emit selectedNone();
	}
}

void FtpFileManager::ftpCommandFinished(int, bool error)
{
	switch (ftp_->currentCommand())
	{
	//连接
	case QFtp::ConnectToHost:
	{
		if (error)
		{
			//连接失败
			emit connectFail();
		}
		else
		{
			//连接成功
			emit connectSuccess();
		}
		return;
	}
	break;
	//登录
	case QFtp::Login:
	{
		ftp_->list();
	}
	break;
	//列出文件夹内容
	case QFtp::List:
	{
		// 获取的是空文件夹
		if (isDirectory_.isEmpty())
		{
			ui.tableWidget_->setItem(0, 0, new QTableWidgetItem(QString(tr("空文件夹"))));
			ui.tableWidget_->setEnabled(false);
		}
		//设定项目数量
		ui.itemNumber_->setText(QString::number(isDirectory_.size()));
	}
	break;
	default:
		break;
	}
}

void FtpFileManager::addToList(const QUrlInfo& urlInfo)
{
	QString suffix = "";
	QString fileSize = "";
	QString fileName = "";
	QString fileDate = "";
	QString fileAuthority = "";
	int     fileSizeInteger = 0;
	double  fileSizeDouble = 0.0;

	//控制器段ftp使用gbk编码，urlInfo内部使用latin1编解码，因此需要将远程传输的gbk解码为unicode（QString内部编码）
	QTextCodec* codec = QTextCodec::codecForName("gbk");
	fileName = codec->toUnicode(urlInfo.name().toLatin1());				// 文件名
	fileDate = urlInfo.lastModified().toString("yyyy-MM-dd hh:mm");		// 最后修改时间
	fileSizeInteger = urlInfo.size();												// 文件大小

	// 截取文件类型
	QString str = ".";
	suffix = fileName.mid(fileName.lastIndexOf(str));					// 截取.后面文件后缀
	if (suffix == fileName)												// 文件没有后缀名
	{
		suffix = "";
	}

	if (urlInfo.isDir() == false)				// 不是目录文件，获取文件大小
	{
		if (fileSizeInteger < 1024)					// 字节
		{
			fileSize = QString::number(fileSizeInteger) + QString(tr(" B"));
		}
		else if (fileSizeInteger >= 1024)
		{
			fileSizeInteger /= 1024;
			if (fileSizeInteger < 1024)				// KB
			{
				fileSize = QString::number(fileSizeInteger) + QString(tr(" KB"));
			}
			else								// MB
			{
				fileSizeDouble = fileSizeInteger / 1024.0;
				fileSize = QString::number(fileSizeDouble, 'f', 1) + QString(tr(" MB"));
			}
		}
	}

	// 获取文件的读写权限
	if (urlInfo.isReadable() && urlInfo.isWritable())
	{
		fileAuthority = "读写";
	}
	else if (urlInfo.isWritable())
	{
		fileAuthority = "写";
	}
	else if (urlInfo.isReadable())
	{
		fileAuthority = "读";
	}

	// 添加新的表格项目
	QTableWidgetItem* fileNameItem = new QTableWidgetItem(fileName);
	QTableWidgetItem* fileSizeItem = new QTableWidgetItem(fileSize);
	QTableWidgetItem* fileTypeItem = new QTableWidgetItem(suffix);
	QTableWidgetItem* fileDateItem = new QTableWidgetItem(fileDate);
	QTableWidgetItem* filePermissionItem = new QTableWidgetItem(fileAuthority);

	QPixmap pixmap(urlInfo.isDir() ? (":/LtpClient/image/folder.png") : (":/LtpClient/image/file.png"));
	fileNameItem->setIcon(pixmap);

	// 插入表格
	int row = ui.tableWidget_->rowCount();
	ui.tableWidget_->insertRow(row);
	ui.tableWidget_->setItem(row, 0, fileNameItem);
	ui.tableWidget_->setItem(row, 1, fileSizeItem);
	ui.tableWidget_->setItem(row, 2, fileTypeItem);
	ui.tableWidget_->setItem(row, 3, filePermissionItem);
	ui.tableWidget_->setItem(row, 4, fileDateItem);

	isDirectory_[urlInfo.name()] = urlInfo.isDir();		// 存储文件是否是目录
	ui.tableWidget_->setEnabled(true);
}