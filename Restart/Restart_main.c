
#include "..\\include\Lib_Clara.h"
#include "..\\include\Dir.h"

#define ElfName "Restart elf"
#define ElfVer "1.0"

BOOK * HWBook;

 int KeyPr ( int key, int r1, int mode, LPARAM lparam, DISP_OBJ*dispobj )
    {
        
       if(key==KEY_POWER && mode==KBD_REPEAT && !(isKeylocked()) )                                                                        
          {
            REQUEST_SYSTEM_RESTART();
            return(-1);
          }
      
      return(0);   
    }

void elf_exit(void)

{
  kill_data(&ELF_BEGIN, (void(*)(void*))mfree_adr());
}


int TerminateElf(void * ,BOOK* book)
{
  FreeBook(book);
  return(1);
}

typedef struct
{
  BOOK * book;
}MSG;


int ShowAuthorInfo(void *mess ,BOOK* book)
{
  MSG * msg = (MSG*)mess;
  wchar_t info[256];
  snwprintf(info,255,L"%s \nv.%s\n(c)Metaler\n%s",ElfName,ElfVer,__DATE__);
  MessageBox(EMPTY_TEXTID,TextID_Create(info,ENC_UCS2,TEXTID_ANY_LEN),NOIMAGE,1,0,msg->book);
  return(1);
}


const PAGE_MSG HW_PageEvents[]@ "DYN_PAGE" ={
  ELF_TERMINATE_EVENT , TerminateElf,
  ELF_SHOW_INFO_EVENT  , ShowAuthorInfo,
  0,0
};

PAGE_DESC base_page ={"HW_BasePage",0,HW_PageEvents};

void onCloseHWBook(BOOK * book)
{
  if (book)
  { 
    ModifyKeyHook( KeyPr,0,0 );
    SUBPROC(elf_exit);
  }
}

BOOK * CreateHWBook()
{
  HWBook= new BOOK;
  CreateBook(HWBook,onCloseHWBook,&base_page,ElfName,-1,0);
  return(HWBook);
}

//Проверяем, а не запущен ли наш эльф?------------------------------------------
int myFind(BOOK* book)
{
   if(!strcmp(book->xbook->name,ElfName))
     return(1);
   return(0);
}
 
int main(void)
   {
     
     if (FindBook(myFind))
       {
        MessageBox(EMPTY_TEXTID,STR("Уже запущен! =)"),NOIMAGE,1,5000,0);
        SUBPROC(elf_exit);
       }
     else 
     {
      CreateHWBook();
      ModifyKeyHook( KeyPr, KEY_HOOK_ADD, NULL );
      return(0);
     }
 }
