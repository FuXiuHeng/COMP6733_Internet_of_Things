
#include "contiki.h"

#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include "rest-engine.h"
#include "board-peripherals.h"

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
	SENSOR_ACTIVATE(mpu_9250_sensor);
	printf("Hello Motion Sensor\n");
	printf("Hello Motion Sensor\n");
	printf("Hello Motion Sensor\n");
	printf("Hello Motion Sensor\n");
	printf("Hello Motion Sensor\n");
	printf(mpu_9250_sensor.value(MPU_9250_SENSOR_TYPE_GYRO_X));
	printf("\n\n\n\n");
}

