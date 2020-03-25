#ifndef LTP_CLIENT_TEACHCOMMANDLINE_H_
#define LTP_CLIENT_TEACHCOMMANDLINE_H_

#include "teachcommand.h"

namespace ltp
{
	namespace client
	{
		class TeachCommandLine : public TeachCommand
		{
		public:
			TeachCommandLine(const QString& command, const QString& schematicDiagramPath);
			virtual bool checkPoint() throw (RepeatPointException);
			virtual bool hasPreviousPoint() const;
			virtual QString getCommand() const;
			virtual bool canChangeMode() const;
			virtual void reset();

		private:
			//线段指令中的指令，如G00、G01
			const QString kCommand_;
		};
	}
}

#endif // !LTP_CLIENT_TEACHCOMMANDLINE_H_
