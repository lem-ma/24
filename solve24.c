/* Library for solving the 24 game
 * Author: lem-ma (@Github)
 */
#include <string.h>
#include <stdio.h>

#include "solve24.h"

char* output(char *dest, char *answ, int mode)
{
    /*                  0   1   2   3   4   5   6
     * ((a b) (c d))    d   c   op  b   a   op  op
     * (((a b) c) d)    d   c   b   a   op  op  op
     * ((a (b c)) d)    d   c   b   op  a   op  op
     * (a ((b c) d))    d   c   b   op  op  a   op
     * (a (b (c d)))    d   c   op  b   op  a   op
     * that's all!
     */
    switch(mode)
    {
        case 1:
            sprintf(dest,"(%hhd%c%hhd)%c(%hhd%c%hhd)",
                    answ[4],answ[5],answ[3],answ[6]
                    ,answ[1],answ[2],answ[0]);
            break;
        case 2:
            sprintf(dest,"((%hhd%c%hhd)%c%hhd)%c%hhd",
                    answ[3],answ[4],answ[2],answ[5]
                    ,answ[1],answ[6],answ[0]);
            break;
        case 3:
            sprintf(dest,"(%hhd%c(%hhd%c%hhd))%c%hhd",
                    answ[4],answ[5],answ[2],answ[3]
                    ,answ[1],answ[6],answ[0]);
            break;
        case 4:
            sprintf(dest,"%hhd%c((%hhd%c%hhd)%c%hhd)",
                    answ[5],answ[6],answ[2],answ[3]
                    ,answ[1],answ[4],answ[0]);
            break;
        case 5:
            sprintf(dest,"%hhd%c(%hhd%c(%hhd%c%hhd))",
                    answ[5],answ[6],answ[3],answ[4]
                    ,answ[1],answ[2],answ[0]);
            break;
    }
    return dest;
}

/*Sometimes static inline is not working properly, so use macro*/
#define solve24_checkorreturn(x) \
for(int level=0,l=0;config[l];l++)\
{\
    if(config[l]<32) tower[level++]=(float)config[l];\
    else if(config[l]=='+')\
        tower[level-2]=tower[level-1]+tower[level-2],level--;\
    else if(config[l]=='-')\
        tower[level-2]=tower[level-1]-tower[level-2],level--;\
    else if(config[l]=='*')\
        tower[level-2]=tower[level-1]*tower[level-2],level--;\
    else if(config[l]=='/')\
        tower[level-2]=tower[level-1]/tower[level-2],level--;\
}\
if(*tower==24.0f)\
{\
    strcpy(dest,config);\
    return (x);\
}

int tryout(char *dest, char *token)
{
    /*
     * ((a b) (c d))    d   c   op  b   a   op  op
     * (((a b) c) d)    d   c   b   a   op  op  op
     * ((a (b c)) d)    d   c   b   op  a   op  op
     * (a ((b c) d))    d   c   b   op  op  a   op
     * (a (b (c d)))    d   c   op  b   op  a   op
     * that's all!
     * only for <32 integers
     */
    int cases[24][4]={
        {0,1,2,3},{0,1,3,2},{0,2,1,3},{0,2,3,1},{0,3,1,2},{0,3,2,1},
        {1,0,2,3},{1,0,3,2},{1,2,0,3},{1,2,3,0},{1,3,0,2},{1,3,2,0},
        {2,0,1,3},{2,0,3,1},{2,1,0,3},{2,1,3,0},{2,3,0,1},{2,3,1,0},
        {3,0,1,2},{3,0,2,1},{3,1,0,2},{3,1,2,0},{3,2,0,1},{3,2,1,0},
    };
    char ops[]="+-*/";
    char config[8];
    config[7]='\0';
    float tower[4];
    for(int take=0;take<24;take++)
    {
        config[0]=token[cases[take][3]];
        config[1]=token[cases[take][2]];
        for(int i=0;ops[i];i++)
        {
            for(int j=0;ops[j];j++)
            {
                for(int k=0;ops[k];k++)
                {
                    config[6]=ops[k];
                    config[2]=ops[i];
                    config[3]=token[cases[take][1]];
                    config[4]=token[cases[take][0]];
                    config[5]=ops[j];
                    solve24_checkorreturn(1);
                    config[2]=token[cases[take][1]];
                    config[3]=token[cases[take][0]];
                    config[4]=ops[i];
                    //config[5]=ops[j];
                    solve24_checkorreturn(2);
                    //config[2]=token[cases[take][1]];
                    config[3]=ops[i];
                    config[4]=token[cases[take][0]];
                    //config[5]=ops[j];
                    solve24_checkorreturn(3);
                    //config[2]=token[cases[take][1]];
                    //config[3]=ops[i];
                    config[4]=ops[j];
                    config[5]=token[cases[take][0]];
                    solve24_checkorreturn(4);
                    config[2]=ops[i];
                    config[3]=token[cases[take][1]];
                    //config[4]=ops[j];
                    //config[5]=token[cases[take][0]];
                    solve24_checkorreturn(5);
                }
            }
        }
    }
    return 0;
}
