#include "stm32f10x.h"
#include "usart.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "led.h"
#include "lcd.h"
#include "touch.h"
#include "ui.h"

/*u8是unsigned char类型，从其名称就可以看出u8占1个字节（因为1个字节是8位），所以它的范围是0~(2^8)-1。
u16是unsigned short类型，从其名称就可以看出u8占2个字节，所以它的范围是0~(2^16)-1。
u32是unsigned long类型，从其名称就可以看出u8占4个字节，所以它的范围是0~(2^32)-1。
int是有符号整数类型，int占4个字节，它的范围是-(2^31)-1~(2 ^31)-1。*/

int voltage =3000;			//初始峰峰值3V
int mode = 0; 				//0 键盘禁用 1 键盘启用
double frequency = 20; 	//初始频率20kHz




int main(void)
{	
	delay_init();	//该函数放在前面位置较好
	LED_Init();
	uart_init(115200);	//波特率115200
    LCD_Init();	//其中有delay的函数
	
	LCD_Display_Dir(1); 			//横屏显示
	tp_dev.init();					//初始化触摸屏
	TP_Adjust();					//触摸屏校准
	
while(1)
{	
	ui_init();
    double a = Get_Num();
	printf("%f\r\n",a);
	printf("cnm\r\n");
}

}
