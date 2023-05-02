#include <stdio.h>
#include <stdlib.h>

typedef struct node{

    int token;
    struct node * next;
}Node;

typedef struct queue{
    
    struct node * head;
    struct node * tail;
    int size;
}priorityQueue;

Node * initNode(int token){

    Node * auxNd = malloc(sizeof(Node));
    auxNd -> token = token;
    auxNd -> next = NULL;

    return auxNd;
}

priorityQueue * initQueue(void){

    priorityQueue * auxQueue = malloc(sizeof(priorityQueue));
    auxQueue -> tail = NULL;
    auxQueue -> head = NULL;
    auxQueue -> size = 0;

    return auxQueue;
}

void enqueue(priorityQueue * auxQueue, int newValue){

    Node * newNode = initNode(newValue);

    if (auxQueue -> head == NULL){
        
        auxQueue -> head = newNode;
        auxQueue -> tail = newNode;
    }else if ((auxQueue -> head -> token) < (newNode -> token)){

        newNode -> next = auxQueue -> head;
        auxQueue -> head = newNode;
    }else if ((auxQueue -> tail -> token) > (newNode -> token)){

        auxQueue -> tail -> next = newNode;
        auxQueue -> tail = newNode;
    }else{

        Node * auxSearch = auxQueue -> head;

        while (auxSearch -> next -> token > newNode -> token){
            auxSearch = auxSearch -> next;
        }

        newNode -> next = auxSearch ->next;
        auxSearch -> next = newNode;
    }
    auxQueue -> size++;
}

int dequeue(priorityQueue * auxQueue){

    if (auxQueue -> size != 0){

        Node * garbage = auxQueue -> head;
        auxQueue -> head = auxQueue -> head -> next;

        int returnValue = garbage -> token;
        free(garbage);
        auxQueue -> size--;
        return returnValue;
    }else{
        return -1;
    }
}

void printQueue(priorityQueue * auxQueue){

    Node * auxPrint = auxQueue -> head;

    printf("Head -> ");
    while (auxPrint != NULL){

        printf("%d ", auxPrint -> token);
        auxPrint = auxPrint -> next;
    }
    printf("<- Tail <=> Size: %d\n", auxQueue -> size);
}

int main(void){

    priorityQueue * queue = initQueue();

    enqueue(queue, 10);
    enqueue(queue, 30);
    enqueue(queue, 20);
    enqueue(queue, 50);
    enqueue(queue, 15);
    enqueue(queue, 25);

    printQueue(queue);
    dequeue(queue);
    dequeue(queue);

    printQueue(queue);

    return 0;
}