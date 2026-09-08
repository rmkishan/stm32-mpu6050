#ifndef MOTOR_H
#define MOTOR_H

#include "main.h"

HAL_StatusTypeDef Motor_Init(void);

HAL_StatusTypeDef Motor_SetCommand(float command);

#endif
