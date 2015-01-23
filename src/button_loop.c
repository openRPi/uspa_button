/**
 *  循环检测GPIO（按键）输入电平
 * 
 *  Copyright (C) 2014 concefly  <h.wenjian@openrpi.org>
 *	Copyright (C) 2014 w.guihong <w.guihong@openrpi.org>
 *	Copyright (C) 2014 openRPi   <www.openrpi.org>
 *
 *	代码遵循GNU协议
 *
 */

#include <stdio.h>
#include <signal.h>
#include "bcm2835.h"

#define BTN_PIN		RPI_V2_GPIO_P1_11

int loop_run = 1;

void loop_stop(int sig)
{
	loop_run = 0;
}

/**
 * GPIO初始化，按键初始化
 * @return: 成功1，失败0
 */
int button_init(void)
{
	if(!bcm2835_init())
		return 0;
	bcm2835_gpio_fsel(BTN_PIN, BCM2835_GPIO_FSEL_INPT);
	
	// 设置GPIO下拉电阻
	bcm2835_gpio_set_pud(BTN_PIN, BCM2835_GPIO_PUD_DOWN);
	return 1;
}

#define button_value() bcm2835_gpio_lev(BTN_PIN)
#define button_end() bcm2835_close()

int main()
{
	if(!button_init())
		return 1;
		
	/**
	 * 设置SIGINT信号。CTRL-C 发出SIGINT信号。
	 */
	signal(SIGINT,loop_stop);
	
	printf("Checking button,press Ctrl-C to exit...\n");
	while(loop_run)
	{
		printf("\rbtn = %d",button_value());
	}
	printf("Exit\n");

	button_end();
	return 0;
}