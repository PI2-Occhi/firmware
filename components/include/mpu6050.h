#pragma once

#include <stdio.h>
#include <math.h>
#include "driver/i2c.h"

#ifdef __cplusplus
extern "C" {
#endif

// Address of MPU6050 (Can be 0x68 or 0x69):
#define MPU6050_ADDRESS_LOW     0x68 // Address pin low (GND).
#define MPU6050_ADDRESS_HIGH    0x69 // Address pin high (VCC).
#define MPU6050_DEVICE          MPU6050_ADDRESS_LOW

// Structure of battery
typedef struct _mpu6050_rotation_t
{
    int16_t gyro_x;
    int16_t gyro_y;
    int16_t gyro_z;
} mpu6050_rotation_t;

uint8_t mpu6050_device_address;
uint8_t buffer[14];

void mpu6050_init();
bool mpu6050_test_connection();
const char* mpu6050_get_tag();
uint8_t mpu6050_get_accel_z_self_test_factory_trim();
uint8_t mpu6050_get_gyro_x_self_test_factory_trim();
uint8_t mpu6050_get_gyro_y_self_test_factory_trim();
uint8_t mpu6050_get_gyro_z_self_test_factory_trim();

#ifdef __cplusplus
}
#endif