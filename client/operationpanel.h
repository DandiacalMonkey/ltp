#ifndef LTP_CLIENT_OPERATIONPANEL_H_
#define LTP_CLIENT_OPERATIONPANEL_H_

#include <QtGui/QWidget>
#include "ui_operationpanel.h"

namespace ltp
{
	namespace client
	{
		class OperationPanel : public QWidget
		{
			Q_OBJECT
		 
		public:
			OperationPanel(QWidget *parent = 0);
			~OperationPanel();  

		private:
			Ui::OperationPanelClass ui;

		};
	}
}


#endif // LTP_CLIENT_OPERATIONPANEL_H_