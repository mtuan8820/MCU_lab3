/*
 * global.h
 *
 *  Created on: Nov 8, 2022
 *      Author: legolas
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#define INIT 			0
#define NORMAL 			1
#define MODIFY_RED		2
#define MODIFY_AMBER	3
#define MODIFY_GREEN	4

extern int index_led;
extern int counter1;
extern int counter2;
extern int state;

extern int led_red_duration;
extern int led_amber_duration;
extern int led_green_duration;

extern int light_state1;
extern int light_state2;
#endif /* INC_GLOBAL_H_ */
