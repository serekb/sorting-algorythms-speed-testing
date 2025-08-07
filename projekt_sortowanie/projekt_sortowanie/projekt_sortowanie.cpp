#include "Sort.h"
#include <memory.h>
#include <time.h>
#include <stdlib.h>

#define PARAMNO 2
#define MAXNUM 30
#define IS_TEST
#define NEWLINE 10

void initTab( int pTab[], int nSize );
void printTab( int pTab[], int nSize );
int createTab( int**, int );

typedef void (*pFunType)(int* pTab, int nSize);

int main( int argc, char* argv[] )
{
    //sprawdzic parametry
    if(argc != PARAMNO)
    {
        printf("Usage: %s <tab_size> <file_name>", argv[0]);
        return -1;
    }
    void (*pSortTab[])(int*, int) = { bubbleSort, simpleSelectionSort , simpleInsertionSort , mixedSort , quickSort , binaryInsertion , heapSort};
    const char* nameTab[] = {"bubbleSort", "simpleSelectionSort", "simpleInsertionSort",
        "mixedSort", "quickSort", "binaryInsertion", "heapSort"};

    //obliczyc rozmiar tablicy
    int nSize = atoi(argv[1]);
    //alokacja tablicy wzorcowej i jej zainicjowanie (funkje)
    int* pTab = NULL; 
    if( !createTab( &pTab, nSize ) )
    {
        printf("Memory allocation error!!\n");//w projekcie bêd¹ 2 tablice do zdefiniowania
        return -2;
    }
    initTab( pTab, nSize );
    // wydruk na warunkowej kompil
#ifdef IS_TEST
    printTab(pTab, (nSize > MAXNUM) ? MAXNUM : nSize);
#endif
    //----------odczytac czasy poszczegolnych sortowan

    // alokacja pamieci na tabl do sortow
    int* pTabCpy = NULL;// wskaznik musi byc zainicjowany
    if( !createTab( &pTabCpy, nSize ) )
    {
        printf("Memory allocation error!!\n");//w projekcie bêd¹ 2 tablice do zdefiniowania
        return -2;
    }
    // obliczyc rozmiar tablicy adresoww funkcji
    int pSortTabSize = sizeof(pSortTab)/sizeof(void*);

  //TO W PETLI for
    //clock_t czas;
    for(int i = 0; i < pSortTabSize; i++)
    {
        // wkopiowanie do niej tabl wzorcowej
        memcpy( pTabCpy, pTab, nSize*sizeof(int) );
        // -- odczytac czas  clock()
        clock_t czas = clock();
        // -- posortowac
        pSortTab[i](pTabCpy, nSize);
        // -- odczytac czas i wypisac czas sortowania (wzor w helpach), wypisac nazwe sortowania
        czas = clock() - czas;
        printf("%s: %lf sekund\n", nameTab[i], (double)czas /CLOCKS_PER_SEC );
        // -- na warunkowej kompilacji wydruk posortowanej
#ifdef IS_TEST
        printTab(pTabCpy, (nSize > MAXNUM)? MAXNUM : nSize );
        printf( "\n" );
#endif
    }
    // zwolnic pamiec
        free( pTab );
        free( pTabCpy );
    return 0;
}

void initTab(int pTab[], int nSize)
{
    srand((unsigned int)time(NULL));
    for(int i = 0; i < nSize; i++)
        pTab[i] = rand() % nSize;
}

void printTab(int pTab[], int nSize)
{
    for(int i = 0; i < nSize; i++)
    {
        printf("%d ", pTab[i]);
        if((i + 1) % NEWLINE == 0)
            printf("\n");
    }
}

int createTab(int** pTab, int nSize)
{
    *pTab = (int*)malloc(nSize * sizeof(int));
    if(!*pTab) // if(*pTab == NULL)
        return 0; // nie powiodlo sie
    // wyzerowac tablice
    // dla ZEROWANIA NIGDY NIE U¯YWAÆ PÊTLI FOR
    memset(*pTab, 0, nSize * sizeof(int));
    return 1; // jest okej
}


