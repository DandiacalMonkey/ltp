#ifndef LTP_CLIENT_AXESINFORMATION_H_
#define LTP_CLIENT_AXESINFORMATION_H_

#include <QtGui/QWidget>
#include "ui_axesinformation.h"
#include "base/globals.h"

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

			void setValidAxes(const std::vector<ltp::base::Axis> &validAxes);

		private:
			Ui::AxesInformationClass ui;

		};
	}
}


#endif // LTP_CLIENT_AXESINFORMATION_H_