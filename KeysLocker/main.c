//****************************************************************************//
//============================================================================//
//====================***KeysLocker v.1.0 bcfg***=======================//
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

#define ElfName "KeysLocker"
#define ElfVer "v.1.0"
#define ElfAuthor "(c)Metaler"

//Важные штуки------------------------------------------------------------------
typedef struct
{
  BOOK * book;
}MSG;

BOOK * PKPBook;

//----------------===Кейхук===--------------------------------------------------
int MyKey(int key,int r1,int mode,LPARAM,DISP_OBJ*dispobj)
 { 
//Кнопка 1----------------------------------------------------------------------   
   if(key==BCFG_k1_KeyCode && mode==BCFG_k1_KeyMode )                                                                        
    { 
      return(-1);
    }
//конец Кнопка 1----------------------------------------------------------------

   if(key==BCFG_k2_KeyCode && mode==BCFG_k2_KeyMode )                                                                        
    { 
      return(-1);
    }
    
    
    if(key==BCFG_k3_KeyCode && mode==BCFG_k3_KeyMode )                                                                        
    { 
      return(-1);
    }
    
    if(key==BCFG_k4_KeyCode && mode==BCFG_k4_KeyMode )                                                                        
    { 
      return(-1);
    }
    
    if(key==BCFG_k5_KeyCode && mode==BCFG_k5_KeyMode )                                                                        
    { 
      return(-1);
    }
    
    if(key==BCFG_k6_KeyCode && mode==BCFG_k6_KeyMode )                                                                        
    { 
      return(-1);
    }
    
    if(key==BCFG_k7_KeyCode && mode==BCFG_k7_KeyMode )                                                                        
    { 
      return(-1);
    }
    
    if(key==BCFG_k8_KeyCode && mode==BCFG_k8_KeyMode )                                                                        
    { 
      return(-1);
    }
    
    if(key==BCFG_k9_KeyCode && mode==BCFG_k9_KeyMode )                                                                        
    { 
      return(-1);
    }
    
    if(key==BCFG_k10_KeyCode && mode==BCFG_k10_KeyMode )                                                                        
    { 
      return(-1);
    }
    
    
 return(0);
 }
//конец Кнопки 3----------------------------------------------------------------
//--------------===конец Кейхука===---------------------------------------------
//============================================================================== 
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
  ModifyKeyHook(MyKey,KEY_HOOK_REMOVE,NULL);
  FreeBook(book);
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
  SUBPROC(elf_exit);
}

//------------===Информация об эльфе===-----------------------------------------
int ShowAuthorInfo(void *mess ,BOOK* book)
{
  MSG * msg = (MSG*)mess;
  wchar_t info[256];
  snwprintf(info,255,L"%s\n%s\n%s",ElfName,ElfVer,ElfAuthor);
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
  CreateBook(PKPBook,onClosePKPBook,&base_page,ElfName,-1,0);
  return(PKPBook);
}

//---------------===Проверяем, а не запущен ли наш эльф?===---------------------
int myFind(BOOK* book)
{
   if(!strcmp(book->xbook->name,ElfName))
     return(1);
   return(0);
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
    CreatePKPBook();
    InitConfig();
    ModifyKeyHook(MyKey,KEY_HOOK_ADD,NULL);
    return(0);
  }
}
//============================ Конец ===========================================
//(с) Metaler 2011. Вроде нормальный код =)-------------------------------------
