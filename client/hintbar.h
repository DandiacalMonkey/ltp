#ifndef LTP_CLIENT_HINTBAR_H_
#define LTP_CLIENT_HINTBAR_H_

#include <QtGui/QWidget>
#include "ui_hintbar.h"

namespace ltp
{
namespace client
{
class HintBar : public QWidget
{
	Q_OBJECT

public:
	explict HintBar(QWidget* parent = 0);
	~HintBar();

public slots:
	//设定要显示的提示
	void setHint(const QString& hint)
	{
		ui.hintLabel_->setText(hint);
	}

private:
	Ui::HintBarClass ui;
};
}
}


#endif // LTP_CLIENT_HINTBAR_H_