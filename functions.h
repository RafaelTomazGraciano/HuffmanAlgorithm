#include <stdio.h>

typedef struct node Node;

typedef struct list List;

/*------------------------Part 1: Read File------------------------*/

// Alocate vector and stores the file in the vector 
unsigned char *loadFileContent(FILE *file);

/*------------------------Part 2: Create Frequency Tabel------------------------*/

// Initialize tabel with 0 
void initializeTabel(unsigned int *tabel);

// Fill the tabel with the frequency 
void fillFrequencyTabel(unsigned char *text, unsigned int *tab);

/*------------------------Part 3: Create Ordered List------------------------*/

// Create list
List *createList(List *list);

// insert elements in the list in order
void insertOrdered(List *list, Node *node);

// Create node and insert in the list 
void fillList(unsigned int *tab, List *list);

/*------------------------Part 4: Create Huffman Tree------------------------*/

//Remove de first node of the list 
Node *removeStartNode(List *list);

// Create Huffman tree 
Node *createTree(List *list);

// Calculate the maximum depth of the tree
int maxDepth(Node *tree);

/*------------------------Part 5: Create Dictionary------------------------*/

// Alocate memory for the dictionary
char **alocateDictionary(int columns);

// Generate the Dictionary
void generateDictionary(char **dictionary, Node *tree, char *path, int columns);

/*------------------------Part 6: Codificate------------------------*/

// Calculate the length of the Dictionary
int stringLength(char **dictionary, unsigned char *text);

// Encode the text with the correct string legth
char *encode(char **dictionary, unsigned char *text);

/*------------------------Part 7: Decodificate------------------------*/

// Decode the text
char *decode(char *code, Node *tree);

/*------------------------Part 8: Compress------------------------*/

// Cmpress the file
void compress(char *code);

/*------------------------Part 9: Decompress------------------------*/

// Return if the bit is 1 or not
unsigned int bit1(unsigned char byte, int i);

// Decompress the file
void decompress(Node *tree);

/*------------------------Part 10: Free Memory------------------------*/

//Free memory for the matrix
void freeMatrix(char **matrix, int columns);

//Free memory for the tree
void freeTree(Node *tree);
