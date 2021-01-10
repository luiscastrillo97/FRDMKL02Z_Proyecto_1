/*
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*@brief Programa para encender LEDs RGB utilizando el puerto UART para obtener datos del teclado
 * Oprimiendo R encendemos el LED ROJO
 * Oprimiendo r apagamos el LED ROJO
 * Oprimiendo V encendemos el LED Verde
 * Oprimiendo v apagamos el LED Verde
 * Oprimiendo A encendemos el LED Azul
 * Oprimiendo a apagamos el LED Azul
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
					GPIO_PortClear(GPIOB, 1u << 6U);
					break;

				//Apagar LED Rojo
				case 'r':
					GPIO_PortSet(GPIOB, 1u << 6U);
					break;

				//Encender LED Verde
				case 'V':
					GPIO_PortClear(GPIOB, 1u << 7U);
					break;

				//Apagar LED Rojo
				case 'v':
					GPIO_PortSet(GPIOB, 1u << 7U);
					break;

				//Encender LED Azul
				case 'A':
					GPIO_PortClear(GPIOB, 1u << 10U);
					break;

				//Apagar LED Azul
				case 'a':
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
