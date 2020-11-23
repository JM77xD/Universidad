/**
  * @file pila_max.h
  * @brief Fichero para compilar usopilas_max con VD o con cola.
  *
  *
  * @author José María Ramírez González
  * @date Noviembre 2020
  */


#define CUAL_COMPILA 2
#if CUAL_COMPILA==1
#include "pila_max_VD.h"
#elif CUAL_COMPILA==2
#include "pila_max_cola.h"
#endif