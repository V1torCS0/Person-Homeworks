#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int isVowel (char str){

    if (str == 'a' || str == 'e' 
    || str == 'i' || str == 'o'
    || str == 'u' || str == 'A'
    || str == 'E' || str == 'I'
    || str == 'O' || str == 'U'){ return 1; }

    return 0;
}

typedef struct node{

    char consonant;
    struct node * bottom;
}Node;

typedef struct stk{

    Node * top;
    int size;
}Stack;

Stack * init(void){

    Stack * auxStk = malloc(sizeof(Stack));
    auxStk -> top = NULL;
    auxStk -> size = 0;

    return auxStk;
}

void pushChar(Stack * auxStk, char letter){

    Node * newNode = malloc(sizeof(Node));
    newNode -> consonant = letter;
    newNode -> bottom = NULL;

    if (auxStk -> top == NULL){
        auxStk -> top = newNode;
    }else{

        newNode -> bottom = auxStk -> top;
        auxStk -> top = newNode;
    }
    auxStk -> size++;
}

char popChar(Stack * auxStk){

    Node * garbage = auxStk -> top;
    char character = ' ';

    if (auxStk -> top != NULL){

        character = auxStk -> top -> consonant;
        auxStk -> top = auxStk -> top -> bottom;
    }

    free(garbage);
    auxStk -> size--;
    return character;
}

int main() {

    char inputUser[100];
    Stack * charStk = init();
    int j = 0;

    printf("Digite uma expressao para ser criptografada: ");
    fgets(inputUser, 100, stdin);

    while (inputUser[j] != '\0'){    

        if (isalpha(inputUser[j]) && !(isVowel(inputUser[j]))){
            pushChar(charStk, inputUser[j]);
        }else{

            while (charStk -> size != 0){
                printf("%c", popChar(charStk));
            }
            printf("%c", inputUser[j]);
        }
        j++;
    }

    return 0;
}