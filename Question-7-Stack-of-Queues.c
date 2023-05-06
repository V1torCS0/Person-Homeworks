#include <stdio.h>
#include <stdlib.h>

typedef struct node{

    int value;
    struct node * ndNext;
}Node;

typedef struct queue{
    
    int size;
    Node * head;
    Node * tail;
    struct queue * qeNext;
}Queue;

typedef struct mainstk{

    int size;
    Queue * topMain;
}MainStack;

Node * createNode(int value){

    Node * auxNode = malloc(sizeof(Node));

    auxNode -> value = value;
    auxNode -> ndNext = NULL;
    return auxNode;
}

Queue * createQueue(void){

    Queue * auxQueue = malloc(sizeof(Queue));

    auxQueue -> head = NULL;
    auxQueue -> tail = NULL;
    auxQueue -> qeNext = NULL;
    auxQueue -> size = 0;
    return auxQueue;
}

MainStack * createMain(void){

    MainStack * auxMain = malloc(sizeof(MainStack));

    auxMain -> size = 0;
    auxMain -> topMain = NULL;
    return auxMain;
}

//funções da fila
void enqueue(Queue * auxQueue, int newValue){

    Node * newNode = createNode(newValue);

    if (auxQueue -> head == NULL){

        auxQueue -> head = newNode;
        auxQueue -> tail = newNode;
    }else{

        auxQueue -> tail -> ndNext = newNode;
        auxQueue -> tail = newNode;
    }
    auxQueue -> size++;
}

int dequeue(Queue * auxQueue){

    int valueReturned = -1;
    if (auxQueue -> size != 0){

        Node * garbage = auxQueue -> head;
        valueReturned = garbage -> value;
        auxQueue -> head = auxQueue -> head -> ndNext;

        free(garbage);
        auxQueue -> size--;
    }
    return valueReturned;
}

void printQueue(Queue * auxQueue){

    Node * auxPrint = auxQueue -> head;

    printf("|Head -> ");
    while (auxPrint != NULL){
        
        printf("%d ", auxPrint -> value);
        auxPrint = auxPrint -> ndNext;
    }
    printf("<- Tail <=> Size: %d|", auxQueue -> size);
}

//funções da pilha main

void pushMain(MainStack * auxMain, Queue * auxQueue){

    auxQueue -> qeNext = auxMain -> topMain;
    auxMain -> topMain = auxQueue;
    auxMain -> size++;
}

void popMain(MainStack * auxMain){

    if (auxMain -> topMain != NULL){

        Queue * qeGarbage = auxMain -> topMain;
        Node * ndReturned = auxMain -> topMain -> head;
        auxMain -> topMain = auxMain -> topMain -> qeNext;
        
        printf("Removed Elements: ( ");
        while (ndReturned != NULL){
            
            printf("%d ", ndReturned -> value);
            ndReturned = ndReturned -> ndNext;
        }
        printf(")\n");
        
        free(qeGarbage);
        auxMain -> size--;
    }else{ printf("Empty Stack\n");}
}

void printMain(MainStack * auxMain){

    Queue * auxPrint = auxMain -> topMain;

    printf("\nTop ->(");
    while (auxPrint != NULL){

        printQueue(auxPrint);
        auxPrint = auxPrint -> qeNext;
    }
    printf(")<- Base <=> Size: %d\n", auxMain -> size);
}

int main(){

    Queue * fila = createQueue();
    Queue * fila2 = createQueue();
    MainStack * pilha = createMain();

    enqueue(fila, 2);
    enqueue(fila, 6);
    enqueue(fila2, 9);
    enqueue(fila2, 23);
    dequeue(fila);

    pushMain(pilha, fila);
    pushMain(pilha, fila2);
    printMain(pilha);
    popMain(pilha);
    printMain(pilha);
    return 0;
}