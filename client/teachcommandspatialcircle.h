#ifndef LTP_CLIENT_TEACHCOMMANDPLANARCIRCLE_H_
#define LTP_CLIENT_TEACHCOMMANDPLANARCIRCLE_H_
#include "teachcommandspatialarc.h"

namespace ltp
{
	namespace client
	{
		class TeachCommandSpatialCircle : public TeachCommandSpatialArc
		{
		public:
			//整圆示教不允许旋转轴变化
			class rotate : public TeachCommandException
			{
			public:
				virtual QString hint() const
				{
					return QObject::tr("旋转坐标发生了变化，无法示教空间整圆");
				}
			};
			virtual bool checkPoint() throw (RepeatPointException, PointCollinear, PointCollinear);
			virtual QString getCommand() const;
		};
	}
}


#endif // !LTP_CLIENT_TEACHCOMMANDPLANARCIRCLE_H_