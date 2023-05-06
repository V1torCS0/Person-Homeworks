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

typedef struct mainqe{

    int size;
    Queue * headMain;
    Queue * tailMain;
}MainQueue;

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

MainQueue * createMain(void){

    MainQueue * auxMain = malloc(sizeof(MainQueue));

    auxMain -> headMain = NULL;
    auxMain -> tailMain = NULL;
    auxMain -> size = 0;
    return auxMain;
}

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

void enqueueMain(MainQueue * auxMain, Queue * auxQueue){

    if (auxMain -> headMain == NULL){

        auxMain -> headMain = auxQueue;
        auxMain -> tailMain = auxQueue;
    }else{

        auxMain -> tailMain -> qeNext = auxQueue;
        auxMain -> tailMain = auxQueue;
    }
    auxMain -> size++;
}

void dequeueMain(MainQueue * auxMain){

    if (auxMain -> size != 0){

        Queue * qeGarbage = auxMain -> headMain;
        Node * ndReturned = auxMain -> headMain -> head;
        auxMain -> headMain = auxMain -> headMain -> qeNext;

        printf("Removed Elements: ( ");
        while (ndReturned != NULL){
            
            printf("%d ", ndReturned -> value);
            ndReturned = ndReturned -> ndNext;
        }
        printf(")\n");

        free(qeGarbage);
        auxMain -> size--;        
    }else{ printf("Empty Queue\n");}
}

void printMain(MainQueue * auxMain){

    Queue * auxPrint = auxMain -> headMain;

    printf("\nHead ->(");
    while (auxPrint != NULL){

        printQueue(auxPrint);
        auxPrint = auxPrint -> qeNext;
    }
    printf(")<- Tail <=> Size: %d\n", auxMain -> size);
}

int main(){

    Queue * fila1 = createQueue();
    Queue * fila2 = createQueue();
    MainQueue * master = createMain();

    enqueue(fila1, 9);
    enqueue(fila2, 7);
    enqueue(fila1, 28);
    enqueue(fila2, 62);
    enqueue(fila1, 23);
    enqueue(fila2, 15);
    dequeue(fila1);
    dequeue(fila2);

    enqueueMain(master, fila1);
    enqueueMain(master, fila2);
    dequeueMain(master);
    dequeueMain(master);
    dequeueMain(master);

    printMain(master);
    
    return 0;
}