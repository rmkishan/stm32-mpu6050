/*
 * system_state.h
 *
 *  Created on: Aug 30, 2026
 *      Author: kishan
 */

#ifndef INC_SYSTEM_STATE_H_
#define INC_SYSTEM_STATE_H_


typedef enum{
	SYSTEM_BOOT = 0,
	SYSTEM_INIT,
	SYSTEM_SELF_TEST,
	SYSTEM_READY,
	SYSTEM_RUNNING,
	SYSTEM_ERROR

} SystemState ;


typedef enum {
	ERROR_NONE = 0,
	ERROR_IMU,
	ERROR_QUEUE,
	ERROR_CONTROL,
	ERROR_TIMEOUT
} SystemError;

#endif /* INC_SYSTEM_STATE_H_ */
