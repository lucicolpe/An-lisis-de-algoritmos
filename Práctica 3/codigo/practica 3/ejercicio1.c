/***********************************************/
/* Programa: ejercicio1     Fecha:             */
/* Autores:                                    */
/*                                             */
/* Programa que comprueba el funcionamiento de */
/* la busqueda lineal                          */
/*                                             */
/* Entrada: Linea de comandos                  */
/*   -tamanio: numero elementos diccionario    */
/*   -clave:   clave a buscar                  */
/*                                             */
/* Salida: 0: OK, -1: ERR                      */
/***********************************************/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>

#include "ordenacion.h"
#include "busqueda.h"
#include "permutaciones.h"

int main(int argc, char** argv)
{
  int i, nob, pos=-1;
  unsigned int clave, tamanio;
  PDICC pdicc;
  int *perm;
  char algoritmo[64];
  int orden;
  srand(time(NULL));

  if (argc != 9) {
    fprintf(stderr, "Error en los parametros de entrada:\n\n");
    fprintf(stderr, "%s -tamanio <int> -clave <int> -algoritmo <string> -orden <int>\n", argv[0]);
    fprintf(stderr, "Donde:\n");
    fprintf(stderr, " -tamanio : numero elementos de la tabla.\n");
    fprintf(stderr, " -clave : clave a buscar.\n");
    fprintf(stderr, " -algoritmo : nombre del algoritmo de busqueda blin, bbin, blinauto.\n");
    fprintf(stderr, " -orden : orden del diccionario 0 para no ordenado, 1 para ordenado.\n");
    exit(-1);
  }

  printf("Practica numero 3, apartado 1\n");
  printf("Realizada por: Vuestros nombres\n");
  printf("Grupo: Vuestro grupo\n");

  /* comprueba la linea de comandos */
  for(i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-tamanio") == 0) {
      tamanio = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-clave") == 0) {
      clave = atoi(argv[++i]);
    }else if (strcmp(argv[i], "-algoritmo") == 0) {
     strcpy(algoritmo, argv[++i]);
    }else if (strcmp(argv[i], "-orden") == 0) {
      orden = atoi(argv[++i]);
    } else {
      fprintf(stderr, "Parametro %s es incorrecto\n", argv[i]);
    }
  }

  if(orden==0){
  pdicc = ini_diccionario(tamanio,NO_ORDENADO);
   if (pdicc == NULL) {
    /* error */
    printf("Error: No se puede Iniciar el diccionario\n");
    exit(-1);
  }
  }
  else if(orden==1){
    pdicc = ini_diccionario(tamanio,ORDENADO);
     if (pdicc == NULL) {
    /* error */
    printf("Error: No se puede Iniciar el diccionario\n");
    exit(-1);
    }
  }
  else{
    printf("Parametro -orden erroneo");
    exit(-1);
  }
 

  perm = genera_perm(tamanio);

  if (perm == NULL) {
    /* error */
    printf("Error: No hay memoria\n");
    libera_diccionario(pdicc);
    exit(-1);
  }

  nob = insercion_masiva_diccionario(pdicc, perm, tamanio);

  if (nob == ERR) {
    /* error */
    printf("Error: No se puede crear el diccionario memoria\n");
    free(perm);
    libera_diccionario(pdicc);
    exit(-1);
  }
  if(strcmp(algoritmo, "blin")==0){
  nob = busca_diccionario(pdicc,clave,&pos,blin);
  }
  else if(strcmp(algoritmo, "bbin")==0){
  nob = busca_diccionario(pdicc,clave,&pos,bbin);
  }
  else if(strcmp(algoritmo, "blinauto")==0){
    nob = busca_diccionario(pdicc,clave,&pos,blin_auto);
  }
  else{
    printf("Parametro -algoritmo erroneo"); 
    free(perm);
    libera_diccionario(pdicc);
    exit(-1);
  }
  if(nob >= 0) {
    printf("Clave %d encontrada en la posicion %d en %d op. basicas\n",clave,pos,nob);
  } else if (nob==NO_ENCONTRADO) {
    printf("La clave %d no se encontro en la tabla\n",clave);
  } else {
    printf("Error al buscar la clave %d\n",clave);
  }
  
  free(perm);
  libera_diccionario(pdicc);

  return 0;
}

