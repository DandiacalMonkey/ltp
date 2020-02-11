#ifndef LTP_CLIENT_TITLEBAR_H_
#define LTP_CLIENT_TITLEBAR_H_

#include <QtGui/QWidget>
#include "ui_titlebar.h"

namespace ltp
{
namespace client
{
class TitleBar : public QWidget
{
	Q_OBJECT

public:
	TitleBar(QWidget *parent = 0);
	~TitleBar();

private:
	Ui::TitleBarClass ui;
};
}
}


#endif // LTP_CLIENT_TITLEBAR_H_