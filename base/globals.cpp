#include "globals.h"
#include <cassert>
#include <algorithm>
#include <iterator>

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
		std::vector<char> axesEnumToAxesChar(const std::vector<base::Axis>& axesEnum)
		{
			std::vector<char> result;
			std::transform(axesEnum.begin(), axesEnum.end(), std::back_inserter(result), axisEnumToAxisChar);
			return std::move(result);
		}
		Axis axisCharToAxisEnum(char axisChar)
		{
			switch (axisChar)
			{
			case 'X':
				return base::X_AXIS;
			case 'Y':
				return base::Y_AXIS;
			case 'Z':
				return base::Z_AXIS;
			case 'A':
				return base::A_AXIS;
			case 'B':
				return base::B_AXIS;
			case 'C':
				return base::C_AXIS;
			case 'U':
				return base::U_AXIS;
			case 'V':
				return base::V_AXIS;
			case 'W':
				return base::W_AXIS;
			default:
				assert(false);
				return base::X_AXIS;
			}
		}
		std::vector<base::Axis> axesCharToAxesEnum(const std::vector<char>& axesChar)
		{
			std::vector<base::Axis> result;
			std::transform(axesChar.begin(), axesChar.end(), std::back_inserter(result), axisCharToAxisEnum);
			return std::move(result);
		}
		char axisEnumToArcChar(Axis axisEnum)
		{
			static char axesChar[] = { 'I', 'J', 'K', 'L', 'P', 'Q', 'E', 'L' };
			assert(axisEnum < sizeof(axesChar));
			return axesChar[axisEnum];
		}
	}
}