#include <reg52.h>

#define LCD1602_DATAPINS P0
sbit LCD1602_E =P3^4;
sbit LCD1602_RW=P3^6;
sbit LCD1602_RS=P3^5;
//��ʱ
extern void delay(unsigned int n,unsigned char mode);
//PWM
extern unsigned char PWM_LEVEL_1;
extern unsigned char PWM_LEVEL_2;
//US
extern unsigned long int Distance;

unsigned char i;
unsigned char MN[] ="Manual    ";
unsigned char FT[] ="FindTrack ";
unsigned char AA[] ="AutoAvoid ";
unsigned char AF[] ="AutoFollow";

void LcdWriteCom(unsigned char com)	  //д������
{
	LCD1602_E = 0;     //ʹ��
	LCD1602_RS = 0;	   //ѡ��������
	LCD1602_RW = 0;	   //ѡ��д��
	
	LCD1602_DATAPINS = com;     //��������
	delay(1,0);		//�ȴ������ȶ�

	LCD1602_E = 1;	          //д��ʱ��
	delay(5,0);	  //����ʱ��
	LCD1602_E = 0;
}		   
 
void LcdWriteData(unsigned char dat)			//д������
{
	LCD1602_E = 0;	//ʹ������
	LCD1602_RS = 1;	//ѡ����������
	LCD1602_RW = 0;	//ѡ��д��

	LCD1602_DATAPINS = dat; //д������
	delay(1,0);

	LCD1602_E = 1;   //д��ʱ��
	delay(5,0);   //����ʱ��
	LCD1602_E = 0;
}

void lcd_manual()
{
	LcdWriteCom(0x80+0x06);
	for(i=0;i<10;i++)
	{
		LcdWriteData(MN[i]);
	}
}
void lcd_speed()
{
	LcdWriteCom(0x80+0x40+0x07);
	switch(PWM_LEVEL_1)
	{
		case 2	:LcdWriteData('1');break;
		case 4	:LcdWriteData('2');break;
		case 6	:LcdWriteData('3');break;
		case 8	:LcdWriteData('4');break;
		case 10	:LcdWriteData('5');break;
	}
}
void lcd_find_track()
{
	LcdWriteCom(0x80+0x06);
	for(i=0;i<10;i++)
	{
		LcdWriteData(FT[i]);
	}
}
void lcd_auto_avoid()
{
	LcdWriteCom(0x80+0x06);
	for(i=0;i<10;i++)
	{
		LcdWriteData(AA[i]);	      
	}
}
void lcd_auto_follow()
{
	LcdWriteCom(0x80+0x06);
	for(i=0;i<10;i++)
	{
		LcdWriteData(AF[i]);
	}
}
void lcd_Distance()
{
	LcdWriteCom(0x80+0x40+0x09);
	LcdWriteData((Distance/1000)%10+48);
	LcdWriteData((Distance/100)%10+48);
	LcdWriteData((Distance/10)%10+48);
	LcdWriteData(Distance%10+48);
}		   
void LcdInit()	
{
	unsigned char words_1[]="Mode:";	
	unsigned char words_2[]="Speed:";	
 	LcdWriteCom(0x38);  //����ʾ
	LcdWriteCom(0x0c);  //����ʾ����ʾ���
	LcdWriteCom(0x06);  //дһ��ָ���1
	LcdWriteCom(0x01);  //����
	LcdWriteCom(0x80);  //��������ָ�����

	for(i=0;i<5;i++)
	{
		LcdWriteData(words_1[i]);
	}
	lcd_manual();
	LcdWriteCom(0x80+0x40);
	for(i=0;i<6;i++)
	{
		LcdWriteData(words_2[i]);
	}
	LcdWriteCom(0x80+0x40+0x07);
	LcdWriteData('3');

	lcd_Distance();
}
