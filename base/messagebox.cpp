#include "messagebox.h"
#include <QBoxLayout>
#include "base/pushbutton.h"

using ltp::base::MessageBox;

MessageBox::MessageBox(QDialog*parent)
	: QDialog(parent),
	  clickedButton_(nullptr)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);
	//close按钮
	connect(ui.titleWidget_, SIGNAL(signalClose()), this, SLOT(reject()));
	//拖动标题栏进行移动
	connect(ui.titleWidget_, SIGNAL(mouseMove(QPoint)), this, SLOT(moveDialog(QPoint)));
}

MessageBox::~MessageBox()
{
	contentWidget_->setParent(nullptr);
}

void MessageBox::setContentWidget(std::shared_ptr<QWidget> contentWidget)
{
	contentWidget_ = contentWidget;
	dynamic_cast<QBoxLayout*>(ui.contentWidget_->layout())->addWidget(contentWidget_.get(), 1, Qt::AlignCenter);
}

void MessageBox::setTitleName(const QString& text)
{
	//设置窗口标题名
	ui.titleWidget_->setTitleName(text);
}

QPushButton* ltp::base::MessageBox::addButton(const QString& text, QMessageBox::ButtonRole /*role*/)
{
	//构造按钮
	DialogButton* dialogButton = new DialogButton(ui.bottomWidget_);
	dialogButton->setText(text);
	dialogButton->setMinimumSize(86, 24);
	//按钮添加显示
	dynamic_cast<QBoxLayout*>(ui.bottomWidget_->layout())->addWidget(dialogButton, 1, Qt::AlignCenter);
	//按钮处理
	connect(dialogButton, SIGNAL(clicked()), SLOT(buttonClick()));
	return dialogButton;
}

void MessageBox::buttonClick()
{
	//储存最后按下按钮指针
	clickedButton_ = dynamic_cast<QPushButton*>(sender());
	//关闭窗口
	close();
}

void MessageBox::moveDialog(QPoint point)
{
	//以当前位置做偏移移动窗口
	move(x() + point.x(), y() + point.y());
}
