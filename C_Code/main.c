#include<stdio.h>
#include"generic/GenericBlocks.h"
#include "vienna.h"


void main()
{


    vienna_initialize();

    for(int i=0; i<=5; i++)
    {
    vienna_calc();
    }


}