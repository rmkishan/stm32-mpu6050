#ifndef MPU6050_H
#define MPU6050_H

#include "main.h"

#define MPU6050_ADDR (0x68 << 1)

#define MPU6050_WHO_AM_I 0x75

#define SENSOR_DT 0.01f
#define FILTER_ALPHA 0.98f

// Register definitions

#define MPU6050_SMPLRT_DIV     0x19
#define MPU6050_CONFIG         0x1A
#define MPU6050_GYRO_CONFIG    0x1B
#define MPU6050_ACCEL_CONFIG   0x1C
#define MPU6050_PWR_MGMT_1     0x6B

// Configuration values

#define MPU6050_ACCEL_FS_2G    0x00
#define MPU6050_GYRO_FS_250    0x00

HAL_StatusTypeDef MPU6050_ReadByte(uint8_t reg, uint8_t *data) ;
HAL_StatusTypeDef MPU6050_WriteByte(uint8_t reg, uint8_t data);
HAL_StatusTypeDef MPU6050_Init(void) ;

HAL_StatusTypeDef MPU6050_WhoAmI(uint8_t *id);



typedef struct
{
    int16_t accel_x;
    int16_t accel_y;
    int16_t accel_z;
} MPU6050_AccelData;

typedef struct
{
    int16_t accel_x;
    int16_t accel_y;
    int16_t accel_z;

    int16_t temp;

    int16_t gyro_x;
    int16_t gyro_y;
    int16_t gyro_z;
} MPU6050_SensorData;


typedef struct
{
    float accel_x_g;
    float accel_y_g;
    float accel_z_g;

    float gyro_x_dps;
    float gyro_y_dps;
    float gyro_z_dps;
} MPU6050_PhysicalData;

HAL_StatusTypeDef MPU6050_ReadAccel(MPU6050_AccelData *data);
HAL_StatusTypeDef MPU6050_ReadData(MPU6050_SensorData *data);

typedef struct
{
    float roll;
    float pitch;
} MPU6050_Angles;

void MPU6050_ConvertData(
    const MPU6050_SensorData *raw,
    MPU6050_PhysicalData *physical
);


void MPU6050_CalculateAngles(const MPU6050_PhysicalData *data, MPU6050_Angles *angles);

#endif
