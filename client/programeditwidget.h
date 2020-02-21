#ifndef LTP_CLIENT_PROGRAMEDITWIDGET_H_
#define LTP_CLIENT_PROGRAMEDITWIDGET_H_

#include <QtGui/QWidget>
#include "ui_programeditwidget.h"

namespace ltp
{
	namespace client
	{

		class ProgramEditWidget : public QWidget
		{
			Q_OBJECT
		 
		public:
			ProgramEditWidget(QWidget *parent = 0);
			~ProgramEditWidget();  

		private:
			Ui::ProgramEditWidgetClass ui;

		};
	}
}
#endif // LTP_CLIENT_PROGRAMEDITWIDGET_H_