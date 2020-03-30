#include "setwidget.h"
#include <QtXml>
#include <QtNetwork/QtNetwork>
#include "network.h"
#include "hintbar.h"
#include "hintwidgetproxy.h"

using ltp::client::SetWidget;

SetWidget::SetWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connectState(false);			// 初始连接状态
	readIPSetting();				// 读取断电保存ip地址	
	ui.teachIPLineEdit_->setIP(getTeachIP());
	ltp::base::getInstance<ltp::client::Network>().setHost(ui.controllerIPLineEdit_->getIP().toStdString());

	// 连接状态改变
	connect(&base::getInstance<Network>(), SIGNAL(connected(const std::string&)), this, SLOT(setConnected()));
	connect(&base::getInstance<Network>(), SIGNAL(unconnected()), this, SLOT(setDisconnected()));
	connect(&base::getInstance<Network>(), SIGNAL(disconnected()), this, SLOT(setDisconnected()));
	// 连接按钮作用
	connect(ui.connectButton_, SIGNAL(clicked(bool)), this, SLOT(connectClicked())); 
}

SetWidget::~SetWidget()
{
	
}

void SetWidget::changeTeachIP()
{
	QString ipValue = ui.teachIPLineEdit_->getIP();			// 示教器输入框ip
	QString ipSystem = getTeachIP();						// 当前示教器系统ip值
	if (ipSystem != ipValue)								// 当前实际ip与输入框ip不一致进行修改
	{	
		QString ipadd;
		QString netmask;
		QString network;
		QString broadcast;
		QString gateway;
		int pos1 = 0,pos2 = 0,pos3 = 0;
		ipadd = ipValue;
		for(int i = 0; i < 15; i++)
		{
			if(pos1 == 0)
			{
				if((ipadd.mid(i, 1)) == ".")
				{
					pos1 = i;
					continue;
				}
			}
			if(pos2 == 0)
			{
				if((ipadd.mid(i, 1)) == ".")
				{
					pos2 = i;
					continue;
				}
			}

			if(pos3 == 0)
			{
				if((ipadd.mid(i, 1)) == ".")
				{
					pos3 = i;
					continue;
				}
			}
		}
		// netmask
		if(pos1 == 3)
		{
			netmask="255.";
		}
		if(pos2 <= 7)
		{
			netmask += "255.";
		}
		if(pos3 <= 11)
		{
			netmask += "255.";
			netmask += "0";

		}
		qDebug()<< netmask;
		//network
		network = ipadd.mid(0, pos3);
		network += ".1";
		qDebug()<<network;
		//broadcast
		broadcast = ipadd.mid(0, pos3);
		broadcast += ".255";
		qDebug()<<broadcast;
		//gateway
		gateway=ipadd.mid(0, pos3);
		gateway += ".1";
		qDebug()<<gateway;
		// 删除原先网络配置文件，重新编写
		system("rm /userfs/network/interfaces");
		system("touch /userfs/network/interfaces");
		QFile f("/userfs/network/interfaces");
		if(!f.open(QIODevice::ReadWrite | QIODevice::Text))		// 示教器ip设置失败，输入框设为原先ip值
		{
			base::getInstance<HintWidgetProxy<HintBar>>().setHint("设置示教器IP失败!");
			ui.teachIPLineEdit_->setIP(ipSystem);
		}

		// 将配置信息写入interfaces文件
		QTextStream txtOutput(&f);
		QString line1,line2,line3,line4,line5,line6,line7,line8,line9,line10;
		line1 = "# Configure Loopback";
		line2 = "auto lo";
		line3 = "iface lo inet loopback";
		line4 = "auto eth0";
		line5 = "iface eth0 inet static";
		line6 = ("address  "+ipadd);
		line7 = ("netmask  "+netmask);
		line8 = ("network  "+network);
		line9 = ("broadcast  "+broadcast);
		line10 = ("gateway  "+gateway);
		txtOutput<< line1<<endl;
		txtOutput<< line2<< endl;
		txtOutput<< line3<< endl;
		txtOutput<< line4<< endl;
		txtOutput<< line5<< endl;
		txtOutput<< line6<< endl;
		txtOutput<< line7<< endl;
		txtOutput<< line8<< endl;
		txtOutput<< line9<< endl;
		txtOutput<< line10<< endl;
		f.close();
		system("chmod 777 -R /userfs/network/interfaces");
		system("ifdown eth0 && ifup eth0");
		base::getInstance<HintWidgetProxy<HintBar>>().setHint("修改示教器IP成功!");
		this->repaint();
	}
}

QString SetWidget::getTeachIP()
{
	QFile dataFile("/userfs/network/interfaces");			// 配置文件
	if (dataFile.open(QFile::ReadOnly|QIODevice::Text))
	{
		QTextStream data(&dataFile);
		QString line;
		while (!data.atEnd())								// 逐行读取文本，并去除每行的回车
		{
			line = data.readLine();
			line.remove('\n');
			if(line.contains("address"))					// 获取本机ip地址
			{
				return str_Analysis(line);
			}
		}
	}
	return "";
}

QString SetWidget::str_Analysis(QString line)
{
	QString str = line;
	// 取数字，去除其他信息如address
	for(int i = 0; i < str.size(); i++)
	{
		if((str.at(i) >= '0') && (str.at(i) <= '9'))
		{
			str.remove(0, i);
			break;
		}
	}
	return str;
}

void SetWidget::readIPSetting()
{
	QFile file("Settings/ip_address.xml");
	if (!file.open(QFile::ReadOnly | QFile::Text))
	{
		// 无法打开
		return;
	}
	QXmlStreamReader reader(&file);
	while (!reader.atEnd())
	{
		if (reader.isStartElement())
		{
			if (reader.name() == "ip")				// 读到ip
			{
				 reader.readNext();
				 while (!reader.atEnd())
				 {
					 if (reader.isEndElement())		// 结尾标志跳出循环
					 {
						 reader.readNext();
						 break;
					 }

					 if (reader.isStartElement())
					 {
						 if (reader.name() == "ControllerIP")		// 读取控制器ip
						 {
							 ui.controllerIPLineEdit_->setIP(reader.readElementText());
							 reader.readNext();
						 }
						 //else if (reader.name() == "TeachIP")		// 读取示教器ip
						 //{
							// ui.teachIPLineEdit_->setIP(reader.readElementText());
							// reader.readNext();
						 //}
						 else
						 {
							 reader.readNext();
						 }
					 }
					 else
					 {
						 reader.readNext();
					 }
				 }
			}
		}
		else
		{
			reader.readNext();
		}
	}
	file.close();
}

void SetWidget::writeIPSetting()
{
	//打开或创建文件
	QFile file("Settings/ip_address.xml");
	if (!file.open(QIODevice::WriteOnly))
	{
		qDebug() << "writeIPSetting error";
		return;
	}

	// 写入ip信息
	QXmlStreamWriter xmlWriter(&file);
	xmlWriter.setAutoFormatting(true);
	xmlWriter.writeStartDocument();
	xmlWriter.writeStartElement("ip");
	xmlWriter.writeTextElement("ControllerIP", ui.controllerIPLineEdit_->getIP());
	//xmlWriter.writeTextElement("TeachIP", ui.teachIPLineEdit_->getIP());
	xmlWriter.writeEndElement();
	xmlWriter.writeEndDocument();
	file.close();
}

void SetWidget::setDisconnected()
{
	connectState(false);
}

void SetWidget::setConnected()
{
	connectState(true);
}

void SetWidget::connectState(bool connected)
{
	if (connected)			// 连接状态改变按钮文字，输入框禁用
	{
		ui.connectButton_->setText(tr("断开"));
		ui.controllerIPLineEdit_->setEnabled(false);
		ui.teachIPLineEdit_->setEnabled(false);
	} 
	else					// 断开状态改变按钮文字，输入框启用
	{
		ui.connectButton_->setText(tr("连接"));
		ui.controllerIPLineEdit_->setEnabled(true);
		ui.teachIPLineEdit_->setEnabled(true);
	}
}

void SetWidget::connectClicked()
{
	if (ui.connectButton_->text() == tr("断开"))
	{
		ltp::base::getInstance<ltp::client::Network>().disconnect();
	}
	else if (ui.connectButton_->text() == tr("连接"))
	{
		// 修改示教器ip
		changeTeachIP();
		ltp::base::getInstance<ltp::client::Network>().setHost(ui.controllerIPLineEdit_->getIP().toStdString());
		// 网络连接需要最后执行，部分初始化依赖于网络连接信号
		ltp::base::getInstance<ltp::client::Network>().connect();		
		// 断电保存
		writeIPSetting();
	}
}