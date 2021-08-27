//Funciones de la máquina de estados del sistema

#include "fsmsys.h"
#include "led.h"
#include "fsm_tecla.h"

/*===========================================================================
 * Se definen los estados de la MEF
 *	INICIAL: En este estado se inicializan la UART y ADC. Para pasar al estado
 *			 Normal es necesario apretar la tecla 1 (TEC1)  de la placa CIAA.
 *	NORMAL: En este estado activa pasos de carga de acuerdo al valor
 *		    obtenido a través del ADC, mientras sea menor o igual a 900.
 *	ALARMA: Se ingresa a este estado cuando se detecta alguna anomalía en el sistema
 *           como un sobrecarga (se simula por un exceso en el valor de ADC por
 *           encima de 900).
 *===========================================================================*/
typedef enum{
   MODO_INICIAL,
   MODO_NORMAL,
   MODO_ALARMA,
}fsmEstado_t;

static void fsmSysError( void );

bool_t flagTeclaLiberada=FALSE;

static fsmEstado_t fsmEstado; // Variable de estado (privada)

/* ===============================================================
 * Se definen las banderas para cada estado dentro de la MEF
 * flagSate[0]-> INICIAL
 * flagSate[1]-> NORMAL
 * flagSate[2]-> ALARMA
 * Las bandejas cambia de FALSE a TRUE para indicar que se encuentran en un
 * estado determinado.
 ==================================================================*/
bool_t flagState[]={FALSE, FALSE, FALSE};

/* ===============================================================
 * Función: fsmSysError
 * Descripción: En caso de no encontrarse en alguno de los estados definidos
 * 				se envía el sistema al estado INICIAL y se envía un mensaje
 * 				a través de la UART
 * Entradas: No recibe argumento de entrada.
 ==================================================================*/
static void fsmSysError( void ){
	fsmEstado = MODO_INICIAL;
    uartWriteString( UART_USB, "Error, vuelta a Modo Inicial\r\n" );
}

/* ===============================================================
 * Función: fsmSysInit
 * Descripción: Inicializa los perifèridos con los que trabajará el sistema.
 * Entradas: No recibe argumento de entrada.
 ==================================================================*/
void fsmSysInit( void ){
// Inicializa la placa CIAA
	boardInit();
	ledsInit();  //En el futuro servirá para definir las salidas GPIO
				 //para la activación de pasos de carga

	uartConfig( UART_USB, 115200 ); //Inicialización de la UART
	adcConfig( ADC_ENABLE ); // Habilitación del ADC
	fsmButtonInit(); // Inicializa la MEF antirrebote
	fsmEstado = MODO_INICIAL; //Se establece el estado inicial del sistema
}

/* ===============================================================
 * Función: fsmSysUpdate
 * Descripción: Actualiza el estado del sistema de acuerdo a las condiciones
 *				determinadas para cada uno de ellos.
 * Entradas: No recibe argumento de entrada.
 ==================================================================*/
void fsmSysUpdate( void ){
    /* Variable para almacenar el valor AI0 - ADC0 CH1 */
	uint16_t carga_actual = 0;

	fsmButtonUpdate(TEC1);

	switch( fsmEstado ){

		case MODO_INICIAL:
			/* Se establece un mensaje de inicio de sistema*/
			 if (flagState[0] == FALSE){
				 uartWriteString( UART_USB, "SYSTEM READY TO WORK\r\n" );
			 }
			 flagState[0] = TRUE;
			 if (flagTeclaLiberada==TRUE){  //!gpioRead( TEC1 )
				 fsmEstado = MODO_NORMAL; // TEC1-> Botón de encendido
				 flagState[0] = FALSE;
			 }
			 else
				 fsmEstado = MODO_INICIAL;

		break;

		  case MODO_NORMAL:
			  flagTeclaLiberada==FALSE;
			  flagState[1] = TRUE; //Se activa la bandera del Modo Normal

			  carga_actual = adcRead( CH1 ); //Se adquiere dato del ADC - Canal 1

    	  /*Se simulan estados de carga con los datos obtenidos por el ADC */
    	  /* */
		            if( carga_actual < 102 ){
		               uartWriteString( UART_USB, "INGRESAN 03 BANCOS\r\n" );
		               //Se encienden 3 pasos de carga
		               encenderLed(CARGA_1);
		               encenderLed(CARGA_2);
		               encenderLed(CARGA_3);
		            }
		            if( 102 < carga_actual && carga_actual <= 204){
		               uartWriteString( UART_USB, "INGRESAN 02 BANCOS\r\n" );
		               //Se encienden 2 pasos de carga
		               apagarLeds();
		               encenderLed(CARGA_2);
		               encenderLed(CARGA_3);
		            }
		            if( 204 < carga_actual && carga_actual <= 306 ){
		               uartWriteString( UART_USB, "INGRESA 01 BANCO\r\n" );
		               //Se enciende 1 paso de carga
		               apagarLeds();
		               encenderLed(CARGA_3);
		            }
		            if( 307 < carga_actual && carga_actual <=900){
		               uartWriteString( UART_USB, "BANCOS APAGADOS\r\n" );
		               //Se apagan los bancos
		               apagarLeds();
		            }
		            if( 900 < carga_actual ){
		            	fsmEstado = MODO_ALARMA;
		            	flagState[1] = FALSE;
		            	uartWriteString( UART_USB, "SOBRECARGA\r\n" );
		            	apagarLeds();
		            }
	      break;

	      case MODO_ALARMA:
	    	  flagState[2] = TRUE; //Se activa la bandera del Modo Alarma
	    	  uartWriteString( UART_USB, "ALERTA\r\n" );

	    	  //Se adquiere dato del ADC - Canal 1
	    	  carga_actual = adcRead( CH1 );
	    	  //Se verifica si bajó la carga para pasar al estado Normal
	    	  if(0<=carga_actual && carga_actual<=900){
	    		 fsmEstado = MODO_NORMAL;
		    	 flagState[2] = FALSE;
	    	  }
	    	  else
	    	  //Si no disminuye la carga permanece en estado Alarma
		    	 fsmEstado = MODO_ALARMA;

	      break;

	      default:
	    	  	  fsmSysError(); //Función en caso de un error dentro de la MEF
	      break;
	   }
}
