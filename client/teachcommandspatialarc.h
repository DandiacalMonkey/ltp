#ifndef LTP_CLIENT_TEACHCOMMANDSPATIALARC_H_
#define LTP_CLIENT_TEACHCOMMANDSPATIALARC_H_

#include "teachcommand.h"

namespace ltp
{
	namespace client
	{
		class TeachCommandSpatialArc : public TeachCommand
		{
		public:
			//圆弧记录点不能共线
			class PointCollinear : public TeachCommandException
			{
			public:
				virtual QString hint() const
				{
					return QObject::tr("三点共线，无法完成圆弧示教");
				}
			};
			TeachCommandSpatialArc();
			virtual bool checkPoint() throw (RepeatPointException, PointCollinear);
			virtual bool hasPreviousPoint() const;
			virtual QString getCommand() const;
			virtual bool canChangeMode() const;
			virtual void reset();
		};
	}
}

#endif // !LTP_CLIENT_TEACHCOMMANDSPATIALARC_H_
