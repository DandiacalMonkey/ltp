#ifndef LTP_BASE_MODULEBUTTONS_H_
#define LTP_BASE_MODULEBUTTONS_H_

#include <QtGui/QPushButton>

namespace ltp
{
	namespace base
	{
		namespace ModuleButtons
		{
			class ReturnButton : public QPushButton
			{
				Q_OBJECT
		 
			public:
				ReturnButton(QWidget *parent = 0);
				~ReturnButton(); 
			};

			class CommandButton : public QPushButton
			{
				Q_OBJECT

			public:
				CommandButton(QWidget *parent = 0);
				~CommandButton(); 
			};
		}
	}
}


#endif // LTP_BASE_MODULEBUTTONS_H_