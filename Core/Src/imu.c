#include "imu.h"
#include <math.h>

#define FILTER_ALPHA 0.98f

static float filtered_roll = 0.0f;
static float filtered_pitch = 0.0f;

IMU_Status IMU_Init(void) {
    filtered_roll = 0.0f;
    filtered_pitch = 0.0f;

    if (MPU6050_Init() != HAL_OK) {
        return IMU_ERROR_SENSOR;
    }

    return IMU_OK;
}

IMU_Status IMU_Update(float dt, IMU_State *state)
{
    MPU6050_SensorData raw;
    MPU6050_PhysicalData physical;
    MPU6050_Angles accel_angles;

    static uint32_t test_read_count = 0;

    if (state == NULL)
    {
        return HAL_ERROR;
    }

    if (MPU6050_ReadData(&raw) != HAL_OK)
    {
        return HAL_ERROR;
    }

    MPU6050_ConvertData(&raw, &physical);

    MPU6050_CalculateAngles(&physical, &accel_angles);

    /*
     * Copy physical sensor values into public IMU state
     */
    state->accel_x_g = physical.accel_x_g;
    state->accel_y_g = physical.accel_y_g;
    state->accel_z_g = physical.accel_z_g;

    state->gyro_x_dps = physical.gyro_x_dps;
    state->gyro_y_dps = physical.gyro_y_dps;
    state->gyro_z_dps = physical.gyro_z_dps;

    /*
     * Complementary filter
     */
    filtered_roll =
        FILTER_ALPHA *
        (filtered_roll + physical.gyro_x_dps * dt)
        +
        (1.0f - FILTER_ALPHA) * accel_angles.roll;

    filtered_pitch =
        FILTER_ALPHA *
        (filtered_pitch + physical.gyro_y_dps * dt)
        +
        (1.0f - FILTER_ALPHA) * accel_angles.pitch;

    state->roll = filtered_roll;
    state->pitch = filtered_pitch;

    return HAL_OK;
}
