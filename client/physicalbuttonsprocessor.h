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
			bool isPhysicalButtonsProcessor(QKeyEvent* event) const;
			void getMapFunction(QKeyEvent* event);

		signals:
			// 左边
			void returnButtonClicked();
			void leftButtonClicked(int key);
			// 下边
			void bottomButtonModeClicked(int key);
			void bottomButtonRateClicked(int key);
			// 右边
			void rightButtonPlus(int key);
			void rightButtonMinus(int key);
			void rightButtonStart();
			void rightButtonStop();
			void rightButtonReset();

		private:
			PhysicalButtonsProcessor(QObject *parent = nullptr);
			~PhysicalButtonsProcessor();
			// 按钮键值和相关事件的映射
			std::unordered_map<int, std::function<void()>> keyValueSignalMap_;
			void initKeyMap();
		};
	}
}
#endif // LTP_CLIENT_PHYSICALBUTTONSPROCESSOR_H_
