#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

void loadFileContent(FILE *file, unsigned char *text){
//move pointer to end of file
    fseek(file, 0, SEEK_END);

    //size of file
    long filesize = ftell(file);

    //return pointer to beginning of file
    rewind(file);

    //allocate memory to the vector
    char *text = (char *) malloc(filesize + 1 *sizeof (char)); // +1 for null character
    if(text == NULL){
        perror("Error alocating memory");
        fclose(file);
        return 1;
    }

    //read content of file and stores in vector
    size_t bytesRead = fread(text, 1, filesize, file);
    if (bytesRead != filesize) {
        perror("Erro ao ler o arquivo");
        free(text);
        fclose(file);
        return 1;
    }

    // Add null character at the end of vector
    text[filesize] = '\0';
}