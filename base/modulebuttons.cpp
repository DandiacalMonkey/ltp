#include "modulebuttons.h"

using ltp::base::ModuleButtons::CommandButton;
using ltp::base::ModuleButtons::ReturnButton;

ReturnButton::ReturnButton(QWidget *parent)
	: QPushButton(parent)
{
	this->setStyleSheet("QPushButton{background:transparent; border-image:url(:/LtpClient/image/Back_rest.png)0 25 0 0;} \
						QPushButton:checked{background:#0064C8; border-image:url(:/LtpClient/image/Back_pressed.png)0 25 0 0;} \
						QPushButton:hover{background:#0064C8; border-image:url(:/LtpClient/image/Back_pressed.png)0 25 0 0;}");
	
}

ReturnButton::~ReturnButton()
{
	
}


CommandButton::CommandButton(QWidget *parent)
	: QPushButton(parent)
{
	this->setCheckable(true);
	this->setStyleSheet("QPushButton{background:transparent; border:0px; font:14px SIMHEI;} \
						 QPushButton:checked{background:#0064C8; color:white;} \
					     QPushButton:hover{background:#0064C8; color:white;}"); 
}

CommandButton::~CommandButton()
{

}


