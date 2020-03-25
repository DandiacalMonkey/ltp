﻿#include "teachcommand.h"

namespace ltp
{
	namespace client
	{
		class TeachCommandG114 : public TeachCommand
		{
		public:
			TeachCommandG114();
			virtual bool checkPoint() throw (RepeatPointException);
			virtual bool hasPreviousPoint() const;
			virtual QString getCommand() const;
			virtual bool canChangeMode() const;
			virtual void reset();
		};
	}
}


