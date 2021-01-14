/*@brief Programa para encender LEDs RGB utilizando el puerto UART para obtener datos del teclado
 */
 
/**
 * @file    FDRMKL02Z_LED_y_UART.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL02Z4.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

status_t uart0Inicializar(uint32_t);
uint8_t uart0NuevosDatosEnBuffer(void);
status_t uart0LeerByteDesdeBufferCircular(uint8_t *);
//void delay_s(uint32_t segundos);
void delay_ms(uint32_t milis);

/*
 * @brief   Application entry point.
 */


int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    //Inicializando Puerto UART
    (void)uart0Inicializar(115200);


    	//Ciclo Infinito
        while(1) {

        	//Variables
        	status_t status;
        	uint8_t nuevo_byte;
        	uint32_t j = 0;

        	//Verificar si hay datos en el Buffer
        	if(uart0NuevosDatosEnBuffer()>0){

        		//Leer los datos del Buffer
        		status=uart0LeerByteDesdeBufferCircular(&nuevo_byte);

        		//Verificar si el estado es correcto
        		if(status==kStatus_Success){

				//Imprimir que tecla ha sido presionada
				printf("Tecla: %c\r\n",nuevo_byte);

        		//Switch para encender y apagar LEDs
				switch (nuevo_byte) {

				//Encender LED Rojo
				case 'R':
					GPIO_PortClear(GPIOB, 1u << 6U); //Encender LED mediante PortClear
					GPIO_PortSet(GPIOB, 1u << 7U);
					GPIO_PortSet(GPIOB, 1u << 10U);
					//GPIO_PinWrite(GPIOB,6,0); //Encender LED mediante PinWrite
					break;

				//Apagar LED Rojo
				case 'r':
					GPIO_PortSet(GPIOB, 1u << 6U);
					break;

				//Encender LED Verde
				case 'V':
					GPIO_PortClear(GPIOB, 1u << 7U);
					GPIO_PortSet(GPIOB, 1u << 6U);
					GPIO_PortSet(GPIOB, 1u << 10U);
					break;

				//Apagar LED Rojo
				case 'v':
					GPIO_PortSet(GPIOB, 1u << 7U);
					break;

				//Encender LED Azul
				case 'A':
					GPIO_PortClear(GPIOB, 1u << 10U);
					GPIO_PortSet(GPIOB, 1u << 6U);
					GPIO_PortSet(GPIOB, 1u << 7U);
					break;

				//Apagar LED Azul
				case 'a':
					GPIO_PortSet(GPIOB, 1u << 10U);
					break;

				//Combinaciones

				//Encender Color Amarillo (Yellow)
				case 'Y':
					GPIO_PortClear(GPIOB, 1u << 6U);
					GPIO_PortClear(GPIOB, 1u << 7U);
					GPIO_PortSet(GPIOB, 1u << 10U);
					break;

				//Apagar Color Amarillo (Yellow)
				case 'y':
					GPIO_PortSet(GPIOB, 1u << 6U);
					GPIO_PortSet(GPIOB, 1u << 7U);
					break;

				//Encender Color Magenta
				case 'M':
					GPIO_PortClear(GPIOB, 1u << 6U);
					GPIO_PortClear(GPIOB, 1u << 10U);
					GPIO_PortSet(GPIOB, 1u << 7U);
					break;

				//Apagar Color Magenta
				case 'm':
					GPIO_PortSet(GPIOB, 1u << 6U);
					GPIO_PortSet(GPIOB, 1u << 10U);
					break;

				//Encender Color Cyan
				case 'C':
					GPIO_PortClear(GPIOB, 1u << 7U);
					GPIO_PortClear(GPIOB, 1u << 10U);
					GPIO_PortSet(GPIOB, 1u << 6U);
					break;

				//Apagar Color Cyan
				case 'c':
					GPIO_PortSet(GPIOB, 1u << 7U);
					GPIO_PortSet(GPIOB, 1u << 10U);
					break;

				//Apagar cualquier color o combinación
				case 't':
					GPIO_PortSet(GPIOB, 1u << 6U);
					GPIO_PortSet(GPIOB, 1u << 7U);
					GPIO_PortSet(GPIOB, 1u << 10U);
					break;

				//Combinación automática con duración de 10 segundos
				case 'P':
					for (j=0;j<5;j++){
						GPIO_PortClear(GPIOB, 1u << 6U);
						GPIO_PortSet(GPIOB, 1u << 7U);
						GPIO_PortSet(GPIOB, 1u << 10U);
						delay_ms(300);
						GPIO_PortClear(GPIOB, 1u << 7U);
						GPIO_PortSet(GPIOB, 1u << 6U);
						delay_ms(300);
						GPIO_PortClear(GPIOB, 1u << 10U);
						GPIO_PortSet(GPIOB, 1u << 7U);
						delay_ms(300);
						GPIO_PortClear(GPIOB, 1u << 6U);
						GPIO_PortClear(GPIOB, 1u << 7U);
						GPIO_PortSet(GPIOB, 1u << 10U);
						delay_ms(300);
						GPIO_PortClear(GPIOB, 1u << 6U);
						GPIO_PortClear(GPIOB, 1u << 10U);
						GPIO_PortSet(GPIOB, 1u << 7U);
						delay_ms(300);
						GPIO_PortClear(GPIOB, 1u << 7U);
						GPIO_PortClear(GPIOB, 1u << 10U);
						GPIO_PortSet(GPIOB, 1u << 6U);
						delay_ms(300);
						GPIO_PortClear(GPIOB, 1u << 6U);
						delay_ms(200);
					}
					GPIO_PortSet(GPIOB, 1u << 6U);
					GPIO_PortSet(GPIOB, 1u << 7U);
					GPIO_PortSet(GPIOB, 1u << 10U);
					break;
				}
        		}else{
        			printf("error\r\n");
        		}
        	}
}

    return 0 ;
}

