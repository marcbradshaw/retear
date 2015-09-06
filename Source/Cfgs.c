/*
** ReTear dBnY^nBS/Raven^Mercyground
**
** Config File Related Bits
*/



char *crstring(char *stringa,char *stringb)
{
    char *temp;
    int len;

    len=strlen(stringa)+strlen(stringb);
    if (!(temp=malloc(len+1)))
    {
        printf("Memory Allocation Error 1.\n");
        exit(103);
    }
    strcpy(temp,stringa);
    strcat(temp,stringb);
    return temp;
}



void addreplace(Replacelist *list,char *string)
{
    Stringlist *shead;
    Stringlist *stemp;

    shead=list->replace;

    if(!(stemp=malloc(sizeof(Stringlist))))
    {
        printf("Memory Allocation Error 2.\n");
        exit(103);
    }

    list->replacehead = stemp;
    list->replace = stemp;
    stemp->point = shead;
    stemp->replacestr = crstring(list->find,string);
}



void addireplace(Insertlist *list,char *string)
{
    Stringlist *shead;
    Stringlist *stemp;

    shead=list->insert;

    if(!(stemp=malloc(sizeof(Stringlist))))
    {
        printf("Memory Allocation Error 3.\n");
        exit(103);
    }

    list->inserthead = stemp;
    list->insert = stemp;
    stemp->point = shead;
    if (string[0]==1)
        stemp->replacestr = crstring(string,"");
    else
        stemp->replacestr = crstring("\1",string);
}




Replacelist *newnode(char type,Replacelist *head,char *find,char *thingid)
{
    Replacelist *templist;

    if (!(templist = malloc(sizeof(Replacelist))))
    {
        printf("Memory Allocation Error 4.\n");
        exit(103);
    }

    templist->type=type;
    templist->find=crstring(find,"");
    templist->thingid=crstring(thingid,"");
    templist->thingcount=0;
    templist->point=head;
    templist->replace=NULL;
    templist->replacehead=NULL;
    head=templist;
    return templist;
}



Insertlist *newinode(Insertlist *head,char *thingid)
{
    Insertlist *templist;

    if (!(templist = malloc(sizeof(Insertlist))))
    {
        printf("Memory Allocation Error 5.\n");
        exit(103);
    }

    templist->thingid=crstring(thingid,"");
    templist->point=head;
    templist->insert=NULL;
    templist->inserthead=NULL;

    head=templist;
    return templist;
}



void printconfig(Config *cfg)
{
    Replacelist *temp;
    Insertlist  *itemp;
    Stringlist *stemp;

    temp=cfg->head;
    itemp=cfg->insert;

    printf("Configuration.\n\n");

    /* inserts */
    if (cfg->insert)
    {
        while(itemp)
            {
            printf("Type    - Insert\n");
            printf("ID      - %s\n",itemp->thingid);

            stemp=itemp->insert;

            while(stemp)
            {
                printf("Insert  - \"%s\"\n",stemp->replacestr);
                stemp=stemp->point;
            }

            itemp=itemp->point;
            printf("\n");
        }
    }

    /* general config */
    while(temp)
    {
        printf("Type    - ");
        switch(temp->type)
        {
            case 'V':
                printf("View\n");
                break;
            case 'R':
                printf("Replace\n");
                break;
            case 'D':
                printf("Delete\n");
                break;
            default:
                /* SHOULD never happen */
                printf("Error in config file.\nUnknown type \"%c\".\n",temp->type);
                break;
        }
        printf("ID      - %s\n",temp->thingid);
        printf("Find    - \"%s\"\n",temp->find);

        stemp=temp->replace;

        while(stemp)
        {
            printf("Replace - \"%s\"\n",stemp->replacestr);
            stemp=stemp->point;
        }

        temp=temp->point;
        printf("\n");
    }

}



char *convertstring(char *string)
{
    char c;
    int counts,countd,quoted;

    quoted=counts=countd=0;

    if (string[0]=='\"')
        counts=quoted=1;

    while (string[counts])
    {
        c=string[counts++];

        if (c=='\\')
        {
            c=string[counts++];
            if (c=='1') c='\1';
            if (c=='b') c='\b';
            if (c=='f') c='\f';
            if (c=='n') c='\n';
            if (c=='r') c='\r';
            if (c=='t') c='\t';
            if (c=='\\') c='\\';
        }
        string[countd++]=c;
    }

    if (countd>1)
        string[countd-quoted]='\0';

    return string;
}



void nfgets(char *string,int size,FILE *getfile)
{
    char c;
    int i;

    if (size)
        size--;

    for (i=0 ; (i<size) ;)
    {
        c=fgetc(getfile);

        if (c=='\n')
            break;
        else if (c!='\r')
            string[i++]=c;
    }
    string[i++]=0;
}



void readconfig(Config *cfg , char *filename)
{

    Replacelist *head;
    Insertlist  *ihead;
    char inline[CFGBUFF];
    FILE *cfgfile;

    char t_type;
    char t_find[CFGBUFF];
    char t_id[CFGBUFF];

    head=cfg->head;
    ihead=cfg->insert;

    if(!(cfgfile=fopen(filename,"rb")))
        printf("Error opening config file.\n\n");
    else
    {
        while (!feof(cfgfile))
        {
            /* read main entry */
            nfgets(inline,CFGBUFF,cfgfile);
            t_type=inline[0];

            if (!((t_type==';')||(t_type=='\0')))
            {
                if (t_type=='E')
                    break;
                if (t_type=='I')
                {
                    nfgets(inline,CFGBUFF,cfgfile);
                    strcpy(t_id,convertstring(inline));
                    ihead=newinode(ihead,t_id);
                    /* read insert lines */
                    nfgets(inline,CFGBUFF,cfgfile);
                    convertstring(inline);
                    while(strcmp(inline,""))
                    {
                        addireplace(ihead,inline);
                        nfgets(inline,CFGBUFF,cfgfile);
                        convertstring(inline);
                    }
                }
                else
                {
                    if ( !strchr("RDV",t_type))
                    {
                        printf("Error in config file.\nUnknown type \"%c\".\n\n",t_type);
                        head=NULL;
                        break;
                    }
                    nfgets(inline,CFGBUFF,cfgfile);
                    strcpy(t_find,convertstring(inline));
                    nfgets(inline,CFGBUFF,cfgfile);
                    strcpy(t_id,convertstring(inline));
                    head=newnode(t_type,head,t_find,t_id);
                    /* read replace lines */
                    nfgets(inline,CFGBUFF,cfgfile);
                    convertstring(inline);
                    while(strcmp(inline,""))
                    {
                        addreplace(head,inline);
                        nfgets(inline,CFGBUFF,cfgfile);
                        convertstring(inline);
                    }
                }
            }
        }
        fclose(cfgfile);
    }

    cfg->head=head;
    cfg->insert=ihead;
}



/* all lies lead to the truth */

