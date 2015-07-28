#include "token_head.h"

int main()
{
    initial();
    char line_buf[120] = {0};
    node *pid_kw = NULL;
    int row = 0;
    
    while(!feof(fin))
    {
        fgets(line_buf, MAX, fin);
        row++;
        grow = row;
        printf("%s\n",line_buf);
        while(token_analyze(line_buf) == true)
        {
//            printf("check: %s", gtoken);
            // 判断是标识符还是关键字
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

//            node *ptemp = NULL;

            switch(gtypecode)
            {
                case 1:
                    counter(gtoken, &pid_kw);
                    break;
                
            }
            
            printf("Token:%s\tType:%s\tType_Code:%d\tCount:%d\tRow:%d\tCol:%d\n", gtoken, gtype, gtypecode, gcnt, grow, gcol);
        }
//        printf("check | gtoken:%s", gtoken);
//        write_file();
    }
}

void counter(const char *token, node **pphd)
{
    node *ptemp = NULL;
//    char buf[50] = {0};
    int flag = 0;
    node *phead = *pphd;

    for(ptemp = phead; ptemp != NULL; ptemp = ptemp->pnext)
    {
        if(0 == strcmp(token, ptemp->ps))
        {
            flag = 1;
            break;
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

bool ident_or_key(char * token)
{
   int i = 0;
   for(i = 0; i < N; i++)
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

void initial()
{
    // prepare the file
    if((fin = fopen(in_file, "r")) == NULL)
    {
        printf("Error: unable to open the %s\n", in_file);
        exit(-1);
    }
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
    

    while(state < 1 || state > 6)
    {
        ch = line[i];
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
            
        }
        i++;
    }
    // 重置state
        state = 0;
//    gtypecode = state;
    return true;
}   
