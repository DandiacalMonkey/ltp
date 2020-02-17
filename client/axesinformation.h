#ifndef LTP_CLIENT_AXESINFORMATION_H_
#define LTP_CLIENT_AXESINFORMATION_H_

#include <QtGui/QWidget>
#include "ui_axesinformation.h"

namespace ltp
{
	namespace client
	{
		class AxesInformation : public QWidget
		{
			Q_OBJECT
		 
		public:
			AxesInformation(QWidget *parent = 0);
			~AxesInformation();  

		private:
			Ui::AxesInformationClass ui;

		};
	}
}


#endif // LTP_CLIENT_AXESINFORMATION_H_