#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "solve24.h"

int main(int argc, char *argv[])
{
    int m;
    char ind,c=0,pa[4],answer[8],hum[20];
    clock_t start;
    double dt;
    srand(time(NULL));
    while(c!=EOF)
    {
        do for(int i=0;i<4;i++) pa[i]=(rand()%13)+1;
        while(!(m=tryout(answer, pa)));
        printf("Puzzle: %hhd, %hhd, %hhd, %hhd\nPress <Enter> to"
                " reveal the answer.",pa[0],pa[1],pa[2],pa[3]);
        start=clock();
        while((c=getchar())!='\n'&&c!='\r'&&c!=EOF);
        dt=(double)(clock()-start)/CLOCKS_PER_SEC;
        puts(output(hum,answer,m));
        printf("Time used: %.3lf seconds.\nPress <Enter> to start a new"
                " puzzle, or <Ctrl-Z><Enter> to end the game.\n",dt);
        while((c=getchar())!='\n'&&c!='\r'&&c!=EOF);
    }
    return 0;
}
