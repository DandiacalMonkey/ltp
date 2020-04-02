#include "dialogtitlewidget.h"
#include <QMouseEvent>

using ltp::base::DialogTitleWidget;

DialogTitleWidget::DialogTitleWidget(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	// close按钮按下，发出关闭信号
	connect(ui.closeButton_, SIGNAL(clicked()), this, SIGNAL(signalClose()));
}

DialogTitleWidget::~DialogTitleWidget()
{

}

void DialogTitleWidget::setTitleName(const QString &text)
{
	// 设置标题名
	ui.titleLabel_->setText(text);
}

void DialogTitleWidget::mousePressEvent(QMouseEvent *event)
{
	// 鼠标左键按下，记录当前鼠标位置，移动标志位置1
	if (event->button() == Qt::LeftButton)
	{
		isMoveFlag_ = true;
		mousePressPos_ = event->globalPos();
	}
	return QWidget::mousePressEvent(event);
}

void DialogTitleWidget::mouseReleaseEvent(QMouseEvent *event)
{
	// 鼠标松开代表停止移动
	isMoveFlag_ = false;
	return QWidget::mouseReleaseEvent(event);
}

void DialogTitleWidget::mouseMoveEvent(QMouseEvent *event)
{
	// 当前是移动状态
	if (isMoveFlag_)
	{
		// 发送移动位置坐标
		QPoint mouseMoveTemp;
		mouseMoveTemp.setX(event->globalX() - mousePressPos_.x());
		mouseMoveTemp.setY(event->globalY() - mousePressPos_.y());
		emit mouseMove(mouseMoveTemp);
		// 更新当前位置
		mousePressPos_ = event->globalPos();
	}
	return QWidget::mouseMoveEvent(event);
}