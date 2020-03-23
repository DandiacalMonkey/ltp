#ifndef LTP_CLIENT_TEACHCOMMANDLINE_H_
#define LTP_CLIENT_TEACHCOMMANDLINE_H_

#include "teachcommand.h"
#include "base/systemvariables.hpp"
#include "remotevariables.hpp"

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
			virtual void reset();

		private:
			//线段指令中的指令，如G00、G01
			const QString kCommand_;
			//用于获取坐标
			base::SystemVariables<RemoteVariables>& systemVariables_;
		};
	}
}

#endif // !LTP_CLIENT_TEACHCOMMANDLINE_H_
