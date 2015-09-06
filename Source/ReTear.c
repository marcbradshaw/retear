/*
** ReTear dBnY^nBS/Raven^Mercyground
**
** Should compile on any standard C Compiler.
** see ReTear.history for version history.
** Freeware, but dont be lame and claim its your work! ;)
*/

#define STRBUFF 256
#define CFGBUFF 256

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "Misc.c"
#include "Struct.c"
#include "Cfgs.c"
#include "Replace.c"
#include "Packet.c"


/* begin protos */
/* end protos */



void getsnt(char *string,int size,FILE *getfile)
{
    char c;
    int i;

    for (i=0 ; (i<size) ;)
    {
        c=fgetc(getfile);

        if (c=='\0')
            break;
        string[i++]=c;
    }
    string[i++]=0;
}



void printtotals(Replacelist *head)
{
    Replacelist *temp;

    temp=head;

    printf("Totals List.\n");

    printf("+---+--------------------------+--------+\n");
    while(temp)
    {
        printf("| %c | %-25s| %-5i  |\n",temp->type,temp->thingid,temp->thingcount);
        temp=temp->point;
    }
    printf("+---+--------------------------+--------+\n\n");
}



void retearfile(char *filenin,char *filenout,Config *cfg,int *messagecount)
{

    Replacelist *head;
    char strings[STRBUFF+2];
    char *stringp;
    char msg_time[20];
    char msg_to[36];
    char msg_from[36];
    char msg_subj[72];
    char ch,ch2;
    char end;
    int quit1=0;
    int quit2=0;
    int count;
    int line;
    int buffchar;

    FILE *filein,*fileout;

    char packetheader[58];
    char msgheader[12];

    head=cfg->head;

    if (!(filein = fopen(filenin,"rb")))
    {
        printf("Error opening infile\n");
        exit(11);
    }
    if (!(fileout = fopen(filenout,"wb")))
    {
        printf("Error opening outfile\n");
        fclose(filein);
        exit(12);
    }

    /* read packet header */
    for (count=0 ; count<58 ; count++)
    {
        ch=fgetc(filein);
        packetheader[count]=ch;
    }

    if ((packetheader[18]==2)&&(packetheader[19])==0)
    {
        showpktheader(packetheader);
        for (count=0 ; count<58 ; count++)
            fputc(packetheader[count],fileout);
    }
    else
    {
        printf("Not a valid packet file.\n");
        fclose(filein);
        fclose(fileout);
        exit(20);
    }

    while (!quit1)
    {

        ch=fgetc(filein);
        ch2=fgetc(filein);

        fputc(ch,fileout);
        fputc(ch2,fileout);

        if ((ch==2)&&(ch2==0))
        {
            /* valid msg */
            (*messagecount)++;

            /* read/write message header */
            for (count=0 ; count<12 ; count++)
            {
                ch=fgetc(filein);
                msgheader[count]=ch;
                fputc(ch,fileout);
            }

            /* read header strings */
            getsnt(msg_time,20,filein);
            getsnt(msg_to,36,filein);
            getsnt(msg_from,36,filein);
            getsnt(msg_subj,72,filein);

            /* write header strings */
            fputs(msg_time,fileout);
            fputc('\0',fileout);
            fputs(msg_to,fileout);
            fputc('\0',fileout);
            fputs(msg_from,fileout);
            fputc('\0',fileout);
            fputs(msg_subj,fileout);
            fputc('\0',fileout);

            /* process msg body */
            line=0;
            quit2=0;
            while (!quit2)
            {

                end='\0';
                for (buffchar=0 ; buffchar<STRBUFF ; )
                {
                    if ((ch=fgetc(filein))==EOF)
                        if (feof(filein))
                        {
                            printf("Warning - Packet File Too Short!\n");
                            fclose(filein);
                            fclose(fileout);
                            exit(22);
                        }
                    if (ch=='\r')
                    {
                        end=ch;
                        break;
                    }
                    else if (ch=='\n')
                    {
                        end=ch;
                        break;
                    }
                    else if (ch=='\0')
                    {
                        quit2=1;
                        break;
                    }
                    else
                        strings[buffchar++]=ch;
                }
                strings[buffchar++]='\0';
                /* strings now holds text line and buffchar holds its length */

                if (!quit2)
                {
                    stringp=replaceline(strings,head);

                    if (stringp)
                    {
                        if (!line++)
                        {
                            if (beginstr("AREA:",stringp,5))
                            {
                                fputs(stringp,fileout);
                                if (end)
                                    fputc(end,fileout);
                                insert(cfg->insert,fileout);
                            }
                            else
                            {
                                insert(cfg->insert,fileout);
                                fputs(stringp,fileout);
                                if (end)
                                    fputc(end,fileout);
                            }
                        }
                        else
                        {
                            fputs(stringp,fileout);
                            if (end)
                                fputc(end,fileout);
                        }
                    }
                }
            }
            fputc('\0',fileout);
        }
        else if ((ch==0)&&(ch2==0))
        {
            /* end of packet */
            quit1=1;
        }
        else
        {
            /* error */
            printf("Warning - Error In Packet!\n");
            fclose(filein);
            fclose(fileout);
            exit(21);
        }

    }

    fclose(filein);
    fclose(fileout);

}



int main(int argc,char *argv[])
{

    Config cfg;
    
    int count;
    int time;
    int messagecount=0;
    int argoff=0;

    char *filenin,*filenout,*filencfg;
    


/* argument handling */

    time=clock();

    printf("\n%s\n\n",idstring);

    cfg.head=NULL;
    cfg.insert=NULL;

    if (argc==1)
    {
        usage(argv[0]);
        exit(0);
    }

    for (argoff=0 ; argv[argoff+1][0]=='-' ; argoff++ );

    if ((1+argoff)<argc)
    {
        filencfg=argv[1+argoff];
        readconfig(&cfg,filencfg);
    }

    if (argoff)
        for (count=1 ; count<=argoff ; count++)
        {
            /* There were flags */
            if (strchr(argv[count],'v'))
                printconfig(&cfg);
            if (strchr(argv[count],'a'))
                help();
        }

    if (!cfg.head)
    {
        printf("No Config File.\n\n");
        exit(10);
    }

    if ((argc-argoff)<3)
    {
        usage(argv[0]);
        exit(0);
    }

    filenin=argv[2+argoff];
    filenout=argv[3+argoff];

/* retear the damn thing */

    retearfile(filenin,filenout,&cfg,&messagecount);

    printtotals(cfg.head);

    printf("Message Count : %i\n\n",messagecount);

    time=clock()-time;
    time=time/CLOCKS_PER_SEC;
    printf ("Time Taken %u seconds.\n\n",time);

    return 0;

}



/* all lies lead to the truth */

