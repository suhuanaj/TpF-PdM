// led.h
#ifndef MY_PROGRAMAS_TP5_ARMANDOSUHUANF_INC_LED_H_
#define MY_PROGRAMAS_TP5_ARMANDOSUHUANF_INC_LED_H_

// Se incluye biblioteca
#include "sapi.h"

/*============================================================
 * Macros públicas para simular el ingreso de pasos de carga.
 * Se consideran 03 cargas representadas a travès de 03 leds.
 *	CARGA_1 -> LED1
 *	CARGA_2 -> LED2
 *	CARGA_3 -> LED3
 * ==========================================================*/
#define CARGA_1  LED1
#define CARGA_2  LED2
#define CARGA_3  LED3

// Declaraciones de funciones publicas

/*============================================================
 * Función: ledsInit
 * Descripción: Define como salidas CARGA_1, CARGA_2, CARGA_3
 *	CARGA_1 -> Salida
 *	CARGA_2 -> Salida
 *	CARGA_3 -> Salida
 * ==========================================================*/
void ledsInit( void );

/*============================================================
 * Función: encenderLed
 * Descripción: Enciende un led en particular
 * Entrada: Led que se busca encender
 * Salida: Sin salida
 * ==========================================================*/
void encenderLed(gpioMap_t led);

/*============================================================
 * Función: apagarLed
 * Descripción: Apaga un led en particular
 * Entrada: Led que se busca apagar
 * Salida: Sin salida
 * ==========================================================*/
void apagarLeds(void);

#endif /* MY_PROGRAMAS_TP5_ARMANDOSUHUANF_INC_LED_H_ */
