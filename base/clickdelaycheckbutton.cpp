#include "clickdelaycheckbutton.h"

using ltp::base::ClickDelayCheckButton;

ClickDelayCheckButton::ClickDelayCheckButton(QWidget* parent)
	: QPushButton(parent),
	  isAutoChecked_(true),
	  timer_(nullptr)
{
	setCheckable(true);
}

ClickDelayCheckButton::~ClickDelayCheckButton()
{
}

void ClickDelayCheckButton::setCheckFunction(const std::function<void ()>& function, int milliseconds)
{
	//设定点按时不会切换checked状态
	isAutoChecked_ = false;
	//定时确认checked状态函数
	checkFunction_ = function;
	//检查定时器启动
	if (timer_ == nullptr)
	{
		timer_ = new QTimer(this);
	}
	connect(timer_, SIGNAL(timeout()), SLOT(checkState()));
	timer_->start(milliseconds);
}

void ClickDelayCheckButton::setClickDelayCheck(const std::function<void()>& clickFunction, int miliseconds, const std::function<void()>& delayCheckFunction)
{
	//点按时执行函数
	clickFunction_ = clickFunction;
	//延迟时间
	delayMilliseconds_ = miliseconds;
	//时间结束后执行函数
	delayCheckFunction_ = delayCheckFunction;
	//点击触发
	connect(this, SIGNAL(clicked()), SLOT(onClick()));
}

void ltp::base::ClickDelayCheckButton::setAutoChecked(bool isAutoChecked)
{
	isAutoChecked_ = isAutoChecked;
}

void ClickDelayCheckButton::nextCheckState()
{
	//点击时Qt自动调用，重写可屏蔽checked自动切换
	if (isAutoChecked_ && isCheckable())
	{
		setChecked(!isChecked());
	}
}

void ClickDelayCheckButton::onClick()
{
	clickFunction_();
	QTimer::singleShot(delayMilliseconds_, this, SLOT(checkClick()));
}

void ClickDelayCheckButton::checkClick()
{
	delayCheckFunction_();
}

void ClickDelayCheckButton::checkState()
{
	checkFunction_();
}
