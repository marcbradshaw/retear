/*
** ReTear dBnY^nBS/Raven^Mercyground
**
** Search/Replace Bits
*/



int beginstr(char *stra,char *strb,int size)
{
    int cnt,l;
    int is=0;

    l=strlen(stra);

    if (size>=l)
    {
        is=1;
        for (cnt=0 ; cnt<l ; cnt++)
        {
            if(stra[cnt]!=strb[cnt])
            {
                is=0;
                break;
            }
        }
    }
    return is;
}



char *replaceline(char *line,Replacelist *head)
{
    Replacelist *temp;
    Stringlist *stemp;

    temp=head;

    while(temp)
    {
        if (beginstr(temp->find,line,strlen(line)))
        {
            (temp->thingcount)++;

            switch(temp->type)
            {

                case 'R':
                stemp=temp->replace;
                if (stemp)
                {
                    line=stemp->replacestr;
                    temp->replace=stemp->point;
                    if (!(temp->replace))
                        temp->replace=temp->replacehead;
                }
                break;

                case 'D':
                line=NULL;
                break;

                case 'V':
                printf("%s\n",line);
                break;

                default:
                /* SHOULD never happen */
                printf("Error in config file.\nUnknown type \"%c\".\n",temp->type);
                exit(30);
                break;
            }

            break;
        }

        temp=temp->point;
    }

    return line;
}



void insert(Insertlist *head,FILE *fp)
{
    Insertlist *temp;
    Stringlist *stemp;

    char *line;

    temp=head;

    while(temp)
    {
        line=NULL;

        stemp=temp->insert;
        if (stemp)
        {
            line=stemp->replacestr;
            temp->insert=stemp->point;
            if (!(temp->insert))
                temp->insert=temp->inserthead;
            fputs(line,fp);
            fputc('\r',fp);
        }
        temp=temp->point;
    }
}



/* all lies lead to the truth */

