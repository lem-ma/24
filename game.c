#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "solve24.h"

int main(int argc, char *argv[])
{
    int m,mod;
    if(argc==1||(mod=atoi(argv[1]))>31||mod<3) mod=13;
    char ind,c=0,pa[4],answer[8],hum[20];
    srand(time(NULL));
    while(c!=EOF)
    {
        fputs("Initializing...",stdout);
        do for(int i=0;i<4;i++) pa[i]=(rand()%mod)+1;
        while(!(m=solve24_tryout(answer, pa)));
        printf("\rPuzzle: %hhd, %hhd, %hhd, %hhd\nPress <Enter> to"
                " reveal the answer.",pa[0],pa[1],pa[2],pa[3]);
        clock_t start=clock();
        while((c=getchar())!='\n'&&c!='\r'&&c!=EOF);
        double dt=(double)(clock()-start)/CLOCKS_PER_SEC;
        puts(solve24_output(hum,answer,m));
        printf("Time used: %.3lf seconds.\nPress <Enter> to start a new"
                " puzzle, or <Ctrl-Z><Enter> to end the game.\n",dt);
        while((c=getchar())!='\n'&&c!='\r'&&c!=EOF);
    }
    return 0;
}
