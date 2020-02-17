#ifndef LTP_BASE_TEXTEDIT_H_
#define LTP_BASE_TEXTEDIT_H_

#include <QtGui/QWidget>
#include "ui_textedit.h"

namespace ltp
{
	namespace base
	{
		class TextEdit : public QWidget
		{
			Q_OBJECT
		 
		public:
			TextEdit(QWidget *parent = 0);
			~TextEdit();  

		private:
			Ui::TextEditClass ui;

		};
	}
}


#endif // LTP_BASE_TEXTEDIT_H_