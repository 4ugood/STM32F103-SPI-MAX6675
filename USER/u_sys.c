#include "u_sys.h" 
//THUMBָ�֧�ֻ������
//�������·���ʵ��ִ�л��ָ��WFI  
void WFI_SET(void)
{
	__ASM volatile("wfi");		  
}
//�ر������ж�
void INTX_DISABLE(void)
{		  
	__ASM volatile("cpsid i");
}
//���������ж�
void INTX_ENABLE(void)
{
	__ASM volatile("cpsie i");		  
}
//����ջ����ַ
//addr:ջ����ַ
__asm void MSR_MSP(u32 addr) 
{
  MSR MSP, r0 			//set Main Stack value
  BX r14
}
u8 Bflg1msDelaytime;       //1ms
u8 BflgKey1Done;
u8 BflgBuzzerRingDelaytime;
u8 BflgBuzzerStopDelaytime;
u8 BflgBuzzerRing;
u8 BflgSwitchOnDone;
u8 BflgWaterPumpEnable;
u8 BflgProcessDone;
u8 BflgKey1EnableType;
u8 Guc10msDelaytime;
u8 Guc100msDelaytime;
u8 GucSwitchEnableOnDelaytime;
u8 GucSwitchEnableOffDelaytime;
u8 GucKey1EnableOffDelaytime;
u8 GucBuzzerRingType;
u8 GucBuzzerRingCount;
u8 GucBuzzerStopDelaytime;
u8 GucBuzzerStopDelaytimeTemp;
u8 GucRunningDelaytime;
u8 GucRunningStatusDelaytime;
u8 GucLastTimeHour;
u8 GucLastTimeMinute;
u8 GucLastTimeSecond;
u8 GucThermocoupleNum;
u8 GucCalcNum;
u8 GucMenuSwitch;
u8 GucBackToMainMenuDelaytime;
u8 GucParameterNum;
u16 GusBuzzerDelaytime;
u16 GusBuzzerRingDelaytime;
u16 GusLastTimeDelaytime;
u16 GusKey1EnableOnDelaytime;
s16 GssThermocoupleTemperature[3];
s16 GssTargetTemperature;
u32 GulThermocoupleTemperatureTemp[3];
