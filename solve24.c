/* Library for solving the 24 game
 * Author: lem-ma (@Github)
 * Version 1.0
 */

#include <string.h>
#include <stdio.h>

#include "solve24.h"

char* solve24_output(char *dest, char *answ, int mode)
{
    /*                  0   1   2   3   4   5   6
     * ((a b) (c d))    d   c   op  b   a   op  op
     * (((a b) c) d)    d   c   b   a   op  op  op
     * ((a (b c)) d)    d   c   b   op  a   op  op
     * (a ((b c) d))    d   c   b   op  op  a   op
     * (a (b (c d)))    d   c   op  b   op  a   op
     * that's all!
     * need 20 bytes allocated to dest
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

static inline int yield24(char *config)
{
    int temp,den[4],num[4];
    for(int level=0;*config;config++)
    {
        if(*config<32) num[level]=(*config),den[level]=1,level++;
        else if(*config=='+')
        {
            num[level-2]*=den[level-1];
            num[level-2]+=num[level-1]*den[level-2];
            den[level-2]*=den[level-1];
            level--;
        }
        else if(*config=='-')
        {
            num[level-2]*=(-den[level-1]);
            num[level-2]+=num[level-1]*den[level-2];
            den[level-2]*=den[level-1];
            level--;
        }
        else if(*config=='*')
        {
            num[level-2]*=num[level-1];
            den[level-2]*=den[level-1];
            level--;
        }
        else if(*config=='/')
        {
            temp=num[level-2];
            num[level-2]=den[level-2]*num[level-1];
            den[level-2]=temp*den[level-1];
            level--;
        }
    }
    if((*den==0)||(*num)%(*den)) return 0;
    else return (*num)/(*den)==24;
}

int solve24_tryout(char *dest, char *token)
{
    /*
     * ((a b) (c d))    d   c   op  b   a   op  op
     * (((a b) c) d)    d   c   b   a   op  op  op
     * ((a (b c)) d)    d   c   b   op  a   op  op
     * (a ((b c) d))    d   c   b   op  op  a   op
     * (a (b (c d)))    d   c   op  b   op  a   op
     * that's all!
     * only for <32 integers
     * need 8 bytes allocated to dest
     */
    int cases[24][4]={
        {0,1,2,3},{0,1,3,2},{0,2,1,3},{0,2,3,1},{0,3,1,2},{0,3,2,1},
        {1,0,2,3},{1,0,3,2},{1,2,0,3},{1,2,3,0},{1,3,0,2},{1,3,2,0},
        {2,0,1,3},{2,0,3,1},{2,1,0,3},{2,1,3,0},{2,3,0,1},{2,3,1,0},
        {3,0,1,2},{3,0,2,1},{3,1,0,2},{3,1,2,0},{3,2,0,1},{3,2,1,0}
    };
    char ops[]="+-*/";
    char config[8];
    config[7]='\0';
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
                    if(yield24(config))
                    {
                        strcpy(dest,config);
                        return 1;
                    }
                    config[2]=token[cases[take][1]];
                    config[3]=token[cases[take][0]];
                    config[4]=ops[i];
                    //config[5]=ops[j];
                    if(yield24(config))
                    {
                        strcpy(dest,config);
                        return 2;
                    }
                    //config[2]=token[cases[take][1]];
                    config[3]=ops[i];
                    config[4]=token[cases[take][0]];
                    //config[5]=ops[j];
                    if(yield24(config))
                    {
                        strcpy(dest,config);
                        return 3;
                    }
                    //config[2]=token[cases[take][1]];
                    //config[3]=ops[i];
                    config[4]=ops[j];
                    config[5]=token[cases[take][0]];
                    if(yield24(config))
                    {
                        strcpy(dest,config);
                        return 4;
                    }
                    config[2]=ops[i];
                    config[3]=token[cases[take][1]];
                    //config[4]=ops[j];
                    //config[5]=token[cases[take][0]];
                    if(yield24(config))
                    {
                        strcpy(dest,config);
                        return 5;
                    }
                }
            }
        }
    }
    return 0;
}
