#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

#define SIZE 256

int main(){

    //open the file
    FILE *file  = fopen("input.txt", "rb");
    if(file == NULL){
        perror("Error opening file");
        return 1;
    }

    /*Part 1: Read File*/

    unsigned char *text = loadFileContent(file);

    /*Part 2: Create Frequency Tabel*/

    unsigned int *tabel = (unsigned int *) malloc(SIZE * sizeof(unsigned int));
    initializeTabel(tabel);
    fillFrequencyTabel(text, tabel);

    /*Part 3: Create Ordered List*/

    List *list = createList(list);
    fillList(tabel, list);

    /*Part 4: Create Huffman Tree*/

    Node *tree = createTree(list);
    int columns = maxDepth(tree);

    /*Part 5: Create Dictionary*/

    char **dictionary = alocateDictionary(columns);
    generateDictionary(dictionary, tree, "", columns);

    /*Part 6: Codificate*/

    char *encoded = encode(dictionary, text);
    //puts(encoded);
    
    /*Part 7: Decodificate*/
    char *decoded = decode(encoded, tree);
    //puts(decoded);

    /*Part 8: Compress*/
    compress(encoded);

    /*Part 9: Decompress*/
    decompress(tree);

    // close file
    fclose(file);

    // free alocated memory
    free(text);
    free(tabel);
    free(encoded);
    free(decoded);
    freeMatrix(dictionary, columns);
    freeTree(tree);

    return 0;
}