/**
 *
 * Descripcion: Implementacion funciones para busqueda 
 *
 * Fichero: busqueda.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 11-11-2016
 *
 */

#include "busqueda.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
/**
 *  Funciones de geracion de claves
 *
 *  Descripcion: Recibe el numero de claves que hay que generar
 *               en el parametro n_claves. Las claves generadas
 *               iran de 1 a max. Las claves se devuelven en 
 *               el parametro claves que se debe reservar externamente
 *               a la funcion.
 */
  
/**
 *  Funcion: generador_claves_uniforme
 *               Esta fucnion genera todas las claves de 1 a max de forma 
 *               secuencial. Si n_claves==max entonces se generan cada clave
 *               una unica vez.
 */
void generador_claves_uniforme(int *claves, int n_claves, int max){
  int i;

  for(i = 0; i < n_claves; i++) claves[i] = 1 + (i % max);

  return;
}

/**
 *  Funcion: generador_claves_potencial
 *               Esta funcion genera siguiendo una distribucion aproximadamente
 *               potencial. Siendo los valores mas pequenos mucho mas probables
 *               que los mas grandes. El valor 1 tiene una probabilidad del 50%,
 *               el dos del 17%, el tres el 9%, etc.
 */
void generador_claves_potencial(int *claves, int n_claves, int max){
  int i;

  for(i = 0; i < n_claves; i++) {
    claves[i] = (1+max) / (1 + max*((double)rand()/RAND_MAX));	
  }

  return;
}

/***************************************************/
/* Funcion:ini_diccionario         Fecha:08/12/2016*/
/* Autores:Lucia Colmenarejo Pérez y               */
/* Litzy Tatiana Rocha Avila                       */
/* Función que crea un diccionario de un cierto    */
/* tamaño ya sea ordenado o no ordenado            */
/* Entrada:                                        */
/* int tamanio:Tamaño de la tabla del diccionario  */
/* char orden: indica si la tabla es ordenada o no */
/* Salida:                                         */
/* PDICC: un diccionario                           */
/***************************************************/

PDICC ini_diccionario (int tamanio, char orden){
   if(tamanio>MAX_TAMANIO)return NULL;

   PDICC newdiccionario= NULL;
    
    newdiccionario = (PDICC)malloc(sizeof(DICC));;
    if(! newdiccionario){
        return NULL;
    }
    
    newdiccionario->n_datos = 0;
    newdiccionario->tamanio = tamanio;
    newdiccionario->orden = orden;
    newdiccionario->tabla = (int *)malloc(sizeof(int)*newdiccionario->tamanio);
    if(!newdiccionario->tabla){
	libera_diccionario(newdiccionario);
	return NULL;
    }
    
    return newdiccionario;
}

/***************************************************/
/* Funcion:libera_diccionario      Fecha:08/12/2016*/
/* Autores:Lucia Colmenarejo Pérez y               */
/* Litzy Tatiana Rocha Avila                       */
/* Función que libera la tabla de un diccionario   */
/* Entrada:                                        */
/* PDICC: el diccionario a liberar                 */
/* Salida:                                         */
/* No tiene (void)                                 */
/***************************************************/

void libera_diccionario(PDICC pdicc){
    if(!pdicc) return;
    if(pdicc->tabla!=NULL){
        free(pdicc->tabla);
    }
    free(pdicc);
    
}   
/***************************************************/
/* Funcion:inserta_diccionario     Fecha:08/12/2016*/
/* Autores:Lucia Colmenarejo Pérez y               */
/* Litzy Tatiana Rocha Avila                       */
/* Función que inserta el elemento clave en la     */
/* posición correcta del diccionario               */
/* Entrada:                                        */
/* PDICC pdicc: diccionario donde introducimos la  */
/* clave                                           */
/* int clave: clave a insertar                     */
/* Salida:                                         */
/* int i: contador                                 */
/***************************************************/


int inserta_diccionario(PDICC pdicc, int clave){
	int a,i,j;
	    
	if(!pdicc || clave<0) return ERR;

	if(pdicc->orden==NO_ORDENADO){
	    pdicc->tabla[pdicc->n_datos]=clave;
	    pdicc->n_datos++;
	}
	else if(pdicc->orden==ORDENADO){
		pdicc->tabla[pdicc->n_datos]=clave;
		pdicc->n_datos++;
	    a=pdicc->tabla[pdicc->n_datos-1];
	    j=pdicc->n_datos -2;
	    while(j>=0 && pdicc->tabla[j]>a){
	        pdicc->tabla[j+1]=pdicc->tabla[j];
	        j--;
	        i++;
	    }
	pdicc->tabla[j+1]=a;

	}

	return i;
}

/***************************************************/
/*                                Fecha: 08/12/2016*/
/* Funcion:inserta_masiva_diccionario              */
/* Autores:Lucia Colmenarejo Pérez y               */
/* Litzy Tatiana Rocha Avila                       */
/* Función que inserta todas las claves en el      */
/* diccionario                                     */
/* Entrada:                                        */
/* PDICC pdicc: diccionario donde introducimos la  */
/* clave                                           */
/* int n_claves: número de claves a insertar       */
/* int *claves: claves a insertar                  */
/* Salida:                                         */
/* OK si inserta bien todas las claves, si no ERR  */
/***************************************************/

int insercion_masiva_diccionario (PDICC pdicc,int *claves, int n_claves){
    int i;
	if(!pdicc || !claves|| n_claves<0 || n_claves>pdicc->tamanio|| n_claves+pdicc->n_datos>pdicc->tamanio){
	    return ERR;
	}
    for(i=0;i<n_claves;i++){
        inserta_diccionario(pdicc, claves[i]);
    }
    return OK;
}

/***************************************************/
/* Funcion:busca_diccionario      Fecha: 08/12/2016*/
/* Autores:Lucia Colmenarejo Pérez y               */
/* Litzy Tatiana Rocha Avila                       */
/* Función que busca la clave en el diccionario    */
/* Entrada:                                        */
/* PDICC pdicc: diccionario donde introducimos la  */
/* clave                                           */
/* int clave: clave a buscar                       */
/* int *ppos: posición de la clave buscada         */
/* pfunc_busqueda metodo: metodo de búsqueda       */
/* Salida:                                         */
/* int i: número de OBs realizadas                 */
/***************************************************/

int busca_diccionario(PDICC pdicc, int clave, int *ppos, pfunc_busqueda metodo){
	int i=-1;
	if(!pdicc || clave < 0 || !ppos ||!metodo){
	  return ERR;  
	} 
	i=metodo(pdicc->tabla, 0,(pdicc->n_datos-1), clave, ppos);

	return i;
}

/***************************************************/
/* Funcion:imprime_diccionario    Fecha: 08/12/2016*/
/* Autores:Lucia Colmenarejo Pérez y               */
/* Litzy Tatiana Rocha Avila                       */
/* Función que imprime la tabla del diccionario    */
/* Entrada:                                        */
/* PDICC pdicc: diccionario a imprimir             */
/* Salida:                                         */
/* No devuelve nada (void)                         */
/***************************************************/



void imprime_diccionario(PDICC pdicc){
	int i;
	if(!pdicc) return;
	for(i=0;i<pdicc->n_datos;i++){
	    printf("%d\n", pdicc->tabla[i]);
	}
}

/***************************************************/
/* Funcion:bbin                   Fecha: 08/12/2016*/
/* Autores:Lucia Colmenarejo Pérez y               */
/* Litzy Tatiana Rocha Avila                       */
/* Función que busca la clave en el diccionario    */
/* utilizando el algoritmo de búsqueda binaria     */
/* Entrada:                                        */
/* int *tabla: tabla donde buscar la clave         */
/* int P: primer elemento de la tabla              */
/* int U: último elemento de la tabla              */
/* int clave: clave a buscar                       */
/* int *ppos: posición de la clave buscada         */
/* Salida:                                         */
/* int i: número de OBs si está en la tabla        */
/* NO_ENCONTRADO si la clave no esta en la tabla   */
/***************************************************/

int bbin(int *tabla,int P,int U,int clave,int *ppos){
    int m,i=0;
	if(!tabla|| P<0||U<0||clave<0||!ppos){
	    return ERR;
	}
	while(P<=U){
	    m=(P+U)/2;
	    if(tabla[m]==clave){
	        *ppos=m;
	       i++;
	        return i;
	    }
	    else if(clave<tabla[m]){
	        U=m-1;
	    }
	    else {
	        P=m+1;
	    }
	    i++;
	}
	return NO_ENCONTRADO;
}

/***************************************************/
/* Funcion:bbin                   Fecha: 08/12/2016*/
/* Autores:Lucia Colmenarejo Pérez y               */
/* Litzy Tatiana Rocha Avila                       */
/* Función que busca la clave en el diccionario    */
/* utilizando el algoritmo de búsqueda lineal      */
/* Entrada:                                        */
/* int *tabla: tabla donde buscar la clave         */
/* int P: primer elemento de la tabla              */
/* int U: último elemento de la tabla              */
/* int clave: clave a buscar                       */
/* int *ppos: posición de la clave buscada         */
/* Salida:                                         */
/* int j: número de OBs si se ha encontrado        */
/* NO_ENCONTRADO si la clave no esta en la tabla   */
/***************************************************/

int blin(int *tabla,int P,int U,int clave,int *ppos){
    int j=0, i;

	for(i=P;i<=U;i++, j++){
	    if(tabla[i]==clave){
	          *ppos=i;
	          j++;
	          return j;
	    }
	   
	}
	
	return NO_ENCONTRADO;
}

/***************************************************/
/* Funcion:bbin                   Fecha: 08/12/2016*/
/* Autores:Lucia Colmenarejo Pérez y               */
/* Litzy Tatiana Rocha Avila                       */
/* Función que busca la clave en el diccionario    */
/* utilizando el algoritmo de búsqueda lineal      */
/* auto-organizada                                 */
/* Entrada:                                        */
/* int *tabla: tabla donde buscar la clave         */
/* int P: primer elemento de la tabla              */
/* int U: último elemento de la tabla              */
/* int clave: clave a buscar                       */
/* int *ppos: posición de la clave buscada         */
/* Salida:                                         */
/* int j: número de OBs si se ha encontrado        */
/* NO_ENCONTRADO si la clave no esta en la tabla   */
/***************************************************/

int blin_auto(int *tabla,int P,int U,int clave,int *ppos){
	int i, j=0;
	int aux;
	if(!tabla||P<0||U<0||clave<0||!ppos){
		return ERR;
	}
	for(i=P; i<=U; i++,j++){
		if(tabla[i]==clave){
	          j++;
	          if(i==P){
	          	*ppos=i;
	          return j;
	          }
	          *ppos=(i-1);
	          aux=tabla[i];
	          tabla[i]=tabla[i-1];
	          tabla[i-1]= aux;
	          return j;
	    }
	}
	return NO_ENCONTRADO;
}


