#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node{

    float operand;
    struct node * bottom;
}Node;

typedef struct stk{

    Node * top;
    int size;
}Stack;

Stack * initCalc(void){

    Stack * auxStk = malloc(sizeof(Stack));
    auxStk -> top = NULL;
    auxStk -> size = 0;

    return auxStk;
}

void pushCalc(Stack * auxStk, float value){

    Node * newNode = malloc(sizeof(Node));
    newNode -> operand = value;
    newNode -> bottom = NULL;

    if (auxStk -> top == NULL){
        auxStk -> top = newNode;
    }else{

        newNode -> bottom = auxStk -> top;
        auxStk -> top = newNode;
    }
    auxStk -> size++;
}

int popCalc(Stack * auxStk){

    Node * garbage = auxStk -> top;
    float value = 0;

    if (auxStk -> top != NULL){

        value = auxStk -> top -> operand;
        auxStk -> top = auxStk -> top -> bottom;
    }

    free(garbage);
    auxStk -> size--;
    return value;
}

void printStkCalc(Stack * auxStk){

    Node * auxPrint = auxStk -> top;

    printf("Topo -> ");
    while (auxPrint != NULL){

        printf("%.2f ", auxPrint -> operand);
        auxPrint = auxPrint -> bottom;
    }
    printf("<- Base\nTamanho: %d\n", auxStk -> size);
}


int main(void){

    Stack * operandStk = initCalc();

    char inputUser[20];

    printf("Adicione uma entrada: ");
    fgets(inputUser, 20, stdin);

    for (int i = 0; inputUser[i] != '\0'; i++){

        if (isdigit(inputUser[i])){

            float operand = atof(&inputUser[i]);
            pushCalc(operandStk, operand);

            while (isdigit(inputUser[i])){
                i++;
            }
            i--;
        }else if (isspace(inputUser[i])){
            continue;
        }else{

            float operandOne = popCalc(operandStk), operandTwo = popCalc(operandStk);
            float result;

            switch (inputUser[i]){

                case '+': result = operandTwo + operandOne; break;
                case '-': result = operandTwo - operandOne; break;
                case '*': result = operandTwo * operandOne; break;
                case '/': result = operandTwo / operandOne; break;
                
                default: printf("Expressao que nao consta.\n"); exit(1);
            }
            pushCalc(operandStk, result);
        }
    }

    float resultExpression = popCalc(operandStk);

    if (operandStk -> top != NULL) { 
        printf("Sentenca numerica nao formulada corretamente.\n");
        exit(1);    
    }else{ printf("RESULTADO = %.2f\n", resultExpression); exit(0); }
}