/*
** ReTear dBnY^nBS/Raven^Mercyground
**
** Packet info Bit
**/



unsigned int cnvpkt(unsigned char lsb,unsigned char msb)
{
    unsigned int ret;

    ret=msb;
    ret=ret * 256;
    ret=ret + lsb;

    return ret;
}



void showpktheader(char *ph)
{
    int count;
    unsigned int onode,dnode,year,month,day,hour,minute;
    unsigned int second,onet,dnet,ozone,dzone,opnt,dpnt;
    char passwd[9];

    onode  = cnvpkt (ph[0] ,ph[1]);
    dnode  = cnvpkt (ph[2] ,ph[3]);
    year   = cnvpkt (ph[4] ,ph[5]);
    month  = cnvpkt (ph[6] ,ph[7]);
    day    = cnvpkt (ph[8] ,ph[9]);
    hour   = cnvpkt (ph[10],ph[11]);
    minute = cnvpkt (ph[12],ph[13]);
    second = cnvpkt (ph[14],ph[15]);
    onet   = cnvpkt (ph[20],ph[21]);
    dnet   = cnvpkt (ph[22],ph[23]);
    ozone  = cnvpkt (ph[34],ph[35]);
    dzone  = cnvpkt (ph[36],ph[37]);
    opnt   = cnvpkt (ph[50],ph[51]);
    dpnt   = cnvpkt (ph[52],ph[53]);

    month++;
    if (onet==65535)
        onet=dnet;

    for (count=0 ; count<8 ; count++)
    {
        passwd[count]=ph[count+26];
    }
    passwd[8]=0;

    printf("Packet From : %u:%u/%u.%u\n",ozone,onet,onode,opnt);
    printf("Packet To   : %u:%u/%u.%u\n",dzone,dnet,dnode,dpnt);
    printf("Packet Time : %02u/%02u/%u %02u:%02u:%02u\n",day,month,year,hour,minute,second);
    printf("Packet Pswd : %s\n",passwd);
    printf("\n");

}

