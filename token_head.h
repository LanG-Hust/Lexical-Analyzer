#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

//#define true 1
//#define false 0
//#define bool int
#define MAX 120
#define N 17

typedef struct NODE 
{
    char *ptoken;
    int cnt;
    struct NODE *pnext;
}node;

char gtoken[40] = {0};
char gtype[30] = {0};
int gtypecode = 0;
int grow = 0;
int gcol = 0;
int gcnt = 0;
int gorder = 1;
FILE *fin = NULL;
FILE *fout = NULL;
char *in_file = "exp.c";

const char *gtype_array[] = { "keywords", "identifier", "operator", "separator"};
const char *gkeyws_array[] = {"int", "char", "float", "double", "bool", "struct", "for", "return", "while", "do", "switch", "break", "default", "continue", "true", "false", "typedef"};

int state = 0; // 注释要换行，必须是全局变量

void initial();
bool sep_or_ope(char *token);
// true : keyword false: identifier
bool ident_or_key(char *token);
// true : not a '\n' false : reach '\n'
bool token_analyze(char *line);
void counter(const char* token, node *phead);
