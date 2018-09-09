/**
 * \file
 *         Collect two sets of 600 samples from light sensor OPT3001 at 10Hz 
 * 		   and save it in a CSV format file.
 * \author
 *         mds
 */

#include "contiki.h"
#include "contiki-net.h"
#include "sys/cc.h"
#include "dev/leds.h"
#include "dev/serial-line.h"
#include "dev/cc26xx-uart.h"
#include "ieee-addr.h"
#include "buzzer.h"
#include "board-peripherals.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOGGLE_OFF 0
#define TOGGLE_ON 1 

/* Process Declaration*/
PROCESS(procKeys, "Key-Press Handler Process");
AUTOSTART_PROCESSES(&procKeys);

/* Global Variables */
// Optic Variables
static struct ctimer optic_ctimer;
int optic_sampling_freq = 0.1; // 0.1 sec = 10 Hz
int optic_total_samples = 600;
int optic_sample_count = 0;

/* Helper Functions */
void optic_samples() {

	if (optic_sample_count < optic_total_samples) {

		// int optic_val = opt_3001_sensor.value(1);
		// printf("%d. Light = %d.%02d\r\n", optic_sample_count, optic_val / 100, optic_val % 100);

		optic_sample_count++;
		SENSORS_ACTIVATE(opt_3001_sensor);

	} else {

		optic_sample_count = 0;
		ctimer_stop(&optic_ctimer);

	}


}

/* Processes Code*/
// Process to handle key-presses
PROCESS_THREAD(procKeys, ev, data) {
	PROCESS_BEGIN();

	cc26xx_uart_set_input(serial_line_input_byte);	//Initalise UART in serial driver

   	while (1) {
     	PROCESS_YIELD();	//Let other threads run

		if (ev == serial_line_event_message) {
       		printf("received line: %s\n\r", (char *)data);

       		if (strcmp(data, "l") == 0) {
       			printf("Starting collection of 600 samples from light sensort at 10Hz\r\n");
				ctimer_set(&optic_ctimer, CLOCK_SECOND * optic_sampling_freq, optic_samples, NULL);
       		}
       		
     	} else if (ev == sensors_event && data == &opt_3001_sensor) {
     		int optic_val = opt_3001_sensor.value(0);
			printf("%d. Light = %d.%02d\r\n", optic_sample_count, optic_val / 100, optic_val % 100);
			ctimer_reset(&optic_ctimer);

     	}
   	}

   	PROCESS_END();
}