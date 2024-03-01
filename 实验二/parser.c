#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#define StateNum 32
#define N 100

char str[N];
int S[N], topS;
char B[N], topB;
int po;
int len;

/*
(0) E' --> E
(1) E --> E+F 
(2) E --> E-F 
(3) E --> F
(4) F --> F*G 
(5) F --> F/G 
(6) F --> G
(7) G --> H 
(8) G --> (E)
(9) H --> a
*/

int rightSize[10] = {1,3,3,1,3,3,1,1,3,1};  //length of the right part of the production
char leftB[10] = {'E','E','E','E','F','F','F','G','G','H'};

//S +
//R -
//+-*/()a$
int ACTION[StateNum][8] =
{   {0,0,0,0,5,0,6,0},
    {7,8,0,0,0,0,0,100}, 
    {-3,-3,9,10,0,0,0,-3}, 
    {-6,-6,-6,-6,0,0,0,-6},
    {-7,-7,-7,-7,0,0,0,-7}, 
    {0,0,0,0,15,0,16,-9},
    {-9,-9,-9,-9,0,0,0,-9}, 
    {0,0,0,0,5,0,6,0},
    {0,0,0,0,5,0,6,0},
    {0,0,0,0,5,0,6,0},
    {0,0,0,0,5,0,6,0},
    {22,23,0,0,0,21,0,0},
    {-3,-3,24,25,0,-3,0,0},
    {-6,-6,-6,-6,0,-6,0,0},
    {-7,-7,-7,-7,0,-7,0,0},
    {0,0,0,0,15,0,16,0},
    {-9,-9,-9,-9,0,-9,0,0},
    {-1,-1,9,10,0,0,0,-1},
    {-2,-2,9,10,0,0,0,-2},
    {-4,-4,-4,-4,0,0,0,-4},
    {-5,-5,-5,-5,0,0,0,-5},
    {-8,-8,-8,-8,0,0,0,-8},
    {0,0,0,0,15,0,16,0},
    {0,0,0,0,15,0,16,0},
    {0,0,0,0,15,0,16,0},
    {0,0,0,0,15,0,16,0},
    {22,23,0,0,0,31,0,0},
    {-1,-1,24,25,0,-1,0,0},
    {-2,-2,24,25,0,-2,0,0},
    {-4,-4,-4,-4,0,-4,0,0},
    {-5,-5,-5,-5,0,-5,0,0},
    {-8,-8,-8,-8,0,-8,0,0} };

//EFGH
int GOTO[StateNum][4] = 
{  {1,2,3,4},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {11,12,13,14},
    {0,0,0,0},
    {0,17,3,4},
    {0,18,3,4},
    {0,0,19,4},
    {0,0,20,4},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {26,12,13,14},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,27,13,14},
    {0,28,13,14},
    {0,0,29,14},
    {0,0,30,14},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
   };

void init() {
    str[len++] = '$';
    topS = 0;
    topB = 0;
    po = 0;
    S[topS++] = 0;
    B[topB++] = '$';
}

void prt() {
    printf("=> ");
    for (int i = 1; i < topS; ++i) {
        printf("%c", B[i]);
    }
    for (int i = po; i < len-1; i++) {
        printf("%c", str[i]);
    }
    printf("\n");
}

int changeToNum(char c) {
    switch (c) {
    case('E'):
        return 0;
        break;
    case('F'):
        return 1;
        break;
    case('G'):
        return 2;
        break;
    case('H'):
        return 3;
        break;
    case('+'):
        return 0;
        break;
    case('-'):
        return 1;
        break;
    case('*'):
        return 2;
        break;
    case('/'):
        return 3;
        break;
    case('('):
        return 4;
        break;
    case(')'):
        return 5;
        break;
    case('a'):
        return 6;
        break;
    case('$'):
        return 7;
        break;
    }
}

void scaner() {
    while (1) {
        int act = ACTION[S[topS - 1]][changeToNum(str[po])];
        if (act == 100) {
            printf("Success!\n");
            break;
        }
        if (act > 0) {  //Shift
            S[topS++] = act;
            B[topB++] = str[po];
            po++;
        }
        else if (act < 0) {  //Reduce
            act = -act;
            for(int k = 0; k < rightSize[act]; ++k) {
                topS--;
                topB--;  
            }
            B[topB++] = leftB[act];
            int state = GOTO[S[topS-1]][changeToNum(leftB[act])];
            S[topS++] = state;
            prt();
        }
        else {
            printf("Error!\n");
            break;
        }
    }
}

//LR(1)
int main(){
    freopen("input.txt", "r", stdin);
    freopen("result.txt", "w", stdout);
    //printf("Please input an expression which contains {+,-,*,/,(,),a} :\n");
    scanf("%s", str);
    len = strlen(str);
    init();
    scaner();
    fclose(stdin);
    fclose(stdout);
    return 0;
}