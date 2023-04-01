#include "u_sys.h"
#include "u_delay.h"
#include "u_key.h"
#include "u_led.h"
#include "u_timer.h"
#include "u_usart.h"
//SPIx ��дһ���ֽ�
//TxData:Ҫд����ֽ�
//����ֵ:��ȡ�����ֽ�
u8 SPI1_ReadWriteByte(u8 TxData)
{
  u8 retry=0;				 	
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
  {
    retry++;
    if(retry>200)
    {
      return 0;
    }
  }			  
  SPI_I2S_SendData(SPI1, TxData);               //ͨ������SPIx����һ������
  retry=0;
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)
  {
    retry++;
    if(retry>200)
    {
      return 0;
    }
  }	  						    
  return SPI_I2S_ReceiveData(SPI1);             //����ͨ��SPIx������յ�����					    
}
void SPI1_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_SetBits(GPIOA, GPIO_Pin_5 | GPIO_Pin_6);
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //����SPI�������˫�������ģʽ
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;                       //����SPI����ģʽ
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;                   //����SPI�����ݴ�С
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;                          //����ͬ��ʱ�ӵĿ���״̬Ϊ�͵�ƽ
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;                        //����ͬ��ʱ�ӵĵ�1�������أ��������½������ݱ�����
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;                           //NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;                  //ָ�����ݴ����MSBλ����LSBλ��ʼ
  SPI_InitStructure.SPI_CRCPolynomial = 7;                            //CRCֵ����Ķ���ʽ
  SPI_Init(SPI1, &SPI_InitStructure);                                 //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
  SPI_Cmd(SPI1, ENABLE);                                              //ʹ��SPI����
}
/**
 * ����: SPI�ٶ����ú���
 * ����: ��Ƶ����
*/
void SPI1_SetSpeed(u8 SPI_BaudRatePrescaler)
{
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));
  SPI1->CR1&=0XFFC7;
  SPI1->CR1|=SPI_BaudRatePrescaler;
  SPI_Cmd(SPI1, ENABLE); 
}
void ThermocoupleInit(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 |GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_SetBits(GPIOA, GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_7);
  SPI1_Init();
  SPI1_SetSpeed(SPI_BaudRatePrescaler_8);                     //����Ϊ4.5Mʱ��
}
/**
 * ����: ��ȡ�ȵ�ż�¶�
 * ����: �ȵ�ż���
 * ����: �¶�
*/
float readThermocoupleTemperature(u8 Num)
{
  u8 i, pBuffer[2];
  float Temp;
  switch (Num)
  {
    case 0:
      CS_K1 = 0;
      break;
    case 1:
      CS_K2 = 0;
      break;
    case 2:
      CS_K3 = 0;
      break;
    default:
      break;
  }
  for(i = 0; i < 2; i ++)
  {
    pBuffer[i] = SPI1_ReadWriteByte(0XFF);
  }
  switch (Num)
  {
    case 0:
      CS_K1 = 1;
      break;
    case 1:
      CS_K2 = 1;
      break;
    case 2:
      CS_K3 = 1;
      break;
    default:
      break;
  }
  Temp=((((pBuffer[1]|pBuffer[0]<<8)))>>3);
  Temp*=0.25;
  return Temp;
}
/**
 * ����: �¶ȼ���
 * λ��: 100ms
*/
void runTempCalc(void)
{
  u8 i;
  GulThermocoupleTemperatureTemp[GucThermocoupleNum] += readThermocoupleTemperature(GucThermocoupleNum);
  GucThermocoupleNum ++;
  if (GucThermocoupleNum > 2)
  {
    GucThermocoupleNum = 0;
    GucCalcNum ++;
  }
  if (GucCalcNum >= 3)
  {
    GucCalcNum = 0;
    for (i = 0; i < 3; i++)
    {
      GssThermocoupleTemperature[i] = (u16)(GulThermocoupleTemperatureTemp[i]/3);
      GulThermocoupleTemperatureTemp[i] = 0;
    }
  }
}
/**
 * ����: ʱ��ѭ������
 * λ��: ��ѭ��
*/
void runTimeTask(void)
{
  //1ms
  if (1 == Bflg1msDelaytime)
  {
    Bflg1msDelaytime = 0;
    Guc10msDelaytime ++;
  }
  //10ms
  if (Guc10msDelaytime >= 10)
  {
    Guc10msDelaytime = 0;
    Guc100msDelaytime ++;
  }
  //100ms
  if (Guc100msDelaytime >= 10)
  {
    Guc100msDelaytime = 0;
    runTempCalc();
  }
}
int main(void)
{
  delay_init();	    	                            //��ʱ������ʼ��
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	ThermocoupleInit();
  TIM3_Int_Init(9,7199);                          //10Khz�ļ���Ƶ�ʣ�������10Ϊ1ms
  while(1)
  {
    runTimeTask();
  }
}
