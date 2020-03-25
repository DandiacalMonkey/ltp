#ifndef LTP_BASE_GLOBALS_H_
#define LTP_BASE_GLOBALS_H_

#include <functional>

namespace ltp
{
	namespace base
	{
		// 外设按键枚举
		enum BUTTONS
		{
			LEFTRETURNBUTTON,
			LEFTBUTTON1,
			LEFTBUTTON2,
			LEFTBUTTON3,
			LEFTBUTTON4,
			LEFTBUTTON5,
			LEFTBUTTON6,
			RIGHTBUTTON1,
			RIGHTBUTTON2,
			RIGHTBUTTON3,
			RIGHTBUTTON4,
			RIGHTBUTTON5,
			RIGHTBUTTON6,
			RIGHTBUTTONSTOP,
			RIGHTBUTTONSTART,
			RIGHTBUTTONRESET,
			BOTTOMBUTTON1,
			BOTTOMBUTTON2,
			BOTTOMBUTTON3,
			BOTTOMBUTTON4,
			BOTTOMBUTTON5,
			BOTTOMBUTTON6,
			BOTTOMBUTTON7,
			BOTTOMBUTTON8,
			BOTTOMBUTTON9
		};

		//模式枚举
		enum Mode
		{
			CODELESS = 1,
			MEMORY,
			REMOTE,
			HANDLE,
			JOG,
			HOME,
			DRNC,
			MDI
		};
		//轴相关数据存储下标
		enum Axis
		{
			X_AXIS,
			Y_AXIS,
			Z_AXIS,
			A_AXIS,
			B_AXIS,
			C_AXIS,
			U_AXIS,
			V_AXIS,
			W_AXIS,
			AXIS_COUNT = 9,
			AXIS_MAX = 16
		};
		//加工状态
		enum MachiningState
		{
			READY,
			BUSY,
			HOLD,
			STOP
		};
		//坐标类型（机械、绝对、增量）
		enum CoordinateType
		{
			MECHANICAL,
			ABSOLUTE,
			INBREMENTAL
		};
		//宏变量地址
		enum MacroAddress
		{
			AXIS_CONTROL_INTERVAL = 50,//轴控制数据的间隔
			AXIS_SETTING_INTERVAL = 100,//轴设定数据的间隔
			WORKPIECE_COORDINATE = 30118,//工件坐标基地址
			MACHINING_REMAIN = 30122,//加工余量
			MECHANICAL_COORDINATE = 30128,//机械坐标基地址
			MOTOR_LOAD = 30132,//马达负载
			TEACH_POSITION = 30142,//示教使用坐标
			PROGRAM_NUMBER = 33500,//程序号
			CURRENT_PROGRAM_LINE_NUMBER = 33501,//当前程序行号
			FEED_SPEED = 33563,//进给速度
			FEED_RATE = 33554,//进给倍率
			HANDWHEEL_OVERRIDE = 33517,//手轮倍率
			SPINDLE_OVERRIDE = 33518,//主轴倍率
			JOG_OVERRIDE = 33520,//jog倍率
			JOG_STEPPING_OVERRIDE = 33537,//jog步进倍率
			RAPID_OVERRIDE = 33555,//快速定位倍率
			COORDINATE = 33614,//工件坐标系
			TEACH_MODE = 34641,//示教编程模式，有刀尖坐标和工件坐标
			SYSTEM_MODE = 50000,//模式
			FEED_AXIS_VALID = 74100,//轴有效
			AXIS_ADDRESS = 74112,//轴地址
			FEED_AXIS_CHARACTER = 74113,//轴对应的字符
			CHANNEL_INTERVAL = 100000//通道1通道2数据间隔
		};
		//报警等级
		enum ErrorLevel
		{
			NO_ERROR,
			WARNNING,
			ERROR,
			DISCONNECTED
		};
		//轴枚举转换成轴字符
		char axisEnumToAxisChar(Axis axisEnum);
	}
}

namespace std 
{
    template <>
    struct hash<ltp::base::Axis> 
	{
        size_t operator ()(ltp::base::Axis value) const 
		{
            return static_cast<size_t>(value);
        }
    };
}

#endif // LTP_BASE_GLOBALS_H_