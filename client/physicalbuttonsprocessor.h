#ifndef LTP_CLIENT_PHYSICALBUTTONSPROCESSOR_H_
#define LTP_CLIENT_PHYSICALBUTTONSPROCESSOR_H_

#include <QObject>
#include <QKeyEvent>
#include <unordered_map>
#include <functional>
#include "base/singleton.hpp"

namespace ltp
{
	namespace client
	{
		class PhysicalButtonsProcessor : public QObject
		{
			Q_OBJECT
			friend PhysicalButtonsProcessor& base::getInstance<PhysicalButtonsProcessor>();

		public:	
			bool isPhysicalButtonsPressProcessor(QKeyEvent* event) const;
			bool isPhysicalButtonsRealeaseProcessor(QKeyEvent* event) const;
			void getMapPressFunction(QKeyEvent* event);
			void getMapRealeaseFunction(QKeyEvent* event);

		signals:
			// 左边
			void returnButtonClicked();
			void leftButtonClicked(int key);
			// 下边
			void bottomButtonModeClicked(int key);
			void bottomButtonRateClicked(int key);
			// 右边
			void rightButtonPlusPress(int key);
			void rightButtonMinusPress(int key);
			void rightButtonPlusRealease(int key);
			void rightButtonMinusRealease(int key);
			void rightButtonStart();
			void rightButtonStop();
			void rightButtonReset();

		private:
			PhysicalButtonsProcessor(QObject *parent = nullptr);
			~PhysicalButtonsProcessor();
			// 按钮键值和相关事件的映射
			std::unordered_map<int, std::function<void()>> keyPressValueSignalMap_;
			std::unordered_map<int, std::function<void()>> keyRealeaseValueSignalMap_;
			void initKeyMap();
		};
	}
}
#endif // LTP_CLIENT_PHYSICALBUTTONSPROCESSOR_H_
