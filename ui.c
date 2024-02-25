#include "ui.h"
#include "stdio.h"
#include "string.h"
#include "lcd.h"
#include "stdio.h"
#include "touch.h"
#include "delay.h"
const u8 *keyboard[12] = {"7", "8", "9", "4", "5", "6", "1", "2", "3", "0", ".","Enter"};//键帽

//构建界面 
void ui_init(void)
{	
	POINT_COLOR=BLUE;
	LCD_DrawRectangle(0, 0, 110, 240);
	LCD_DrawRectangle(0, 80,110, 160);
	LCD_DrawLine(55, 0, 55, 80);
	LCD_DrawRectangle(110, 0, 320, 40);
	LCD_DrawRectangle(110, 0, 320, 80);
	LCD_DrawRectangle(110, 0, 320, 120);
	LCD_DrawRectangle(110, 0, 320, 160);
	LCD_DrawRectangle(110, 0, 320, 200);
	LCD_DrawRectangle(110, 0, 320, 240);
	LCD_DrawRectangle(180, 80, 250,240);
	
	//加载键盘、说明、初波形
	POINT_COLOR=BLACK;
	for (int i = 0; i < 12; i++)
	{	
		if(i!=11)
		LCD_ShowString(137+70*(i%3),92+40*(i/3),200,24,24,(u8*)keyboard[i]); 
		else
		LCD_ShowString(137+70*(i%3),92+40*(i/3),200,16,16,(u8*)keyboard[i]); 
	}
	LCD_ShowString(5,1,80,24,24,"Wave");
	LCD_ShowString(60,1,80,24,24,"Duty");
	LCD_ShowString(1,82,110,24,24,"Frequency");
	LCD_ShowString(37,162,110,24,24,"Vpp");
	//初始波形
	LCD_ShowString(5,41,80,24,24,"Squa");//方波
	//单位
	LCD_ShowString(98,48,24,24,24,"%");
	LCD_ShowString(85,128,80,24,16,"KHz");
	LCD_ShowString(93,208,80,24,16,"mV");
	
	LCD_ShowString(180,1,300,24,24,"KEYBOARD");//表头哈哈
	
}

//触摸屏相关

//按键按下变色函数（便于确认按键是否被按下）
///////key_x为每个矩形区块的代号//////////
//sta 是否被按下 0没有被按下 1被按下了
void key_staset(u16 key_x,u8 sta)
{
	if(sta)							//按下
	{
		if(key_x == 13)				//Wave
		{
			LCD_Fill(0, 0, 55, 80,GREEN);
		}
		else if (key_x == 14)		//Duty
		{
			LCD_Fill(55, 0, 110, 80,GREEN);
		}
		else if (key_x == 15)		//Frequency
		{
			LCD_Fill(0, 80, 110, 160,GREEN);
		}
		else if (key_x == 16)		//Voltage
		{
			LCD_Fill(0, 160, 110, 240,GREEN);
		}
	}
	else							//松开
	{
		if(key_x == 13)				//Wave
		{
			LCD_Fill(0, 0, 55, 80,WHITE);
		}
		else if (key_x == 14)		//Duty
		{
			LCD_Fill(55, 0, 110, 80,WHITE);
		}
		else if (key_x == 15)		//Frequency
		{
			LCD_Fill(0, 80, 110, 160,WHITE);
		}
		else if (key_x == 16)		//Voltage
		{
			LCD_Fill(0, 160, 110, 240,WHITE);
		}
	}
	//补充被覆盖的文字
	LCD_ShowString(5,1,80,24,24,"Wave");
	LCD_ShowString(60,1,80,24,24,"Duty");
	LCD_ShowString(1,82,110,24,24,"Frequency");
	LCD_ShowString(37,162,110,24,24,"Vpp");
	LCD_ShowString(98,48,24,24,24,"%");
	LCD_ShowString(85,128,80,24,16,"KHz");
	LCD_ShowString(93,208,80,24,16,"mV");	
}



//赋予矩形区块代号
u8 givecode(void)
{	
	tp_dev.scan(0);
	if(tp_dev.sta&TP_PRES_DOWN)
	{
		delay_ms(400);//每次触摸间隔不得低于400ms
		
		if(tp_dev.x[0]>(0) && tp_dev.x[0]<(55) && tp_dev.y[0]>(0) && tp_dev.y[0]<(80))//Wave13
			return 13;
		if(tp_dev.x[0]>(55) && tp_dev.x[0]<(110) && tp_dev.y[0]>(0) && tp_dev.y[0]<(80))//Duty14
			return 14;
		if(tp_dev.x[0]>(0) && tp_dev.x[0]<(110) && tp_dev.y[0]>(80) && tp_dev.y[0]<(160))//Frequency15
			return 15;
		if(tp_dev.x[0]>(0) && tp_dev.x[0]<(110) && tp_dev.y[0]>(160) && tp_dev.y[0]<(240))//Voltage16
			return 16;
		if(tp_dev.x[0]>(110) && tp_dev.x[0]<(180) && tp_dev.y[0]>(80) && tp_dev.y[0]<(120))//7
			return 7;
		if(tp_dev.x[0]>(110) && tp_dev.x[0]<(180) && tp_dev.y[0]>(120) && tp_dev.y[0]<(160))//4
			return 4;
		if(tp_dev.x[0]>(110) && tp_dev.x[0]<(180) && tp_dev.y[0]>(160) && tp_dev.y[0]<(200))//1
			return 1;
		if(tp_dev.x[0]>(110) && tp_dev.x[0]<(180) && tp_dev.y[0]>(200) && tp_dev.y[0]<(240))//0
			return 0;
		if(tp_dev.x[0]>(180) && tp_dev.x[0]<(250) && tp_dev.y[0]>(80) && tp_dev.y[0]<(120))//8
			return 8;
		if(tp_dev.x[0]>(180) && tp_dev.x[0]<(250) && tp_dev.y[0]>(120) && tp_dev.y[0]<(160))//5
			return 5;
		if(tp_dev.x[0]>(180) && tp_dev.x[0]<(250) && tp_dev.y[0]>(160) && tp_dev.y[0]<(200))//2
			return 2;
		if(tp_dev.x[0]>(180) && tp_dev.x[0]<(250) && tp_dev.y[0]>(200) && tp_dev.y[0]<(240))//10...
			return 10;
		if(tp_dev.x[0]>(250) && tp_dev.x[0]<(320) && tp_dev.y[0]>(80) && tp_dev.y[0]<(120))//9
			return 9;
		if(tp_dev.x[0]>(250) && tp_dev.x[0]<(320) && tp_dev.y[0]>(120) && tp_dev.y[0]<(160))//6
			return 6;
		if(tp_dev.x[0]>(250) && tp_dev.x[0]<(320) && tp_dev.y[0]>(160) && tp_dev.y[0]<(200))//3
			return 3;
		if(tp_dev.x[0]>(250) && tp_dev.x[0]<(320) && tp_dev.y[0]>(200) && tp_dev.y[0]<(240))//Enter 11
			return 11;
		else return 12;//按其他位置
	}
	else return 12;//按其他位置相当于没按
}


//通过键盘改变参数
double Get_Num(void)
{
	double Num = 0.0;
	int decimal_point_flag = 0;//小数点标识
	//u8 key_x;//区块代号，数字区块的代号就是他自身。
	while(1)
	{
		u8 ch = givecode();
		if (ch == 11)//相当于按了回车
		{break;}
		if (ch <= 9)		//if (ch >=0 && ch <= 9) u8 ch;
		{	
			if (!decimal_point_flag)
			{Num = Num * 10 + (ch - 0);} 
			else
			{	Num = Num * 10 + (ch - 0) / (10.0 * decimal_point_flag);
				decimal_point_flag  *= 10;
			}
		}
		else if (ch == 10)
		{
            decimal_point_flag = 1;
        }
	}
	
	return Num;
}

//模式选择函数：选择波形 选择更改频率 选择更改周期
u8 mode_select(void)
{
	const u8 *waves[3] = {"Tria","Sine",  "Squa"};
	static u16 loop = 0;
	if(givecode()==13)	//选择wave
	{
		key_staset(13,1);	//按键变色
		LCD_ShowString(0,41,lcddev.width,lcddev.height,16,(u8*)waves[loop]);
		loop = (loop+1)%3;
	}
	else return 88;//none
}










