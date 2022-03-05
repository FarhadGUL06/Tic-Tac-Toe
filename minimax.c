#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "structuri.h"

#define MARIME 3
#define SIZE 100

// Functii pentru implementarea arborelui de joc

// Initializarea arborelui standard
void init (Tree **nod,char table[MARIME][MARIME],int verif);
// Initializarea arborelui de joc pentru cerinta 3
void init_minimax(Tree **nod,int valoare,int nr_fii);
// Insereaza valoarea verif si matricea table in nod
void insert_element(Tree **arbore, char table[MARIME][MARIME],int verif);
// Afisarea matricelor jocurilor generate
void afisare (Tree *nod, int adancime, FILE *output);
// Afisarea valorilor T sau F pentru cerinta 2
void afisare_verif (Tree *nod, int adancime, FILE *output);
// Afisarea valorilor in adancime pentru cerinta 3
void afisare_minimax (Tree *nod, int adancime, FILE *output);
void free_arbore(Tree *arbore);

// Functii pentru implementarea cozii

void init_q(Queue **q);
int add_queue(Queue *q,Tree *val);
int pop_queue(Queue *q);

// Functii pentru efectuarea cerintelor si a operatiilor necesare

// Imi schimba jucatorul curent
void inversare_valoare(char *jucator);
// Verifica daca e joc terminat - returneaza 1 sau nu (0)
int joc_terminat(char tabla[MARIME][MARIME]);
// Verifica daca jocul s-a terminat cu victoria unui jucator specific
int joc_terminat_specific(char tabla[MARIME][MARIME],int verif);
// Functia recursiva de construire al arborelui pentru cerintele 1 si 2
int efectuare_joc(Tree **arbore,char jucator,char initial,int ex);
// Functia de setare a valorilor logice pentru cerinta 2
int verificare_victorie (Tree **nod,int adancime);
// Functia recursiva de minimax pentru cerinta 3
int minimax_joc(Tree *arbore,int adancime);

// Functii pentru specificarea cerintei de lucru
void apelare_cerinte(char argumente[],FILE *input, FILE *output);
void cerinta1(FILE *input,FILE *output);
void cerinta2(FILE *input,FILE *output);
void cerinta3(FILE *input,FILE *output);

// Implementarea functiilor

void init (Tree **nod,char table[MARIME][MARIME],int verif)
{
    int i,j;
    (*nod)=malloc(sizeof(Tree));
    for (i=0; i<MARIME; i++)
    {
        for (j=0; j<MARIME; j++)
        {
            (*nod)->tabla[i][j]=table[i][j];
        }
    }
    (*nod)->child[0]=NULL;
    (*nod)->valoare=verif;
}

void init_minimax(Tree **nod,int valoare,int nr_fii)
{
    int i;
    (*nod)=malloc(sizeof(Tree));
    // Setam in nod valoarea
    (*nod)->valoare=valoare;
    // Setam in nod numarul de fii
    (*nod)->nr_fii=nr_fii;
    for (i=0; i<SIZE; i++)
    {
        (*nod)->child[i]=NULL;
    }
}

void init_q(Queue **q)
{
    (*q)=(Queue*)malloc(sizeof(Queue));
    (*q)->head=NULL;
    (*q)->tail=NULL;
    (*q)->len=0;
}

void insert_element(Tree **arbore, char table[MARIME][MARIME],int verif)
{
    if((*arbore) == NULL)
    {
        Tree *nod;
        init(&nod,table,verif);
        *arbore=nod;
        return;
    }
    int i=0;
    while ((*arbore)->child[i]!=NULL)
    {
        i++;
    }
    Tree *nou;
    init(&nou,table,verif);
    (*arbore)->child[i]=nou;
    (*arbore)->child[i+1]=NULL;
}

int add_queue(Queue *q,Tree *val)
{
    q->len = q->len+1;
    node *nou=(node*)malloc(sizeof(node));
    if (nou==NULL)
    {
        return 0;
    }
    nou->data=val;
    if (q->len==1)
    {
        nou->next=NULL;
        q->head=nou;
        q->tail=nou;
        return 1;
    }
    q->tail->next=nou;
    q->tail=nou;
    q->tail->next=NULL;
    return 1;
}

int pop_queue(Queue *q)
{
    if(q->len==0)
    {
        return 0;
    }
    node *primul;
    q->len=q->len-1;
    primul = q->head;
    if (q->head->next!=NULL)
    {
        q->head=q->head->next;
    }
    else
    {
        q->head=NULL;
        q->tail=NULL;
    }
    free(primul);
    return 0;
}

void afisare (Tree *nod, int adancime, FILE *output)
{
    int i,j,k;
    for (i=0; i<MARIME; i++)
    {
        // Afisam tab-urile necesare
        for(k=0; k<adancime; k++)
        {
            fputc('\t',output);
        }
        // Afisam elementele matricei urmate de spatiu
        for (j=0; j<MARIME; j++)
        {
            fputc(nod->tabla[i][j],output);
            if (j!=MARIME-1)
            {
                fputc(' ',output);
            }
        }
        fputc('\n',output);
    }
    fputc('\n',output);
    i=0;
    // Cat timp avem fii, ii afisam
    while (nod->child[i]!=NULL)
    {
        afisare(nod->child[i],adancime+1,output);
        i++;
    }
}

void afisare_verif (Tree *nod, int adancime, FILE *output)
{
    int i,k;
    // Afisam tab-urile necesare
    for(k=0; k<adancime; k++)
    {
        fputc('\t',output);
    }
    // Daca valoarea este 1, afisam T
    if (nod->valoare==1)
    {
        fputc('T',output);
    }
    else
    {
        // Daca valoarea este 0, afisam F
        if (nod->valoare==0)
        {
            fputc('F',output);
        }
    }
    fputc('\n',output);
    i=0;
    // Cat timp avem fii, ii afisam
    while (nod->child[i]!=NULL)
    {
        afisare_verif(nod->child[i],adancime+1,output);
        i++;
    }
}

void afisare_minimax (Tree *nod, int adancime, FILE *output)
{
    int i,j,k;
    for(k=0; k<adancime; k++)
    {
        fputc('\t',output);
    }
    fprintf(output,"%d",nod->valoare);
    fputc('\n',output);
    i=0;
    while (nod->child[i]!=NULL)
    {
        afisare_minimax(nod->child[i],adancime+1,output);
        i++;
    }
}

void free_arbore(Tree *arbore)
{
    int i=0;
    while (arbore->child[i]!=NULL)
    {
        free_arbore(arbore->child[i]);
        i++;
    }
    free(arbore);
}

void inversare_valoare(char *jucator)
{
    // Functie care schimba din X in O si invers
    if (*jucator=='X')
    {
        *jucator='O';
    }
    else *jucator='X';
}

int joc_terminat(char tabla[MARIME][MARIME])
{
    int i,j,ok=0,ord=1;
    char curent;
    // return 1 - joc terminat , 0 - joc neterminat
    // Verificari pe orizontala
    for (i=0; i<MARIME; i++)
    {
        ord=1;
        curent=tabla[i][0];
        if (curent!='-')
        {
            for (j=1; j<MARIME; j++)
            {
                if (curent==tabla[i][j])
                {
                    ord++;
                }
            }
            if (ord==3)
            {
                return 1;
            }
        }
    }
    // Verificari pe verticala
    for (j=0; j<MARIME; j++)
    {
        ord=1;
        curent=tabla[0][j];
        if (curent!='-')
        {
            for (i=1; i<MARIME; i++)
            {
                if (curent==tabla[i][j])
                {
                    ord++;
                }
            }
            if (ord==3)
            {
                return 1;
            }
        }
    }
    // Verificari pe diagonala principala
    curent=tabla[0][0];
    if (curent!='-')
    {
        ord=1;
        for (i=1; i<MARIME; i++)
        {
            if (curent==tabla[i][i])
            {
                ord++;
            }
        }
        if (ord==3)
        {
            return 1;
        }
    }
    // Verificam pe diagonala secundara
    curent=tabla[0][MARIME-1];
    if (curent!='-')
    {
        j=1;
        ord=1;
        i=MARIME-2;
        while (i>=0)
        {
            if (curent==tabla[j][i])
            {
                ord++;
            }
            i--;
            j++;
        }
        if (ord==3)
        {
            return 1;
        }
    }
    return 0;
}

int joc_terminat_specific(char tabla[MARIME][MARIME],int verif)
{
    int i,j,ok=0,ord=1;
    char curent;
    // return 1 - joc terminat , 0 - joc neterminat
    // Verificari pe orizontala
    for (i=0; i<MARIME; i++)
    {
        ord=1;
        curent=tabla[i][0];
        if (curent==verif)
        {
            for (j=1; j<MARIME; j++)
            {
                if (curent==tabla[i][j])
                {
                    ord++;
                }
            }
            if (ord==3)
            {
                return 1;
            }
        }
    }
    // Verificari pe verticala
    for (j=0; j<MARIME; j++)
    {
        ord=1;
        curent=tabla[0][j];
        if (curent==verif)
        {
            for (i=1; i<MARIME; i++)
            {
                if (curent==tabla[i][j])
                {
                    ord++;
                }
            }
            if (ord==3)
            {
                return 1;
            }
        }
    }
    // Verificari pe diagonala principala
    curent=tabla[0][0];
    if (curent==verif)
    {
        ord=1;
        for (i=1; i<MARIME; i++)
        {
            if (curent==tabla[i][i])
            {
                ord++;
            }
        }
        if (ord==3)
        {
            return 1;
        }
    }
    // Verificam pe diagonala secundara
    curent=tabla[0][MARIME-1];
    if (curent==verif)
    {
        j=1;
        ord=1;
        i=MARIME-2;
        while (i>=0)
        {
            if (curent==tabla[j][i])
            {
                ord++;
            }
            i--;
            j++;
        }
        if (ord==3)
        {
            return 1;
        }
    }
    return 0;
}

int verificare_victorie (Tree **nod,int adancime)
{
    if ((*nod)->child[0]==NULL)
    {
        if ((*nod)->valoare==1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    int i=0,rez=0;
    while ((*nod)->child[i]!=NULL)
    {
        rez=rez+verificare_victorie(&(*nod)->child[i],adancime+1);
        i++;
    }
    // La acest nivel este necesar doar ca unul din fii sa fie true
    if (adancime%2==0)
    {
        if(rez>0)
        {
            (*nod)->valoare=1;
            return 1;
        }
        else
        {
            // Altfel parintele e false
            (*nod)->valoare=0;
            return 0;
        }
    }
    else
    {
        // La acest nivel este necesar ca toti fii sa fie true
        if (rez==i)
        {
            (*nod)->valoare=1;
            return 1;
        }
        else
        {
            // Altfel parintele e false
            (*nod)->valoare=0;
            return 0;
        }
    }
}

int efectuare_joc(Tree **arbore,char jucator,char initial,int ex)
{
    int i,j,posibile=0;
    char matrice[MARIME][MARIME];
    pozitie pozitii[100],curent;
    for (i=0; i<MARIME; i++)
    {
        for (j=0; j<MARIME; j++)
        {
            if ((*arbore)->tabla[i][j]=='-')
            {
                pozitii[posibile].coloana=j;
                pozitii[posibile].linie=i;
                pozitii[posibile].prioritate=3*i+j;
                posibile++;
            }
        }
    }
    if (posibile==0)
    {
        // Jocul s-a terminat
        return 1;
    }
    int k=0,l=0,poz=0;
    // Cat timp avem jocuri posibile pe acest nivel
    while (k<posibile)
    {
        // Stocam in matrice jocul initial
        for (i=0; i<MARIME; i++)
        {
            for (j=0; j<MARIME; j++)
            {
                matrice[i][j]=(*arbore)->tabla[i][j];
            }
        }
        curent=pozitii[poz];
        // Setam prioritatea
        for (l=0; l<posibile; l++)
        {
            if (curent.prioritate>pozitii[l].prioritate)
            {
                poz=l;
                curent=pozitii[l];
            }
        }
        pozitii[poz].prioritate=100;
        i=curent.linie;
        matrice[curent.linie][curent.coloana]=jucator;
        int rezultat,rezex2;
        // Verificam daca e un joc terminat
        rezultat=joc_terminat(matrice);
        rezex2=joc_terminat_specific(matrice,initial);
        // Inseram matricea
        insert_element(&(*arbore),matrice,rezex2);
        inversare_valoare(&jucator);
        // Daca jocul nu este terminat
        if (rezultat==0)
        {
            efectuare_joc(&(*arbore)->child[k],jucator,initial,ex);
        }
        inversare_valoare(&jucator);
        k++;
    }
}

int minimax_joc(Tree *arbore,int adancime)
{
    int i=0,a;
    if (arbore==NULL)
    {
        // Daca arborele este nul, returnam 0
        return 0;
    }
    if ((arbore->child[0]==NULL)||(arbore->nr_fii==0))
    {
        // Daca este nod frunza, returnam valoarea
        return arbore->valoare;
    }
    if (adancime%2==1)
    {
        // Daca avem de efectuat minimul, dam valoarea primului fiu
        a=arbore->child[0]->valoare;
    }
    else
    {
        // Daca avem de efectuat maximul, dam valoarea cea mai mica posibila
        a=-INT_MAX;
    }
    while (arbore->child[i]!=NULL)
    {
        // Cat timp nu am o valoare corecta in nod, apelam functia
        if (arbore->valoare==INT_MAX)
        {
            arbore->child[i]->valoare=minimax_joc(arbore->child[i],adancime+1);
        }
        if (adancime%2==0)
        {
            // Daca avem de efectuat minimul, il retin in a
            if (a<arbore->child[i]->valoare)
            {
                a=arbore->child[i]->valoare;
            }
        }
        else
        {
            // Daca avem de efectuat maximul, il retin in a
            if (a>arbore->child[i]->valoare)
            {
                a=arbore->child[i]->valoare;
            }
        }
        i++;
    }
    // Punem in nod valoarea obtinuta si o returnam
    arbore->valoare=a;
    return arbore->valoare;
}

void cerinta1(FILE *input,FILE *output)
{
    Tree *arbore;
    int i,j;
    char matrice[MARIME][MARIME],curent,spatiu;
    curent=fgetc(input);
    spatiu=fgetc(input);
    for (i=0; i<MARIME; i++)
    {
        for (j=0; j<MARIME; j++)
        {
            matrice[i][j]=fgetc(input);
            spatiu=fgetc(input);
        }
    }
    // initializam arborele cu radacina - matricea citita
    init(&arbore,matrice,0);
    // Apelam functia de efectuare joc
    efectuare_joc(&arbore,curent,curent,1);
    // Afisam matricele jocurilor rezultate
    afisare(arbore,0,output);
    free_arbore(arbore);
}

void cerinta2(FILE *input, FILE *output)
{
    Tree *arbore;
    int i,j;
    char matrice[MARIME][MARIME],curent,spatiu;
    curent=fgetc(input);
    spatiu=fgetc(input);
    // Citim elementele matricei
    for (i=0; i<MARIME; i++)
    {
        for (j=0; j<MARIME; j++)
        {
            matrice[i][j]=fgetc(input);
            spatiu=fgetc(input);
        }
    }
    init(&arbore,matrice,0);
    efectuare_joc(&arbore,curent,curent,2);
    verificare_victorie(&arbore,0);
    // Afisam elementul corespunzator fiecarei matrici de joc (T sau F)
    afisare_verif(arbore,0,output);
    free_arbore(arbore);
}

void cerinta3(FILE *input, FILE *output)
{
    Tree *arbore;
    // Initializam o coada in care sa pastrez radacinile subarborilor
    Queue *coada;
    init_q(&coada);
    int adancime=0,inaltime,lungime,k=0,ord,i;
    char newline;
    // Citim inaltimea arborelui
    fscanf(input,"%d",&inaltime);
    int tip,nr_noduri=0,valoare=0,j;
    Tree *nod;
    // Initializam nodul root cu valoare maxima
    init_minimax(&arbore,INT_MAX,nr_noduri);
    nod=arbore;
    // Adaugam in coada elementul
    add_queue(coada,nod);
    for (i=0; i<=inaltime; i++)
    {
        // Citesc prima paranteza
        newline=fgetc(input);
        while (newline!='\n')
        {
            // Daca este paranteza deschisa, avem nod intern cu fii
            if (newline=='(')
            {
                // Citim numarul de fii
                fscanf(input,"%d",&nr_noduri);
                // Punem o valoare maxima in nod
                valoare=INT_MAX;
                // tip=0 -> nod intern
                tip=0;
            }
            else
            {
                // Este paranteza inchisa deci este nod frunza
                // Citim valoarea din frunza
                fscanf(input,"%d",&valoare);
                nr_noduri=0;
                // tip=1 -> nod frunza
                tip=1;
            }
            // Extragem primul nod parinte din coada
            nod=coada->head->data;
            // Ii adaugam cati fii are
            nod->nr_fii=nr_noduri;
            // Il extragem din coada
            pop_queue(coada);
            // Daca avem nod frunza
            if (tip==1)
            {
                //Ii punem valoarea
                nod->valoare=valoare;
                nod->nr_fii=0;
            }
            else
            {
                // Daca este nod intern
                for (j=0; j<nr_noduri; j++)
                {
                    // Initializez cate noduri interne am nevoie
                    init_minimax(&nod->child[j],valoare,nr_noduri);
                    // Adaug in coada de radacini de subarbori
                    add_queue(coada,nod->child[j]);
                }
            }
            // Citim 2 char-uri (paranteza inchisa si spatiu sau endline)
            newline=fgetc(input);
            newline=fgetc(input);
            /* Daca intalnim endline, s-a terminat randul
            si citim urmatoarea paranteza */
            if (newline!='\n')
            {
                newline=fgetc(input);
            }
        }
    }
    // Apelam algoritmul minimax
    minimax_joc(arbore,0);
    afisare_minimax(arbore,0,output);
    // Eliberam memoria alocata
    free_arbore(arbore);
    free(coada);
}

void apelare_cerinte(char argumente[],FILE *input, FILE *output)
{
    if (!strcmp(argumente,"-c1"))
    {
        // Daca argumentul 1 este c1, efectuam cerinta 1
        cerinta1(input,output);
    }
    if (!strcmp(argumente,"-c2"))
    {
        // Daca argumentul 1 este c2, efectuam cerinta 2
        cerinta2(input,output);
    }
    if (!strcmp(argumente,"-c3"))
    {
        // Daca argumentul 1 este c3, efectuam cerinta 3
        cerinta3(input,output);
    }
}

int main(int argc, char *argv[])
{
    FILE *input,*output;
    input=fopen(argv[2],"r");
    output=fopen(argv[3],"w");
    apelare_cerinte(argv[1],input,output);
    fclose(input);
    fclose(output);
    return 0;
}
