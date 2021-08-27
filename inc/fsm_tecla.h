//fsm_tecla.h

#ifndef MY_PROGRAMAS_TP5_ARMANDOSUHUANF_INC_FSM_TECLA_H_
#define MY_PROGRAMAS_TP5_ARMANDOSUHUANF_INC_FSM_TECLA_H_
#include "sapi.h"
#ifdef __cplusplus
extern "C" {
#endif

extern bool_t flagTeclaLiberada;

/* ========================================================================
 * Función: fsmButtonError
 * Descripción: En caso de un error en la MEF, actualiza el estado a BUTTON_UP.
 * Entradas: No recibe argumento de entrada.
 =========================================================================*/
static void fsmButtonError( void );
/* ========================================================================
 * Función: fsmButtonInit
 * Descripción: Se establece el estado inicial de la MEF en BUTTON_UP.
 * Entradas: No recibe argumento de entrada.
 =========================================================================*/
void fsmButtonInit( void );
/* ========================================================================
 * Función: fsmButtonUpdate
 * Descripción: La función actualiza el estado de la MEF antirrebote.
 * Entradas: Tecla sobre la que se aplicará el antirrebote. Para este proyecto
 * se usará la Tecla 1 (TEC1).
 =========================================================================*/
void fsmButtonUpdate( gpioMap_t tecla );
/* ========================================================================
 * Función: buttonPressed
 * Descripción: Ejecuta una rutina cuando la tecla se encuentra presionada.
 * Entradas: No recibe argumento de entrada.
 =========================================================================*/
static void buttonPressed( void );
/* ========================================================================
 * Función: buttonReleased
 * Descripción: Activa una bandera cuando la tecla es soltada.
 * Entradas: No recibe argumento de entrada.
 =========================================================================*/
static void buttonReleased( void );

#ifdef __cplusplus

#endif

#endif /* MY_PROGRAMAS_TP5_ARMANDOSUHUANF_INC_FSM_TECLA_H_ */
