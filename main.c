#include <stdio.h>
#include <stdlib.h>

#include "solve24.h"

int main(int argc, char *argv[])
{
    int manual=1;
    char pa[4],answer[8],hum[20];
    if(argc>4)
    {
        manual=0;
        for(int i=0;i<4;i++) if((pa[i]=atoi(argv[i+1]))>31||pa[i]<1)
            puts("Invalid input!"),exit(0);
    }
    if(manual)
    {
        puts("Please input the numbers (1--31), split with spaces.");
        scanf("%hhd %hhd %hhd %hhd", pa, pa+1, pa+2, pa+3);
        for(int i=0;i<4;i++)
            if(pa[i]<1||pa[i]>31) puts("Invalid input!"),exit(1);
    }
    printf("Inputs: %hhd, %hhd, %hhd, %hhd\n",pa[0],pa[1],pa[2],pa[3]);
    if((manual=solve24_tryout(answer, pa)))
        puts(solve24_output(hum,answer,manual));
    else puts("No solution!");
    return 0;
}
