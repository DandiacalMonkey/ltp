#ifndef LTP_CLIENT_PROCESSBAR_H_
#define LTP_CLIENT_PROCESSBAR_H_

#include <QtGui/QWidget>
#include "ui_processbar.h"

namespace ltp
{
	namespace client
	{

		class ProcessBar : public QWidget
		{
			Q_OBJECT
		 
		public:
			ProcessBar(QWidget *parent = 0);
			~ProcessBar();  

		private:
			Ui::ProcessBarClass ui;

		private slots:
			void onProcessFile(QString);

		};
	}
}
#endif // LTP_CLIENT_PROCESSBAR_H_