#include <reg52.h>
//����
extern unsigned char ircode[4];
sbit beep=P2^3;
//��־
extern bit IFFlag;
//oled
extern void	oled_speed();
extern void	oled_manual();
extern void	oled_find_track();
extern void	oled_auto_avoid();
extern void	oled_auto_follow();
//�������
extern void DECISION(void);

void ConfigUART(unsigned int baud)
{
    SCON  = 0x50;  //���ô���Ϊģʽ1
    TMOD &= 0x0F;  //����T1�Ŀ���λ
    TMOD |= 0x20;  //����T1Ϊģʽ2
    TH1 = 256 - (11059200/12/32)/baud;  //����T1����ֵ
    TL1 = TH1;     //��ֵ��������ֵ
    ET1 = 0;       //��ֹT1�ж�
    ES  = 1;       //ʹ�ܴ����ж�
    TR1 = 1;       //����T1
}

void InterruptUART() interrupt 4
{

	if(RI)
	{
		IFFlag=0;
		RI = 0;
		ircode[2]=SBUF;
		DECISION();
	}
	if(TI)
	{
		TI = 0;
	}
}
