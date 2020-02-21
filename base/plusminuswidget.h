#ifndef LTP_CLIENT_PLUSMINUSWIDGET_H_
#define LTP_CLIENT_PLUSMINUSWIDGET_H_

#include <QtGui/QWidget>
#include "ui_plusminuswidget.h"

namespace ltp
{
	namespace base
	{
		class PlusMinusWidget : public QWidget
		{
			Q_OBJECT

		public:
			PlusMinusWidget(QWidget* parent = 0);
			~PlusMinusWidget();

			void setValue(int value);
		private:
			Ui::PlusMinusWidgetClass ui;
		};
	}
}


#endif // LTP_CLIENT_PLUSMINUSWIDGET_H_