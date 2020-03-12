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
	isAutoChecked_ = false;
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
	clickFunction_ = clickFunction;
	delayMilliseconds_ = miliseconds;
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
