#ifndef LTP_CLIENT_HINTBAR_H_
#define LTP_CLIENT_HINTBAR_H_

#include <QWidget>
#include <QTime>
#include <QTimer>
#include "ui_hintbar.h"

namespace ltp
{
namespace client
{
class HintBar : public QWidget
{
	Q_OBJECT

public:
	HintBar(QWidget* parent = 0);
	~HintBar();

public slots:
	//设定要显示的提示
	void setHint(const QString& hint);

private:
	//提示保留最长时间
	static const int kHintSurvivalSeconds_ = 10;
	Ui::HintBarClass ui;
	//提示设定的时间点
	QTime hintTime_;
	//定时清空提示信息
	QTimer hintClearTimer_;

private slots:
	//定时清空提示信息
	void hintClear();

};
}
}


#endif // LTP_CLIENT_HINTBAR_H_