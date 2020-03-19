#include "keybutton.h"
#include <QGraphicsDropShadowEffect>

using ltp::base::KeyButton;
using ltp::base::KeyFunctionButton;
using ltp::base::ReturnButton;
using ltp::base::DeleteButton;
using ltp::base::ConfirmButton;

// 普通虚拟键盘按钮
KeyButton::KeyButton(QWidget *parent)
	: QPushButton(parent)
{
	// 样式设置
	this->setStyleSheet("QPushButton{background:#FFFFFF; font:20px Arial; border-radius:5px;} \
						QPushButton:pressed{background:#0080FF; color:white;}");

	// 阴影设置
	QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
	shadow_effect->setOffset(0, 1);
	shadow_effect->setColor(QColor(160, 160, 160));
	shadow_effect->setBlurRadius(0);
	this->setGraphicsEffect(shadow_effect);
}

KeyButton::~KeyButton()
{

}

// 功能虚拟按键
KeyFunctionButton::KeyFunctionButton(QWidget *parent)
	: QPushButton(parent)
{
	// 样式设置
	this->setStyleSheet("QPushButton{background:#E6E6E6; font:20px Arial; border-radius:5px;} \
						 QPushButton:pressed{background:#0080FF; color:white;} \
						 QPushButton:checked{background:#0064C8; color:white;}");
	// 阴影设置
	QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
	shadow_effect->setOffset(0, 1);
	shadow_effect->setColor(QColor(160, 160, 160));
	shadow_effect->setBlurRadius(0);
	this->setGraphicsEffect(shadow_effect);
}

KeyFunctionButton::~KeyFunctionButton()
{

}

// 回车键
ReturnButton::ReturnButton(QWidget *parent)
	: QPushButton(parent)
{
	// 样式设置
	this->setStyleSheet("QPushButton{background:#E6E6E6; font:20px Arial; border-radius:5px; background-image:url(:/LtpClient/image/enter.png); background-repeat:no-repeat; background-position:center;} \
						QPushButton:pressed{background:#0080FF; color:white; background-image:url(:/LtpClient/image/enter_pressed.png); background-repeat:no-repeat; background-position:center;} ");
	// 阴影设置
	QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
	shadow_effect->setOffset(0, 1);
	shadow_effect->setColor(QColor(160, 160, 160));
	shadow_effect->setBlurRadius(0);
	this->setGraphicsEffect(shadow_effect);
}

ReturnButton::~ReturnButton()
{

}

// backspace按键
DeleteButton::DeleteButton(QWidget *parent)
	: QPushButton(parent)
{
	// 样式设置
	this->setStyleSheet("QPushButton{background:#E6E6E6; font:20px Arial; border-radius:5px; background-image:url(:/LtpClient/image/backspace.png); background-repeat:no-repeat; background-position:center;} \
						QPushButton:pressed{background:#0080FF; color:white;background-image:url(:/LtpClient/image/backspace_pressed.png); background-repeat:no-repeat; background-position:center;} ");
	// 阴影设置
	QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
	shadow_effect->setOffset(0, 1);
	shadow_effect->setColor(QColor(160, 160, 160));
	shadow_effect->setBlurRadius(0);
	this->setGraphicsEffect(shadow_effect);
}

DeleteButton::~DeleteButton()
{

}

// 确认键
ConfirmButton::ConfirmButton(QWidget *parent)
	: QPushButton(parent)
{
	// 样式设置
	this->setStyleSheet("QPushButton{background:#E6E6E6; font:16px SIMHEI; border-radius:5px;} \
						QPushButton:pressed{background:#0080FF; color:white;} ");
	// 阴影设置
	QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
	shadow_effect->setOffset(0, 1);
	shadow_effect->setColor(QColor(160, 160, 160));
	shadow_effect->setBlurRadius(0);
	this->setGraphicsEffect(shadow_effect);
}

ConfirmButton::~ConfirmButton()
{

}

