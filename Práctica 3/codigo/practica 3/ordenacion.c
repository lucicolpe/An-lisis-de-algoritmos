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
#include "permutaciones.h"
#include <stdlib.h>
#include <stdio.h>
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
int InsertSort(int* tabla, int ip, int iu, int algoritmo) {
    int i = 0, j = 0, a = 0, contador = 0;

    if (!tabla || ip < 0 || iu < -1 ) return ERR;

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
/* -1: En caso de error                            */
/***************************************************/
int InsertSortInv(int* tabla, int ip, int iu, int algoritmo) {
    int i, j, a, contador = 0;

    if (!tabla || ip < 0 || iu < -1) return ERR;

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




/***************************************************/
/* Funcion:merge      Fecha:21/10/2016             */
/* Autores:Lucia Colmenarejo Pérez y               */
/* Litzy Tatiana  Rocha Avila                      */    
/* Función que dada una tabla desordenada la       */
/* ordena de mayor a menor                         */
/* Entrada:                                        */
/* int* tabla:Tabla desordenada a ordenar          */
/* int ip:primer elemento de la tabla              */
/* int iu:ultimo elemento de la tabla              */
/* Salida:                                         */
/* Contador:Devuelve el número de comparación de   */
/* claves realizadas durante la ordenación         */
/* -1: En caso de error                            */
/***************************************************/

int merge(int* tabla, int ip, int iu, int imedio){
    int* tablaAux=NULL;
    int i=0,j=0,k=0, contador=0;
    if(!tabla || ip<0 || iu<-1 || imedio<0){
        return ERR;
    }
    
    tablaAux=(int *)malloc(sizeof(int)*(iu-ip+1));
    if(tablaAux==NULL)return ERR;
    
    
    for(i=ip, j=imedio+1, k=0; i<=imedio && j<=iu; k++, contador++){
         if(tabla[i]<tabla[j]){
            tablaAux[k]=tabla[i];
           
         
            i++;
        }
        else{
            tablaAux[k]=tabla[j];
             j++;
        }
    }
    
    if(i>imedio){
        for( ; j<=iu;j++, k++){
            tablaAux[k]=tabla[j];
        }
    }
    else if(j>iu){
        for( ;i<=imedio;i++,k++){
            tablaAux[k]=tabla[i];
        }
    }
    for(i=ip;i<=iu;i++){
        tabla[i]=tablaAux[i-ip];
    }
    free(tablaAux);
   
   return contador;
}

/***************************************************/
/* Funcion:mergesort_re   Fecha:21/10/2016         */
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

int mergesort_re(int * tabla, int ip, int iu, int* contador){
    int imedio=0;
      if(ip>iu){
        return ERR;
    }
    else if(ip==iu){
        return 0;
    }
    imedio=(iu+ip)/2;
    mergesort_re(tabla,ip,imedio, contador);
    mergesort_re(tabla,imedio+1,iu, contador);
    (*contador)+=merge(tabla,ip,iu,imedio);
    return *contador;
}

/***************************************************/
/* Funcion:mergesort      Fecha:21/10/2016         */
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
int MergeSort(int* tabla, int ip, int iu, int algoritmo){
    int  contador=0;
    if(!tabla||ip<0||iu<-1) return ERR;
    mergesort_re(tabla, ip, iu, &contador);
    
    return contador;
}



/***************************************************/
/* Funcion:medio      Fecha:08/11/2016             */
/* Autores:Lucia Colmenarejo Pérez y               */
/* Litzy Tatiana Rocha Avila                       */
/* Función que devuelve como pivote el primer      */
/* elemento de la tabla                            */
/* Entrada:                                        */
/* int* tabla:Tabla desordenada a ordenar          */
/* int ip:primer elemento de la tabla              */
/* int iu:ultimo elemento de la tabla              */
/* int* pos: posición del pivote                   */
/* Salida:                                         */
/* Contador:Devuelve el número de comparación de   */
/* claves realizadas durante la ordenación         */
/* -1: En caso de error                            */
/***************************************************/

int medio(int *tabla, int ip, int iu, int* pos){
    if(!tabla || ip<0 || iu<0 || !pos)return ERR;
    *pos=ip;
    return 0;
}

/***************************************************/
/* Funcion:medio_avg  Fecha:08/11/2016             */
/* Autores:Lucia Colmenarejo Pérez y               */
/* Litzy Tatiana Rocha Avila                       */
/* Función que devuelve como pivote el elemento    */
/* de la posición media de la tabla                */
/* Entrada:                                        */
/* int* tabla:Tabla desordenada a ordenar          */
/* int ip:primer elemento de la tabla              */
/* int iu:ultimo elemento de la tabla              */
/* int* pos: posición del pivote                   */
/* Salida:                                         */
/* Contador:Devuelve el número de comparación de   */
/* claves realizadas durante la ordenación         */
/* -1: En caso de error                            */
/***************************************************/

int medio_avg(int *tabla, int ip, int iu, int *pos){
    if(!tabla || ip<0 || iu<0 || !pos) return ERR;
    *pos =(ip+iu)/2;
    return 0;
    
}

/***************************************************/
/* Funcion:medio_stat    Fecha:08/11/2016          */
/* Autores:Lucia Colmenarejo Pérez y               */
/* Litzy Tatiana Rocha Avila                       */
/* Función que compara los valores de las          */
/* posiciones ip, iu e (ip+ iu)/2 y devuelva       */
/* la posición que contenga el valor intermedio    */ 
/* entre las tres.                                 */
/* Entrada:                                        */
/* int* tabla:Tabla desordenada a ordenar          */
/* int ip:primer elemento de la tabla              */
/* int iu:ultimo elemento de la tabla              */
/* int* pos: posición del pivote                   */
/* Salida:                                         */
/* Contador:Devuelve el número de comparación de   */
/* claves realizadas durante la ordenación         */
/* -1: En caso de error                            */
/***************************************************/

int medio_stat(int *tabla, int ip, int iu, int *pos){
    int v_ip,v_m,v_iu, m, contador=0;
    if(!tabla || ip<0 || iu<0 || !pos) return ERR; 
    
    m=(ip+iu)/2;
    v_ip=tabla[ip];
    v_m=tabla[m];
    v_iu=tabla[iu];
    
    if(v_ip<=v_iu){
        contador++;
        if(v_ip<=v_m){
            contador++;
            if(v_m<=v_iu){
                contador++;
                *pos=m;
            } else{
                contador++;
                *pos=iu;
            }
        }
        else {
            contador++;
            *pos=ip;
        }
    } else{
        if(v_iu<=v_m){
            contador++;
            if(v_ip<=v_m){
                contador++;
                *pos=ip;
            }else{
                contador++;
                *pos=m;
            }
        }else{
            contador++;
            *pos=iu;
        }
    }            
   
    return contador;
}

/***************************************************/
/* Funcion:partir        Fecha:08/11/2016          */
/* Autores:Lucia Colmenarejo Pérez y               */
/* Litzy Tatiana Rocha Avila                       */
/* Función que divide la tabla en funcion del      */
/* pivote escogido                                 */
/* Entrada:                                        */
/* int* tabla:Tabla desordenada a ordenar          */
/* int ip:primer elemento de la tabla              */
/* int iu:ultimo elemento de la tabla              */
/* int* pos: posición del pivote                   */
/* int algoritmo: elegimos qué tipo de pivote      */
/* queremos llamando a las funciones               */
/* implementadas anteriormente                     */
/* Salida:                                         */
/* Contador:Devuelve el número de comparación de   */
/* claves realizadas durante la ordenación         */
/* -1: En caso de error                            */
/***************************************************/


int partir(int* tabla, int ip, int iu, int* position, int algoritmo){
    int contador=0;
    int k=0;
    int i=0;
 
   if(algoritmo==2){
    if(medio(tabla,ip,iu,position)==ERR)return ERR;
   }
   else if(algoritmo==3){
     if(medio_avg(tabla,ip,iu,position)==ERR)return ERR;
   }
   else{
        medio_stat(tabla, ip, iu, position);
   }
   
    k=tabla[*position];
    intercambiar(&tabla[ip],&tabla[*position]);
    *position=ip;
    for(i=ip+1; i<=iu ;i++){
        if(tabla[i]<k){
           (*position)++; 
            intercambiar(&tabla[i],&tabla[*position]);
        }
        contador++;
    }
    
    intercambiar(&tabla[ip], &tabla[*position]);
    
    return contador;
}


/***************************************************/
/* Funcion:quicksort_re   Fecha:21/10/2016         */
/* Autores:Lucia Colmenarejo Pérez y               */
/* Litzy Tatiana Rocha Avila                       */
/* Función que dada una tabla desordenada la       */
/* ordena de menor a mayor                         */
/* Entrada:                                        */
/* int* tabla:Tabla desordenada a ordenar          */
/* int ip:primer elemento de la tabla              */
/* int iu:ultimo elemento de la tabla              */
/* int algoritmo: elegimos qué tipo de pivote      */
/* queremos llamando a las funciones               */
/* implementadas anteriormente                     */
/* Salida:                                         */
/* Contador:Devuelve el número de comparación de   */
/* claves realizadas durante la ordenación         */
/* -1: En caso de error                            */
/***************************************************/

int quicksort_re(int *tabla, int ip, int iu, int *contador, int algoritmo){
    int m = 0;
    int n=0;
    
    if(ip>iu){
        return ERR;
    }
    if(ip==iu){
        return 0;
    }
    else{
        m=partir(tabla, ip, iu, &n, algoritmo);
        (*contador)+=m;
       
        if(m==ERR){
            return ERR;
        }
        if(ip<n-1){
            quicksort_re(tabla, ip, n-1, contador,algoritmo);
        }
        if(n+1<iu){
            quicksort_re(tabla, n+1, iu, contador, algoritmo);
        }
    }
        return *contador;
}

/***************************************************/
/* Funcion:QuickSort      Fecha:21/10/2016         */
/* Autores:Lucia Colmenarejo Pérez y               */
/* Litzy Tatiana Rocha Avila                       */
/* Función que dada una tabla desordenada la       */
/* ordena de menor a mayor                         */
/* Entrada:                                        */
/* int* tabla:Tabla desordenada a ordenar          */
/* int ip:primer elemento de la tabla              */
/* Salida:                                         */
/* Contador:Devuelve el número de comparación de   */
/* claves realizadas durante la ordenación         */
/* -1: En caso de error                            */
/***************************************************/

int QuickSort(int* tabla, int ip, int iu, int algoritmo){
    int contador=0;
    quicksort_re(tabla, ip, iu, &contador, algoritmo);
    return contador;
}






