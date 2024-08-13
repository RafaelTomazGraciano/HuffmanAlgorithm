#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

#define SIZE 256

int main(){

    //define name of file
    const char *filename = "text.txt";

    FILE *file  = fopen(filename, "rb");
    if(file == NULL){
        perror("Error opening file");
        return 1;
    }

    unsigned char *text = loadFileContent(file);

    unsigned int *tabel = (unsigned int *) malloc(SIZE * sizeof(unsigned int));

    initializeTabel(tabel);
    fillFrequencyTabel(text, tabel);

    List *list = createList(list);
    fillList(tabel, list);

    Node *tree = createTree(list);

    int columns = maxDepth(tree);
    char **dictionary = alocateDictionary(columns);
    generateDictionary(dictionary, tree, "", columns);

    char *code = codificate(dictionary, text);
    printf("\n Codigo: %s", code);
    //imprimeDictionary(dictionary);

    // lst_imprime(list);
    // printf("\nArvore");
    // arv_imprime(tree, 0);

    // close file
    fclose(file);

    // free alocated memory
    free(text);
    free(tabel);

    return 0;
}