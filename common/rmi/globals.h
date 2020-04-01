#ifndef RMI_GLOBALS_H_
#define RMI_GLOBALS_H_

namespace rmi
{
	/* 定义PLC只写变量名 */
	enum PlcWriteOnlyVariableName
	{
		G_CHAN1,
		G_CHAN2,
		G_HALTSYS,
		G_OT2,
		G_AUTOHW,
		G_JOGMODE,
		G_SELSP,
		G_SELSP2,
		G_SELSP3,
		G_SELSP4,

		G_HWAXIS,
		G_JOVRD,
		G_JINC_OVRD,
		G_ROVRD,
		G_FOVRD,
		G_SOVRD,
		G_HWOVRD,
		G_HWAXIS2,

		DIS_CYCLESTART,
		DIS_JOG,
		DIS_HANDLE,

		G_SINGLE,
		G_OPSTOP,
		G_BLKSKIP,
		G_DRYRUN,
		G_CYCLESTART,
		G_FEEDHOLD,
		G_PROGSTOP,
		G_RESET,
		G_MPGTRACE,
		G_FRESET,
		G_WAXIS,
		G_MODE,
		G_AXIS,
		G_JOGPLUS,
		G_JOGMINUS,
		G_JMPLUS,
		G_JMMINUS,

		G_JMPLUS2,
		G_JMMINUS2
	};

	//定义PLC只读变量名
	enum PlcReadOnlyVariableName
	{
		F_CHAN1,
		F_CHAN2,
		F_SYSREADY,
		F_EMGSTOP,
		F_PWSTS,
		F_OT2,
		F_AUTOHW,
		F_JOGMODE,
		F_MPG2,
		F_HWAXIS,
		F_JOVRD,
		F_JINC_OVRD,
		F_ROVRD,
		F_FOVRD,
		F_SOVRD,
		F_HWOVRD,
		F_HWAXIS2,
		F_FATALERR,
		F_CIERR,
		F_WARN,
		F_SELSP,
		F_SELSP2,
		F_SELSP3,
		F_SELSP4,
		F_SELSP5,
		F_SELSP6,
		F_SELSP7,
		F_SELSP8,

		F_SINGLE,
		F_OPSTOP,
		F_BLKSKIP,
		F_DRYRUN,
		F_MPGTRACE,
		F_WAXIS,
		F_MODE,
		F_AXIS,
		F_RUNNING,
		F_HOLDING,
		F_STOPPED,
		F_READY,

		F_AXIS2,
		F_RUNNING2,
		F_HOLDING2,
		F_STOPPED2,
		F_READY2
	};
}

#endif // RMI_GLOBALS_H_