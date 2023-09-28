/* ========================================================================== */
/*                                                                            */
/*  Перевод числа из 16-ти значной системы в 10-ти значную                    */
/*                                                                            */
/*                                                                            */
/*   Description                                                              */
/*                                                                            */
/* ========================================================================== */

void win12512unicode(wchar_t *ws, const char *s, int len)
{
  int c;
  while((c=*s++)&&((len--)>0))
  {
    if (c==0xA8) c=0x401;
    if (c==0xAA) c=0x404;
    if (c==0xAF) c=0x407;
    if (c==0xB8) c=0x451;
    if (c==0xBA) c=0x454;
    if (c==0xBF) c=0x457;
    if ((c>=0xC0)&&(c<0x100)) c+=0x350;
    *ws++=c;
  }
  *ws=0;
}

char * unicode2win1251(char *s, wchar_t *ws, int len)
{
  char *d=s;
  int c;
  while((c=*ws++)&&((len--)>0))
  {
    if (c==0x401) c=0xA8;
    if (c==0x404) c=0xAA;
    if (c==0x407) c=0xAF;
    if (c==0x451) c=0xB8;
    if (c==0x454) c=0xBA;
    if (c==0x457) c=0xBF;
    if ((c>=0x410)&&(c<0x450)) c-=0x350;
    *s++=c;
  }
  *s=0;
  return(d);
}


int hex2int(char * h)
{
  char c;
  int res=0;
  while((*h++)!='X');
  do
  {
    c=*h++;
    if (c>0x60) c-=0x20; else c-=0x30;
    if (c>9) c-=7;
    res<<=4;
    res|=c;
  }
  while(*h!='\0');
  return(res);
};


int atoi(char *s)
{
    int i, n;
    n = 0;
    for (i = 0; s[i] >= '0' && s[i] <= '9';++i)
        n = 10 * n + (s[i] - '0');
    return n;
}
