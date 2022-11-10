/*
 * fsm_auto.c
 *
 *  Created on: Nov 8, 2022
 *      Author: legolas
 */


#include "fsm_auto.h"
#include "global.h"
#include "main.h"
#include "led7seg.h"


void fsm_auto_run_for_led_7seg_1(){
	switch (light_state1){
	case 0:	//turn on red led
		HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED_AMBER1_GPIO_Port, LED_AMBER1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin ,GPIO_PIN_SET);

		break;
	case 1: //turn on amber led
  		  HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, GPIO_PIN_SET);
  		  HAL_GPIO_WritePin(LED_AMBER1_GPIO_Port, LED_AMBER1_Pin, GPIO_PIN_RESET);
  		  HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin ,GPIO_PIN_SET);

		  break;
	case 2: //turn on green led
  		  HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, GPIO_PIN_SET);
  		  HAL_GPIO_WritePin(LED_AMBER1_GPIO_Port, LED_AMBER1_Pin, GPIO_PIN_SET);
  		  HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin ,GPIO_PIN_RESET);

		  break;
	default:
		  break;
	}
}

void set_counter(int state){
	switch (state){
	case 0://red
		counter1=led_amber_duration;
		break;
	case 1://amber
		counter1=led_green_duration;
		break;
	case 2://amber
		counter1=led_red_duration;
		break;
	default:
		break;
	}

}

void fsm_auto_run_for_led_7seg_2(){
	switch (light_state2){
	case 0: //turn on green led
		HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED_AMBER2_GPIO_Port, LED_AMBER2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin ,GPIO_PIN_RESET);
		break;
	case 1: //turn on amber led
		HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED_AMBER2_GPIO_Port, LED_AMBER2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin ,GPIO_PIN_SET);
		break;
	case 2: //turn on red led
		HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED_AMBER2_GPIO_Port, LED_AMBER2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin ,GPIO_PIN_SET);
		break;
	default:
		break;
	}

}
