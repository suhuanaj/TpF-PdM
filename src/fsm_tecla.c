//Funciones de la MEF para el antirrebote de tecla de encendido (TEC 1)

#include "fsm_tecla.h"
#include "sapi.h"
#include "teclas.h"

/*===========================================================================
 * Se definen los estados de la MEF antirrebote
 *	BUTTON_UP: Tecla sin ser presionada o soltada. Estado inicial de la MEF.
 *	BUTTON_DOWN: Tecla presionada.
 *	BUTTON_FALLING: Transición de tecla suelta a presionada. UP -> DOWN
 *	BUTTON_RISING: Transición de tecla presiona a soltada. DOWN -> UP
 *===========================================================================*/
typedef enum{
   ESTADO_BUTTON_UP,
   ESTADO_BUTTON_DOWN,
   ESTADO_BUTTON_FALLING,
   ESTADO_BUTTON_RISING
} fsmButtonState_t;

fsmButtonState_t fsmEstadoTecla; //Variable que almacena el estado de la MEF

/* ========================================================================
 * Función: buttonPressed
 * Descripción: Ejecuta una rutina cuando la tecla se encuentra presionada.
 * Entradas: No recibe argumento de entrada.
 =========================================================================*/
static void buttonPressed( void )
{
	;
}
/* ========================================================================
 * Función: buttonReleased
 * Descripción: Activa una bandera cuando la tecla es soltada.
 * Entradas: No recibe argumento de entrada.
 =========================================================================*/
static void buttonReleased( void )
{
	flagTeclaLiberada=TRUE;
}
/* ========================================================================
 * Función: fsmButtonError
 * Descripción: En caso de un error en la MEF, actualiza el estado a BUTTON_UP.
 * Entradas: No recibe argumento de entrada.
 =========================================================================*/
static void fsmButtonError( void )
{
	fsmEstadoTecla = ESTADO_BUTTON_UP;
}
/* ========================================================================
 * Función: fsmButtonInit
 * Descripción: Se establece el estado inicial de la MEF en BUTTON_UP.
 * Entradas: No recibe argumento de entrada.
 =========================================================================*/
void fsmButtonInit( void )
{
	fsmEstadoTecla = ESTADO_BUTTON_UP;  // Estado inicial de la tecla (TEC1)
}
/* ========================================================================
 * Función: fsmButtonUpdate
 * Descripción: La función actualiza el estado de la MEF antirrebote.
 * Entradas: Tecla sobre la que se aplicará el antirrebote. Para este proyecto
 * se usará la Tecla 1 (TEC1).
 =========================================================================*/
void fsmButtonUpdate( gpioMap_t tecla )
{
   static bool_t flagFalling = FALSE;
   static bool_t flagRising = FALSE;

   switch( fsmEstadoTecla ){

      case ESTADO_BUTTON_UP:
         /* Detección del flanco de bajada */
         if( !leerTecla(tecla) ){
        	 fsmEstadoTecla = ESTADO_BUTTON_FALLING;
         }
      break;

      case ESTADO_BUTTON_DOWN:
         /* Detección del flanco de subida */
         if( leerTecla(tecla) ){
        	 fsmEstadoTecla = ESTADO_BUTTON_RISING;
         }
      break;

      case ESTADO_BUTTON_FALLING:
         /* Ingreso al estado que detecta el flanco de bajada */
         if( flagFalling == FALSE ){
            flagFalling = TRUE;
         }

         if( !leerTecla(tecla) ){
            fsmEstadoTecla = ESTADO_BUTTON_DOWN; //Tecla presionada
            buttonPressed();

         }
         else{
            fsmEstadoTecla = ESTADO_BUTTON_UP;
         }

         /* Tecla soltada */
         if( fsmEstadoTecla != ESTADO_BUTTON_FALLING ){
            flagFalling = FALSE;
         }
      break;

      case ESTADO_BUTTON_RISING:
    	 /* Ingreso al estado que detecta el flanco de subida */
         if( flagRising == FALSE ){
            flagRising = TRUE;
         }

         if( leerTecla(tecla) ){
            fsmEstadoTecla = ESTADO_BUTTON_UP; //Tecla soltada
            buttonReleased();
         }
         else{
            fsmEstadoTecla = ESTADO_BUTTON_DOWN;
         }

         if( fsmEstadoTecla != ESTADO_BUTTON_RISING ){
            flagRising = FALSE;
         }
      break;

      default:
         fsmButtonError(); //Función de error de la MEF antirrebote
      break;
   }
}


