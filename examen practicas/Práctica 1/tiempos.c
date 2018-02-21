/**
 *
 * Descripcion: Implementacion de funciones de tiempo
 *
 * Fichero: tiempos.c
 * Autor: Carlos Aguirre Maeso
 * Version: 1.0
 * Fecha: 16-09-2016
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tiempos.h"
#include "ordenacion.h"
#include "permutaciones.h"
#include <limits.h>
/***************************************************/
/* Funcion:tiempo_medio_ordenacion Fecha:08/10/2016*/
/* Autores:Lucia Colmenarejo Pérez y               */
/* Litzy Tatiana Rocha Avila                       */
/* Función que calcula el tiempo que tarda un      */
/* algoritmo en ordenar una tabla                  */
/* Entrada:                                        */
/* pfunc_ordena metodo:Puntero a la función de     */
/* ordenación                                      */
/* int n_perms:Número de permutaciones a evaluar   */
/* int tamanio:Tamaño de las permutaciones         */
/* PTIEMPO ptiempo:Puntero a la estructura TIEMPO  */
/* definida en tiempos.h                           */
/* Salida:                                         */
/* OK en caso de que se el cálculo                 */
/* ERR en caso de error                            */

/***************************************************/
short tiempo_medio_ordenacion(pfunc_ordena metodo, int n_perms, int tamanio, PTIEMPO ptiempo) {
    int ob[n_perms]; /*Array donde guardaremos el número de operaciones básicas para cada permutación*/
    int i = 0, k = 0;
    int **perm = NULL;
    int j, medio = 0;
    int minimo = INT_MAX;
    int maximo = INT_MIN;
    double tiempo;
    clock_t t1, t2; /*Utilización del reloj para calcular el tiempo de ejecución*/

    if (!metodo || n_perms < 1 || tamanio < 1 || !ptiempo) return ERR; /*Comprobamos que nos pasan correctamente los argumentos de entrada*/

    perm = genera_permutaciones(n_perms, tamanio); /*Generamos las permutaciones*/

    t1 = clock(); /*Tiempo antes de empezar la ordenación*/

    for (j = 0; j < n_perms; j++) {
        i = metodo(perm[j], 0, tamanio - 1); /*llamamos al algoritmo de ordenación*/
        ob[j] = i; /*Introducimos el numero de operaciones básicas en nuestro array de ob*/
        if (ob[j] > maximo) { /*Comprobamos si el numero de ob realizadas para la permutación es mayor que el máximo actual*/
            maximo = ob[j];
        }
        if (ob[j] < minimo) { /*Comprobamos si el numero de ob realizadas para la permutación es menor que el mínimo actual*/
            minimo = ob[j];
        }
    }

    t2 = clock(); /*Tiempo tras terminar la ordenación*/
    tiempo = ((double) (t2 - t1)) / (n_perms * CLOCKS_PER_SEC); /*Tiempo promedio de ejecución*/

    for (i = 0; i < j; i++) {
        k = k + ob[i];
    }/*Sumamos los elementos de nuestro array de ob*/

    medio = k / j; /*Calculamos el tiempo medio de ob realizadas*/

    ptiempo->n_perms = n_perms;
    ptiempo->tamanio = tamanio;
    ptiempo->min_ob = minimo;
    ptiempo->max_ob = maximo;
    ptiempo->medio_ob = medio;
    ptiempo->tiempo = tiempo;

    for (i = 0; i < n_perms; i++) {/*Liberamos la memoria utilizada*/
        free(perm[i]);
    }
    free(perm);

    return OK;
}

/***************************************************/
/* Funcion:genera_tiempos_ordenación Fecha:08/10/16*/
/* Autores:Lucia Colmenarejo Pérez y               */
/* Litzy Tatiana Rocha Avila                       */
/* Función que calcula el tiempo que tarda un      */
/* algoritmo en ordenar permutaciones cuyo tamaño  */
/* esta definido entre dos numeros y se incrementa */
/* segun un valor establecido escribe el resultado */
/* en un archivo                                   */
/* Entradas:                                       */
/* pfunc_ordena metodo:Puntero a la función de     */
/* ordenación                                      */
/* char* fichero:Fichero donde escribir            */
/* int num_min:Número que delimita el tamaño de la */
/* permutación por abajo                           */
/* int num_max:Número que delimita el tamaño de la */
/* permutación por arriba                          */
/* int incr:Incremento del tamaño de la permutación*/
/* int n_perms:Número de permutaciones a evaluar   */
/* Salida:                                         */
/* OK en caso de que se realice el cálculo         */
/* ERR en caso de error                            */

/***************************************************/
short genera_tiempos_ordenacion(pfunc_ordena metodo, char* fichero, int num_min, int num_max, int incr, int n_perms) {

    int i = 0, j = 0, k = 0, n = 0;
    PTIEMPO ptiempo;

    if (!metodo || !fichero || num_min < 0 || num_max < 0 || incr < 0 || n_perms < 0) return ERR; /*Comprobamos que nos pasan bien los argumentos de entrada*/

    n = ((num_max - num_min) / incr) + 1; /*Calculamos el numero de veces que se ejecutará tiempo_medio_ordenación*/

    ptiempo = (PTIEMPO) malloc(sizeof (TIEMPO) * n); /*Reservamos memoria para el puntero a TIEMPO*/
    if (!ptiempo) return ERR; /*Comprobamos que se reservó correctamente la memoria*/

    for (i = num_min, k = 0; i <= num_max; i = i + incr, k++) {/*Bucle que permite incrementar el tamaño de las permutaciones y 
                                                                                llama a tiempo_medio_ordeacion para cada tamaño*/
        j = tiempo_medio_ordenacion(metodo, n_perms, i, ptiempo + k); /*Llamamos a tiempo_medio ordenación para calcular el tiempo*/
        if (j == ERR)return ERR;
    }
    if (guarda_tabla_tiempos(fichero, ptiempo, n) == ERR) return ERR; /*Llamamos a guarda_tabla_tiempos para que nos imprima los datos*/
    free(ptiempo); /*Liberamos la memoria utilizada*/

    return OK;
}

/***************************************************/
/* Funcion: guarda_tabla_tiempos Fecha:13/10/2016  */
/* Autores:Lucia Colmenarejo Pérez y               */
/* Litzy Tatiana Rocha Avila                       */
/* Funcion que escribe en un fichero los datos     */
/* de los tiempos de ordenación                    */
/*                                                 */
/* Entrada:                                        */
/* char* fichero:fichero donde escribir            */
/* PTIEMPO tiempo:Puntero a la estructura TIEMPO   */
/* definida en tiempos.h                           */
/* int N:Numero de veces que se realizo la         */
/* ordenación                                      */
/* Salida:                                         */
/* OK en caso de que se realice la escritura       */
/* ERR en caso de error                            */

/***************************************************/
short guarda_tabla_tiempos(char* fichero, PTIEMPO tiempo, int N) {
    int i;
    FILE* f = NULL;

    if (!fichero || !tiempo || N < 0) return ERR; /*Comprobamos que nos pasan bien los argumentos de entrada*/

    f = fopen(fichero, "w"); /*Abrimos el fichero en modo escritura*/
    if (!f)return ERR; /*Comprobamos que se abrió correctamente*/

    for (i = 0; i < N; i++) { /*Bucle que imprime el tamaño de permutaciones y los tiempos del array de punteros a TIEMPO*/
        fprintf(f, "%d  %f  %f  %d  %d\n",(tiempo + i)->tamanio, (tiempo + i)->tiempo, (tiempo + i)->medio_ob, (tiempo + i)->min_ob, (tiempo + i)->max_ob);
    }

    fclose(f); /*Cerramos el fichero*/
    return OK;
}


