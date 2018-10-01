#include <stdio.h>
#include <stdlib.h>

#include "solve24.h"

int main(int argc, char* argv[])
{
    int tks[4],manual=1;
    char pa[4],answer[8];
    if(argc==5)
    {
        manual=0;
        for(int i=0;i<4;i++) tks[i]=atoi(argv[i+1]);
    }
    if(manual)
    {
        puts("Please input the numbers (1--31), split with spaces.");
        scanf("%d %d %d %d", tks, tks+1, tks+2, tks+3);
    }
    for(int i=0;i<4;i++) (tks[i]>0&&tks[i]<32)?
        (pa[i]=(char)tks[i]):(puts("Invalid input!"),exit(1));
    printf("Inputs: %d, %d, %d, %d\n",tks[0],tks[1],tks[2],tks[3]);
    if((manual=tryout(answer, pa)))
    {
        char hum[20];
        puts(output(hum,answer,manual));
    }
    else puts("No solution!");
    return 0;
}
