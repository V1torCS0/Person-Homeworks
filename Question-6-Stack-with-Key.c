#include <stdlib.h>
#include <stdio.h>

typedef struct node{

    int value;
    int _id;
    struct node * next;
}idNode;

typedef struct{

    int size;
   idNode * topStk;
}idStack;

idStack * initStk(void){//função de inicializa uma pilha

    idStack * auxStk = malloc(sizeof(idStack));
    auxStk -> topStk = NULL;
    auxStk -> size = 0;

    return auxStk;
}

idNode * initNd(int value, int keyC){//função que inicializa um no

    idNode * auxNd = malloc(sizeof(idNode));
    auxNd -> value = value;
    auxNd -> _id = keyC;
    auxNd -> next = NULL;

    return auxNd;
}

void pushId(idStack * auxStk, int value, int key){

    idNode * newNode = initNd(value, key);
    
    newNode -> next = auxStk -> topStk;
    auxStk -> topStk = newNode;
    auxStk -> size++;    
}

/*
int pop(Stack * auxStk){

    Node * garbage = auxStk -> top;
    int value = 0;

    if (auxStk -> top != NULL){

        value = auxStk -> top -> weight;
        auxStk -> top = auxStk -> top -> bottom;
    }

    free(garbage);
    auxStk -> size--;
    return value;
}
*/

void printStk(idStack * auxStk){//função que imprime a pilha passada por parâmetro

    idNode * auxPrint = auxStk -> topStk;

    printf("\nTopo -> ");
    while (auxPrint != NULL){

        printf("{ _id: %d Valor: %d } ", auxPrint -> _id, auxPrint -> value);
        auxPrint = auxPrint -> next;
    }
    printf("<- Base <=> Tamanho: %d\n", auxStk -> size);
}


int main(){

    idStack * pilhaA = initStk();

    pushId(pilhaA, 29, 1);
    pushId(pilhaA, 15, 2);
    pushId(pilhaA, 30, 0);

    printStk(pilhaA);
    
    return 0;
}