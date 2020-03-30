#include "iplineedit.h"

#include <QButtonGroup>
#include <QKeyEvent>

using ltp::base::IPLineEdit;

IPLineEdit::IPLineEdit(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	// 设置IP地址校验过滤
	QRegExp regExp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
	QRegExpValidator *validator = new QRegExpValidator(regExp, this);
	ui.txtIP1_->setValidator(validator);
	ui.txtIP2_->setValidator(validator);
	ui.txtIP3_->setValidator(validator);
	ui.txtIP4_->setValidator(validator);

	// 安装事件过滤器
	ui.txtIP1_->installEventFilter(this);
	ui.txtIP2_->installEventFilter(this);
	ui.txtIP3_->installEventFilter(this);
	ui.txtIP4_->installEventFilter(this);

	// 四个输入框输入改变
	connect(ui.txtIP1_, SIGNAL(textChanged(QString)), this, SLOT(textChanged(QString)));
	connect(ui.txtIP2_, SIGNAL(textChanged(QString)), this, SLOT(textChanged(QString)));
	connect(ui.txtIP3_, SIGNAL(textChanged(QString)), this, SLOT(textChanged(QString)));
	connect(ui.txtIP4_, SIGNAL(textChanged(QString)), this, SLOT(textChanged(QString)));
}

IPLineEdit::~IPLineEdit()
{

}

QString IPLineEdit::getIP()
{
	return stringIP_;		// 返回当前IP地址
}

void IPLineEdit::textChanged(const QString& text)
{
	int len = text.length();
	int value = text.toInt();

	// 判断当前是否输入完成一个网段,是的话则自动移动到下一个输入框
	if (len == 3) 
	{
		if (value >= 100 && value <= 255) 
		{
			this->focusNextChild();
		}
	}

	// 判断当前输入有.作为分割符，跳到下一输入框
	if (text.indexOf(".") == 1 || text.indexOf(".") == 2)
	{
		QString textTemp = text.mid(0, text.indexOf("."));
		QLineEdit *currentLineEdit = static_cast<QLineEdit*>(this->focusWidget());
		currentLineEdit->setText(textTemp);
		this->focusNextChild();
	}

	// 判断是否全部输入完毕
	if (ui.txtIP1_->text() != "" && ui.txtIP2_->text() != "" &&
		ui.txtIP3_->text() != "" && ui.txtIP4_->text() != "")
	{
		emit hasFinished(true);
	} 
	else
	{
		emit hasFinished(false);
	}

	//拼接成完整IP地址
	stringIP_ = QString("%1.%2.%3.%4").arg(ui.txtIP1_->text()).arg(ui.txtIP2_->text())
				.arg(ui.txtIP3_->text()).arg(ui.txtIP4_->text());
}

void IPLineEdit::setIP(const QString ip)
{
	//先检测IP地址是否合法
	QRegExp regExp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
	if (!regExp.exactMatch(ip)) 
	{
		return;
	}

	if (stringIP_ != ip)
	{
		stringIP_ = ip;

		//将IP地址填入各个网段
		QStringList list = ip.split(".");
		ui.txtIP1_->setText(list.at(0));
		ui.txtIP2_->setText(list.at(1));
		ui.txtIP3_->setText(list.at(2));
		ui.txtIP4_->setText(list.at(3));
	}
}

void IPLineEdit::clear()
{
	ui.txtIP1_->clear();
	ui.txtIP2_->clear();
	ui.txtIP3_->clear();
	ui.txtIP4_->clear();
	ui.txtIP1_->setFocus();
}

bool IPLineEdit::eventFilter(QObject *obj, QEvent *event)
{
	if  (obj == ui.txtIP1_ || obj == ui.txtIP2_|| obj == ui.txtIP3_ || obj == ui.txtIP4_)
	{
		if (event->type() == QEvent::KeyPress) 
		{
			QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);// 转换为键盘事件
			//如果当前按下回车键则移动焦点到下一个输入框
			if (keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return)
			{
				this->focusNextChild();
			}

			//如果按下了退格键并且当前文本框已经没有了内容则焦点往前移
			if (keyEvent->key() == Qt::Key_Backspace) 
			{
				QLineEdit *editTemp = static_cast<QLineEdit*>(obj);
				if (editTemp->text().length() <= 1) 
				{
					this->focusNextPrevChild(false);
				}
			}
		}
	}
	return QWidget::eventFilter(obj, event);
}