// iconattach.cpp : Defines the entry point for the console application.
//
#include "..\\include\Lib_Clara.h"
#include "..\\include\Types.h"
#include "main.h"
#include "iconattach.h"

typedef int FILE;
wchar_t FULL_ELF_NAME[32];
wchar_t FULL_SICON_NAME[32];
wchar_t FULL_BICON_NAME[32];

typedef enum {
 Png = 0,
 Gif = 1,
 Jpg = 2,
 Bmp = 3,
 
 END = 0xFFFFFFFF
}IconFormat;

typedef struct {
 unsigned long version;
 
 unsigned long sicon_off;
 unsigned long sicon_size; 
 IconFormat sicon_format;
 
 unsigned long bicon_off;
 unsigned long bicon_size;  
 IconFormat bicon_format; 
} ElfIconHeader;

// и так ясно..
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

char* read(char* p)
{
  FILE ini_file=NULL;
  W_FSTAT _fstat;
  char * buf=0;
  char* param=0;
  if( w_fstat( L"usb/other/ini/iconattach.ini", &_fstat )>=0 )
  {
    if( ( ini_file=w_fopen(L"usb/other/ini/iconattach.ini", WA_Read, 0x1FF, 0))>=0 )
    {
      buf=new char[_fstat.st_size+1];
      buf[w_fread(ini_file,buf,_fstat.st_size)]=0;
      param = manifest_GetParam(buf, p, 0);
      delete buf;
      w_fclose(ini_file);
    }
  }
  else return 0; //если нет файла
  if (param)  return param;
  else return 0; //если не удалось прочитать
}

//Читаем значения из конфига.
int readconfig()
{
  char elf_name[]="[ELF_NAME]";
  char small_icon[]="[SMALL_ICON_NAME]";
  char big_icon[]="[BIG_ICON_NAME]";
  char* relf_name=0;
  char* rsmall_icon=0;
  char* rbig_icon=0;
  relf_name=read(elf_name);
  rsmall_icon=read(small_icon);
  rbig_icon=read(big_icon);
  if( (relf_name!=0) && (rsmall_icon!=0) ) //если прочитали параметры
  {  
    win12512unicode(FULL_ELF_NAME, relf_name, strlen(relf_name));
    win12512unicode(FULL_SICON_NAME, rsmall_icon, strlen(rsmall_icon));
    if(rbig_icon!=0)
    {
      win12512unicode(FULL_BICON_NAME, rbig_icon, strlen(rbig_icon));
      return 2;
    }
    return 1;
  }
  else
   return 0;
}

int iconattach()
{
  int start=0;
  switch(readconfig())
  {
   case 0: { start=-1; break; }
   case 1: { start=0; break; }
   case 2: { start=1; break; }
  }
  if( start>=0 )
  {
    // открываем эльф
    W_FSTAT elffs;
    FILE elf;
    if( w_fstat( FULL_ELF_NAME, &elffs )>=0 )
      elf = w_fopen( FULL_ELF_NAME, WA_Read, 0x1FF, 0 );
    else
    {
      MessageBox(EMPTY_TEXTID,STR("Elf is not found!"),NOIMAGE,1,3000,0);
      return -1;
    }
 
    // открываем маленькую иконку
    W_FSTAT siconfs;
    FILE sicon;
    if( w_fstat( FULL_SICON_NAME, &siconfs )>=0 )
      sicon=w_fopen( FULL_SICON_NAME, WA_Read, 0x1FF, 0 );
    else
    {
      MessageBox(EMPTY_TEXTID,STR("Small Icon not found"),NOIMAGE,1,3000,0);
      return -2;
    }
  
    // если есть имя большой иконки, откроем её
    FILE bicon = NULL;
    W_FSTAT biconfs;
    if( start==1 )
    {
      if( w_fstat( FULL_BICON_NAME, &biconfs )>=0 )
        sicon=w_fopen( FULL_BICON_NAME, WA_Read, 0x1FF, 0 );
      else MessageBox(EMPTY_TEXTID,STR("Big Icon not found"),NOIMAGE,1,3000,0);
    }
 
    unsigned char e_ident[16];
 
    w_fread( elf, e_ident, 16 );
    //а эльф ли это?
    if( *(unsigned long*)e_ident != 0x464C457FUL )
    {
      MessageBox(EMPTY_TEXTID,STR("Not an elf file."),NOIMAGE,1,3000,0);
      return -3;
    }
 
    int elfend = elffs.st_size;
    if( *(unsigned long*)&e_ident[12] != 0UL )
    elfend = *(unsigned long*)&e_ident[12];
    // пишем структуру png
    ElfIconHeader *eih = (ElfIconHeader *)malloc(sizeof(ElfIconHeader));
    memset(eih, 0, sizeof(ElfIconHeader));
    eih->version = 1;
    //маленькая иконка
    eih->sicon_size = siconfs.st_size;
    eih->sicon_off = elfend + sizeof(ElfIconHeader);
    eih->sicon_format = Png;
 
    if( bicon )
    { //большая иконка, если открыта
      eih->bicon_size = biconfs.st_size;
      eih->bicon_off = elfend + sizeof(ElfIconHeader) + siconfs.st_size;
      eih->bicon_format = Png;
    }

    *(unsigned long*)&e_ident[12] = elfend;
 
    char *buf = (char *)malloc( elfend - 16 );
 
    w_fread( elf, buf, elfend - 16 );
 
    w_fclose( elf );
    elf = w_fopen( FULL_ELF_NAME, WA_Write, 0x1FF, 0 );

    w_fwrite( elf, e_ident, 16 );
    w_fwrite( elf, buf, elfend - 16 );

    w_fwrite( elf, eih, sizeof(ElfIconHeader) );
    mfree(eih);
 
    mfree(buf);
 
    buf = (char *)malloc( siconfs.st_size );
 
    w_fread( sicon, buf, siconfs.st_size );
    w_fclose(sicon);
 
    w_fwrite( elf, buf, siconfs.st_size );
 
    mfree(buf);
 
    if( bicon )
    {
      buf = (char *)malloc( biconfs.st_size );

      w_fread( bicon, buf, biconfs.st_size );
      w_fclose(bicon);

      w_fwrite( elf, buf, biconfs.st_size );
      mfree(buf);
    }

    w_fclose(elf);
 
    return 0;
  }
  else
  {
    MessageBox(EMPTY_TEXTID,STR("Error!\nCould not read iconattach.ini"),NOIMAGE,1,3000,0);
    return -4;
  }
}

