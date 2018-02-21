/**
 *
 * Descripcion: Implementacion de funciones de generacion de permutaciones
 *
 * Fichero: permutaciones.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2016
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "permutaciones.h"

/***************************************************/
/* Funcion: aleat_num Fecha:08/10/2016             */
/* Autores:Lucia Colmenarejo Pérez y               */
/* Litzy Tatiana Rocha Avila                       */
/* Rutina que genera un numero aleatorio           */
/* entre dos numeros dados                         */
/*                                                 */
/* Entrada:                                        */
/* int inf: limite inferior                        */
/* int sup: limite superior                        */
/* Salida:                                         */
/* int: numero aleatorio                           */

/***************************************************/
int aleat_num(int inf, int sup) {
    int r = 0;

    if (inf < 0 || sup < 0) return -1; /*comprobamos que nos pasan correctamente los argumentos*/

    r = (rand() / ((double) RAND_MAX + 1.))*(sup - inf + 1) + inf; /*utilizamos la función rand para generar numeros aleatorios*/
    return r;
}


/***************************************************/
/* Funcion: genera_perm Fecha:08/10/2016           */
/* AutoresLucia Colmenarejo Pérez y                */
/* Litzy Tatiana Rocha Avila                       */
/* Rutina que genera una permutacion               */
/* aleatoria                                       */
/*                                                 */
/* Entrada:                                        */
/* int n: Numero de elementos de la                */
/* permutacion                                     */
/* Salida:                                         */
/* int *: puntero a un array de enteros            */
/* que contiene a la permutacion                   */
/* o NULL en caso de error                         */

/***************************************************/
void intercambiar(int *a, int *b) { /*función privada que intercambia numeros*/
    int aux = 0;

    aux = *a;
    *a = *b;
    *b = aux;
}

int* genera_perm(int n) {
    int* permutacion = NULL;
    int i = 0;

    if (n < 1) return NULL; /*Comprobamos que nos pasan bien el tamaño de la permutación a generar*/

    permutacion = (int*) malloc((n + 1) * sizeof (int)); /*Reservamos memoria para la permutación*/
    if (!permutacion) return NULL; /*Comprobamos que la reserva se realizó correctamente*/

    for (i = 0; i < n; i++) {
        permutacion[i] = i + 1;
    }

    for (i = 0; i < n - 1; i++) {
        intercambiar(&(permutacion[i]), &(permutacion[aleat_num(i + 1, n - 1)])); /*Intercambiamos los números de el array*/
    }
    return permutacion;
}

/***************************************************/
/* Funcion: genera_permutaciones Fecha:08/10/2016  */
/* Autores:Lucia Colmenarejo Pérez y               */
/* Litzy Tatiana Rocha Avila                       */
/* Funcion que genera n_perms permutaciones        */
/* aleatorias de tamanio elementos                 */
/*                                                 */
/* Entrada:                                        */
/* int n_perms: Numero de permutaciones            */
/* int tamanio: Numero de elementos de cada        */
/* permutacion                                     */
/* Salida:                                         */
/* int**: Array de punteros a enteros              */
/* que apuntan a cada una de las                   */
/* permutaciones                                   */
/* NULL en caso de error                           */

/***************************************************/
int** genera_permutaciones(int n_perms, int tamanio) {
    int** permu = NULL;
    int i = 0;

    if (n_perms < 1 || tamanio < 1) return NULL; /*Comprobamos que nos pasan correctamente los argumentos de entrada*/

    permu = (int **) malloc(n_perms * sizeof (int*)); /*Reservamos la memoria para el puntero a permutaciones*/
    for (i = 0; i < n_perms; i++) {
        (permu)[i] = (genera_perm(tamanio)); /*llamamos a genera_perm que nos generará permutaciones de tamaño tamanio*/
    }
    return permu;
}