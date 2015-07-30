#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define MAX 120
#define LEN_KWD 17
#define LEN_SEP 3

typedef struct NODE 
{
    char *ps;
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
char gfile[30] = {0};

const char *gtype_array[] = { "关键字", "标识符", "运算符", "分隔符", "整型常量     ", "浮点型常量", "字符常量     ", "字符串文字"};
const char *gkeyws_array[] =
{
    "int", "char", "float", "double", "struct", "for",
    "while", "do", "switch", "break", 
    "continue", "typedef", "if", "else", 
    "case", "enum", "register", "extern", "return", "union",
    "const", "short", "unsigned", "signed", "void", "default",
    "goto", "sizeof", "volatile", "static", "auto", "long"
};
const char *gsep_array[] = {";", "{", "}" };

int state = 0; // 注释要换行，必须是全局变量

void initial(int argc, char *file);
// true : operator    false : separator
bool sep_or_ope(char *token);
// true : keyword false: identifier
bool ident_or_key(char *token);
bool isnothing(char *token);

// true : not a '\n' false : reach '\n'
bool token_analyze(char *line);
void counter(const char* token, node **phead);
node *new_node();
