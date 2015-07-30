#include "token_head.h"

int main(int argc, char *argv[])
{
    initial(argc, argv[1]);
    char line_buf[120] = {0};

    // the following are the heads of lists
    node *pid_kw = NULL;
    node *pint_flt = NULL;
    node *pchar = NULL;
    node *pstr = NULL;
    node *psgn = NULL;

    int row = 0;
    
    while(!feof(fin))
    {
        fgets(line_buf, MAX, fin);
        row++;
        grow = row;
//        printf("%s\n",line_buf);
        while(token_analyze(line_buf) == true) // token_analyze() 分析出词，词性（以code形式），列数
        {
//            printf("check: %s", gtoken);
            // 判断是标识符还是关键字, 在gtype内写下token类型
            if(gtypecode == 1)
            {
               if(ident_or_key(gtoken) == true)
               {
                    strcpy(gtype, gtype_array[0]);

                   
               }
               else
               {
                    strcpy(gtype, gtype_array[1]);
               }
            }
            else if(gtypecode == 2)
                strcpy(gtype, gtype_array[4]);
            else if(gtypecode == 3)
                strcpy(gtype, gtype_array[5]);

            else if(gtypecode == 4)
                strcpy(gtype, gtype_array[6]);
            else if(gtypecode == 5)
                strcpy(gtype, gtype_array[7]);
            else if(gtypecode == 6)
            {
                strcpy(gtype, gtype_array[3]);
//                if(sep_or_ope(gtoken) == true)
//                {
//                    strcpy(gtype, gtype_array[2]);
//
//                }
//                else
//                {
//                    strcpy(gtype, gtype_array[3]);
//                }
            }
            else if(gtypecode == 7)
            {
                strcpy(gtype, gtype_array[2]);
            } 



            switch(gtypecode)
            {
                case 1:
                    counter(gtoken, &pid_kw);
                    break;

                case 2: 
                case 3:
                    counter(gtoken, &pint_flt);
                    break;

                case 4:
                    counter(gtoken, &pchar);
                    break;

                case 5:
                    counter(gtoken, &pstr);
                    break;

                case 6: case 7:
                    counter(gtoken, &psgn);
                    break;
            }
            if(gtypecode != -1 && !isnothing(gtoken))
            { 
                fprintf(fout,"\t%-8d%-16s%-25s%-7d%-6d%-6d\n", 
                       gorder, gtype, gtoken, grow, gcol, gcnt);
                gorder++;
            }
        }
//        printf("check | gtoken:%s", gtoken);
//        write_file();
    }
    return 0;
}

void counter(const char *token, node **pphd)
{
    node *ptemp = NULL;
//    char buf[50] = {0};
    int flag = 0;
    node *phead = *pphd;

    for(ptemp = phead; ptemp != NULL; ptemp = ptemp->pnext)
    {
        if(gtypecode != 2 && gtypecode != 3)
        {
            if( 0 == strcmp(token, ptemp->ps))
            {
                flag = 1;
                break;
            }
        }
        else 
        {
            if(atof(token) == atof(ptemp->ps))
            {
                flag = 1;
                break;
            }
        }
    }
    if(flag == 0)
    {
        ptemp = new_node();
        ptemp->pnext = phead;
        phead = ptemp;
        int len = strlen(token);
        ptemp->ps = malloc(sizeof(len + 1));
        strcpy(ptemp->ps, token);
    }
    else
    {
        ptemp->cnt ++;
    }
    gcnt = ptemp->cnt;    
    *pphd = phead;
    return ;
}

// true : operator    false : separator
bool sep_or_ope(char *token)
{
   int i = 0;
   for(i = 0; i < LEN_SEP ; i++)
   {
       if(strcmp(gsep_array[i], token) == 0) // if 2 strings are identical, the STRCMP() return 0;
           return false;
   }
   return true;
    
}

bool ident_or_key(char * token)
{
   int i = 0;
   for(i = 0; i < LEN_KWD ; i++)
   {
//       printf("check: %s\t%s\n",gkeyws_array[i], token);
       if(strcmp(gkeyws_array[i], token) == 0) // if 2 strings are identical, the STRCMP() return 0;
           return true;
   }
   return false;
}

node *new_node()
{
    node *ptemp = malloc(sizeof(node));
    ptemp->cnt = 1;
   ptemp->pnext = NULL;
   return ptemp;
}

void initial(int argc, char *file)
{
    // check the parameters
    if(argc != 2)
    {
        printf("Error: Please enter 2 parameters\n");
        exit(-1);
    }
    else
    {
        strcpy(gfile, file);
    }
    
    // prepare the file
    if((fin = fopen(gfile, "r")) == NULL)
    {
        printf("Error: unable to open the %s\n", in_file);
        exit(-2);
    }
    // get the fout file name
    int i = 0;
    char out_file[33] = {0};
    strcpy(out_file, file);
    while(out_file[i] != '.')
        i++;
    out_file[++i] = 'L';
    out_file[++i] = 'e';
    out_file[++i] = 'x';
    out_file[++i] = '\0';
    // open the out file 
    if((fout = fopen(out_file, "w")) == NULL)
    {
        printf("Error: unable to open the %s\n", out_file);
        exit(-3);
    }

    // 打印表头，作者信息
    fprintf(fout,"Copyright@ 高天林\t\tGithub @ https://github.com/LanG-Hust/Lexical-Analyzer\n");
    fprintf(fout,"\t%-10s%-15s%-24s%-9s%-9s%-14s\n","序号","token类型", "token", "行号", "列号", "出现次数");
    fprintf(fout,"\t---------------------------------------------------------------\n");
}

bool token_analyze(char *line)
{
    static int i = 0; // reader
    int j = 0; // writer 
    char ch ;

    if(line[i] == '\n')
    {
        i = 0;
        return false;
    }
    

    while(state < 1 || state > 7)
    {
        ch = line[i];
        if(ch == '\n')
        {
            i = 0;
            return false;
        }
        if(state == 0)
        {
            gcol = i + 1;
        }
        switch(state)
        {
            case 0:
                if(isalpha(ch) || ch == '_')
                {
                    state = 8;
                    gtoken[j++] = ch;
                }
                else if(isdigit(ch))
                {
                    state = 9;
                    gtoken[j++] = ch;
                }
                else if(ch == '.')
                {
                    state = 22;
                    gtoken[j++] = ch;
                } 
                // separator
                else if(ch == ';' || ch == '{'|| ch == '}')
                {
                    state = 6;
                    gtypecode = 6;
                    gtoken[j++] = ch;
                    gtoken[j++] = '\0';
                }
                // operator
                else if(ch == '[' || ch == ']'|| ch == '('|| ch == ')' || ch == ','|| ch == '?'|| ch == ':')
                {
                    state = 7;
                    gtypecode = 7;
                    gtoken[j++] = ch;
                    gtoken[j++] = '\0';
                }
                else if( ch == '+')
                {
                    state = 14;
                    gtoken[j++] = ch;
                } 
                else if(ch == '=' ||ch == '!' ||ch == '^' ||ch == '*' ||ch == '%'  )
                {
                    state = 24;
                    gtoken[j++] = ch;
                }
                else if(ch == '&')
                {
                    state = 26;
                    gtoken[j++] = ch;
                }
                else if(ch == '|')
                {
                    state = 28;
                    gtoken[j++] = ch;
                } 
                else if(ch == '<')
                {
                    state = 30;
                    gtoken[j++] = ch;
                } 
                else if(ch == '>')
                {
                    state = 32;
                    gtoken[j++] = ch;
                } 
                else if(ch == '-')
                {
                    state = 34;
                    gtoken[j++] = ch;
                } 
                else if(ch == '/')
                {
                    state = 36;
                    gtoken[j++] = ch;
                } 
                else if(ch == '"')
                {
                    state = 40;
                    gtoken[j++] = ch;
                } 
                else if(ch == '\'')
                {
                    state = 42;
                    gtoken[j++] = ch;
                } 
                   

                break;
            
            case 8:
                if(isalpha(ch) || ch == '_' || isdigit(ch))
                {
                    state = 8;
                    gtoken[j++] = ch;
                }
                else
                {
                    gtypecode = 1;
                    state = 1;
                    gtoken[j] = '\0';
                    i--;
                }
                break; 
            
            case 9:
                if(isdigit(ch))
                {
                    state = 9;
                    gtoken[j++] = ch;
                }

                else if(ch == '.')
                {
                    state = 10;
                    gtoken[j++] = ch;
                }

                else if(toupper(ch) == 'L')
                {
                    state = 2;
                    gtypecode = 2;
                    gtoken[j++] = ch;
                    gtoken[j] = '\0';
                }
                else
                {
                    state = 2;
                    gtypecode = 2;
                    gtoken[j] = '\0';
                    i--;
                }
                break; 

            case 10:
                if(isdigit(ch))
                {
                    state = 11;
                    gtoken[j++] = ch;
                }
                else if(toupper(ch) == 'F')
                {
                    state = 3;
                    gtypecode = 3;
                    gtoken[j++] = ch;
                    gtoken[j] = '\0';
                }
                else
                {
                    state = 3;
                    gtypecode = 3;
                    gtoken[j] = '\0';
                    i--;
                }
                break; 

            case 11:
                if(isdigit(ch))
                {
                    state = 11;
                    gtoken[j++] = ch;
                }
                else
                {
                    state = 3;
                    gtypecode = 3;
                    gtoken[j] = '\0';
                    i--;
                }
                break; 
            case 14:
                if(ch == '+' || ch == '=')
                {
                    state = 7;
                    gtypecode = 7;
                    gtoken[j++] = ch;
                    gtoken[j] = '\0';
                }
                else
                {
                    state = 7;
                    gtypecode = 7;
                    gtoken[j] = '\0';
                    i--;
                }
                break;
                    
            case 22:
                if(isdigit(ch))
                {
                    state = 11;
                    gtoken[j++] = ch;
                }
                else
                {
                    state = 7;
                    gtypecode = 7;
                    gtoken[j] = '\0';
                    i--;
                }
                break;

            case 24:
                if(ch == '=')
                {
                    state = 7;
                    gtypecode = 7;
                    gtoken[j++] = ch;
                    gtoken[j] = '\0';
                }
                else
                {
                    state = 7;
                    gtypecode = 7;
                    gtoken[j] = '\0';
                    i--;
                }
                break;

            case 26:
                if(ch == '&')
                {
                    state = 7;
                    gtypecode = 7;
                    gtoken[j++] = ch;
                    gtoken[j] = '\0';
                }
                else
                {
                    state = 7;
                    gtypecode = 7;
                    gtoken[j] = '\0';
                    i--;
                }
                break;
            case 28:
                if(ch == '|')
                {
                    state = 7;
                    gtypecode = 7;
                    gtoken[j++] = ch;
                    gtoken[j] = '\0';
                }
                else
                {
                    state = 7;
                    gtypecode = 7;
                    gtoken[j] = '\0';
                    i--;
                }
                break;
            case 30:
                if(ch == '<' || ch == '=')
                {
                    state = 7;
                    gtypecode = 7;
                    gtoken[j++] = ch;
                    gtoken[j] = '\0';
                }
                else
                {
                    state = 7;
                    gtypecode = 7;
                    gtoken[j] = '\0';
                    i--;
                }
                break;
            case 32:
                if(ch == '>' || ch == '=')
                {
                    state = 7;
                    gtypecode = 7;
                    gtoken[j++] = ch;
                    gtoken[j] = '\0';
                }
                else
                {
                    state = 7;
                    gtypecode = 7;
                    gtoken[j] = '\0';
                    i--;
                }
                break;
            case 34:
                if(ch == '>' || ch == '=' || ch == '-')
                {
                    state = 7;
                    gtypecode = 7;
                    gtoken[j++] = ch;
                    gtoken[j] = '\0';
                }
                else
                {
                    state = 7;
                    gtypecode = 7;
                    gtoken[j] = '\0';
                    i--;
                }
                break;
            case 36:
                if(ch == '=')
                {
                    state = 7;
                    gtypecode = 7;
                    gtoken[j++] = ch;
                    gtoken[j] = '\0';
                }
                else if(ch == '/')
                {
                    state = 0;
                    i = 0;
                    return false;
                }
                else if(ch == '*')
                {
                    state = 37;
                    gtypecode = -1;
                }
                else
                {
                    state = 7;
                    gtypecode = 7;
                    gtoken[j] = '\0';
                    i--;
                }
                break;

            case 37:
                if(ch == '*')
                    state = 38;
                break;
                
            case 38:
                if(ch == '/')
                    state = 0;
                else
                {
                    state = 37;
                    i--;
                }
                break;

            case 40:
                if(ch == '"')
                {
                    gtypecode = 5;
                    state = 5;
                    gtoken[j++] = ch;
                    gtoken[j] = '\0';
                }
                else
                {
                    gtoken[j++] = ch;
                }
                break;

            case 42:
                if(ch == '\'')
                {
                    gtypecode = 4;
                    state = 4;
                    gtoken[j++] = ch;
                    gtoken[j] = '\0';
                }
                else
                {
                    gtoken[j++] = ch;
                }
                break;

        }
        i++;
    }
    // 重置state
        state = 0;
//    gtypecode = state;
    return true;
}   

bool isnothing(char *token)
{
    int i = 0;
    while(token[i] != '\0')
    {
        if(!isspace(token[i]))
            return false;
        i++;
    }
    return true;
}
