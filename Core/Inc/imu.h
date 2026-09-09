#ifndef IMU_H
#define IMU_H

#include "main.h"
#include "mpu6050.h"

typedef enum
{
    IMU_OK = 0,
    IMU_ERROR_NULL_POINTER,
    IMU_ERROR_SENSOR
} IMU_Status;

typedef struct
{
    float accel_x_g;
    float accel_y_g;
    float accel_z_g;

    float gyro_x_dps;
    float gyro_y_dps;
    float gyro_z_dps;

    float roll;
    float pitch;

} IMU_State;

IMU_Status IMU_Init(void);

IMU_Status IMU_Update(
    float dt,
    IMU_State *state
);


#endif
