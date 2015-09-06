/*
** ReTear dBnY^nBS/Raven^Mercyground
**
** Data Structures Bit
*/



typedef
struct strlist
{
    char *replacestr;
    struct strlist *point;
}Stringlist;

typedef
struct replist
{
    char type;
    char *find;
    Stringlist *replacehead;
    Stringlist *replace;
    char *thingid;
    int thingcount;
    struct replist *point;
}Replacelist;

typedef
struct inslist
{
    Stringlist *inserthead;
    Stringlist *insert;
    char *thingid;
    struct inslist *point;
}Insertlist;

typedef
struct cfglist
{
    Replacelist *head;
    Insertlist  *insert;
}Config;



/* all lies lead to the truth */

