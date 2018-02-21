/***********************************************************/
/* Programa: ejercicio5                  Fecha:13/10/2016  */
/* Autores:Lucia Colmenarejo Pérez y                       */
/* Litzy Tatiana Rocha Avila                               */
/* Programa que escribe en un fichero                      */
/* los tiempos medios del algoritmo de                     */
/* ordenacion por Seleccion                                */
/*                                                         */
/* Entrada: Linea de comandos                              */
/* -num_min: numero minimo de elementos de la tabla        */
/* -num_max: numero minimo de elementos de la tabla        */
/* -incr: incremento\n                                     */
/* -numP: Introduce el numero de permutaciones a promediar */
/* -fichSalida: Nombre del fichero de salida               */
/* Salida: 0 si hubo error                                 */
/* -1 en caso contrario                                    */
/***********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "ordenacion.h"
#include "tiempos.h"

int main(int argc, char** argv)
{
  int i, num_min, num_max, incr, n_perms, algoritmo;
  char nombre[256];
  short ret;

  srand(time(NULL));

  if (argc != 13) {
    fprintf(stderr, "Error en los parametros de entrada:\n\n");
    fprintf(stderr, "%s -num_min <int> -num_max <int> -incr <int>\n", argv[0]);
    fprintf(stderr, "\t\t -numP <int> -fichSalida <string> \n");
    fprintf(stderr, "Donde:\n");
    fprintf(stderr, "-num_min: numero minimo de elementos de la tabla\n");
    fprintf(stderr, "-num_max: numero minimo de elementos de la tabla\n");
    fprintf(stderr, "-incr: incremento\n");
    fprintf(stderr, "-numP: Introduce el numero de permutaciones a promediar\n");
    fprintf(stderr, "-fichSalida: Nombre del fichero de salida\n");
    fprintf(stderr, "-pivote:0 IS, 1 MS, 2 QS pivote primer elemento, 3 QS pivote elemento medio, 4 QS pivote valor intermedio entre las tres\n");
    exit(-1);
  }

  printf("Practica numero 1, apartado 5\n");
  printf("Realizada por: Lucia Colmenarejo Pérez y Litzy Tatiana Rocha Avila\n");
  printf("Grupo: 1201\n");

  /* comprueba la linea de comandos */
  for(i = 1; i < argc ; i++) {
    if (strcmp(argv[i], "-num_min") == 0) {
      num_min = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-num_max") == 0) {
      num_max = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-incr") == 0) {
      incr = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-numP") == 0) {
      n_perms = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-fichSalida") == 0) {
      strcpy(nombre, argv[++i]);
    } else if (strcmp(argv[i], "-pivote") == 0) {
      algoritmo=atoi(argv[++i]);
    } else {
      fprintf(stderr, "Parametro %s es incorrecto\n", argv[i]);
    }
  }

  /* calculamos los tiempos */
  if(algoritmo==0){
    ret = genera_tiempos_ordenacion(InsertSort, nombre,num_min, num_max,incr, n_perms, algoritmo);
  }
  else if(algoritmo==1){
    ret = genera_tiempos_ordenacion(MergeSort, nombre ,num_min , num_max , incr, n_perms ,algoritmo);
  }
  else if(algoritmo==2){
  ret = genera_tiempos_ordenacion(QuickSort, nombre , num_min , num_max , incr , n_perms, algoritmo);
  }
 else if(algoritmo==3){
    ret = genera_tiempos_ordenacion(QuickSort, nombre , num_min, num_max, incr, n_perms, algoritmo);
 }
 else if(algoritmo==4){
   ret = genera_tiempos_ordenacion(QuickSort, nombre , num_min, num_max, incr, n_perms, algoritmo);
 }
else{
  printf("Número del algoritmo incorrecto");
  exit(-1);
}
  if (ret == ERR) { /* ERR_TIME debera ser un numero negativo */
    printf("Error en la funcion Time_Ordena\n");
    exit(-1);
  }
  printf("Salida correcta \n");

  return 0;
}

