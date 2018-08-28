
#include "contiki.h"
#include "contiki-net.h"
#include "sys/cc.h"
#include "dev/serial-line.h"
#include "dev/cc26xx-uart.h"
#include "board-peripherals.h"

#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include "rest-engine.h"

static void res_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);

RESOURCE(res_motion,
         "title=\"Motion\";rt=\"Temperature\";obs",
         res_get_handler,
         NULL,
         NULL,
         NULL);

static void
res_get_handler(void *request, void *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset)
{
	printf("Hello Motion Sensor\r\n");
	printf("Hello Motion Sensor\r\n");
	printf("Hello Motion Sensor\r\n");
	printf("Hello Motion Sensor\r\n");
	printf("Hello Motion Sensor\r\n");

	SENSORS_ACTIVATE(mpu_9250_sensor);
	for (int i = 0; i < 100; i ++);
	int x = mpu_9250_sensor.value(MPU_9250_SENSOR_TYPE_GYRO_X);

	SENSORS_ACTIVATE(mpu_9250_sensor);
	for (int i = 0; i < 100; i ++);
	int y = mpu_9250_sensor.value(MPU_9250_SENSOR_TYPE_GYRO_Y);

	SENSORS_ACTIVATE(mpu_9250_sensor);
	for (int i = 0; i < 100; i ++);
	int z = mpu_9250_sensor.value(MPU_9250_SENSOR_TYPE_GYRO_Z);

	printf("X value is %d\r\n", x);
	printf("Y value is %d\r\n", y);
	printf("Z value is %d\r\n", z);
	printf("\n\n\n\n");
}

