#include "stm32f10x.h"
#include "usart.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "led.h"
#include "lcd.h"
#include "touch.h"
#include "ui.h"

/*u8��unsigned char���ͣ��������ƾͿ��Կ���u8ռ1���ֽڣ���Ϊ1���ֽ���8λ�����������ķ�Χ��0~(2^8)-1��
u16��unsigned short���ͣ��������ƾͿ��Կ���u8ռ2���ֽڣ��������ķ�Χ��0~(2^16)-1��
u32��unsigned long���ͣ��������ƾͿ��Կ���u8ռ4���ֽڣ��������ķ�Χ��0~(2^32)-1��
int���з����������ͣ�intռ4���ֽڣ����ķ�Χ��-(2^31)-1~(2 ^31)-1��*/

int voltage =3000;			//��ʼ���ֵ3V
int mode = 0; 				//0 ���̽��� 1 ��������
double frequency = 20; 	//��ʼƵ��20kHz




int main(void)
{	
	delay_init();	//�ú�������ǰ��λ�ýϺ�
	LED_Init();
	uart_init(115200);	//������115200
    LCD_Init();	//������delay�ĺ���
	
	LCD_Display_Dir(1); 			//������ʾ
	tp_dev.init();					//��ʼ��������
	TP_Adjust();					//������У׼
	
while(1)
{	
	ui_init();
    double a = Get_Num();
	printf("%f\r\n",a);
	printf("cnm\r\n");
}

}
