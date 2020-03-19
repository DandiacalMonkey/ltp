#ifndef LTP_CLIENT_SETWIDGET_H_
#define LTP_CLIENT_SETWIDGET_H_

#include <QtGui/QWidget>
#include "ui_setwidget.h"

namespace ltp
{
	namespace client
	{
		class SetWidget : public QWidget
		{
			Q_OBJECT
		 
		public:
			SetWidget(QWidget *parent = 0);
			~SetWidget();

		private:
			Ui::SetWidgetClass ui;

		private slots:
			void connectState(bool);
			void connectClicked(bool);

		signals:
			void connectIP(QString controllerIP, QString teachIP, bool connected);
		};
	}
}
#endif // LTP_CLIENT_SETWIDGET_H_