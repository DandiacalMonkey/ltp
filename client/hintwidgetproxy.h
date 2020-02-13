﻿#ifndef LTP_CLIENT_HINTWIDGETPROXY_H_
#define LTP_CLIENT_HINTWIDGETPROXY_H_

#include <Qstring>

namespace ltp
{
namespace client
{
template<typename T>
class HintWidgetProxy
{
public:
	static HintWidgetProxy<T>& getInstance()
	{
		static HintWidgetProxy<T> hintWidgetProxy;
		return hintWidgetProxy;
	}
	//设定代理的控件
	void setHintWidget(T* hintWidget)
	{
		hintWidget_ = hintWidget;
	}
	//代理控件显示提示
	void setHint(const QString& hint)
	{
		hintWidget_->setHint(hint);
	}

private:
	HintWidgetProxy<T>() {}
	~HintWidgetProxy() {}
	T* hintWidget_;
};
}
}

#endif // !LTP_CLIENT_HINTWIDGETPROXY_H_
