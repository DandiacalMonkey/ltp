#include "buttonprocessor.h"

using ltp::base::ButtonProcessor;

ButtonProcessor::ButtonInterface::ButtonInterface()
	:state_(PRESSED)
{
}

bool ButtonProcessor::ButtonInterface::isFinished() const
{
	return state_ == RELEASED;
}

ButtonProcessor::FunctionalButton::FunctionalButton(
	const std::function<void (ButtonProcessor::ButtonInterface * buttonInterface)>& trigger1,
	const std::function<void (ButtonProcessor::ButtonInterface * buttonInterface)>& trigger2,
	const std::function<void (ButtonProcessor::ButtonInterface * buttonInterface)>& trigger3)
{
	trigger1_ = trigger1;
	trigger2_ = trigger2;
	trigger3_ = trigger3;
}

void ButtonProcessor::FunctionalButton::trigger()
{
	switch (state_)
	{
	case PRESSED:
		trigger1_(this);
		break;
	case HOLD:
		trigger2_(this);
		break;
	case RELEASED:
		trigger3_(this);
		break;
	default:
		break;
	}
}

ButtonProcessor::ButtonProcessor()
	: kProcessInterval_(20)
{
	processTimer_.start(kProcessInterval_);
	connect(&processTimer_, SIGNAL(timeout()), SLOT(processButton()));
}

void ButtonProcessor::addButton(std::shared_ptr<ButtonInterface>& button)
{
	QMutexLocker locker(&mutex_);
	buttonsList_.push_back(button);
}

void ButtonProcessor::processButton()
{
	QMutexLocker locker(&mutex_);
	for (auto iterator = buttonsList_.begin(); iterator != buttonsList_.end(); )
	{
		//判定按钮是否结束工作
		if ((*iterator)->isFinished())
		{
			iterator = buttonsList_.erase(iterator);
		}
		else
		{
			//按钮触发
			(*iterator)->trigger();
			iterator++;
		}
	}
}
