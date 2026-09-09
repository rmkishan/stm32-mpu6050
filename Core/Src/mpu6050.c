#include "mpu6050.h"

extern I2C_HandleTypeDef hi2c1;

HAL_StatusTypeDef MPU6050_ReadByte(uint8_t reg, uint8_t *data){

	return HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, reg, I2C_MEMADD_SIZE_8BIT, data, 1, 100);

}

HAL_StatusTypeDef MPU6050_WriteByte(uint8_t reg, uint8_t data)
{
    return HAL_I2C_Mem_Write(
        &hi2c1,
        MPU6050_ADDR,
        reg,
        I2C_MEMADD_SIZE_8BIT,
        &data,
        1,
        100
    );
}

HAL_StatusTypeDef MPU6050_WhoAmI(uint8_t *id)
{
    return MPU6050_ReadByte(MPU6050_WHO_AM_I, id);
}

HAL_StatusTypeDef MPU6050_Init(void)
{
    uint8_t id;

    /* Check communication */
    if (MPU6050_WhoAmI(&id) != HAL_OK)
    {
        return HAL_ERROR;
    }

    /*
     * Device responded successfully.
     *
     * This module currently reports WHO_AM_I = 0x70.
     * We are allowing initialization to continue while
     * we investigate the device identity.
     */

    // Wake up MPU6050
    if (MPU6050_WriteByte(MPU6050_PWR_MGMT_1, 0x00) != HAL_OK)
    {
        return HAL_ERROR;
    }

    HAL_Delay(100);

    // Digital Low Pass Filter
    if (MPU6050_WriteByte(MPU6050_CONFIG, 0x03) != HAL_OK)
    {
        return HAL_ERROR;
    }

    // Gyroscope: ±250 °/s
    if (MPU6050_WriteByte(MPU6050_GYRO_CONFIG,
                          MPU6050_GYRO_FS_250) != HAL_OK)
    {
        return HAL_ERROR;
    }

    // Accelerometer: ±2 g
    if (MPU6050_WriteByte(MPU6050_ACCEL_CONFIG,
                          MPU6050_ACCEL_FS_2G) != HAL_OK)
    {
        return HAL_ERROR;
    }

    return HAL_OK;
}

HAL_StatusTypeDef MPU6050_ReadAccel(MPU6050_AccelData *data){
	uint8_t buffer[6];

	HAL_StatusTypeDef ret = HAL_I2C_Mem_Read(&hi2c1,
			MPU6050_ADDR,
			0x3B,
			I2C_MEMADD_SIZE_8BIT, buffer,  6, 100);

	if (ret != HAL_OK){
		return ret ;
	}

	data->accel_x = (int16_t)((buffer[0] << 8) | buffer[1]);
	data->accel_y = (int16_t)((buffer[2] << 8) | buffer[3]);
	data->accel_x = (int16_t)((buffer[4] << 8) | buffer[5]);

	return HAL_OK;

}


HAL_StatusTypeDef MPU6050_ReadData(MPU6050_SensorData *data){
	uint8_t buffer[14];

	HAL_StatusTypeDef ret = HAL_I2C_Mem_Read(&hi2c1,
			MPU6050_ADDR,
			0x3B,
			I2C_MEMADD_SIZE_8BIT, buffer,  14, 100);
	if (ret != HAL_OK){
		return ret ;
	}

	data->accel_x = (int16_t)((buffer[0] << 8) | buffer[1]);
	data->accel_y = (int16_t)((buffer[2] << 8) | buffer[3]);
	data->accel_z = (int16_t)((buffer[4] << 8) | buffer[5]);

	data->temp = (int16_t)((buffer[6] << 8) | buffer[7]);

	data->gyro_x = (int16_t)((buffer[8] << 8) | buffer[9]);
	data->gyro_y = (int16_t)((buffer[10] << 8) | buffer[11]);
	data->gyro_z = (int16_t)((buffer[12] << 8) | buffer[13]);

	return HAL_OK;

}


void MPU6050_ConvertData(
    const MPU6050_SensorData *raw,
    MPU6050_PhysicalData *physical
)
{
    physical->accel_x_g = raw->accel_x / 16384.0f;
    physical->accel_y_g = raw->accel_y / 16384.0f;
    physical->accel_z_g = raw->accel_z / 16384.0f;

    physical->gyro_x_dps = raw->gyro_x / 131.0f;
    physical->gyro_y_dps = raw->gyro_y / 131.0f;
    physical->gyro_z_dps = raw->gyro_z / 131.0f;
}

#include <math.h>

void MPU6050_CalculateAngles(
    const MPU6050_PhysicalData *data,
    MPU6050_Angles *angles
)
{
    angles->roll =
        atan2f(
            data->accel_y_g,
            data->accel_z_g
        ) * 180.0f / M_PI;

    angles->pitch =
        atan2f(
            -data->accel_x_g,
            sqrtf(
                data->accel_y_g * data->accel_y_g +
                data->accel_z_g * data->accel_z_g
            )
        ) * 180.0f / M_PI;
}

















