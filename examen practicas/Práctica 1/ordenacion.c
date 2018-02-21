/**
 *
 * Descripcion: Implementacion de funciones de ordenacion 
 *
 * Fichero: ordenacion.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2016
 *
 */


#include "ordenacion.h"

/***************************************************/
/* Funcion:InsertSort         Fecha:08/10/2016     */
/* Autores:Lucia Colmenarejo Pérez y               */
/* Litzy Tatiana Rocha Avila                       */
/* Función que dada una tabla desordenada la       */
/* ordena de menor a mayor                         */
/* Entrada:                                        */
/* int* tabla:Tabla desordenada a ordenar          */
/* int ip:primer elemento de la tabla              */
/* int iu:ultimo elemento de la tabla              */
/* Salida:                                         */
/* Contador:Devuelve el número de comparación de   */
/* claves realizadas durante la ordenación         */
/* -1: En caso de error                            */

/***************************************************/
int InsertSort(int* tabla, int ip, int iu) {
    int i = 0, j = 0, a = 0, contador = 0;

    if (!tabla || ip < 0 || iu < 0 || iu < ip) return -1;

    for (i = ip + 1; i <= iu; i++) {        
        a = tabla[i];                       /*guardamos en a el elemento i de la tabla*/
        j = i - 1;                          
        while (j >= ip && tabla[j] > a) {   /*mientras j sea mayor o igual que el ultimo y tabla[j] (elemento anterior a 'a') sea mayor que a*/
            contador++;                     /*Contador de operación basica*/
            tabla[j + 1] = tabla[j];        /*Se asigna el número mayor en ambas posiciones del array*/
            j--;                            /*Se disminuye el tamañano que debemos analizar*/
        }
        tabla[j + 1] = a;                   /*Se asigna el número guardado en la variable 'a' a la siguiente posición*/
    }
    return contador;
}

/***************************************************/
/* Funcion:InsertSortInv      Fecha:08/10/2016     */
/* Autores:Lucia Colmenarejo Pérez y               */
/* Litzy Tatiana Rocha Avila                       */
/* Función que dada una tabla desordenada la       */
/* ordena de mayor a menor                         */
/* Entrada:                                        */
/* int* tabla:Tabla desordenada a ordenar          */
/* int ip:primer elemento de la tabla              */
/* int iu:ultimo elemento de la tabla              */
/* Salida:                                         */
/* Contador:Devuelve el número de comparación de   */
/* claves realizadas durante la ordenación         */
/* -1: En caso de error
/***************************************************/
int InsertSortInv(int* tabla, int ip, int iu) {
    int i, j, a, contador = 0;

    if (!tabla || ip < 0 || iu < 0 || iu < ip) return ERR;

    for (i = ip + 1; i <= iu; i++) {
        a = tabla[i];                           /*guardamos en a el elemento i de la tabla*/
        j = i - 1;
        while (j >= ip && tabla[j] < a) {       /*mientras j sea mayor o igual que el ultimo y tabla[j] (elemento anterior a 'a') sea menor que a*/
            tabla[j + 1] = tabla[j];
            j--;                                /*Se disminuye el tamañano que debemos analizar*/
            contador++;                          /*Contador de operación basica*/
        }
        tabla[j + 1] = a;                         /*Se asigna el número guardado en la variable 'a' a la siguiente posición*/
    }
    return contador;

}

