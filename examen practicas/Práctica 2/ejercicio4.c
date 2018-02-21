/**************************************************/
/* Programa: ejercicio4       Fecha:08/10/2016    */
/* Autores:Lucia Colmenarejo Pérez y              */
/* Litzy Tatiana Rocha Avila                      */
/* Programa que Comprueba SelectSort              */
/*                                                */
/* Entrada: Linea de comandos                     */
/* -tamanio: numero elementos permutacion         */
/* Salida: 0: OK, -1: ERR                         */
/**************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "permutaciones.h"
#include "ordenacion.h"

int main(int argc, char** argv)
{
  int tamano, i, j, ret=0, algoritmo;
  int* perm = NULL;

  srand(time(NULL));

  if (argc != 5) {
    fprintf(stderr, "Error en los parametros de entrada:\n\n");
    fprintf(stderr, "%s -tamanio <int> -pivote <int> \n", argv[0]);
    fprintf(stderr, "Donde:\n");
    fprintf(stderr, " -tamanio : numero elementos permutacion.\n");
    fprintf(stderr, " -pivote : -pivote:0 IS, 1 MS, 2 QS pivote primer elemento, 3 QS pivote elemento medio, 4 QS pivote valor intermedio entre las tres\n");
    return 0;
  }
  printf("Practica numero 1, apartado 4\n");
  printf("Realizada por: Lucia Colmenarejo Pérez y Litzy Tatiana Rocha Avila\n");
  printf("Grupo: 1201\n");

  /* comprueba la linea de comandos */
  for(i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-tamanio") == 0) {
      tamano = atoi(argv[++i]);
    }
      else if(strcmp(argv[i], "-pivote") == 0) {
      algoritmo = atoi(argv[++i]);
    } else {
      fprintf(stderr, "Parametro %s es incorrecto\n", argv[i]);
    }
    }

  perm = genera_perm(tamano);

  if (perm == NULL) { /* error */
    printf("Error: No hay memoria\n");
    exit(-1);
  }
  if(algoritmo==0){
    ret = InsertSort(perm, 0, tamano-1,algoritmo);
  }
  else if(algoritmo==1){
  ret= MergeSort(perm, 0, tamano-1, algoritmo);
} else if(algoritmo==2){
  ret = QuickSort(perm, 0, tamano-1, algoritmo);
} else if(algoritmo==3){
  ret =QuickSort(perm, 0, tamano-1, algoritmo);
} else if(algoritmo==4){
  ret = QuickSort(perm, 0, tamano-1, algoritmo);
} 
else{
  printf("Número del algoritmo incorrecto\n");
  free(perm);
   exit(-1);
}
  if (ret == ERR) {
    printf("Error: Error en InsertSort\n");
    free(perm);
    exit(-1);
  }

  for(j = 0; j < tamano; j++) {
    printf("%d \t", perm[j]);
  }
  printf("\n");

  free(perm);

  return 0;
}

