#include "Sort.h"
#include <memory.h>
#include <time.h>
#include <stdlib.h>
void update( int l, int r, int t[] );
void sort( int l, int r, int t[] );

void bubbleSort( int t[], int nSize )
{
    for( int i = 1; i < nSize; i++ )
    {
        for( int j = nSize - 1; j >= i; j-- )
            if( t[j] < t[j - 1] ) // warunek zamiany
            {
                int temp = t[j];
                t[j] = t[j - 1];
                t[j - 1] = temp;
            }
    }
}

void simpleSelectionSort( int t[], int nSize )
{
    for( int i = 0; i < nSize - 1; i++ )
    {
        int min = t[i];
        int ix_min = i;
        for( int j = i + 1; j < nSize; j++ )
            if( t[j] < min )
            {
                min = t[j];
                ix_min = j;
            }
        t[ix_min] = t[i];
        t[i] = min;
    }
}

void simpleInsertionSort( int t[], int nSize )
{
    for( int i = 0; i < nSize; i++ )
    {
        int x = t[i];
        int j = i - 1;
        while( j >= 0 && t[j] > x )
        {
            t[j + 1] = t[j--];
        }
        t[j + 1] = x;
    }
}

void mixedSort( int t[], int nSize )
{
    int l = 1;
    int k = nSize-1;
    int p = nSize-1;
    do {
        for( int j = p; j >= l; j-- )
            if( t[j - 1] > t[j] )
            {
                int x = t[j - 1];
                t[j - 1] = t[j];
                t[j] = x;
                k = j;
            }  
        l = k + 1;
        for( int j = l; j <= p; j++ )
            if( t[j - 1] > t[j] )
            {
                int x = t[j-1];
                t[j-1] = t[j];
                t[j] = x;
                k = j;
            }
        p = k-1;
    } while( l<p );
}

void quickSort( int t[], int nSize ) //strona 79
{
    sort( 0, nSize-1, t );
}

void sort( int l, int r, int t[] )
{
    int i = l;
    int j = r;
    int x = t[(l + r) / 2];
    int w;
    do {
        while( t[i] < x )
            i++;
        while( x < t[j] )
            j--;
        if( i <= j )
        {
            w = t[i];
            t[i] = t[j];
            t[j] = w;
            i++;
            j--;
        }
    } while(  i <= j );
    if( l < j )
        sort( l, j, t );
    if(i < r)
        sort( i, r, t );
    return;
}

void heapSort( int t[], int nSize )
{
    int l = nSize/ 2 - 1;
    int r = nSize - 1;
    for( ; l>=0; l-- )
    {
        update( l, r, t );
    } 
    for( ; r > 0 ; r-- ) 
    {
        int x = t[0];
        t[0] = t[r];
        t[r] = x;
        update( 0, r-1, t );
    }
    // indeks i, 2i+1, 2i+2 // do polowy tablicy
    //void update (t[], l, p)// czy l>=p return
    //2 petle for od œrodka nSize/2-1
    //jak skonczysz to na odwrot?
}

void binaryInsertion( int t[], int nSize )
{
    for( int i = 1; i <= nSize - 1; i++ )
    {
        int x = t[i];
        int l = 0;
        int r = i-1;
        while( l <= r )
        {
            int m=(l+r)/2;
            if( x<t[m] )
                r=m-1;
            else
                l=m+1;
        }
        for( int j = i - 1; j >= l; j-- )
            t[j+1] = t[j];
        t[l] = x;
    }
}

void update( int l,int r, int t[] )
{
    int i = l;
    int j = 2*i + 1;
    int x = t[i];
    while( j <= r ) {
        if( j < r )
        {
            if( t[j] < t[j + 1] )
                j++;
        }
        if( x >= t[j] )
            break;
        t[i] = t[j];
        i = j;
        j = 2 * i + 1;
    }
    t[i] = x;
}
