#include "keyboarddialog.h"
#include <QKeyEvent>
#include <QDebug>

using ltp::base::KeyBoardDialog;

KeyBoardDialog::KeyBoardDialog(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setFocusPolicy(Qt::NoFocus);
	setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);
	buttonGroup_ = new QButtonGroup(this);
	initKey();			// 初始化buttonGroup_
	connect(buttonGroup_, SIGNAL(buttonClicked(int)), this, SLOT(keyButtonClicked(int)));
//	connect(ui.titleWidget_, SIGNAL(signalClose()), this, SLOT(closeKeyboardDialog()));
//	connect(ui.confirmButton_, SIGNAL(clicked()), this, SLOT(confirmButonClicked()));
	move(0, 400);
}

KeyBoardDialog::~KeyBoardDialog()
{

}

void KeyBoardDialog::initKey()
{
	// 初始化buttonGroup_
	buttonGroup_->addButton(ui.keyButton1_, KEY_1);
	buttonGroup_->addButton(ui.keyButton2_, KEY_2);
	buttonGroup_->addButton(ui.keyButton3_, KEY_3);
	buttonGroup_->addButton(ui.keyButton4_, KEY_4);
	buttonGroup_->addButton(ui.keyButton5_, KEY_5);
	buttonGroup_->addButton(ui.keyButton6_, KEY_6);
	buttonGroup_->addButton(ui.keyButton7_, KEY_7);
	buttonGroup_->addButton(ui.keyButton8_, KEY_8);
	buttonGroup_->addButton(ui.keyButton9_, KEY_9);
	buttonGroup_->addButton(ui.keyButton0_, KEY_0);
	buttonGroup_->addButton(ui.keyButtonMinus_, KEY_MINUS);
	buttonGroup_->addButton(ui.keyButtonEqual_, KEY_EQUAL);
	buttonGroup_->addButton(ui.keyButtonQ_, KEY_Q);
	buttonGroup_->addButton(ui.keyButtonW_, KEY_W);
	buttonGroup_->addButton(ui.keyButtonE_, KEY_E);
	buttonGroup_->addButton(ui.keyButtonR_, KEY_R);
	buttonGroup_->addButton(ui.keyButtonT_, KEY_T);
	buttonGroup_->addButton(ui.keyButtonY_, KEY_Y);
	buttonGroup_->addButton(ui.keyButtonU_, KEY_U);
	buttonGroup_->addButton(ui.keyButtonI_, KEY_I);
	buttonGroup_->addButton(ui.keyButtonO_, KEY_O);
	buttonGroup_->addButton(ui.keyButtonP_, KEY_P);
	buttonGroup_->addButton(ui.keyButtonBackspace_, KEY_DELETE);
	buttonGroup_->addButton(ui.keyButtonA_, KEY_A);
	buttonGroup_->addButton(ui.keyButtonS_, KEY_S);
	buttonGroup_->addButton(ui.keyButtonD_, KEY_D);
	buttonGroup_->addButton(ui.keyButtonF_, KEY_F);
	buttonGroup_->addButton(ui.keyButtonG_, KEY_G);
	buttonGroup_->addButton(ui.keyButtonH_, KEY_H);
	buttonGroup_->addButton(ui.keyButtonJ_, KEY_J);
	buttonGroup_->addButton(ui.keyButtonK_, KEY_K);
	buttonGroup_->addButton(ui.keyButtonL_, KEY_L);
	buttonGroup_->addButton(ui.keyButtonEnter_, KEY_RETURN);
	//buttonGroup_->addButton(ui.keyButtonShift_, KEY_SHIFT);
	buttonGroup_->addButton(ui.keyButtonZ_, KEY_Z);
	buttonGroup_->addButton(ui.keyButtonX_, KEY_X);
	buttonGroup_->addButton(ui.keyButtonC_, KEY_C);
	buttonGroup_->addButton(ui.keyButtonV_, KEY_V);
	buttonGroup_->addButton(ui.keyButtonB_, KEY_B);
	buttonGroup_->addButton(ui.keyButtonN_, KEY_N);
	buttonGroup_->addButton(ui.keyButtonM_, KEY_M);
	buttonGroup_->addButton(ui.keyButtonLeftBracket_, KEY_LEFTBRACKET);
	buttonGroup_->addButton(ui.keyButtonRightBracket_, KEY_RIGHTBRACKET);
	buttonGroup_->addButton(ui.keyButtonRightSlash_, KEY_RIGHTSLASH);
	buttonGroup_->addButton(ui.keyButtonSemicolon_, KEY_SEMICOLON);
	buttonGroup_->addButton(ui.keyButtonQuotation_, KEY_QUOTATION);
	buttonGroup_->addButton(ui.keyButtonSpace_, KEY_SPACE);
	buttonGroup_->addButton(ui.keyButtonComma_, KEY_COMMA);
	buttonGroup_->addButton(ui.keyButtonPeriod_, KEY_PERIOD);
	buttonGroup_->addButton(ui.keyButtonLeftSlash_, KEY_LEFTSLASH);
	//ui.keyButtonShift_->setAutoExclusive(false);
}

//void KeyBoardDialog::setTitleName(QString &nameStr)
//{
//	ui.titleWidget_->setTitleName(nameStr);
//}

//void KeyBoardDialog::confirmButonClicked()
//{
//	emit insertString(ui.lineEdit_->text());
//	ui.lineEdit_->clear();
//}

void KeyBoardDialog::keyButtonClicked(int key)
{
	QKeyEvent *keyPressEvent = NULL;

	if (key == KEY_DELETE)		// 删除
	{
		keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Backspace, Qt::NoModifier);
	}
	else if (key == KEY_SPACE)	// 空格
	{
		keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Space, Qt::NoModifier, " ");
	}
	else if (key == KEY_RETURN)	// 回车 输入当前文字并移动至下一行
	{
		keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Enter, Qt::NoModifier);
	}
	else						// 其他字符按键
	{
		if (ui.keyButtonShift_->isChecked())		//shift按下
		{
			switch (key)
			{
			case KEY_0:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_ParenRight, Qt::NoModifier, ")");
				break;
			case KEY_1:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Exclam, Qt::NoModifier, "!");
				break;
			case KEY_2:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_At, Qt::NoModifier, "@");
				break;
			case KEY_3:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_NumberSign, Qt::NoModifier, "#");
				break;
			case KEY_4:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Dollar, Qt::NoModifier, "$");
				break;
			case KEY_5:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Percent, Qt::NoModifier, "%");
				break;
			case KEY_6:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_AsciiCircum, Qt::NoModifier, "^");
				break;
			case KEY_7:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Ampersand, Qt::NoModifier, "&");
				break;
			case KEY_8:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Asterisk, Qt::NoModifier, "*");
				break;
			case KEY_9:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_ParenLeft, Qt::NoModifier, "(");
				break;
			case KEY_MINUS:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Underscore, Qt::NoModifier, "_");
				break;
			case KEY_EQUAL:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Plus, Qt::NoModifier, "+");
				break;
			case KEY_Q:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Q, Qt::NoModifier, "Q");
				break;
			case KEY_W:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_W, Qt::NoModifier, "W");
				break;
			case KEY_E:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_E, Qt::NoModifier, "E");
				break;
			case KEY_R:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_R, Qt::NoModifier, "R");
				break;
			case KEY_T:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_T, Qt::NoModifier, "T");
				break;
			case KEY_Y:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Y, Qt::NoModifier, "Y");
				break;
			case KEY_U:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_U, Qt::NoModifier, "U");
				break;
			case KEY_I:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_I, Qt::NoModifier, "I");
				break;
			case KEY_O:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_O, Qt::NoModifier, "O");
				break;
			case KEY_P:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_P, Qt::NoModifier, "P");
				break;
			case KEY_A:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_A, Qt::NoModifier, "A");
				break;
			case KEY_S:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_S, Qt::NoModifier, "S");
				break;
			case KEY_D:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_D, Qt::NoModifier, "D");
				break;
			case KEY_F:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_F, Qt::NoModifier, "F");
				break;
			case KEY_G:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_G, Qt::NoModifier, "G");
				break;
			case KEY_H:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_H, Qt::NoModifier, "H");
				break;
			case KEY_J:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_J, Qt::NoModifier, "J");
				break;
			case KEY_K:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_K, Qt::NoModifier, "K");
				break;
			case KEY_L:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_L, Qt::NoModifier, "L");
				break;
			case KEY_Z:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Z, Qt::NoModifier, "Z");
				break;
			case KEY_X:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_X, Qt::NoModifier, "X");
				break;
			case KEY_C:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_C, Qt::NoModifier, "C");
				break;
			case KEY_V:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_V, Qt::NoModifier, "V");
				break;
			case KEY_B:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_B, Qt::NoModifier, "B");
				break;
			case KEY_N:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_N, Qt::NoModifier, "N");
				break;
			case KEY_M:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_M, Qt::NoModifier, "M");
				break;
			case KEY_LEFTBRACKET:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_BraceLeft, Qt::NoModifier, "{");
				break;
			case KEY_RIGHTBRACKET:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_BraceRight, Qt::NoModifier, "}");
				break;
			case KEY_RIGHTSLASH:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Bar, Qt::NoModifier, "|");
				break;
			case KEY_SEMICOLON:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Colon, Qt::NoModifier, ":");
				break;
			case KEY_QUOTATION:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_QuoteDbl, Qt::NoModifier, "\"");
				break;
			case KEY_COMMA:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Less, Qt::NoModifier, "<");
				break;
			case KEY_PERIOD:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Greater, Qt::NoModifier, ">");
				break;
			case KEY_LEFTSLASH:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Question, Qt::NoModifier, "?");
				break;
			}
		}
		else			// 未按下shift
		{
			switch (key)
			{
			case KEY_0:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_0, Qt::NoModifier, "0");
				break;
			case KEY_1:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_1, Qt::NoModifier, "1");
				break;
			case KEY_2:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_2, Qt::NoModifier, "2");
				break;
			case KEY_3:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_3, Qt::NoModifier, "3");
				break;
			case KEY_4:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_4, Qt::NoModifier, "4");
				break;
			case KEY_5:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_5, Qt::NoModifier, "5");
				break;
			case KEY_6:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_6, Qt::NoModifier, "6");
				break;
			case KEY_7:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_7, Qt::NoModifier, "7");
				break;
			case KEY_8:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_8, Qt::NoModifier, "8");
				break;
			case KEY_9:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_9, Qt::NoModifier, "9");
				break;
			case KEY_MINUS:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Minus, Qt::NoModifier, "-");
				break;
			case KEY_EQUAL:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Equal, Qt::NoModifier, "=");
				break;
			case KEY_Q:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Q, Qt::NoModifier, "q");
				break;
			case KEY_W:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_W, Qt::NoModifier, "w");
				break;
			case KEY_E:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_E, Qt::NoModifier, "e");
				break;
			case KEY_R:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_R, Qt::NoModifier, "r");
				break;
			case KEY_T:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_T, Qt::NoModifier, "t");
				break;
			case KEY_Y:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Y, Qt::NoModifier, "y");
				break;
			case KEY_U:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_U, Qt::NoModifier, "u");
				break;
			case KEY_I:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_I, Qt::NoModifier, "i");
				break;
			case KEY_O:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_O, Qt::NoModifier, "o");
				break;
			case KEY_P:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_P, Qt::NoModifier, "p");
				break;
			case KEY_A:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_A, Qt::NoModifier, "a");
				break;
			case KEY_S:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_S, Qt::NoModifier, "s");
				break;
			case KEY_D:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_D, Qt::NoModifier, "d");
				break;
			case KEY_F:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_F, Qt::NoModifier, "f");
				break;
			case KEY_G:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_G, Qt::NoModifier, "g");
				break;
			case KEY_H:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_H, Qt::NoModifier, "h");
				break;
			case KEY_J:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_J, Qt::NoModifier, "j");
				break;
			case KEY_K:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_K, Qt::NoModifier, "k");
				break;
			case KEY_L:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_L, Qt::NoModifier, "l");
				break;
			case KEY_Z:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Z, Qt::NoModifier, "z");
				break;
			case KEY_X:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_X, Qt::NoModifier, "x");
				break;
			case KEY_C:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_C, Qt::NoModifier, "c");
				break;
			case KEY_V:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_V, Qt::NoModifier, "v");
				break;
			case KEY_B:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_B, Qt::NoModifier, "bB");
				break;
			case KEY_N:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_N, Qt::NoModifier, "n");
				break;
			case KEY_M:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_M, Qt::NoModifier, "m");
				break;
			case KEY_LEFTBRACKET:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_BracketLeft, Qt::NoModifier, "[");
				break;
			case KEY_RIGHTBRACKET:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_BracketRight, Qt::NoModifier, "]");
				break;
			case KEY_RIGHTSLASH:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Backslash, Qt::NoModifier, "\\");
				break;
			case KEY_SEMICOLON:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Semicolon, Qt::NoModifier, ";");
				break;
			case KEY_QUOTATION:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Apostrophe, Qt::NoModifier, "'");
				break;
			case KEY_COMMA:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Comma, Qt::NoModifier, ",");
				break;
			case KEY_PERIOD:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Period, Qt::NoModifier, ".");
				break;
			case KEY_LEFTSLASH:
				keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Slash, Qt::NoModifier, "/");
				break;
			}
		}
	}

	// 发送虚拟键盘按下事件
	if (keyPressEvent != NULL)
	{
		QCoreApplication::postEvent(QApplication::focusWidget(), keyPressEvent);
	}
}

//void KeyBoardDialog::closeKeyboardDialog()
//{
//	ui.lineEdit_->setText("");
//	this->close();
//	emit closeKeyboard();
//}

