// tecla.c
#include "teclas.h"
#include "sapi.h"

//Las funciones de este módulo son Públicas.

/* ===============================================================
 * Función: leerTecla
 * Descripción: La función lee el estado de la entrada correspondiente a una tecla.
 * Entradas: Tecla a leer -> TEC1, TEC2, TEC3, TEC4.
 * Salida: Valor booleano con el estado de la tecla.
 * '0' -> Tecla apretada (ON)
 * '1' -> Tecla sin apretar (OFF)
 ==================================================================*/
bool_t leerTecla( gpioMap_t tecla )
{
   bool_t estado_tecla;
   estado_tecla=gpioRead(tecla);
   return estado_tecla;
}
