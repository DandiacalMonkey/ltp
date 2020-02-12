#include "buttonprocessor.h"

using ltp::base::ButtonProcessor;

ButtonProcessor::ButtonInterface::ButtonInterface()
	:state_(PRESSED)
{
}

bool ButtonProcessor::ButtonInterface::isFinished() const
{
	QMutexLocker locker(&mutex_);
	return state_ == RELEASED;
}

ButtonProcessor& ButtonProcessor::getInstance()
{
	static ButtonProcessor buttonProcessor;
	return buttonProcessor;
}

ButtonProcessor::ButtonProcessor()
	: kProcessInterval_(20)
{
	processTimer_.start(kProcessInterval_);
	connect(&processTimer_, SIGNAL(timeout()), SLOT(processButton()));
}

void ButtonProcessor::addButton(const std::shared_ptr<ButtonInterface>& button)
{
	QMutexLocker locker(&mutex_);
	buttonsList_.push_back(button);
}

void ButtonProcessor::processButton()
{
	QMutexLocker locker(&mutex_);
	for (auto iterator = buttonsList_.begin(); iterator != buttonsList_.end(); )
	{
		//按钮触发
		(*iterator)->trigger();
		//判定按钮是否结束工作
		if ((*iterator)->isFinished())
		{
			iterator = buttonsList_.erase(iterator);
		}
		else
		{
			iterator++;
		}
	}
}
