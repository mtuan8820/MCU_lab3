/*
 * fsm.c
 *
 *  Created on: Nov 8, 2022
 *      Author: legolas
 */


#include "global.h"
#include "fsm.h"
#include "input_reading.h"
#include "fsm_auto.h"
#include "main.h"
#include "led7seg.h"
#include "timer.h"

void fsm_run(){
	switch (state){
	case INIT:
		index_led=0;
		led_red_duration=3;
		led_amber_duration=1;
		led_green_duration=3;
		setTimer1(1000);
		//setTimer2(1000);
		counter1=led_red_duration;
		counter2=led_green_duration;
		display_led7_seg(counter1);
		light_state1=0;
		light_state2=0;
		state=NORMAL;
		break;
	case NORMAL:
//		if(timer2_flag==1){
//			//led_scanning
//			setTimer2(1000);
//			update7seg(index_led);
//			if(index_led==0) index_led=1;
//			else 			 index_led=0;
//		}
		enable_7seg(0);
		display_led7_seg(counter1);
		if(timer1_flag==1) {
			//update light_state: red, yellow or green according to light_state

			counter1--;
			counter2--;
			display_led7_seg(counter1);
			//when counter reach 0, change color and duration for color
			if(counter1<0) {

				switch (light_state1){
					case 0://red
						counter1=led_amber_duration;
						break;
					case 1://amber
						counter1=led_green_duration;
						break;
					case 2://green
						counter1=led_red_duration;
						break;
					default:
						break;
					}
				light_state1++;
				if(light_state1>2) light_state1=0;
			}
			if(counter2<0) {
				switch (light_state2){
					case 0://green
						counter2=led_amber_duration;
						break;
					case 1://amber
						counter2=led_red_duration;
						break;
					case 2://red
						counter2=led_green_duration;
						break;
					default:
						break;
					}
				light_state2++;
				if(light_state2>=3) light_state2=0;
			}
			fsm_auto_run_for_led_7seg_1();
			fsm_auto_run_for_led_7seg_2();
			setTimer1(1000);	//counter is decrease every 1 second
		}



		//if first button is pressed, mode will change to MODIFY_RED
		if(is_button_pressed(0))
			{
			setTimer1(1000);
			setTimer2(1000);
			state=MODIFY_RED;
			HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin ,GPIO_PIN_RESET);
			enable_7seg(0);
			display_led7_seg(led_red_duration);
			}
		break;
	case MODIFY_RED:
		HAL_GPIO_WritePin(LED_AMBER1_GPIO_Port, LED_AMBER1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin ,GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED_AMBER2_GPIO_Port, LED_AMBER2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin ,GPIO_PIN_SET);
		//toggle red led every second to display mode
		if(timer1_flag==1) {
			HAL_GPIO_TogglePin(LED_RED1_GPIO_Port, LED_RED1_Pin);
			HAL_GPIO_TogglePin(LED_RED2_GPIO_Port, LED_RED2_Pin);
			setTimer1(1000);
		}
		//scanning led to display mode and display led duration
		//using timer2
		if(timer2_flag==1){
		switch (index_led){
			case 0:
				enable_7seg(0);
				display_led7_seg(led_red_duration);
				break;
			case 1:
				enable_7seg(1);
				display_led7_seg(state);

			}
		if(index_led)index_led=0; else index_led=1;
		setTimer2(1000);
		}

		//second button is used to increase the red_duration value
		if(is_button_pressed(1)) {
			led_red_duration++;
			if(led_red_duration>=10) led_red_duration=0;
			display_led7_seg(led_red_duration);
		}
		//third button is used to set the value for red led
		if(is_button_pressed(2)) {
			state=NORMAL;
			//set gia tri khoi dau cho trang thai normal
			setTimer1(1000);
			index_led=0;
			counter1=led_red_duration;
			counter2=led_green_duration;
			display_led7_seg(counter1);
			light_state1=0;
			light_state2=0;
		}
		//if first button is pressed, mode will change to MODIFY_AMBER
		if(is_button_pressed(0))
			{
			setTimer1(1000);
			setTimer2(1000);
			state=MODIFY_AMBER;
			HAL_GPIO_WritePin(LED_AMBER1_GPIO_Port, LED_AMBER1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LED_AMBER2_GPIO_Port, LED_AMBER2_Pin ,GPIO_PIN_RESET);
			enable_7seg(0);
			display_led7_seg(led_amber_duration);
			}
		break;
	case MODIFY_AMBER:
		HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin ,GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin ,GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin ,GPIO_PIN_SET);
		//toggle amber led every second to display mode
		if(timer1_flag==1) {
					HAL_GPIO_TogglePin(LED_AMBER1_GPIO_Port, LED_AMBER1_Pin);
					HAL_GPIO_TogglePin(LED_AMBER2_GPIO_Port, LED_AMBER2_Pin);
					setTimer1(1000);
		}
		//scanning led to display mode and display led duration
				//using timer2
				if(timer2_flag==1){
				switch (index_led){
					case 0:
						enable_7seg(0);
						display_led7_seg(led_amber_duration);
						break;
					case 1:
						enable_7seg(1);
						display_led7_seg(state);

					}
				if(index_led)index_led=0; else index_led=1;
				setTimer2(1000);
				}
		//second button is used to increase the amber_duration value
		if(is_button_pressed(1)) {
			led_amber_duration++;
			if(led_amber_duration>=10) led_amber_duration=0;
			display_led7_seg(led_amber_duration);
		}
		//third button is used to set the value for amber led
		if(is_button_pressed(2)) {
			//set gia tri khoi dau cho trang thai normal
			setTimer1(1000);
			index_led=0;
			counter1=led_red_duration;
			counter2=led_green_duration;
			display_led7_seg(counter1);
			light_state1=0;
			light_state2=0;
			state=NORMAL;
		}
		//if first button is pressed, mode will change to MODIFY_GREEN
		if(is_button_pressed(0)){
			setTimer1(1000);
			setTimer2(1000);
			HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin ,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin ,GPIO_PIN_RESET);
			state=MODIFY_GREEN;
			enable_7seg(0);
			display_led7_seg(led_green_duration);
		}
		break;
	case MODIFY_GREEN:
		HAL_GPIO_WritePin(LED_AMBER1_GPIO_Port, LED_AMBER1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED_AMBER2_GPIO_Port, LED_AMBER2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin ,GPIO_PIN_SET);
		//toggle green led every second to display mode
		if(timer1_flag==1) {
							HAL_GPIO_TogglePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin);
							HAL_GPIO_TogglePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin);
							setTimer1(1000);
				}

		//scanning led to display mode and display led duration
				//using timer2
				if(timer2_flag==1){
				switch (index_led){
					case 0:
						enable_7seg(0);
						display_led7_seg(led_amber_duration);
						break;
					case 1:
						enable_7seg(1);
						display_led7_seg(state);

					}
				if(index_led)index_led=0; else index_led=1;
				setTimer2(1000);
				}
		//second button is used to increase the green_duration value
		if(is_button_pressed(1)) {
			led_green_duration++;
			if(led_green_duration>=10) led_green_duration=0;
			display_led7_seg(led_green_duration);
		}
		//third button is used to set the value for green led
		//if first button is pressed, mode will change to NORMAL
		if(is_button_pressed(2)||is_button_pressed(0)) {
			state=NORMAL;
			//set gia tri khoi dau cho trang thai normal
			setTimer1(1000);
			index_led=0;
			counter1=led_red_duration;
			counter2=led_green_duration;
			display_led7_seg(counter1);
			light_state1=0;
			light_state2=0;
		}

		break;
	default:
		break;
	}
	return;
}
