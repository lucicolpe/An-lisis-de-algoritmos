/**
 *
 * Descripcion: Funciones de cabecera para ordenacion 
 *
 * Fichero: tiempos.h
 * Autor: Carlos Aguirre.
 * Version: 1.0
 * Fecha: 15-09-2016
 *
 */

#ifndef TIEMPOS_H
#define TIEMPOS_H

/* constantes */

#ifndef ERR
  #define ERR -1
  #define OK (!(ERR))
#endif

#include "ordenacion.h"

/* definiciones de tipos */
typedef struct tiempo {
  int n_perms;     /* numero de permutaciones */
  int tamanio;     /* tamanio de las permutaciones */
  int n_veces;      /* numero de veces que se evalua cada permutacion */
  double tiempo;   /* tiempo promedio */
  double medio_ob; /* numero premedio de veces que se ejecuta la OB */
  int min_ob;      /* minimo de ejecuciones de la OB */
  int max_ob;      /* maximo de ejecuciones de la OB */
} TIEMPO, *PTIEMPO;


/* Funciones */
short tiempo_medio_ordenacion(pfunc_ordena metodo, int n_perms,int tamanio, PTIEMPO ptiempo, int algoritmo);
short genera_tiempos_ordenacion(pfunc_ordena metodo, char* fichero, int num_min, int num_max, int incr, int n_perms, int algoritmo);
short guarda_tabla_tiempos(char* fichero, PTIEMPO tiempo, int N);

#endif
