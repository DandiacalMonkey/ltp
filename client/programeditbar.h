#ifndef LTP_CLIENT_PROGRAMEDITBAR_H_
#define LTP_CLIENT_PROGRAMEDITBAR_H_

#include <QtGui/QWidget>
#include "ui_programeditbar.h"
#include "base/globals.h"

namespace ltp
{
	namespace client
	{

		class ProgramEditBar : public QWidget
		{
			Q_OBJECT
		 
		public:
			ProgramEditBar(QWidget *parent = 0);
			~ProgramEditBar();  

		private:
			Ui::ProgramEditBarClass ui;

		private slots:
			void setValidAxes(const std::vector<ltp::base::Axis> &validAxes);
		};
	}
}
#endif // LTP_CLIENT_PROGRAMEDITBAR_H_