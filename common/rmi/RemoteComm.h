#ifndef RMI_REMOTE_COMM_H_
#define RMI_REMOTE_COMM_H_

#ifdef _WIN32
#define DLL_DECLARE __declspec(dllexport)
#else
#define DLL_DECLARE
#endif

#define REMOTECOMM_VERSION "2.0.0.0"

/***  该库基本功能：与控制器端宏变量读写，FTP文件传输，远程打开控制器端程序（需要用户盘有要打开的文件）***/

/*
*描  述：创建TCP连接（）
*参  数：char* iP:控制器IP地址   
*返回值：int nHandle : 大于等于0: 成功  -1:失败
*/
extern "C" DLL_DECLARE int remote_new_connect(const char* iP);

/*
*描  述：关闭连接
*参  数：int nHandle
*返回值：无
*/
extern "C" DLL_DECLARE void remote_close(int nHandle);

/*
*描  述：读宏变量
*参  数：int nHandle:句柄 int nMacro：宏变量号
*返回值：宏变量值
*/
extern "C" DLL_DECLARE double remote_read_macro(int nHandle, int nMacro);

/*
*描  述：读宏变量
*参  数：int nHandle：句柄 int nMacro：宏变量号 double* val：读取的数据存放位置
*返回值：int  1：成功，0 :未建立连接，-2 连接失败， -3宏地址错误，-4服务器无返回。
*/
extern "C" DLL_DECLARE int remote_read_macro_p(int nHandle, int nMacro, double* val);

/*
*描  述：写宏变量
*参  数：int nHandle：句柄  int nMacro：宏变量号  double val：要写入宏变量的值
*返回值：int：1：成功  <=0 :写入失败
*/
extern "C" DLL_DECLARE int remote_write_macro(int nHandle, int nMacro, double val);

/*
*描  述：远程打开控制器端指定文件
*参  数：nHandle:句柄  nChannel:当前通道号（通道一：1 通道二：2） chFileName:要远程打开文件的文件名
*返回值：0：打开成功  -1：打开失败
*/
extern "C" DLL_DECLARE int remote_open_file(int nHandle, int nChannel, const char* chFileName);

/*
*描  述：获取控制器端打开的当前文件的文件名
*参  数：nHandle:句柄  chFileName:存储获取到的文件名
*返回值：0：成功  -1：失败
*/
extern "C" DLL_DECLARE int remote_get_open_file_name(int nHandle, char* chFileName);

/*
*描  述：获取控制器端打开的当前文件的md5
*参  数：nHandle:句柄  buf:存储获取到的md5
*返回值：0：成功  -1：失败
*/
extern "C" DLL_DECLARE int remote_get_exe_file_md5sum(int nHandle, int nPath, char *buf);

/*
*描  述：设定除ftp相关接口以外接口（宏变量读写等）的socket接收超时时间
*参  数：nHandle:句柄  nMillisecond:超时时间(ms)
*返回值：0：成功  -1：失败
*/
extern "C" DLL_DECLARE int remote_set_receive_timeout(int nHandle, int nMillisecond);

/*
*描  述：设定除ftp相关接口以外接口（宏变量读写等）的socket发送超时时间
*参  数：nHandle:句柄  nMillisecond:超时时间(ms)
*返回值：0：成功  -1：失败
*/
extern "C" DLL_DECLARE int remote_set_send_timeout(int nHandle, int nMillisecond);

/*
*描  述：获取PLC变量
*参  数：nHandle:句柄  nName:PLC变量对应的枚举值
*返回值：无符号PLC变量
*/
extern "C" DLL_DECLARE unsigned long remote_read_plc_variable(int nHandle, int nName);

/*
*描  述：获取PLC变量
*参  数：nHandle:句柄  nName:PLC变量对应的枚举值 val:储存变量
*返回值：0：成功  -1：失败
*/
extern "C" DLL_DECLARE int remote_read_plc_variable_p(int nHandle, int nName, unsigned long* val);

/*
*描  述：修改PLC变量
*参  数：nHandle:句柄  nName:PLC变量对应的枚举值 val:目标值
*返回值：0：成功  -1：失败
*/
extern "C" DLL_DECLARE int remote_write_plc_variable(int nHandle, int nName, unsigned long val);

/*
*描  述：远程执行NC指令
*参  数：nHandle:句柄  buf:存储需要执行的指令 nLength:buffer的大小
*返回值：0：成功  -1：失败
*/
extern "C" DLL_DECLARE int remote_run_string(int nHandle, const char *buf, int nLength);

/*
*描  述：取得当前文件的指定行号
*参  数：nHandle:句柄， nLine 行号，chLine 返回的行内容， nSize  chLine的buffer大小 
*返回值：int：0：成功  -1：获取失败
*/
extern "C" DLL_DECLARE int remote_get_file_line(int nHandle, int nLine, char* chLine, int size);

/*
*描  述：上传文件到控制器用户盘（该接口执行传输文件过程，需要一定时间，需要放到线程中去执行，否则会卡顿）
*参  数：nHandle:句柄  char* chFileName : 需要传输到控制器的文件名
*返回值：int：0：传输成功   -1：传输失败
*说明：	因为文件名包含大写字母，这个函数将被废弃
*/
extern "C" DLL_DECLARE int remote_upLoad_file(int nHandle, const char* chFileName);

/*
*描  述：上传文件到控制器用户盘（该接口执行传输文件过程，需要一定时间，需要放到线程中去执行，否则会卡顿）
*参  数：nHandle:句柄  
		char* chFileName : 需要传输到控制器的文件名
		int nPath：路径编号
					2 第二通道路径
					1001  NC1
					1002  NC2
					1003  NC3
					1004  NC4
					1005  NC5
					其他  第一通道路径
*返回值：int：0：传输成功   -1：传输失败
*说明  : 增加了路径选择
*/
extern "C" DLL_DECLARE int remote_upload_file(int nHandle, const char* chFileName, int nPath);

/*
*描  述：删除控制器用户盘上的文件
*参  数：nHandle:句柄  
		char* chFileName : 需要传输到控制器的文件名
		int nPath：路径编号
					2 第二通道路径
					1001  NC1
					1002  NC2
					1003  NC3
					1004  NC4
					1005  NC5
					其他  第一通道路径
*返回值：int：0：传输成功   -1：传输失败
*说明  : 增加了路径选择
*/
extern "C" DLL_DECLARE int remote_delete_file(int nHandle, const char* chFileName, int nPath);

/*
*描  述：文件传输进度
*参  数：nHandle:句柄
*返回值：int：返回当前文件传输进度  （范围： 0--100 ）  -1：获取失败
*/
extern "C" DLL_DECLARE int remote_get_process(int nHandle);

/*
*描  述：连接状态
*参  数：nHandle:句柄
*返回值：int：已连接返回：0  连接断开返回-1
*/
extern "C" DLL_DECLARE int remote_connect_status(int nHandle);

#endif // RMI_REMOTE_COMM_H_