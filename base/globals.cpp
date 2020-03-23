#include "globals.h"
#include <cassert>

namespace ltp
{
	namespace base
	{
		char axisEnumToAxisChar(Axis axisEnum)
		{
			static char axesChar[] = { 'X', 'Y', 'Z', 'A', 'B', 'C', 'U', 'V', 'W' };
			assert(axisEnum < sizeof(axesChar));
			return axesChar[axisEnum];
		}
	}
}