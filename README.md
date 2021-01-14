# FRDMKL02Z_Proyecto_1
Este repositorio contiene el programa para encender los LEDs RGB de la tarjeta FRDMKL02Z utilizando el puerto UART para obtener datos del teclado.

 Se copiaron las librerias que generó el Ingeniero Ernerto Rincón para utilizar el puerto UART llamada sdk_hal. Se configuraron los Puertos PTB6, PTB/ y PTB10 como salidas GPIO. Y se desarrolló el código con éxito.
 
 Se creó una librería que contiene una función de retardo (función aproximada) llamada delay. Esta contiene una función de retardo calculada en segundos y otra en milisegundos.

 Cualquier tecla del teclado que se oprima se verá reflejada en la terminal serial.

 * Oprimiendo R encendemos el LED ROJO
 * Oprimiendo r apagamos el LED ROJO
 * Oprimiendo V encendemos el LED Verde
 * Oprimiendo v apagamos el LED Verde
 * Oprimiendo A encendemos el LED Azul
 * Oprimiendo a apagamos el LED Azul
 * Oprimiendo Y encendemos la combinación de LEDs que resulta en el color Amarillo.
 * Oprimiendo y apagamos la combinación Amarillo.
 * Oprimiendo M encendemos la combinación de LEDs que resulta en el color Magenta.
 * Oprimiendo m apagamos la combinación Magenta.
 * Oprimiendo C encendemos la combinación de LEDs que resulta en el color Cyan.
 * Oprimiendo c apagamos la combinación Cyan.
 * Oprimiendo P activamos una secuencia de colores que demora 10 segundos. 
 * Oprimiendo t apagamos cualquier color o combinación en caso de existir un resultado inesperado.
 * Oprimiendo cualquier otra tecla, solo se muestra la tecla que se oprime en la terminal, pero, no realiza otra acción.


 