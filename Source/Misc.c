/*
** ReTear dBnY^nBS/Raven^Mercyground
**
** Misc bits
*/



char idstring[]  = "ReTear 2.08 - dBnY^nBS/Raven^Mercyground" ;
char verstring[] = "$VER: ReTear 2.08 (06.04.98) ("__DATE__") ("__TIME__") dBnY^nBS" ;



void help(void)
{
    printf("ReTear - dBnY^nBS / Raven^Mercyground\n");
    printf("  WWW   : http://www.mercyground.home.ml.org/\n\n");
    printf("To Contact dBnY :\n");
    printf("  BBS   : NBS-Amiga 44-1642-653193\n");
    printf("  Fido  : 2:256/607.9\n");
    printf("  EMail : dBnY@bleach.demon.co.uk\n");
    printf("  WWW   : http://www.nbs-online.home.ml.org/\n\n");
    printf("To Contact Raven :\n");
    printf("  Fido  : 2:256/607.20\n");
    printf("  EMail : raven@bleach.demon.co.uk\n\n");
}



void usage(char *s)
{
    printf("Usage : %s [{flag}] <cfgfile> <infile> <outfile>\n\n",s);
    printf("Flags:\n");
    printf("-v : View config\n");
    printf("-a : Show Contact info\n\n");
}



/* all lies lead to the truth */

