#ifndef LTP_CLIENT_TEACHCOMMANDPOINT_H_
#define LTP_CLIENT_TEACHCOMMANDPOINT_H_

#include "teachcommand.h"

namespace ltp
{
	namespace client
	{
		class TeachCommandPoint : public TeachCommand
		{
		public:
			TeachCommandPoint();
			virtual bool checkPoint();
			virtual bool hasPreviousPoint() const;
			virtual QString getCommand() const;
			virtual bool canChangeMode() const;
			virtual void reset();
		};
	}
}

#endif // !LTP_CLIENT_TEACHCOMMANDPOINT_H_
