#ifndef LTP_CLIENT_PROCESSWIDGET_H_
#define LTP_CLIENT_PROCESSWIDGET_H_

#include <QtGui/QWidget>
#include "ui_processwidget.h"

namespace ltp
{
	namespace client
	{

		class ProcessWidget : public QWidget
		{
			Q_OBJECT
		 
		public:
			ProcessWidget(QWidget *parent = 0);
			~ProcessWidget();  

		private:
			Ui::ProcessWidgetClass ui;

		};
	}
}
#endif // LTP_CLIENT_PROCESSWIDGET_H_