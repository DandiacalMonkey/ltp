#ifndef LTP_BASE_GLOBALS_H_
#define LTP_BASE_GLOBALS_H_

namespace ltp
{
	namespace base
	{
		//模式枚举
		enum Mode
		{
			CODELESS,
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
			COORDINATE = 33614,//工件坐标系
			WORKPIECE_COORDINATE = 30118,//工件坐标基地址
			MACHINING_REMAIN = 30122,//加工余量
			MECHANICAL_COORDINATE = 30128,//机械坐标基地址
			MOTOR_LOAD = 30132,//马达负载
			FEED_SPEED = 31064,//进给速度
			FEED_RATE = 31054,//进给倍率
			SYSTEM_MODE = 50000,//模式
			FEED_AXIS_VALID = 74100,//轴有效
			FEED_AXIS_CHARACTER = 74113,//轴对应的字符
			CHANNEL_INTERVAL = 100000//通道1通道2数据间隔
		};
		//报警等级
		enum ErrorLevel
		{
			NO_ERROR,
			WARNNING,
			ERROR
		};
	}
}

#endif // LTP_BASE_GLOBALS_H_