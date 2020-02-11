#ifndef LTP_CLIENT_HINTWIDGETPROXY_H_
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
	void setHintWidget(T* hintWidget)
	{
		hintWidget_ = hintWidget;
	}
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
