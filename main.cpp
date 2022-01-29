#include <iostream>
#include <stdlib.h>
#include <stdio.h>
//Jorge Jhovan Rodriguez Moreno

typedef struct{
    char titulo[30];
    char cantante[50];
    int minutos;
    int segundos;
    char genero[30];
    int posicion;
}CANCION;
typedef struct strLista{
    CANCION melody;
    struct strLista *sig;
}NODO;
typedef struct{
    NODO *inicio;
    char nombre[30];
    int longitud;
}LISTA;
void inicializarLista(LISTA *lista){
    lista->inicio=NULL;
    lista->longitud=0;
    return;
}
void agregarCancion(LISTA *lista,NODO *temp,int aux){
    static NODO *ultimo,*auxiliar;
    int posicion=0;
    //NODO *temp;
    //temp=(NODO *)malloc(sizeof(NODO));
    if(temp==NULL){
        printf("Problema al asignar memoria!\n");
        exit (0);
    }
    printf("\tCancion %d\n",aux);
    printf("\tTitulo:");
    scanf(" %[^\n]s",&temp->melody.titulo);
    printf("\tInterprete: ");
    scanf(" %[^\n]s",&temp->melody.cantante);
    printf("\tDuracion(mins:seg): ");
    scanf("%d:%d",&temp->melody.minutos,&temp->melody.segundos);
    printf("\tGenero: ");
    scanf(" %[^\n]s",&temp->melody.genero);
    temp->melody.posicion=aux;
    temp->sig=NULL;
    if(!lista->inicio){ //inicio ==NULL
        lista->inicio=ultimo=temp;
    }else{
        ultimo->sig=temp; //Enlazamos el antepenultimo apuntanto al ultimo
        ultimo=temp;//Actualizmos la direccion del ultimo elemento
    }
    lista->longitud++;
    return;
}
void mostrarLista(LISTA *lista){
    NODO *temp;
    temp=lista->inicio;
    int aux=1;
    printf("**** Tu playlist: %s ****\n\n",lista->nombre);
    while(temp!=NULL){
        printf("CANCION %d\n",aux);
        printf("\tTitulo: %s\n",temp->melody.titulo);
        printf("\tInterprete: %s\n",temp->melody.cantante);
        printf("\tDuracion: %d:%d \n",temp->melody.minutos,temp->melody.segundos);
        printf("\tGenero: %s\n",temp->melody.genero);
        printf("\tPosicion: %d\n",temp->melody.posicion);
        printf("\n");
        printf("-----------------------------------------------------------------\n");
        temp=temp->sig;
        aux++;
    }
    printf("**** LA LONGITUD DE TU LISTA ES DE %d CANCIONES ****\n",aux-1);
    return;
}
void obtenerDuracion(LISTA *lista){
    NODO *temp;
    temp=lista->inicio;
    int tminutos=0,tsegundos=0,thoras=0;
    int h,m,s,seg;
    while(temp!=NULL){
        tminutos=tminutos+temp->melody.minutos;
        tsegundos=tsegundos+temp->melody.segundos;
        temp=temp->sig;
    }
    s=(tminutos*60)+tsegundos;
    h=s/3600;
    s%=3600;
    m=s/60;
    seg=s%=60;
    printf("La duracion de la lista es de %d horas %d minutos %d segundos\n",h,m,seg);
}
int main(){
    char resp;
    int aux=1;
    NODO *temp,*ultimo;
    LISTA lista;
    temp=ultimo=NULL;
    inicializarLista(&lista);
    printf("**** BIENVENIDO A SPOTIFY ****\n");
    printf("Ingrese el nombre de la playlist: ");
    scanf(" %[^\n]s",&lista.nombre);
    do{
        temp=(NODO *)malloc(sizeof(CANCION));
        if(temp==NULL){
            printf("Problema al asignar memoria!\n");
            exit (0);
        }
        agregarCancion(&lista,temp,aux);
        printf("Desea agregar otra cancion? (s/n)");
        scanf(" %c",&resp);
        if(resp=='s'){
            aux++;
        }
    }while(resp=='s');
    mostrarLista(&lista);
    obtenerDuracion(&lista);
    free(temp);
    free(ultimo);
    free(lista.inicio);
    return 0;
}
