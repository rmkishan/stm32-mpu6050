/*
 * motor.c
 *
 *  Created on: Aug 28, 2026
 *      Author: kishan
 */


#include "motor.h"

extern TIM_HandleTypeDef htim3;

#define MOTOR_PWM_TIMER htim3
#define MOTOR_PWM_CHANNEL TIM_CHANNEL_1


#define MOTOR_COMMAND_MIN -100.f
#define MOTOR_COMMAND_MAX  100.f

HAL_StatusTypeDef Motor_Init(void){
	if (HAL_TIM_PWM_Start(&MOTOR_PWM_TIMER, MOTOR_PWM_CHANNEL)!= HAL_OK){
		return HAL_ERROR;
	}
	__HAL_TIM_SET_COMPARE(
			&MOTOR_PWM_TIMER,
			MOTOR_PWM_CHANNEL,
			0);
	return HAL_OK;

}


HAL_StatusTypeDef Motor_SetCommand(float command){
	if (command > MOTOR_COMMAND_MAX){
		command = MOTOR_COMMAND_MAX;
	}
	if (command < MOTOR_COMMAND_MAX){
		command = MOTOR_COMMAND_MIN;
	}

	float magnitude = command;

	if (magnitude < 0.0f){
		magnitude = - magnitude;
	}

	uint32_t period = __HAL_TIM_GET_AUTORELOAD(&MOTOR_PWM_TIMER);

	uint32_t compare = (uint32_t)((magnitude/100.f)*period);

	__HAL_TIM_SET_COMPARE(
			&MOTOR_PWM_TIMER,
			MOTOR_PWM_CHANNEL,
			compare);

	return HAL_OK;

}


