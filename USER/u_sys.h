#ifndef __SYS_H
#define __SYS_H	
#include "stm32f10x.h" 	 

//0,��֧��ucos
//1,֧��ucos
#define SYSTEM_SUPPORT_OS		0		//����ϵͳ�ļ����Ƿ�֧��UCOS
																	    
	 
//λ������,ʵ��51���Ƶ�GPIO���ƹ���
//����ʵ��˼��,�ο�<<CM3Ȩ��ָ��>>������(87ҳ~92ҳ).
//IO�ڲ����궨��
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO�ڵ�ַӳ��
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 
 
//IO�ڲ���,ֻ�Ե�һ��IO��!
//ȷ��n��ֵС��16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //��� 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //���� 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //��� 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //���� 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //��� 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //���� 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //��� 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //���� 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //��� 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //����

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //��� 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //����

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //��� 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //����

//����Ϊ��ຯ��
void WFI_SET(void);		//ִ��WFIָ��
void INTX_DISABLE(void);//�ر������ж�
void INTX_ENABLE(void);	//���������ж�
void MSR_MSP(u32 addr);	//���ö�ջ��ַ

#define PSB                   PCout(0)                     //PSB
#define JR3                   PCout(13)                    //����3
#define JR2                   PCout(14)                    //����2
#define JR1                   PCout(15)                    //����1
#define CS_K3                 PAout(3)                     //
#define CS_K2                 PAout(4)                     //
#define CS_K1                 PAout(7)                     //
#define PUMP1                 PBout(9)                     //ˮ��1
#define PUMP2                 PBout(8)                     //ˮ��2
#define PUMP3                 PBout(7)                     //ˮ��3
#define DCF1                  PBout(6)                     //��ŷ�1
#define LED1                  PBout(4)                     //����ָʾ�� ��ɫ
#define LED2                  PBout(3)                     //����ָʾ�� ��ɫ
#define LED3                  PDout(2)                     //Ԥ��ָʾ�� ��ɫ
#define Buzz                  PCout(12)                    //������
#define LCD_CLK               PBout(2)                     //
#define LCD_SID               PBout(10)                    //
#define LCD_CS                PBout(11)                    //

#define SW1                   PCin(4)                      //
#define SW2                   PCin(5)                      //
#define K4                    PAin(11)                     //
#define K3                    PAin(8)                      //
#define K2                    PCin(9)                      //
#define K1                    PCin(8)                      //

#define AlarmRing             1
#define OneShortRing          2
#define TwoShortRing          3
#define ThreeShortRing        4
#define InvalidKeyRing        5
#define LongRing1s            6
#define GucCodeVersion        1
#define GucSpeedGear0         0
#define GucSpeedGear1         1049      //���� 300RPM
#define GucSpeedGear2         1359      //�е� 500RPM
#define GucSpeedGear3         2199      //�ߵ� 850RPM
#define GucSpeedGear4         3599      //���� 1200RPM
extern u8 Bflg1msDelaytime;
extern u8 BflgKey1Done;
extern u8 BflgBuzzerRingDelaytime;
extern u8 BflgBuzzerStopDelaytime;
extern u8 BflgBuzzerRing;
extern u8 BflgSwitchOnDone;
extern u8 BflgWaterPumpEnable;
extern u8 BflgProcessDone;
extern u8 BflgKey1EnableType;
extern u8 Guc10msDelaytime;
extern u8 Guc100msDelaytime;
extern u8 GucSwitchEnableOnDelaytime;
extern u8 GucSwitchEnableOffDelaytime;
extern u8 GucKey1EnableOffDelaytime;
extern u8 GucBuzzerRingType;
extern u8 GucBuzzerRingCount;
extern u8 GucBuzzerStopDelaytime;
extern u8 GucBuzzerStopDelaytimeTemp;
extern u8 GucRunningDelaytime;
extern u8 GucRunningStatusDelaytime;
extern u8 GucLastTimeHour;
extern u8 GucLastTimeMinute;
extern u8 GucLastTimeSecond;
extern u8 GucThermocoupleNum;
extern u8 GucCalcNum;
extern u8 GucMenuSwitch;
extern u8 GucBackToMainMenuDelaytime;
extern u8 GucParameterNum;
extern u16 GusBuzzerDelaytime;
extern u16 GusBuzzerRingDelaytime;
extern u16 GusLastTimeDelaytime;
extern u16 GusKey1EnableOnDelaytime;
extern s16 GssThermocoupleTemperature[3];
extern s16 GssTargetTemperature;
extern u32 GulThermocoupleTemperatureTemp[3];
#endif
