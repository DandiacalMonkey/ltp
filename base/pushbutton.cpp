#include "pushbutton.h"

using ltp::base::PushButton;
using ltp::base::DialogButton;

PushButton::PushButton(QWidget *parent)
	: QPushButton(parent)
{
	this->setStyleSheet("QPushButton{background:#F5F5F5; font:14px SIMHEI; border-color:#D2D2D2; border-width:1px; border-style:solid; padding: 5px 10px 5px 10px;} \
						QPushButton:checked{background:#0064C8; color:white;} \
						QPushButton:pressed{background:#E1EBFF; border:1px solid #CDE1F5;} \
						QPushButton:!enabled{background:#F5F5F5; color:#BEBEBE;}");	
}

PushButton::~PushButton()
{
	
}

DialogButton::DialogButton(QWidget *parent)
	: QPushButton(parent)
{
	this->setStyleSheet("QPushButton{background:#E1E1E1; font:14px SIMHEI; border-color:#D2D2D2; border-width:1px; border-style:solid; padding: 5px 10px 5px 10px;} \
						QPushButton:pressed{background:#E1EBFF; border:1px solid #CDE1F5;} \
						QPushButton:!enabled{background:#F5F5F5; border:1px solid #D2D2D2;}");
}

DialogButton::~DialogButton()
{

}

