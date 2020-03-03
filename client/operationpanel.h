#ifndef LTP_CLIENT_OPERATIONPANEL_H_
#define LTP_CLIENT_OPERATIONPANEL_H_

#include <QtGui/QWidget>
#include "ui_operationpanel.h"
#include <QTimer>

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
			QTimer *timer_;

		private slots:
			void onTimer();
			void changeFeedRate(int);
		};
	}
}


#endif // LTP_CLIENT_OPERATIONPANEL_H_