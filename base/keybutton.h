#ifndef LTP_BASE_KEYBUTTON_H_
#define LTP_BASE_KEYBUTTON_H_

#include <QtGui/QPushButton>
#include <QLabel>

namespace ltp
{
	namespace base
	{
		class KeyButton : public QPushButton
		{
			Q_OBJECT
		 
		public:
			KeyButton(QWidget *parent = 0);
			~KeyButton();

		};

		class KeyFunctionButton : public QPushButton
		{
			Q_OBJECT

		public:
			KeyFunctionButton(QWidget *parent = 0);
			~KeyFunctionButton(); 
		};

		class ReturnButton : public QPushButton
		{
			Q_OBJECT

		public:
			ReturnButton(QWidget *parent = 0);
			~ReturnButton(); 
		};

		class DeleteButton : public QPushButton
		{
			Q_OBJECT

		public:
			DeleteButton(QWidget *parent = 0);
			~DeleteButton(); 
		};

		class ConfirmButton : public QPushButton
		{
			Q_OBJECT

		public:
			ConfirmButton(QWidget *parent = 0);
			~ConfirmButton(); 
		};
	}
}


#endif // LTP_BASE_KEYBUTTON_H_