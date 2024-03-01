#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#define keyNum 34

char* key[keyNum] = { "auto","break","case","char","class","const", "continue","default","do",
                             "double","else","enum","extern","float","for","goto","if","int","long",
                             "main","register","return","short","signed","sizeof","static","struct",
                             "switch","typedef","union","unsigned","void","volate","while" };

char lexeme[100];
int sz = 0;

void prt(char* tp, char* innerCode) {
    lexeme[sz] = '\0';
    printf("(%s,%s,%s)\n", lexeme, tp, innerCode);
    sz = 0;
}

int isKey() {
    int k = 0;
    lexeme[sz] = '\0';
    for (int i = 0; i < keyNum; ++i) {
        if (!strcmp(lexeme, key[i])) {
            printf("(%s,%s,", lexeme, "keyword");
            for (int k = 0; k < strlen(key[i]); ++k) {
                printf("%c",toupper(key[i][k]));
            }
            printf(")\n");
            sz = 0;
            return 1;
        }
    }
    return 0;
}

void scaner() {
    char ch;
    int state = 0;
    while (1) {
        switch (state) {
        case 0:
            ch = getchar();
            if (ch == ' ' || ch == '\n' || ch=='\0' || ch=='\t') {
                state = 0;
            }
            else if (ch >= 'a' && ch <= 'z') {
                state = 1;
                lexeme[sz++] = ch;
            }
            else if (ch >= '0' && ch <= '9') {  /////////////////////
                state = 2;
                lexeme[sz++] = ch;
            }
            //else if (ch == '0') {  
                //state = 3;
                //lexeme[sz++] = ch;
            //}
            else if (ch == '+') {
                state = 6;
                lexeme[sz++] = ch;
            }
            else if (ch == '-') {
                state = 7;
                lexeme[sz++] = ch;
            }
            else if (ch == '*') {
                state = 8;
                lexeme[sz++] = ch;
            }
            else if (ch == '/') {
                state = 9;
                lexeme[sz++] = ch;
            }
            else if (ch == '<') {
                state = 10;
                lexeme[sz++] = ch;
            }
            else if (ch == '>') {
                state = 11;
                lexeme[sz++] = ch;
            }
            else if (ch == '=') {
                state = 12;
                lexeme[sz++] = ch;
            }
            else if (ch == '!') {
                state = 13;
                lexeme[sz++] = ch;
            }
            else if (ch == ',') {
                state = 14;
                lexeme[sz++] = ch;
            }
            else if (ch == ';') {
                state = 15;
                lexeme[sz++] = ch;
            }
            else if (ch == '(') {
                state = 16;
                lexeme[sz++] = ch;
            }
            else if (ch == ')') {
                state = 17;
                lexeme[sz++] = ch;
            }
            else if (ch == '{') {
                state = 18;
                lexeme[sz++] = ch;
            }
            else if (ch == '}') {
                state = 19;
                lexeme[sz++] = ch;
            }
            else if (ch==EOF) {
                printf("Successfully Done!\n");
                return 0;
            }
            else {
                //error
                state = 99;
            }
            break;
        case 1:
            ch = getchar();
            if ((ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9')) {
                state = 1;
                lexeme[sz++] = ch;
            }
            else {
                ungetc(ch, stdin); //backward
                if (!isKey()) prt("id","ID");
                state = 0;
            }
            break;
        case 2:
            //dec
            ch = getchar();
            if (ch >= '0' && ch <= '9') {
                state = 2;
                lexeme[sz++] = ch;
            }
            else if (ch=='.') {
                state = 4;
                lexeme[sz++] = ch;
            }
            else {
                ungetc(ch, stdin); //backward
                //num
                prt("number","INT");
                state = 0;
            }
            break;
        case 4:
            //float
            ch = getchar();
            if (ch >= '0' && ch <= '9') {
                state = 5;
                lexeme[sz++] = ch;
            }
            else {
                //error
                state = 99;
            }
            break;
        case 5:
            //float
            ch = getchar();
            if (ch >= '0' && ch <= '9') {
                state = 5;
                lexeme[sz++] = ch;
            }
            else {
                ungetc(ch, stdin); //backward
                //float
                prt("float","FLOAT");
                state = 0;
            }
            break;
        case 6:
            //+
            prt("operator","ADD");
            state = 0;
            break;
        case 7:
            //-
            prt("operator","MINUS");
            state = 0;
            break;
        case 8:
            //*
            prt("operator","MULTI");
            state = 0;
            break;
        case 9:
            // /
            prt("operator","DIVEDE");
            state = 0;
            break;
        case 10:
            ch = getchar();
            if (ch == '=') {
                state = 20;
                lexeme[sz++] = ch;
            }
            else {
                ungetc(ch, stdin); //backward
                //<
                prt("relation","LT");
                state = 0;
            }  
            break;
        case 11:
            ch = getchar();
            if (ch == '=') {
                state = 21;
                lexeme[sz++] = ch;
            }
            else {
                ungetc(ch, stdin); //backward
                //>
                prt("relation","GT");
                state = 0;
            }
            break;
        case 12:
            ch = getchar();
            if (ch == '=') {
                state = 22;
                lexeme[sz++] = ch;
            }
            else {
                ungetc(ch, stdin); //backward
                //=
                prt("assignment","ASS");
                state = 0;
            }
            break;
        case 13:
            ch = getchar();
            if (ch == '=') {
                state = 23;
                lexeme[sz++] = ch;
            }
            else {
                state = 99;
            }
            break;
        case 14:
            //,
            prt("separator","COMMA");
            state = 0;
            break;
        case 15:
            //;
            prt("separator","SEMICOLON");
            state = 0;
            break;
        case 16:
            //(
            prt("separator","LP");  ///eft parenthesis
            state = 0;
            break;
        case 17:
            //)
            prt("separator","RP");
            state = 0;
            break;
        case 18:
            //{
            prt("separator","LB");  //left brace
            state = 0;
            break;
        case 19:
            //}
            prt("separator","RB");
            state = 0;
            break;
        case 20:
            //<=
            prt("relation","LE");
            state = 0;
            break;
        case 21:
            //>=
            prt("relation","GE");
            state = 0;
            break;
        case 22:
            //==
            prt("relation","EQ");
            state = 0;
            break;
        case 23:
            //!=
            prt("relation","NEQ");
            state = 0;
            break;
        case 99:
            printf("Error!\n");
            return 0;
            break;
        }
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("result.txt", "w", stdout); 
    scaner();
    fclose(stdin);
    fclose(stdout);
    return 0;
}