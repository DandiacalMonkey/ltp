#include "filemanagerbar.h"
#include <QtNetwork>

using ltp::client::FileManagerBar;

FileManagerBar::FileManagerBar(QWidget *parent)
	: QWidget(parent), ftp(0), networkSession(0)
{
	ui.setupUi(this);

	// tablewidget每列所占比例设置
	ui.tableWidget_->horizontalHeader()->resizeSection(0, 355);
	ui.tableWidget_->horizontalHeader()->resizeSection(1, 100);
	ui.tableWidget_->horizontalHeader()->resizeSection(2, 50);
	ui.tableWidget_->horizontalHeader()->resizeSection(3, 50);
	ui.tableWidget_->horizontalHeader()->resizeSection(4, 125);

	// 显示桌面文件信息
	//ui.tableWidget_->showAllFiles("C:/Users/huaguolin/Desktop");
	//ui.informationLabel_->setText("文件数：XX个 | XXMB | 总剩余空间：888.8MB ");

	// 提示信息：请输入ftp连接项
	emit signalTips(QString(tr("请输入ftp连接地址")));

	// 未连接前禁用tablewidget,cdToParentButton,downLoadButton
	ui.tableWidget_->setEnabled(false);
	ui.cdToParentButton_->setEnabled(false);
	ui.downLoadButton_->setEnabled(false);

	progressDialog = new QProgressDialog(this);

	// tableWidget_
	connect(ui.tableWidget_, SIGNAL(itemActivated(QTableWidgetItem*)), this, SLOT(processItem(QTableWidgetItem*)));
	//connect(ui.tableWidget_->horizontalHeader(), SIGNAL(sectionClicked()), this, SLOT(headerClicked(int)));
	// 使能downLoadButton
	connect(ui.tableWidget_, SIGNAL(currentItemChanged(QTableWidgetItem*, QTableWidgetItem*)), this, SLOT(enableDownloadButton()));
	// 是否连接
	connect(ui.connectButton_, SIGNAL(clicked()), this, SLOT(connectOrDisconnect()));
	// 进度条
	connect(progressDialog, SIGNAL(canceled()), this, SLOT(cancelDownload()));
	// 返回上一级目录
	connect(ui.cdToParentButton_, SIGNAL(clicked()), this, SLOT(cdToParent()));
	// 下载文件
	connect(ui.downLoadButton_, SIGNAL(clicked()), this, SLOT(downloadCurrentFile()));
}

FileManagerBar::~FileManagerBar()
{
	
}

void FileManagerBar::enableConnectButton()
{
	// 保存当前配置
	QNetworkConfiguration config = networkSession->configuration();
	QString id;
	if (config.type() == QNetworkConfiguration::UserChoice)
	{
		id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
	}
	else
	{
		id = config.identifier();
	}

	QSettings settings(QSettings::UserScope, QLatin1String("Trolltech"));
	settings.beginGroup(QLatin1String("QtNetwork"));
	settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
	settings.endGroup();

	// 使能连接按钮
	ui.connectButton_->setEnabled(true);
	// 提示信息：请输入连接地址
	emit signalTips(QString(tr("请输入连接地址")));
}

void FileManagerBar::enableDownloadButton()
{
	// 获取所在行的文件名
	QTableWidgetItem *current = ui.tableWidget_->currentItem();
	if (current)				// 当前目录下有内容
	{
		QTableWidgetItem *tempItem = ui.tableWidget_->item(current->row(), 0);
		QString currentFile = tempItem->text();
		ui.downLoadButton_->setEnabled(!isDirectory.value(currentFile));
	} 
	else 
	{
		ui.downLoadButton_->setEnabled(false);
	}
}

void FileManagerBar::processItem(QTableWidgetItem* tableItem)
{
	// 获取所在行第一列name，即文件名
	QTableWidgetItem *tempItem = ui.tableWidget_->item(tableItem->row(), 0);
	QString name = tempItem->text();

	// 是文件夹
	if (isDirectory.value(name)) 
	{
		ui.tableWidget_->tableWidgetClear();
		isDirectory.clear();
		currentPath += '/';
		currentPath += name;
		ftp->cd(name);
		ftp->list();
		ui.cdToParentButton_->setEnabled(true);
#ifndef QT_NO_CURSOR
		setCursor(Qt::WaitCursor);
#endif
		return;
	}
}

void FileManagerBar::connectOrDisconnect()
{
	if (ftp)		// 当前是ftp连接，断开连接
	{
		ftp->abort();
		ftp->deleteLater();
		ftp = 0;
		// 禁用tablewidget,cdToParentButton,downLoadButton，改变连接按钮
		ui.tableWidget_->setEnabled(false);
		ui.cdToParentButton_->setEnabled(false);
		ui.downLoadButton_->setEnabled(false);
		ui.connectButton_->setEnabled(true);
		ui.connectButton_->setText(tr("连接"));
#ifndef QT_NO_CURSOR
		setCursor(Qt::ArrowCursor);
#endif
		// 提示信息：请输入连接地址
		emit signalTips(QString(tr("请输入连接地址")));
		return;
	}

#ifndef QT_NO_CURSOR
	setCursor(Qt::WaitCursor);
#endif

	if (!networkSession || !networkSession->isOpen())			// 连接不成功
	{
		if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) // 在执行网络操作之前创建网络会话的
		{
			if (!networkSession) 
			{
				// 获取保存的网络配置
				QSettings settings(QSettings::UserScope, QLatin1String("Trolltech"));
				settings.beginGroup(QLatin1String("QtNetwork"));
				const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
				settings.endGroup();

				// 保存的网络配置与当前不一致，使用系统默认值
				QNetworkConfiguration config = manager.configurationFromIdentifier(id);
				if ((config.state() & QNetworkConfiguration::Discovered) != QNetworkConfiguration::Discovered) 
				{
					config = manager.defaultConfiguration();		// 获取系统默认配置
				}

				// 重新建立对话
				networkSession = new QNetworkSession(config, this);
				connect(networkSession, SIGNAL(opened()), this, SLOT(connectToFtp()));
				connect(networkSession, SIGNAL(error(QNetworkSession::SessionError)), this, SLOT(enableConnectButton()));
			}
			ui.connectButton_->setEnabled(false);

			// 提示：正在打开对话
			emit signalTips(QString(tr("正在打开对话")));
			networkSession->open();		// 打开对话
			return;
		}
	}
	connectToFtp();
}

void FileManagerBar::connectToFtp()
{
	ftp = new QFtp(this);
	connect(ftp, SIGNAL(commandFinished(int, bool)), this, SLOT(ftpCommandFinished(int, bool)));
	connect(ftp, SIGNAL(listInfo(QUrlInfo)), this, SLOT(addToList(QUrlInfo)));
	connect(ftp, SIGNAL(dataTransferProgress(qint64, qint64)), this, SLOT(updateDataTransferProgress(qint64, qint64)));

	// 更新路径信息，表格信息
	ui.tableWidget_->tableWidgetClear();
	currentPath.clear();
	isDirectory.clear();

	QUrl url(ui.ftpServerLineEdit_->text());
	if (!url.isValid() || url.scheme().toLower() != QLatin1String("ftp")) 
	{
		ftp->connectToHost(ui.ftpServerLineEdit_->text(), 21);
		ftp->login();
	} 
	else 
	{
		ftp->connectToHost(url.host(), url.port(21));

		if (!url.userName().isEmpty())
		{
			ftp->login(QUrl::fromPercentEncoding(url.userName().toLatin1()), url.password());
		}
		else
		{
			ftp->login();
		}
			
		if (!url.path().isEmpty())
		{
			ftp->cd(url.path());
		}
	}

	// 启用tableWidget，改变连接按钮
	ui.tableWidget_->setEnabled(true);
	ui.connectButton_->setEnabled(false);
	ui.connectButton_->setText(tr("断开"));

	// 提示信息：正在连接%1...
	emit signalTips(QString(tr("正在连接%1...").arg(ui.ftpServerLineEdit_->text())));
}

void FileManagerBar::ftpCommandFinished(int, bool error)
{
#ifndef QT_NO_CURSOR
	setCursor(Qt::ArrowCursor);
#endif

	if (ftp->currentCommand() == QFtp::ConnectToHost)		// 连接命令
	{
		if (error)					// 报错
		{
			// error报警提示：连接ui.ftpServerLineEdit_->text()失败
			emit signalTips(QString(tr("错误：连接%1失败").arg(ui.ftpServerLineEdit_->text())));
			connectOrDisconnect();
			return;
		}
		// 提示信息：连接ui.ftpServerLineEdit_->text()成功
		emit signalTips(QString(tr("连接%1成功").arg(ui.ftpServerLineEdit_->text())));
		ui.tableWidget_->setFocus();
		ui.downLoadButton_->setDefault(true);
		ui.connectButton_->setEnabled(true);
		return;
	}

	if (ftp->currentCommand() == QFtp::Login)			// 登录命令
		ftp->list();

	if (ftp->currentCommand() == QFtp::Get)				// 文件下载命令
	{
		if (error)										// 获取失败
		{
			// 提示信息：取消下载
			emit signalTips(QString(tr("取消下载%1...").arg(file->fileName())));
			// 文件关闭，移除
			file->close();
			file->remove();
		} 
		else 
		{
			// 提示信息：已下载
			emit signalTips(QString(tr("已下载%1...").arg(file->fileName())));
			file->close();
		}
		delete file;
		enableDownloadButton();
		progressDialog->hide();
	} 
	else if (ftp->currentCommand() == QFtp::List) 
	{
		if (isDirectory.isEmpty())				// 获取的是空文件夹
		{
			ui.tableWidget_->setItem(0, 0, new QTableWidgetItem(QString(tr("<empty>"))));
			ui.tableWidget_->setEnabled(false);
		}
	}
}

void FileManagerBar::addToList(const QUrlInfo &urlInfo)
{
	QString qSuffix		   = "";
	QString qstrFileSize   = "";
	QString qfilename	   = "";
	QString qfileDate	   = "";
	QString qfileAuthority = "";
	int     nfileSize	   = 0;
	double  dfileSize	   = 0.0;

	qfilename = urlInfo.name();												// 文件名
	qfileDate = urlInfo.lastModified().toString("yyyy-MM-dd hh:mm");		// 最后修改时间
	nfileSize = urlInfo.size();												// 文件大小

	// 截取文件类型
	QString str = ".";
	qSuffix = qfilename.mid(qfilename.lastIndexOf(str));					// 截取.后面文件后缀
	if (qSuffix == qfilename)												// 文件没有后缀名
	{
		qSuffix	= "";
	}

	if (urlInfo.isDir() == false)				// 不是目录文件，获取文件大小
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

	// 获取文件的读写权限
	if (urlInfo.isReadable() && urlInfo.isWritable())
	{
		qfileAuthority = "读写";
	} 
	else if (urlInfo.isWritable())
	{
		qfileAuthority = "写";
	}
	else if (urlInfo.isReadable())
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
	int row = ui.tableWidget_->rowCount();
	ui.tableWidget_->insertRow(row);
	ui.tableWidget_->setItem(row, 0, fileName);
	ui.tableWidget_->setItem(row, 1, fileSize);
	ui.tableWidget_->setItem(row, 2, fileType);
	ui.tableWidget_->setItem(row, 3, filePermission);
	ui.tableWidget_->setItem(row, 4, fileDate);	

	isDirectory[urlInfo.name()] = urlInfo.isDir();		// 存储文件是否是目录
	ui.tableWidget_->setEnabled(true);
}

void FileManagerBar::updateDataTransferProgress(qint64 readBytes, qint64 totalBytes)
{
	progressDialog->setMaximum(totalBytes);
	progressDialog->setValue(readBytes);
}

void FileManagerBar::cdToParent()
{
#ifndef QT_NO_CURSOR
	setCursor(Qt::WaitCursor);
#endif

	// 清楚表格信息
	ui.tableWidget_->tableWidgetClear();
	isDirectory.clear();
	// 返回上一级目录
	currentPath = currentPath.left(currentPath.lastIndexOf('/'));
	if (currentPath.isEmpty()) 
	{
		ui.cdToParentButton_->setEnabled(false);
		ftp->cd("/");
	} 
	else 
	{
		ftp->cd(currentPath);
	}
	ftp->list();
}

void FileManagerBar::downloadCurrentFile()
{
	// 获取所在行第一列name，即文件名
	QTableWidgetItem *tempItem = ui.tableWidget_->item(ui.tableWidget_->currentItem()->row(), 0);
	QString fileName = tempItem->text();
	downloadFile(fileName);
}

bool FileManagerBar::downloadFile(QString fileName)
{
	if (QFile::exists(fileName))			// 当前已存在此文件
	{
		// error报错信息：fileName文件已存在！
		emit signalTips(QString(tr("错误：%1文件已存在！").arg(fileName)));
		return false;
	}

	file = new QFile(fileName);
	if (!file->open(QIODevice::WriteOnly))	// 非只读删除文件
	{
		// error报错信息
		emit signalTips(QString(tr("错误：%1文件不可保存！%2").arg(fileName).arg(file->errorString())));
		delete file;
		return false;
	}

	ftp->get(fileName, file);				// 获取文件
	progressDialog->setLabelText(tr("Downloading %1...").arg(fileName));
	ui.downLoadButton_->setEnabled(false);
	progressDialog->exec();
	return true;
}

void FileManagerBar::cancelDownload()
{
	ftp->abort();			// 中止命令
	if (file->exists())		// 文件存在则删除
	{
		file->close();
		file->remove();
	}
	delete file;
}

QString FileManagerBar::getCurrentFileName()
{
	QTableWidgetItem *tempItem = ui.tableWidget_->item(ui.tableWidget_->currentItem()->row(), 0);
	QString fileName = tempItem->text();		// 当前行文件名
	return fileName;
}

bool FileManagerBar::checkDownload(QString fileName)
{
	if (QFile::exists(fileName))				// 当前已存在此文件
	{
		return true;
	}
	else
	{
		return downloadFile(fileName);			// 文件未下载先下载
	}
}