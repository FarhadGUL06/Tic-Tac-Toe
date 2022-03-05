// Structuri pentru arbore
typedef struct Tree
{
    char tabla[3][3];
    int valoare;
    int nr_fii;
    struct Tree* child[100];
} Tree;

// Structuri pentru prioritate
typedef struct pozitie
{
    int linie;
    int coloana;
    int prioritate;
} pozitie;

// Structuri pentru coada
typedef struct Queue
{
    struct node *head, *tail;
    int len;
} Queue;

typedef struct node
{
    // tip = 0 - nod intern , 1 - frunza
    Tree *data;
    int tip;
    struct node *next;
} node;
