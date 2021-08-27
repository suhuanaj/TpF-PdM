/*=============================================================================
 * Program: TP5_ArmandoSuhuanF
 * Date: 2021/08/27
 * Version: 1
 * Descripción general: El sistema busca ingresar pasos de carga de acuerdo a la
 * potencia leía por el sistema. Esta lectura será simulada con lecturas a través
 * del ADC - Canal 1 (CH1) de la placa CIAA y la activación de pasos de carga será
 * simulada con el encendido de Leds.
 * Se consideran 03 rangos de datos para la activación de pasos de carga y
 * 03 pasos de carga correspondientes a cada rango definido.
 *===========================================================================*/

#include "TP5_ArmandoSuhuanF.h"
#include "sapi.h"
#include "fsmsys.h"

int main( void )
{
	/* Inicializar retardo no bloqueante con tiempo en ms */
	delay_t delay1;
	delayConfig( &delay1, 100 );

	/* La función inicializa la placa CIAA, los leds como salida, UART, ADC,
	   y el estado inicial de la máquina de estado del sistema */
	fsmSysInit();
   // ----- Repeat for ever -------------------------
   while( true ) {

	   if (delayRead(&delay1)){
		   fsmSysUpdate();
	   }
   }

   return 0;
}
