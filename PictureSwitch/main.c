//****************************************************************************//
//============================================================================//
//====================***PictureSwitch v.1.0 bcfg***==========================//
//=========================***(c)Metaler 20011.***============================//
//============================================================================//
//****************************************************************************//
//========================***�������***=========================================
#include "..\\include\Lib_Clara.h"
#include "..\\include\Dir.h"

#define ElfName "PictureSwitch"
#define ElfVer "v.1.0"
#define ElfAuthor "(c)Metaler"

//������ �����------------------------------------------------------------------
typedef struct
{
  BOOK * book;
}MSG;

BOOK * PKPBook;


//==============================================================================
int isBook(BOOK* book,int* param)
{
  if(!strcmp(book->xbook->name, (char*)param)) return (1);
  return (0);
}

int DispObj()
 {
   char StringInput[]="ListObject";
  int StrIp=strcmp(DispObject_GetName(Display_GetFocusedDispObject(0)),StringInput);
  if ( StrIp==0 )
  {
     return (0);
  }
  else {
   return(1);
  }
 }

//----------------===������===--------------------------------------------------
int MyKey(int key,int r1,int mode,LPARAM,DISP_OBJ*dispobj)
 { 
//������ 1----------------------------------------------------------------------   
 if(key==KEY_UP && mode==KBD_SHORT_PRESS && (Display_GetTopBook(0)==FindBookEx(isBook, (int*)"ImageViewerBook")) && !(isKeylocked()) && (DispObj()==1) && ( 0==BookObj_GetDisplayOrientation( FindBookEx(isBook, (int*)"ImageViewerBook") ) ) )                                                                       
    {  
       return( KEY_LEFT );
     }
     
  if(key==KEY_DOWN && mode==KBD_SHORT_PRESS && (Display_GetTopBook(0)==FindBookEx(isBook, (int*)"ImageViewerBook")) && !(isKeylocked()) && (DispObj()==1) && ( 0==BookObj_GetDisplayOrientation( FindBookEx(isBook, (int*)"ImageViewerBook") ) ) )                                                                        
    {  
       return( KEY_RIGHT );
     }
     
   if(key==KEY_UP && mode==KBD_SHORT_PRESS && (Display_GetTopBook(0)==FindBookEx(isBook, (int*)"ImageViewerBook")) && !(isKeylocked()) && (DispObj()==1) && ( 1==BookObj_GetDisplayOrientation( FindBookEx(isBook, (int*)"ImageViewerBook") ) ) )                                                                        
    {  
       return( KEY_LEFT );
     }
     
  if(key==KEY_DOWN && mode==KBD_SHORT_PRESS && (Display_GetTopBook(0)==FindBookEx(isBook, (int*)"ImageViewerBook")) && !(isKeylocked()) && (DispObj()==1) && ( 1==BookObj_GetDisplayOrientation( FindBookEx(isBook, (int*)"ImageViewerBook") ) ) )                                                                        
    {  
       return( KEY_RIGHT );
     }
 return(0);
};             
//����� ������ 1----------------------------------------------------------------
//------------------------------------------------------------------------------

//--------------===����� �������===---------------------------------------------
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

//--------------------------===������===----------------------------------------
const PAGE_MSG HW_PageEvents[]@ "DYN_PAGE" ={
  ELF_TERMINATE_EVENT, TerminateElf,
  ELF_SHOW_INFO_EVENT, ShowAuthorInfo,
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
    ModifyKeyHook(MyKey,KEY_HOOK_ADD,NULL);
    return(0);
  }
}
//============================ ����� ===========================================
//(�) Metaler 2011. ����� ���������� ��� =)-------------------------------------
