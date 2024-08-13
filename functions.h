#include <stdio.h>

typedef struct node Node;

typedef struct list List;

/* Alocate vector and stores the file in the vector */
unsigned char *loadFileContent(FILE *file);

/* initialize tabel with 0 */
void initializeTabel(unsigned int *tabel);

/* Fill the tabel with the frequency */
void fillFrequencyTabel(unsigned char *text, unsigned int *tab);

/*create list*/
List *createList(List *list);

/* insert elements in the list in order*/
void insertOrdered(List *list, Node *node);

/* Create node and insert in the list */
void fillList(unsigned int *tab, List *list);

/* Remove de first node of the list */
Node *removeStartNode(List *list);

/* Create Huffman tree */
Node *createTree(List *list);

/*  */
int maxDepth(Node *tree);

/*  */
char **alocateDictionary(int columns);

/*  */
void generateDictionary(char **dictionary, Node *tree, char *path, int columns);

/*   */
int stringLength(char **dictionary, unsigned char *text);

/*  */
char *codificate(char **dictionary, unsigned char *text);


void imprimeDictionary(char **dictionary);

void lst_imprime(List *lst);

void arv_imprime(Node *raiz, int tam);