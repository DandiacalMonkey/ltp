#include "pushbutton.h"

using ltp::base::PushButton;


PushButton::PushButton(QWidget *parent)
	: QPushButton(parent)
{
	this->setStyleSheet("QPushButton{background:#F5F5F5; font:14px SIMHEI; border-color:#D2D2D2; border-width:1px; border-style:solid; padding: 5px 10px 5px 10px;} \
						QPushButton:checked{background:#0064C8; color:white;} \
						QPushButton:hover{background:#0064C8; color:white;} \
						QPushButton:!enabled{background:#F5F5F5; color:#BEBEBE;}");
	
}

PushButton::~PushButton()
{
	
}



