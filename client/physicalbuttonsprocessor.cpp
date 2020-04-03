#include "physicalbuttonsprocessor.h"
#include <utility>
#include "base/globals.h"

using ltp::client::PhysicalButtonsProcessor;
PhysicalButtonsProcessor::PhysicalButtonsProcessor(QObject *parent)
	: QObject(parent)
{
	initKeyMap();		// 初始化外设键值
}

PhysicalButtonsProcessor::~PhysicalButtonsProcessor()
{
}

void PhysicalButtonsProcessor::initKeyMap()
{
	// 插入键值和信号的对应关系
	keyPressValueSignalMap_.insert(std::make_pair(Qt::Key_1, [this](){emit returnButtonClicked();}));
	keyPressValueSignalMap_.insert(std::make_pair(Qt::Key_2, [this](){emit leftButtonClicked(base::LEFTBUTTON1);}));
	keyPressValueSignalMap_.insert(std::make_pair(Qt::Key_9, [this](){emit leftButtonClicked(base::LEFTBUTTON2);}));
	keyPressValueSignalMap_.insert(std::make_pair(Qt::Key_0, [this](){emit leftButtonClicked(base::LEFTBUTTON3);}));
	keyPressValueSignalMap_.insert(std::make_pair(Qt::Key_Z, [this](){emit leftButtonClicked(base::LEFTBUTTON4);}));
	keyPressValueSignalMap_.insert(std::make_pair(Qt::Key_Comma, [this](){emit leftButtonClicked(base::LEFTBUTTON5);}));
	keyPressValueSignalMap_.insert(std::make_pair(Qt::Key_Y, [this](){emit leftButtonClicked(base::LEFTBUTTON6);}));
	keyPressValueSignalMap_.insert(std::make_pair(Qt::Key_A, [this](){emit rightButtonStop();}));
	keyPressValueSignalMap_.insert(std::make_pair(Qt::Key_B, [this](){emit rightButtonStart();}));
	keyPressValueSignalMap_.insert(std::make_pair(Qt::Key_C, [this](){emit rightButtonMinusPress(base::RIGHTBUTTON1);}));
	keyPressValueSignalMap_.insert(std::make_pair(Qt::Key_D, [this](){emit rightButtonPlusPress(base::RIGHTBUTTON1);}));
	keyPressValueSignalMap_.insert(std::make_pair(Qt::Key_E, [this](){emit rightButtonMinusPress(base::RIGHTBUTTON2);}));
	keyPressValueSignalMap_.insert(std::make_pair(Qt::Key_F, [this](){emit rightButtonPlusPress(base::RIGHTBUTTON2);}));
	keyPressValueSignalMap_.insert(std::make_pair(Qt::Key_G, [this](){emit rightButtonMinusPress(base::RIGHTBUTTON3);}));
	keyPressValueSignalMap_.insert(std::make_pair(Qt::Key_H, [this](){emit rightButtonPlusPress(base::RIGHTBUTTON3);}));
	keyPressValueSignalMap_.insert(std::make_pair(Qt::Key_I, [this](){emit rightButtonMinusPress(base::RIGHTBUTTON4);}));
	keyPressValueSignalMap_.insert(std::make_pair(Qt::Key_J, [this](){emit rightButtonPlusPress(base::RIGHTBUTTON4);}));
	keyPressValueSignalMap_.insert(std::make_pair(Qt::Key_K, [this](){emit rightButtonMinusPress(base::RIGHTBUTTON5);}));
	keyPressValueSignalMap_.insert(std::make_pair(Qt::Key_L, [this](){emit rightButtonPlusPress(base::RIGHTBUTTON5);}));
	keyPressValueSignalMap_.insert(std::make_pair(Qt::Key_M, [this](){emit rightButtonMinusPress(base::RIGHTBUTTON6);}));
	keyPressValueSignalMap_.insert(std::make_pair(Qt::Key_N, [this](){emit rightButtonPlusPress(base::RIGHTBUTTON6);}));
	keyPressValueSignalMap_.insert(std::make_pair(Qt::Key_O, [this](){emit rightButtonReset();}));
	keyPressValueSignalMap_.insert(std::make_pair(Qt::Key_P, [this](){emit bottomButtonModeClicked(base::BOTTOMBUTTON1);}));
	keyPressValueSignalMap_.insert(std::make_pair(Qt::Key_Q, [this](){emit bottomButtonModeClicked(base::BOTTOMBUTTON2);}));
	keyPressValueSignalMap_.insert(std::make_pair(Qt::Key_R, [this](){emit bottomButtonModeClicked(base::BOTTOMBUTTON3);}));
	keyPressValueSignalMap_.insert(std::make_pair(Qt::Key_S, [this](){emit bottomButtonModeClicked(base::BOTTOMBUTTON4);}));		// BOTTOMBUTTON4，5暂时未用
	keyPressValueSignalMap_.insert(std::make_pair(Qt::Key_T, [this](){emit bottomButtonModeClicked(base::BOTTOMBUTTON5);}));
	keyPressValueSignalMap_.insert(std::make_pair(Qt::Key_U, [this](){emit bottomButtonRateClicked(base::BOTTOMBUTTON6);}));
	keyPressValueSignalMap_.insert(std::make_pair(Qt::Key_V, [this](){emit bottomButtonRateClicked(base::BOTTOMBUTTON7);}));
	keyPressValueSignalMap_.insert(std::make_pair(Qt::Key_W, [this](){emit bottomButtonRateClicked(base::BOTTOMBUTTON8);}));
	keyPressValueSignalMap_.insert(std::make_pair(Qt::Key_X, [this](){emit bottomButtonRateClicked(base::BOTTOMBUTTON9);}));

	// 插入键值和信号的对应关系
	keyRealeaseValueSignalMap_.insert(std::make_pair(Qt::Key_C, [this](){emit rightButtonMinusRealease(base::RIGHTBUTTON1);}));
	keyRealeaseValueSignalMap_.insert(std::make_pair(Qt::Key_D, [this](){emit rightButtonPlusRealease(base::RIGHTBUTTON1);}));
	keyRealeaseValueSignalMap_.insert(std::make_pair(Qt::Key_E, [this](){emit rightButtonMinusRealease(base::RIGHTBUTTON2);}));
	keyRealeaseValueSignalMap_.insert(std::make_pair(Qt::Key_F, [this](){emit rightButtonPlusRealease(base::RIGHTBUTTON2);}));
	keyRealeaseValueSignalMap_.insert(std::make_pair(Qt::Key_G, [this](){emit rightButtonMinusRealease(base::RIGHTBUTTON3);}));
	keyRealeaseValueSignalMap_.insert(std::make_pair(Qt::Key_H, [this](){emit rightButtonPlusRealease(base::RIGHTBUTTON3);}));
	keyRealeaseValueSignalMap_.insert(std::make_pair(Qt::Key_I, [this](){emit rightButtonMinusRealease(base::RIGHTBUTTON4);}));
	keyRealeaseValueSignalMap_.insert(std::make_pair(Qt::Key_J, [this](){emit rightButtonPlusRealease(base::RIGHTBUTTON4);}));
	keyRealeaseValueSignalMap_.insert(std::make_pair(Qt::Key_K, [this](){emit rightButtonMinusRealease(base::RIGHTBUTTON5);}));
	keyRealeaseValueSignalMap_.insert(std::make_pair(Qt::Key_L, [this](){emit rightButtonPlusRealease(base::RIGHTBUTTON5);}));
	keyRealeaseValueSignalMap_.insert(std::make_pair(Qt::Key_M, [this](){emit rightButtonMinusRealease(base::RIGHTBUTTON6);}));
	keyRealeaseValueSignalMap_.insert(std::make_pair(Qt::Key_N, [this](){emit rightButtonPlusRealease(base::RIGHTBUTTON6);}));
	keyRealeaseValueSignalMap_.insert(std::make_pair(Qt::Key_O, [this](){emit rightButtonResetRealease();}));
	keyRealeaseValueSignalMap_.insert(std::make_pair(Qt::Key_A, [this](){emit rightButtonStopRealease();}));
	keyRealeaseValueSignalMap_.insert(std::make_pair(Qt::Key_B, [this](){emit rightButtonStartRealease();}));
}

bool PhysicalButtonsProcessor::isPhysicalButtonsPressProcessor(QKeyEvent* event) const
{
	// 检测输入键值是否为外设键值
	if (event->modifiers() == Qt::ControlModifier && 
		keyPressValueSignalMap_.find(event->key()) != keyPressValueSignalMap_.end())
	{
		return true;
	}
	return false;
}

bool PhysicalButtonsProcessor::isPhysicalButtonsRealeaseProcessor(QKeyEvent* event) const
{
	// 检测输入键值是否为外设键值
	if (event->modifiers() == Qt::ControlModifier && 
		keyPressValueSignalMap_.find(event->key()) != keyPressValueSignalMap_.end())
	{
		return true;
	}
	return false;
}

void PhysicalButtonsProcessor::getMapPressFunction(QKeyEvent* event)
{
	int key = event->key();								// 输入键值
	auto element = keyPressValueSignalMap_.find(key);	// 查询输入键值对应的外设键值
	if (element != keyPressValueSignalMap_.end())		// 查询到外设键值
	{
		auto function = element->second;
		function();										// 执行对应函数
	}
}

void PhysicalButtonsProcessor::getMapRealeaseFunction(QKeyEvent* event)
{
	int key = event->key();									// 输入键值
	auto element = keyRealeaseValueSignalMap_.find(key);	// 查询输入键值对应的外设键值
	if (element != keyRealeaseValueSignalMap_.end())		// 查询到外设键值
	{
		auto function = element->second;
		function();											// 执行对应函数
	}
}