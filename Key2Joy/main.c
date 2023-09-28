//****************************************************************************//
//============================================================================//
//=========================***Key2Joy v.1.0 bcfg***===========================//
//=========================***(c)Metaler 20011.***============================//
//============================================================================//
//****************************************************************************//
//========================***�������***=========================================
#include "..\\include\Lib_Clara.h"
#include "..\\include\Dir.h"
#include "..\\include\cfg_items.h"
#include "conf_loader.h"
#include "config_data.h"
#define ELF_BCFG_CONFIG_EVENT 994

#define ElfName "Key2Joy"
#define ElfVer "v.1.0"
#define ElfAuthor "(c)Metaler"

//������ �����------------------------------------------------------------------
typedef struct
{
  BOOK * book;
}MSG;

BOOK * PKPBook;

// � �� � ���� ����� �� ��? ----------------------------------------------------
int OffBook()
{ 
  char StringInput[]="StringInput";
  int StrIp=strcmp(DispObject_GetName(Display_GetFocusedDispObject(0)),StringInput);
  if ( StrIp==0 )      
   {
    return(0);
   }
 
};

//----------------===������===--------------------------------------------------
int MyKey(int key,int r1,int mode,LPARAM,DISP_OBJ*dispobj)
 { 
// �������� ����� --------------------------------------------------------------
   if(key==KEY_DIGITAL_0+2 && mode==KBD_SHORT_PRESS && !(OffBook()==0) && !(isKeylocked()))                                                                        
    {  
       return( KEY_UP );
     }
     
// �������� ���� --------------------------------------------------------------     
   if(key==KEY_DIGITAL_0+8 && mode==KBD_SHORT_PRESS && !(OffBook()==0) && !(isKeylocked()))// && (Display_GetTopBook(0) ))                                                                        
    {  
       return( KEY_DOWN );
     }
     
// �������� ������ --------------------------------------------------------------     
   if(key==KEY_DIGITAL_0+6 && mode==KBD_SHORT_PRESS && !(OffBook()==0) && !(isKeylocked()))// && (Display_GetTopBook(0)))                                                                    
    {  
       return( KEY_RIGHT );
     }
     
// �������� ����� --------------------------------------------------------------
   if(key==KEY_DIGITAL_0+4 && mode==KBD_SHORT_PRESS && !(OffBook()==0) && !(isKeylocked()))// && (Display_GetTopBook(0)))                                                                    
    {  
       return( KEY_LEFT );
     }
     
// �������� ������ --------------------------------------------------------------
   if(key==KEY_DIGITAL_0+5 && mode==KBD_SHORT_PRESS && !(OffBook()==0) && !(isKeylocked()))// && (Display_GetTopBook(0)))                                                                    
    {  
       return( KEY_ENTER );
     }
     
   if(key==BCFG_InputKeyEnter && mode==BCFG_InputKeyEnter_KeyMode && (OffBook()==0) && !(isKeylocked()))// && (Display_GetTopBook(0)))                                                                    
    {  
       return( KEY_ENTER );
     }
//==============================================================================
//======================*** �������� ���� long press ***======================== 
 int i=0;
    if (key==KEY_DIGITAL_0+8 && mode==KBD_SHORT_RELEASE && !(OffBook()==0) && !(isKeylocked()))
          {
            i=1;
          }
          
   if(key==KEY_DIGITAL_0+8 && mode==KBD_LONG_PRESS && !(OffBook()==0) && !(isKeylocked()))                                                                        
    {  
       
      for(;;)
        { 
          
          if (!(i==1))
          {
            return( KEY_DOWN );
          }
          else {
                break;
               }
        }  
    }      
     
     
     
     
       
  return(0);     
};             
//����� ������ 1----------------------------------------------------------------
//------------------------------------------------------------------------------

//--------------===����� �������===---------------------------------------------
//============================================================================== 
//--------------===��� �������===-----------------------------------------------
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

//----------===��� ������ ��� �������� �����===---------------------------------
int TerminateElf(void * ,BOOK* book)
{
  ModifyKeyHook(MyKey,KEY_HOOK_REMOVE,NULL);
  FreeBook(book);
  return(1);
}

//----------===������� ������ �����===------------------------------------------
void elf_exit(void)
{
  kill_data(&ELF_BEGIN, (void(*)(void*))mfree_adr());
}

//----------===��� ������ ��� �������� �����===---------------------------------
void onClosePKPBook(BOOK * book)
{
  SUBPROC(elf_exit);
}

//------------===���������� �� �����===-----------------------------------------
int ShowAuthorInfo(void *mess ,BOOK* book)
{
  MSG * msg = (MSG*)mess;
  wchar_t info[256];
  snwprintf(info,255,L"%s\n%s\n%s",ElfName,ElfVer,ElfAuthor);
  MessageBox(EMPTY_TEXTID,TextID_Create(info,ENC_UCS2,TEXTID_ANY_LEN),NOIMAGE,1,5000,msg->book);
  return(1);
}

//-------------===��� ������ ������� ����� ��� �������===-----------------------
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
    MessageBox(0x6FFFFFFF, STR("�� ���� ����� BcfgEdit.elf! =("), NOIMAGE, 1 ,5000, 0);
    return (1);
  }
  wstrcat(path,L"/BcfgEdit.elf");
  elfload(path,(void*)successed_config_path,(void*)successed_config_name,0);
  return (1);
}

//--------------------------===������===----------------------------------------
const PAGE_MSG HW_PageEvents[]@ "DYN_PAGE" ={
  ELF_TERMINATE_EVENT, TerminateElf,
  ELF_SHOW_INFO_EVENT, ShowAuthorInfo,
  ELF_RECONFIG_EVENT , ReconfigElf,
  ELF_BCFG_CONFIG_EVENT, onBcfgConfig,
  NIL_EVENT_TAG, NULL
};

PAGE_DESC base_page ={"HW_BasePage",0,HW_PageEvents};

//---------------------===������� ��� ��� �����===------------------------------
BOOK * CreatePKPBook()
{
  PKPBook= new BOOK;
  CreateBook(PKPBook,onClosePKPBook,&base_page,ElfName,-1,0);
  return(PKPBook);
}

//---------------===���������, � �� ������� �� ��� ����?===---------------------
int myFind(BOOK* book)
{
   if(!strcmp(book->xbook->name,ElfName))
     return(1);
   return(0);
}

//--------------------===��������� ��� ��� ����===------------------------------
int main (void)
{
  if (FindBook(myFind))
  {
    MessageBox(EMPTY_TEXTID,STR("��� ������� =)"),NOIMAGE,1,3000,0);
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
//============================ ����� ===========================================
//(�) Metaler 2011. ����� ���������� ��� =)-------------------------------------
