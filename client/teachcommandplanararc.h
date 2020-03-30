#ifndef LTP_CLIENT_TEACHCOMMANDPLANARARC_H_
#define LTP_CLIENT_TEACHCOMMANDPLANARARC_H_
#include "teachcommand.h"

namespace ltp
{
	namespace client
	{
		class TeachCommandPlanarArc : public TeachCommand
		{
		public:
			//平面圆弧记录点应在垂直于某一轴的平面之中
			class PlaneError : public TeachCommandException
			{
			public:
				virtual QString hint() const
				{
					return QObject::tr("无法选定加工平面，请确保示教点均位于XY,YZ,XZ三平面之一");
				}
			};
			//平面圆弧记录点不能共线
			class PointCollinear : public TeachCommandException
			{
			public:
				virtual QString hint() const
				{
					return QObject::tr("三点共线，无法完成圆弧示教");
				}
			};
			TeachCommandPlanarArc();
			virtual bool checkPoint() throw (RepeatPointException, PlaneError, PointCollinear);
			virtual bool hasPreviousPoint() const;
			virtual QString getCommand() const;
			virtual bool canChangeMode() const;
			virtual void reset();

		};
	}
}

#endif // !LTP_CLIENT_TEACHCOMMANDPLANARARC_H_
