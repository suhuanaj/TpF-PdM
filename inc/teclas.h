//teclas.h

#ifndef MY_PROGRAMAS_TP5_ARMANDOSUHUANF_INC_TECLAS_H_
#define MY_PROGRAMAS_TP5_ARMANDOSUHUANF_INC_TECLAS_H_

// Se incluye biblioteca
#include "sapi.h"

/* ===============================================================
 * Función: leerTecla
 * Descripción: La función lee el estado de la entrada correspondiente a una tecla.
 * Entradas: Tecla a leer -> TEC1, TEC2, TEC3, TEC4.
 * Salida: Valor booleano con el estado de la tecla.
 * '0' -> Tecla apretada (ON)
 * '1' -> Tecla sin apretar (OFF)
 ==================================================================*/
bool_t leerTecla( gpioMap_t tecla);

#endif /* MY_PROGRAMAS_TP5_ARMANDOSUHUANF_INC_TECLAS_H_ */
