#include "token_head.h"

int main()
{
    initial();
    char line_buf[120] = {0};

    while(!feof(fin))
    {
        fgets(line_buf, MAX, fin);
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

            //node* ptemp = NULL;

            //switch(typecode)
            //{
            //    case 1:
            //        ptemp = pidkw;
            //        counter(gtoken, ptemp);
            //        break;
            //    
            //}
            
            printf("Token:%s\tType:%s\tType_Code:%d\n", gtoken, gtype, gtypecode);
        }
//        printf("check | gtoken:%s", gtoken);
//        write_file();
    }
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
