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

void pushId(idStack * auxStk, int value, int key){//empilha elemento

    idNode * newNode = initNd(value, key);
    
    newNode -> next = auxStk -> topStk;
    auxStk -> topStk = newNode;
    auxStk -> size++;    
}

int popId(idStack * auxStk){//desempilha elemento

    idNode * garbage = auxStk -> topStk;
    int value = -1;

    if (auxStk -> topStk != NULL){

        value = auxStk -> topStk -> value;
        auxStk -> topStk = auxStk -> topStk -> next;
    }

    free(garbage);
    auxStk -> size--;
    return value;
}

void printStk(idStack * auxStk){//função que imprime a pilha passada por parâmetro

    idNode * auxPrint = auxStk -> topStk;

    printf("\nTop -> ");
    while (auxPrint != NULL){

        printf("{ _id: %d Value: %d } ", auxPrint -> _id, auxPrint -> value);
        auxPrint = auxPrint -> next;
    }
    printf("<- Base <=> Size: %d\n", auxStk -> size);
}


int main(){

    idStack * stackMain = initStk();
    idStack * stackAux = initStk();
    int addCall, rmCall, cont;

    printf("\nDigite quantas chamadas vao ser feitas: ");
    scanf("%d", &addCall); cont = 0;

    printf("\nAdicao de elementos:\nDigite o valor e a sua respectiva chave:\n");

    do{

        int valueUser, keyUser;
        scanf("%d", &valueUser);
        scanf("%d", &keyUser); 

        pushId(stackMain, valueUser, keyUser);
        cont++;
    }while (cont < addCall);

    printf("\nESTADO DA PILHA:\n");
    printStk(stackMain);

    printf("\nDigite quantas remocoes vao ser feitas: \n");
    scanf("%d", &rmCall); cont = 0;

    if (rmCall > addCall){
         printf("\nEssa operacao nao eh possível.\n");
         exit(1);
    }else{

        printf("\nRemocao de elementos\nDigite a chave para remocao:\n");

        while (cont < rmCall){    

            int keyRemove;
            scanf("%d", &keyRemove);

            while (stackMain -> size != 0 && stackMain -> topStk -> _id != keyRemove){
        
                pushId(stackAux, stackMain -> topStk -> value, stackMain -> topStk -> _id);
                popId(stackMain);
            }
            printf("\nA chave %d converge com o valor removido, %d\n", keyRemove, popId(stackMain));

            while (stackAux -> topStk != NULL){

                pushId(stackMain, stackAux -> topStk -> value, stackAux -> topStk -> _id);
                popId(stackAux);
            }

            printf("\nESTADO DA PILHA:\n");
            printStk(stackMain);

            cont++;
        }
    }

    return 0;
}