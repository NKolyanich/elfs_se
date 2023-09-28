//****************************************************************************//
//============================================================================//
//====================*** ElfsGlue v.1.1 bcfg ***=============================//
//=========================***(c)Metaler 20011.***============================//
//============================================================================//
//****************************************************************************//
//========================***Инклуды***=========================================
#include "..\\include\Lib_Clara.h"
#include "..\\include\Dir.h"
#include "..\\include\cfg_items.h"
#include "conf_loader.h"
#include "config_data.h"
#define ELF_BCFG_CONFIG_EVENT 994
//#include "..\\ErrorLogger\ErrorLogger.hpp"

#define ELF_NAME "ElfsGlue"
#define ElfVer "v.1.1"
#define ElfAuthor "(c)Metaler"

//Важные штуки------------------------------------------------------------------
typedef struct
{
  BOOK * book;
}MSG;

BOOK * PKPBook;
 
//--------------===Для конфига===-----------------------------------------------
static int ReconfigElf(void *mess ,BOOK *book)
{
  RECONFIG_EVENT_DATA *reconf=(RECONFIG_EVENT_DATA *)mess;
  int result=0;
  if (wstrcmpi(reconf->path,successed_config_path)==0 && wstrcmpi(reconf->name,successed_config_name)==0)
  {
    InitConfig();
    result=1;
  }
  return(result);
}

//----------===Что делать при убивании эльфа===---------------------------------
int TerminateElf(void * ,BOOK* book)
{
  if (book) FreeBook(book);  LogStr( "убиваем книгу", (char*)__FUNCTION__ , RED );
  return(1);
}

//----------===Функция выхода эльфа===------------------------------------------
void elf_exit(void)
{
  kill_data(&ELF_BEGIN, (void(*)(void*))mfree_adr());
}

//----------===Что делать при закрытии эльфа===---------------------------------
void onClosePKPBook(BOOK * book)
{
  SUBPROC(elf_exit);  LogStr( "subproc", (char*)__FUNCTION__ , RED );
}



BOOK* findbook(const char* name)
{              LogStr( "поиск книги", (char*)__FUNCTION__ , BLUE );
  //FUNCTION
  debug_printf("\nфУНКЦИЯ -  <font color=#0000ff> findbook \n</font>");
  int sesscount;
  BOOK * book;
  int sess, bk;
  char javaname[48];
  UI_APP_SESSION * session;
  sesscount=root_list_get_session_count();
  for(sess=0; sess<sesscount; sess++)
  {
    session=root_list_get_session(sess);
    for (bk=0; bk<session->listbook->FirstFree; bk++)
    {
      book=(BOOK*)List_Get(session->listbook, bk);
      if(!strcmp(book->xbook->name, name)) return book;
      //java
      TextID_GetString( BookObj_GetSession(book)->name, javaname, MAXELEMS(javaname) );
     /* int file;
       if((file=w_fopen(L"usb/other/get_JavaName.txt", WA_Create+WA_Append, 0x1FF, 0))>-1)
       {
         char str[256];
         sprintf(str," *NAME-> %s, JAVANAME-> %s\n\n",name,javaname);
         w_fwrite(file, str, strlen(str));
         w_fclose(file);
       } */
      if(!strcmp(javaname, name)) return book;

    }
  }
  return NULL;
}


//------------===Информация об эльфе===-----------------------------------------
int ShowAuthorInfo(void *mess ,BOOK* book)
{
  MSG * msg = (MSG*)mess;
  wchar_t info[256];
  snwprintf(info,255,L"%s\n%s\n%s",ELF_NAME,ElfVer,ElfAuthor);
  MessageBox(EMPTY_TEXTID,TextID_Create(info,ENC_UCS2,TEXTID_ANY_LEN),NOIMAGE,1,5000,msg->book);
  return(1);
}

//-------------===Для вызова конфига через мод букмана===-----------------------
int onBcfgConfig(void* mess,BOOK* book)
{
  FSTAT _fstat;
  wchar_t path[256];
  if(fstat(GetDir(DIR_ELFS|MEM_INTERNAL),L"BcfgEdit.elf",&_fstat)==0)
  {
    wstrcpy(path,GetDir(DIR_ELFS|MEM_INTERNAL));
  }
  else if(fstat(GetDir(DIR_ELFS|MEM_EXTERNAL),L"BcfgEdit.elf",&_fstat)==0)
  {
    wstrcpy(path,GetDir(DIR_ELFS|MEM_EXTERNAL));
  }
  else
  {
    MessageBox(0x6FFFFFFF, STR("Не могу найти BcfgEdit.elf! =("), NOIMAGE, 1 ,5000, 0);
    return (1);
  }
  wstrcat(path,L"/BcfgEdit.elf");
  elfload(path,(void*)successed_config_path,(void*)successed_config_name,0);
  return (1);
}

//--------------------------===Эвенты===----------------------------------------
const PAGE_MSG HW_PageEvents[]@ "DYN_PAGE" ={
  ELF_TERMINATE_EVENT, TerminateElf,
  ELF_SHOW_INFO_EVENT, ShowAuthorInfo,
  ELF_RECONFIG_EVENT , ReconfigElf,
  ELF_BCFG_CONFIG_EVENT, onBcfgConfig,
  NIL_EVENT_TAG, NULL
};

PAGE_DESC base_page ={"HW_BasePage",0,HW_PageEvents};

//---------------------===Создаем бук для эльфа===------------------------------
BOOK * CreatePKPBook()
{
  PKPBook= new BOOK;
  CreateBook(PKPBook,onClosePKPBook,&base_page,ELF_NAME,-1,0);
  return(PKPBook);
}

//---------------===Проверяем, а не запущен ли наш эльф?===---------------------
int myFind(BOOK* book)
{
   if(!strcmp(book->xbook->name,ELF_NAME))
     return(1);
   return(0);
}

int ElfLoad()
{  LogStr( "запускаем эльфов", (char*)__FUNCTION__ , RED );
  if(BCFG_elfstart_1 == 1) elfload(BCFG_elf_1,0,0,0); //1
  if(BCFG_elfstart_2 == 1) elfload(BCFG_elf_2,0,0,0);
  if(BCFG_elfstart_3 == 1) elfload(BCFG_elf_3,0,0,0);
  if(BCFG_elfstart_4 == 1) elfload(BCFG_elf_4,0,0,0);
  if(BCFG_elfstart_5 == 1) elfload(BCFG_elf_5,0,0,0);
  if(BCFG_elfstart_6 == 1) elfload(BCFG_elf_6,0,0,0);
  if(BCFG_elfstart_7 == 1) elfload(BCFG_elf_7,0,0,0);
  if(BCFG_elfstart_8 == 1) elfload(BCFG_elf_8,0,0,0);
  if(BCFG_elfstart_9 == 1) elfload(BCFG_elf_9,0,0,0);
  if(BCFG_elfstart_10 == 1) elfload(BCFG_elf_10,0,0,0);
  if(BCFG_elfstart_11 == 1) elfload(BCFG_elf_11,0,0,0);
  if(BCFG_elfstart_12 == 1) elfload(BCFG_elf_12,0,0,0);
  if(BCFG_elfstart_13 == 1) elfload(BCFG_elf_13,0,0,0);
  if(BCFG_elfstart_14 == 1) elfload(BCFG_elf_14,0,0,0);
  if(BCFG_elfstart_15 == 1) elfload(BCFG_elf_15,0,0,0); //15
  
  return 0;
 // onClosePKPBook(findbook(ELF_NAME));
 // if (findbook(ELF_NAME)) FreeBook(findbook(ELF_NAME));
  //onClosePKPBook(FindBook(myFind));
  //UI_Event(ELF_TERMINATE_EVENT);
}

//--------------------===Запускаем все это чудо===------------------------------
int main (void)
{
  if (FindBook(myFind))
  {
    MessageBox(EMPTY_TEXTID,STR("Уже запущен =)"),NOIMAGE,1,3000,0);
    SUBPROC(elf_exit);
  }
  else
  {
    LogStr( "запустили эльф. создали книгу", (char*)__FUNCTION__ , BLUE );
    CreatePKPBook();
    InitConfig();
    if(BCFG_elfstart == 0)    
    {
      //if (
       ElfLoad();// ==0 )  LogStr( "если ельфы запустились", (char*)__FUNCTION__ , RED );
      //onClosePKPBook(findbook(ELF_NAME));  LogStr( "вызываем убийство книги", (char*)__FUNCTION__ , GREEN );
    }
  return(0);
  }
}
//============================ Конец ===========================================
//(с) Metaler 2011. Вроде нормальный код =)-------------------------------------
