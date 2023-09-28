
#include "main.h"


unsigned int  width, height, size;
char* imgbuf;
BITMAPFILEHEADER *bmp_read_struc;
BITMAPINFOHEADER *inf_read_struc;
BITMAPFILEHEADER *bmp_write_struc;
BITMAPINFOHEADER *inf_write_struc;

wchar_t *temp_file = L"~temp";

//------------------------------------------------------------------------------------------------------------
void elf_exit(void)
{
  kill_data(&ELF_BEGIN, (void(*)(void*))mfree_adr());
}

static int TerminateElf(void *msg, BOOK *book)
{
  FreeBook(book);
  return(1);
}

static int ShowAuthorInfo(void *msg ,BOOK *book)
{
  MessageBox(EMPTY_TEXTID,STR("ImageConverter\n v.a (c)Metaler"),NOIMAGE, 1, 0, NULL);
  return(1);
}


static void onBookClose(BOOK *book)
{
  SUBPROC(elf_exit);
}

const PAGE_MSG IC_PageEvents[] @ "DYN_PAGE" =
{
  ELF_TERMINATE_EVENT,                    TerminateElf,
  ELF_SHOW_INFO_EVENT,                    ShowAuthorInfo,
  NIL_EVENT_TAG,                          NULL
};

PAGE_DESC base_page ={"ImageConverter_Base_Page", 0, IC_PageEvents};

BOOK *NewBook(char *name)
{
  BOOK *book = new BOOK;
  memset(book, 0, sizeof(BOOK));
  if(!CreateBook(book, onBookClose, &base_page, name, -1, 0))
  {
    mfree(book);
    return(NULL);
  }
  return(book);
}
//============================================================================================================

char* Revers(char * buf, int size) // 
{
  char t = 0;
  for(int i = 0; i < size/2; ++i)
  {   
    t = buf[i];
    buf[i] = buf[size - i - 1];
    buf[size - i - 1] = t;
  }
  return buf;
}

bool Read_BMP( wchar_t *fpath, wchar_t *fname)
{
  bmp_read_struc = new BITMAPFILEHEADER;
  memset(bmp_read_struc,0,sizeof(BITMAPFILEHEADER));
  inf_read_struc = new BITMAPINFOHEADER;
  memset(inf_read_struc,0,sizeof(BITMAPINFOHEADER));
  
  int fd;
  FSTAT _fstat;
  if (fstat(fpath, fname,&_fstat)!=-1)
  {
    if((fd=_fopen( fpath, fname, WA_Read, 0x1FF, 0))>=0)
    {    
      fread(fd, bmp_read_struc, sizeof(BITMAPFILEHEADER));
      fread(fd, inf_read_struc, sizeof(BITMAPINFOHEADER));
    }
  }
  else 
	{
		MessageBox(EMPTY_TEXTID, STR("нет файла!"), NOIMAGE, 1, 0, NULL);
    return false;
  }
  
  width = inf_read_struc->biWidth;
  height = inf_read_struc->biHeight;
  
 
  if(inf_read_struc->biSizeImage == 0)
  {
    size = width * 3 + width % 4;
    size = size * height;
  }
  else
  {
    size = inf_read_struc->biSizeImage;
  }

  lseek(fd, bmp_read_struc->bfOffBits, SEEK_SET);

	// пишем данные bmp в temp файл
  int tmp;
  tmp=_fopen( fpath, temp_file, WA_Create+WA_Write, 0x1FF, 0);
  
  const int CopyBuff = 1024;
  int bytesRead = 0;
  long readb = bmp_read_struc->bfOffBits;
  char *buffer = new char[CopyBuff];
     
  while( (bytesRead = fread(fd, buffer, CopyBuff)) !=0)        
  {
      fwrite( tmp, buffer, bytesRead );
      readb += bytesRead;
      lseek(fd, readb, SEEK_SET);
  }
  delete(buffer);
  fclose(tmp);           
  fclose(fd);
  
  //=================================
  int tmp2;
  tmp2=_fopen( fpath, L"~temp2", WA_Create+WA_Write, 0x1FF, 0);
  tmp=_fopen( fpath, temp_file, WA_Read, 0x1FF, 0);
  
  
  int CopyBuff2 = width * 3 + width % 4;
  int bytesRead2 = 0;
  
  long readb2 = (height * ( width * 3 + width % 4))- (width * 3 + width % 4);
  
  char *buffer2 = new char[CopyBuff2];
  
  lseek(tmp, readb2, SEEK_SET);
   
  while( (bytesRead2 = fread(tmp, buffer2, CopyBuff2)) !=0)        
  {     
      fwrite( tmp2, Revers(buffer2, width * 3), width * 3 );
      readb2 -= bytesRead2;
      if(readb2<0)
        break;
      lseek(tmp, readb2, SEEK_SET);  
  }
  delete(buffer2);
  fclose(tmp2);           
  fclose(tmp);
  
  return true;
}


/*
 char *buf1 = new char[width*3];
    unsigned int newind = 0;                
    for(int x=0; x < width*3 ; x++)
    {
      unsigned int r, g, b; 			
      b = buffer2[x];
      x++;
      g = buffer2[x];
      x++;
      r = buffer2[x];				
				
		  //buf1[newind] = (r | g << 8 | b << 16) << 8;
      buf1[newind] = r;
      newind++;
      buf1[newind] = g;
      newind++;
      buf1[newind] = b;
		  newind++;
	   }
*/

/*const int CopyBuff = 1024;
bool RST(wchar_t *fpath, wchar_t *fname1, wchar_t *fname2)
{
  int fdr, fdw;
  if((fdr=_fopen( fpath, fname1, WA_Read, 0x1FF, 0))<0)
 		return false;
  if((fdw=_fopen( fpath, fname2, WA_Create+WA_Write, 0x1FF, 0))<0)
 		return false;  
  int bytesRead=0;
  long readb =0;
  char *buffer = new char[CopyBuff];
     
  while( (bytesRead = fread(fdr, buffer, CopyBuff)) !=0)        
  {
      fwrite( fdw, buffer, bytesRead );
      readb += bytesRead;
      lseek(fdr, readb, SEEK_SET);
  }
  delete(buffer);
  fclose(fdw);
  fclose(fdr);
  return true;
}  */

	
int main(void)
{
   BOOK *book = NewBook(BOOKNAME);
   if(book)
   {
     FSTAT _fstat;
     if (fstat(L"card/test/", L"input.bmp",&_fstat)!=-1)
     {
       if(Read_BMP(L"card/test/", L"input.bmp"))
       {
         MessageBox(EMPTY_TEXTID, STR("Image Converted ok!"),NOIMAGE, 1, 0, NULL);
         FreeBook(book);
       }
       else
       {  
         MessageBox(EMPTY_TEXTID, STR("ImageConverter\n ERROR!"),NOIMAGE, 1, 0, NULL);
         FreeBook(book);
       }
     }
     else
     {
       MessageBox(EMPTY_TEXTID, STR("ImageConverter\n File not found!"),NOIMAGE, 1, 0, NULL);
         FreeBook(book);
     }
     
   } 
   else SUBPROC(elf_exit);
   return 0;
}
