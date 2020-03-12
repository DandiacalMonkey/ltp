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
	keyValueSignalMap_.insert(std::make_pair(Qt::Key_1, [this](){emit returnButtonClicked();}));
	keyValueSignalMap_.insert(std::make_pair(Qt::Key_2, [this](){emit leftButtonClicked(base::LEFTBUTTON1);}));
	keyValueSignalMap_.insert(std::make_pair(Qt::Key_9, [this](){emit leftButtonClicked(base::LEFTBUTTON2);}));
	keyValueSignalMap_.insert(std::make_pair(Qt::Key_0, [this](){emit leftButtonClicked(base::LEFTBUTTON3);}));
	keyValueSignalMap_.insert(std::make_pair(Qt::Key_Z, [this](){emit leftButtonClicked(base::LEFTBUTTON4);}));
	keyValueSignalMap_.insert(std::make_pair(Qt::Key_Comma, [this](){emit leftButtonClicked(base::LEFTBUTTON5);}));
	keyValueSignalMap_.insert(std::make_pair(Qt::Key_Slash, [this](){emit leftButtonClicked(base::LEFTBUTTON6);}));
	keyValueSignalMap_.insert(std::make_pair(Qt::Key_A, [this](){emit rightButtonStop();}));
	keyValueSignalMap_.insert(std::make_pair(Qt::Key_B, [this](){emit rightButtonStart();}));
	keyValueSignalMap_.insert(std::make_pair(Qt::Key_C, [this](){emit rightButtonMinus(base::RIGHTBUTTON1);}));
	keyValueSignalMap_.insert(std::make_pair(Qt::Key_D, [this](){emit rightButtonPlus(base::RIGHTBUTTON1);}));
	keyValueSignalMap_.insert(std::make_pair(Qt::Key_E, [this](){emit rightButtonMinus(base::RIGHTBUTTON2);}));
	keyValueSignalMap_.insert(std::make_pair(Qt::Key_F, [this](){emit rightButtonPlus(base::RIGHTBUTTON2);}));
	keyValueSignalMap_.insert(std::make_pair(Qt::Key_G, [this](){emit rightButtonMinus(base::RIGHTBUTTON3);}));
	keyValueSignalMap_.insert(std::make_pair(Qt::Key_H, [this](){emit rightButtonPlus(base::RIGHTBUTTON3);}));
	keyValueSignalMap_.insert(std::make_pair(Qt::Key_I, [this](){emit rightButtonMinus(base::RIGHTBUTTON4);}));
	keyValueSignalMap_.insert(std::make_pair(Qt::Key_J, [this](){emit rightButtonPlus(base::RIGHTBUTTON4);}));
	keyValueSignalMap_.insert(std::make_pair(Qt::Key_K, [this](){emit rightButtonMinus(base::RIGHTBUTTON5);}));
	keyValueSignalMap_.insert(std::make_pair(Qt::Key_L, [this](){emit rightButtonPlus(base::RIGHTBUTTON5);}));
	keyValueSignalMap_.insert(std::make_pair(Qt::Key_M, [this](){emit rightButtonMinus(base::RIGHTBUTTON6);}));
	keyValueSignalMap_.insert(std::make_pair(Qt::Key_N, [this](){emit rightButtonPlus(base::RIGHTBUTTON6);}));
	keyValueSignalMap_.insert(std::make_pair(Qt::Key_O, [this](){emit rightButtonReset();}));
	keyValueSignalMap_.insert(std::make_pair(Qt::Key_P, [this](){emit bottomButtonModeClicked(base::BOTTOMBUTTON1);}));
	keyValueSignalMap_.insert(std::make_pair(Qt::Key_Q, [this](){emit bottomButtonModeClicked(base::BOTTOMBUTTON2);}));
	keyValueSignalMap_.insert(std::make_pair(Qt::Key_R, [this](){emit bottomButtonModeClicked(base::BOTTOMBUTTON3);}));
	keyValueSignalMap_.insert(std::make_pair(Qt::Key_S, [this](){emit bottomButtonModeClicked(base::BOTTOMBUTTON4);}));		// BOTTOMBUTTON4，5暂时未用
	keyValueSignalMap_.insert(std::make_pair(Qt::Key_T, [this](){emit bottomButtonModeClicked(base::BOTTOMBUTTON5);}));
	keyValueSignalMap_.insert(std::make_pair(Qt::Key_U, [this](){emit bottomButtonRateClicked(base::BOTTOMBUTTON6);}));
	keyValueSignalMap_.insert(std::make_pair(Qt::Key_V, [this](){emit bottomButtonRateClicked(base::BOTTOMBUTTON7);}));
	keyValueSignalMap_.insert(std::make_pair(Qt::Key_W, [this](){emit bottomButtonRateClicked(base::BOTTOMBUTTON8);}));
	keyValueSignalMap_.insert(std::make_pair(Qt::Key_X, [this](){emit bottomButtonRateClicked(base::BOTTOMBUTTON9);}));
}

bool PhysicalButtonsProcessor::isPhysicalButtonsProcessor(QKeyEvent* event) const
{
	// 检测输入键值是否为外设键值
	if (event->modifiers() == Qt::ControlModifier && 
		keyValueSignalMap_.find(event->key()) != keyValueSignalMap_.end())
	{
		return true;
	}
	return false;
}

void PhysicalButtonsProcessor::getMapFunction(QKeyEvent* event)
{
	int key = event->key();							// 输入键值
	auto element = keyValueSignalMap_.find(key);	// 查询输入键值对应的外设键值
	if (element != keyValueSignalMap_.end())		// 查询到外设键值
	{
		auto function = element->second;
		function();									// 执行对应函数
	}
}