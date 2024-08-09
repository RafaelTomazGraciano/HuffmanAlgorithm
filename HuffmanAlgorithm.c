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

    unsigned char *text;
    loadFileContent(file, text);

    printf("Content of file:\n%s", text);

    // close file
    fclose(file);

    // free alocated memory
    free(text);

    return 0;
}