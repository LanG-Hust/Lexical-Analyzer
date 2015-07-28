#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


typedef struct NODE
{
    int cnt;
    char *ps;
    struct NODE *pnext;
}node;

node *new_node();
void print_list(node *phead);

int main()
{

    node *phead = NULL;
    node *ptemp = NULL;

    char buf[50];

    while(scanf("%s", buf) != EOF )
    {
//        scanf("%s", buf);
        int flag = 0;
        for(ptemp = phead; ptemp != NULL; ptemp = ptemp->pnext)
        {
            if(0 == strcmp(buf, ptemp->ps))
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
            int len = strlen(buf);
            ptemp->ps = malloc(sizeof(len + 1));
            strcpy(ptemp->ps, buf);
        }
        else
        {
            ptemp->cnt ++;
        }
    }
    print_list(phead);
    return 0;
}

void print_list(node *phead)
{
    node *ptemp = NULL;

    for(ptemp = phead; ptemp != NULL; ptemp = ptemp->pnext)
    {
        printf("String: %s \t\t Count: %d\n", ptemp->ps, ptemp->cnt);
    }
    
    return;
}

node *new_node()
{
    node *ptemp = malloc(sizeof(node));
    ptemp->cnt = 1;
    ptemp->pnext = NULL;
    return ptemp;
}
