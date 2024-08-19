#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

#define SIZE 256

//Define the structs

struct node{
    unsigned char character;
    int frequency;
    struct node *left, *right, *next;
};

struct list{
    Node *start;
    int size;
};

/*------------------------Part 1: Read File------------------------*/

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
        perror("Error reading file");
        free(text);
        fclose(file);
        exit(1);
    }

    // Add null character at the end of vector
    text[filesize] = '\0';
    return text;
}

/*------------------------Part 2: Create Frequency Tabel------------------------*/

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

/*------------------------Part 3: Create Ordered List------------------------*/

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

/*------------------------Part 4: Create Huffman Tree------------------------*/

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

/*------------------------Part 5: Create Dictionary------------------------*/

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

/*------------------------Part 6: Codificate------------------------*/

int stringLength(char **dictionary, unsigned char *text){
    int length = 0;
    for(int i = 0; text[i] != '\0'; i++){
        length = length + strlen(dictionary[text[i]]);
    }
    return length+1;
}

char *encode(char **dictionary, unsigned char *text){
    int lenght = stringLength(dictionary, text);

    char *encode = calloc(lenght, sizeof(char));
    for(int i = 0; text[i] != '\0'; i++){
        strcat(encode, dictionary[text[i]]);
    } 
    return encode;
}

/*------------------------Part 7: Decodificate------------------------*/

char *decode(char *code, Node *tree){
    Node *aux = tree;
    char *decode = calloc(strlen(code), sizeof(char));
    char temp[2];

    for(int i = 0; code[i] != '\0'; i++){
        if(code[i] == '0'){
            aux = aux->left;
        }
        else{
            aux = aux->right;
        }
        if(aux->left == NULL && aux->right == NULL){
            temp[0] = aux->character; //make it a string
            temp[1] = '\0';
            strcat(decode, temp);
            aux = tree;
        }
    }
    return decode;
}

/*------------------------Part 8: Compress------------------------*/

void compress(char *code){
    FILE *file = fopen("compressed.huff", "wb");
    if(file == NULL){
        perror("Error creating file");
        exit(1);
    }

    int j = 7;
    unsigned char mask, byte = 0; //00000000

    for(int i = 0; code[i] != '\0'; i++){
        mask = 1;
        if(code[i] == '1'){
            mask = mask << j; //shift the bits
            byte = byte | mask; // OR operation
        }
        j--;

        if(j < 0){ // byte formed
            fwrite(&byte, sizeof(unsigned char), 1, file);
            byte = 0;
            j = 7;
        }
    }
    if(j != 7){// byte left
        fwrite(&byte, sizeof(unsigned char), 1, file);
    }
    fclose(file);
}

/*------------------------Part 9: Decompress------------------------*/

unsigned int bit1(unsigned char byte, int i){
    unsigned char mask = (1 << i); //shif the bits
    return byte & mask; //AND operation
}

void decompress(Node *tree){
    FILE *file = fopen("compressed.huff", "rb"); //compressed file
    if(file == NULL){
        perror("Error reading file");
        exit(1);
    }

    FILE *output = fopen("output.txt", "w");  // output file 
    if (output == NULL) {
        perror("Error creating file");
        exit(1);
    }

    Node *aux = tree;
    unsigned char byte;

    while(fread(&byte, sizeof(unsigned char), 1, file)){
        for(int i = 7; i >= 0; i--){
            if(bit1(byte, i)){
                aux = aux->right;
            }
            else{
                aux = aux->left;
            }

            if(aux->left == NULL && aux->right == NULL){
                fputc(aux->character, output);
                aux = tree;
            }
        }
    }
    fclose(file);
    fclose(output);
}

/*------------------------Part 10: Free Memory------------------------*/

void freeMatrix(char **matrix, int columns){
    for (int i = 0; i < columns; i++) {
        free(matrix[i]);  // Free each row
    }
    free(matrix);  // Free the array of row pointers
}

void freeTree(Node *tree) {
    if (tree == NULL) {
        return;
    }

    // Recursivamente libera as subárvores esquerda e direita
    freeTree(tree->left);
    freeTree(tree->right);
    
    // Libera o nó atual
    free(tree);
}