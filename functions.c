#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

#define SIZE 256

struct node{
    unsigned char character;
    int frequency;
    struct node *left, *right, *next;
};

struct list{
    Node *start;
    int size;
};

unsigned char *loadFileContent(FILE *file){
//move pointer to end of file
    fseek(file, 0, SEEK_END);

    //size of file
    long filesize = ftell(file);

    //return pointer to beginning of file
    rewind(file);

    //allocate memory to the vector
    unsigned char *text = (unsigned char *)malloc((filesize + 1) * sizeof(unsigned char)); // +1 for null character
    if(text == NULL){
        perror("Error alocating memory");
        fclose(file);
        exit(1);
    }

    //read content of file and stores in vector
    size_t bytesRead = fread(text, 1, filesize, file);
    if (bytesRead != filesize) {
        perror("Erro ao ler o arquivo");
        free(text);
        fclose(file);
        exit(1);
    }

    // Add null character at the end of vector
    text[filesize] = '\0';
    return text;
}

void initializeTabel(unsigned int *tabel){
    for(int i = 0; i < SIZE; i++){
        tabel[i] = 0; //initialize the frequency with 0
    }
}

void fillFrequencyTabel(unsigned char *text, unsigned int *tabel){
    int i = 0;
    while(text[i] != '\0'){
        tabel[text[i]]++; //fill the tabel in the correct position of ASCII Table
        i++;
    }
}

List *createList(List *list){
    list = (List *) malloc(sizeof(List));
    if(list == NULL){
        perror("Error alocating memory");
        exit(1);
    }
    list->start = NULL;
    list->size = 0;
    return list;
}

void insertOrdered(List *list, Node *node){
    // empty list
    if(list->start == NULL){
        list->start = node;
    }
    // frequency lower than the beginning of the list
    else if(node->frequency < list->start->frequency){
        node->next = list->start;
        list->start = node;
    }
    else{
        Node *aux = list->start;
        while(aux->next && aux->next->frequency <= node->frequency){
            aux = aux->next;
        }
        node->next = aux->next;
        aux->next = node;
    }
    list->size++;
}

void fillList(unsigned int *tab, List *list){
    for(int i = 0; i < SIZE; i++){
        if(tab[i] > 0){
            Node *new = (Node *) malloc(sizeof(Node));
            if(new == NULL){
                perror("Error alocating memory");
                exit(1);
            }
            new->character = i;
            new->frequency = tab[i];
            new->left = NULL;
            new->right = NULL;
            new->next = NULL;
            //insert in order
            insertOrdered(list, new);
        }
    }
}

Node *removeStartNode(List *list){
    Node *aux = NULL;

    if(list->start != NULL){
        aux = list->start;
        list->start = aux->next;
        aux->next = NULL;
        list->size--;
    }

    return aux;
}

Node *createTree(List *list){
    Node *first, *second, *new;
    while(list->size > 1){
        first = removeStartNode(list);
        second = removeStartNode(list);
        new = (Node *) malloc(sizeof(Node));
        if(new == NULL){
            perror("Error alocating memory");
            exit(1);
        }

        new->character = '+';
        new->frequency = first->frequency + second->frequency;
        new->left = first;
        new->right = second;
        new->next = NULL;
        insertOrdered(list, new);
    }
    return list->start;
}

int maxDepth(Node *tree){
    if(tree == NULL){
        return -1;
    }

    else{
        int lDepth = maxDepth(tree->left);
        int rDepth = maxDepth(tree->right);
        if(lDepth > rDepth){
            return (lDepth+1);
        }
        else{
            return (rDepth+1);
        }
    }
}

char **alocateDictionary(int columns){
    char **dictionary = (char **) malloc(SIZE * sizeof(char *));
    if(dictionary == NULL){
            perror("Error alocating memory");
            exit(1);
    }
    for(int i = 0; i < SIZE; i++){
        dictionary[i] = calloc(columns, sizeof(char));
        if(dictionary[i] == NULL){
            perror("Error alocating memory");
            exit(1);
        }
    }
    return dictionary;
}

void generateDictionary(char **dictionary, Node *tree, char *path, int columns){
    char left[columns], right[columns];
    
    if(tree->left == NULL && tree->right == NULL){
        strcpy(dictionary[tree->character], path);
    }
    else{
        strcpy(left, path);
        strcpy(right, path);

        strcat(left, "0");
        strcat(right, "1");

        generateDictionary(dictionary, tree->left, left, columns);
        generateDictionary(dictionary, tree->right, right, columns);
    }
}

int stringLength(char **dictionary, unsigned char *text){
    int length = 0;
    for(int i = 0; text[i] != '\0'; i++){
        length = length + strlen(dictionary[text[i]]);
    }
    return length+1;
}

char *codificate(char **dictionary, unsigned char *text){
    int lenght = stringLength(dictionary, text);

    char *code = calloc(lenght, sizeof(char));
    for(int i = 0; text[i] != '\0'; i++){
        strcat(code, dictionary[text[i]]);
    } 
    return code;
}

// void imprimeDictionary(char **dictionary){
//     for(int i = 0; i < SIZE; i++){
//         printf("%3d: %s\n ", i, dictionary[i]);
//     }
// }

// void lst_imprime(List *lst){
//     Node *p;
//     printf("tamanho lista: %d\n", lst->size);
//     for(p = lst->start; p != NULL; p = p->next)
//         printf("info = %d  character=%c\n", p->frequency, p->character);
// }

// void arv_imprime(Node *raiz, int tam){
//     if(raiz->left == NULL && raiz->right == NULL){
//         printf("Folha : %c | Altura : %d\n", raiz->character, tam);
//     }
//     else{
//         arv_imprime(raiz->left, tam+1);
//         arv_imprime(raiz->right, tam+1);
//     }
// }