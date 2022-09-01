#include <reg52.h>

unsigned char PWM_LEVEL_1=8;//2	 4 6 8 10	�嵲
unsigned char PWM_LEVEL_2=8;
unsigned char COUNT_INTERRUPT=0;

sbit EM1_P=P1^5;
sbit EM2_P=P1^6;


void InitPWM()
{
//        T2MOD=0;  //���ö�ʱ��2���ƼĴ�����������ʵ�������ã�T2CON�ϵ�Ĭ�Ͼ���0
//        T2CON=0;  //���ö�ʱ��2����ģʽ�Ĵ�����������ʵ�������ã�T2MOD�ϵ�Ĭ�Ͼ���0
        TH2=(65536-1000)/256;                        //��ʱ��2����ֵ
        TL2=(65536-1000)%256;                        //1ms                                       
        ET2=1;                        //����ʱ��2�ж�
        EA=1;
        TR2=1;                        //������ʱ��2
}


void PWM() interrupt 5
{
    TF2=0;        //!!!ע��!!! ��ʱ��2����������������־λ���㣬Ӳ����������
	TH2=(65536-1000)/256;                        //��ʱ��2����ֵ
    TL2=(65536-1000)%256;
    COUNT_INTERRUPT++;        

	if(COUNT_INTERRUPT==10)COUNT_INTERRUPT=0,EM2_P=1,EM1_P=1;

	if(COUNT_INTERRUPT==0)EM1_P=1,EM2_P=1;
	if(COUNT_INTERRUPT==(PWM_LEVEL_1-1))EM1_P=0;
	if(COUNT_INTERRUPT==PWM_LEVEL_2)EM2_P=0;
}