#ifndef LTP_BASE_KEYBOARDDIALOG_H
#define LTP_BASE_KEYBOARDDIALOG_H

#include <QtGui/QDialog>
#include <QButtonGroup>
#include "ui_keyboarddialog.h"
#include "base/singleton.hpp"

namespace ltp
{
	namespace base
	{
		enum KeyBoardButtons
		{
			KEY_1,
			KEY_2,
			KEY_3,
			KEY_4,
			KEY_5,
			KEY_6,
			KEY_7,
			KEY_8,
			KEY_9,
			KEY_0,
			KEY_MINUS,
			KEY_EQUAL,
			KEY_Q,
			KEY_W,
			KEY_E,
			KEY_R,
			KEY_T,
			KEY_Y,
			KEY_U,
			KEY_I,
			KEY_O,
			KEY_P,
			KEY_DELETE,
			KEY_A,
			KEY_S,
			KEY_D,
			KEY_F,
			KEY_G,
			KEY_H,
			KEY_J,
			KEY_K,
			KEY_L,
			KEY_RETURN,
			KEY_SHIFT,
			KEY_Z,
			KEY_X,
			KEY_C,
			KEY_V,
			KEY_B,
			KEY_N,
			KEY_M,
			KEY_LEFTBRACKET,
			KEY_RIGHTBRACKET,
			KEY_RIGHTSLASH,
			KEY_SEMICOLON,
			KEY_QUOTATION,
			KEY_SPACE,
			KEY_COMMA,
			KEY_PERIOD,
			KEY_LEFTSLASH
		};

		class KeyBoardDialog : public QDialog
		{
		Q_OBJECT
			friend KeyBoardDialog& getInstance<KeyBoardDialog>();		
		public:
			//void setTitleName(QString &nameStr);
		private:
			Ui::KeyBoardDialogClass ui;
			QButtonGroup* buttonGroup_;
			QString currentString_;			// 当前输入内容

		private:
			KeyBoardDialog(QWidget* parent = 0);
			~KeyBoardDialog();
			void initKey();

		private slots:
			void keyButtonClicked(int);
			//void closeKeyboardDialog();
			//void confirmButonClicked();

		signals:
			//void insertString(QString value);
		//	void closeKeyboard();
			void keyboardEvent(QKeyEvent*);
		};
	}
}

#endif // LTP_BASE_KEYBOARDDIALOG_H
