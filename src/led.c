// led.c
#include "led.h"
//Las funciones de este módulo son Públicas.


/* ===============================================================
 * Función: ledsInit
 * Descripción: Establece como los LEDs a utilizar como salidas.
 * Entradas: No recibe argumento de entrada.
 ==================================================================*/
void ledsInit( void )
{
   gpioInit(CARGA_1, GPIO_OUTPUT );
   gpioInit(CARGA_2, GPIO_OUTPUT );
   gpioInit(CARGA_3, GPIO_OUTPUT );
}

/* ===============================================================
 * Función: encenderLed
 * Descripción: Enciende un led que es entregado como argument.
 * Entradas: Led que se desea encender (LED1, LED2, LED3, LEDR, LEDG, LEDB).
 * Para este sistema sólo se han considerado LED1, LED2 y LED3.
 ==================================================================*/
void encenderLed(gpioMap_t led)
{
   gpioWrite(led, ON );
}
/* ===============================================================
 * Función: encenderLed
 * Descripción: Apaga todos los leds de la placa CIAA.
 * Entradas: No recibe argumento de entrada.
 ==================================================================*/
void apagarLeds(void)
{
   gpioWrite(CARGA_1, OFF );
   gpioWrite(CARGA_2, OFF );
   gpioWrite(CARGA_3, OFF );
   gpioWrite(LEDR, OFF );
   gpioWrite(LEDG, OFF );
   gpioWrite(LEDB, OFF );
}
