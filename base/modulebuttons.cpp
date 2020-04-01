#include "modulebuttons.h"

using ltp::base::ModuleButtons::CommandButton;
using ltp::base::ModuleButtons::ReturnButton;

ReturnButton::ReturnButton(QWidget *parent)
	: QPushButton(parent)
{
	this->setStyleSheet("QPushButton{background:transparent; border-image:url(:/LtpClient/image/Back_rest.png);} \
						QPushButton:checked{background:#0064C8; border-image:url(:/LtpClient/image/Back_pressed.png);} \
						QPushButton:pressed{background:#0080FF; border-image:url(:/LtpClient/image/Back_pressed.png);} \
						QPushButton:!enabled{background:transparent; border-image:none;}");
	
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
					     QPushButton:pressed{background:#0080FF; color:white;} \
						 QPushButton:!enabled{background:transparent; color:#BEBEBE;}"); 
}

CommandButton::~CommandButton()
{

}


