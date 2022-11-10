/*
 * input_processing.c
 *
 *  Created on: Nov 8, 2022
 *      Author: legolas
 */


#include "input_processing.h"
#include "main.h"
#include "input_reading.h"
#include "timer.h"
#include "global.h"
#include "led7seg.h"

void PressedKeyProcess(int index){
	switch (index){
	case 0:
		button_flag[0]=0;



//		if(timer1_flag==1){
//				setTimer1(1000);
//				HAL_GPIO_TogglePin(LED_RED1_GPIO_Port, LED_RED1_Pin);
//				HAL_GPIO_TogglePin(LED_RED2_GPIO_Port, LED_RED2_Pin);
//		}//all led reds are blinking in 2Hz
		break;
	case 1:
		button_flag[1]=0;
		led_red_duration++;
		display_led7_seg(led_red_duration);
		break;
	case 2:
		button_flag[2]=0;
		HAL_GPIO_WritePin(LED_AMBER1_GPIO_Port, LED_AMBER1_Pin, GPIO_PIN_SET);
	    HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin ,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED_AMBER2_GPIO_Port, LED_AMBER2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin ,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, GPIO_PIN_SET);
	    HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin ,GPIO_PIN_SET);
		break;
	default:
		break;
	}

}
