#include "..\\include\Lib_Clara.h"
#include "..\\include\Dir.h"
#include "..\\include\Types.h"
#include "..\\include\var_arg.h"
#include "main.h"

#define ELF_NAME "QuickAccess"
#define ELF_VER  "1.0"
#define QUICKACCESS_MENU_BOOK_NAME "QAMenu_Book"

#define LIST_ITEM_COUNT 13

void QuickAccess_menu( void* r0,BOOK* bk,GUI_LIST* gui );
//=====================

BOOK * QuickAccessBook;
MyBOOK * mbk;
u16 timer;

GUI* QuestionReboot_GUI;
GUI* QuestionShutdown_GUI;

TEXTID names_textid[LIST_ITEM_COUNT];

wchar_t* names_str[] = {
  L"Перезагрузка",      
  L"Выключение",       
  L"Блокировка",
  L" ", // Беззвучный    
  L"Фонарик", 
  L" "
};

int imageid[] = {
  0x8FE,
  0x13F,
  0x47A,
  0x81E,
  0x2E1,
  NOIMAGE,
  0x7DD,
  0x7DA,
  0x7D4,
  0x7E3,
  0x7E9,
  0x7D1,
  0x7E0
};


int isBook(BOOK* book, int* param)
{
  if(!strcmp( book->xbook->name, (char*)param)) return (1);
  return (0);
}

int isCallListBook( BOOK* book )
{
  return 0 == strcmp( book->xbook->name, "PB_UI_CallListBook" );
}

int isMyQABook( BOOK* book )
{
  return 0 == strcmp( book->xbook->name, QUICKACCESS_MENU_BOOK_NAME );
}

//-- YesNoQuestionVA Reboot ----------------------------------------------------------------------------------
void OnNo_QuestionReboot(BOOK * bk, void *)
{
  FREE_GUI(QuestionReboot_GUI);
}
 
void OnYes_QuestionReboot(BOOK * bk, void *)
{
  FREE_GUI(QuestionReboot_GUI);
  REQUEST_SYSTEM_RESTART();
}
 
void Create_QuestionReboot(BOOK* bk)
{
  QuestionReboot_GUI = CreateYesNoQuestionVA(0,
                        VAR_BOOK( bk ),
                        VAR_YESNO_PRE_QUESTION( STR("Перезагрузить телефон?") ),
                        //VAR_YESNO_QUESTION( STR("Продолжить?") ),
                        VAR_YESNO_YES_ACTION( OnYes_QuestionReboot ),
                        VAR_YESNO_NO_ACTION( OnNo_QuestionReboot ),
                        0);
  YesNoQuestion_SetIcon( QuestionReboot_GUI, 0x140);
}
//------------------------------------------------------------------------------------------------------------

//-- YesNoQuestionVA Shutdown --------------------------------------------------------------------------------
void OnNo_QuestionShutdown(BOOK * bk, void *)
{
  FREE_GUI(QuestionShutdown_GUI);
}
 
void OnYes_QuestionShutdown(BOOK * bk, void *)
{
  FREE_GUI(QuestionShutdown_GUI);
  REQUEST_SYSTEM_SHUTDOWN();
}
 
void Create_QuestionShutdown(BOOK* bk)
{
  QuestionShutdown_GUI = CreateYesNoQuestionVA(0,
                        VAR_BOOK( bk ),
                        VAR_YESNO_PRE_QUESTION( STR("Выключить телефон?") ),
                        //VAR_YESNO_QUESTION( STR("Продолжить?") ),
                        VAR_YESNO_YES_ACTION( OnYes_QuestionShutdown ),
                        VAR_YESNO_NO_ACTION( OnNo_QuestionShutdown ),
                        0);
  YesNoQuestion_SetIcon( QuestionShutdown_GUI, 0x140);
}
//------------------------------------------------------------------------------------------------------------
//======* i?e ia?aoee "iacaa" *=================================================
void GuiBack(BOOK* bk,GUI_LIST* gui)
{
  //if(timer) Timer_Kill(&timer);
  ListMenu_DestroyItems(gui);
  GUI_Free(gui);               // oaeaaai  aoe
  FreeBook(&(mbk->book));                // oaeaaai aoe
}

//------------------------------------------------------------------------------------------------------------
void SelectMenuItem_Reboot(BOOK* book)
{
  Create_QuestionReboot(book);
}

void SelectMenuItem_Shutdown(BOOK* book)
{
  Create_QuestionShutdown(book);
} 

void SelectMenuItem_KeyLock(void)
{
  UI_Event(UI_KEYLOCK_ACTIVATE_EVENT);
  UI_Event(UI_SLEEPMODE_ACTIVATE_EVENT);
}

void SelectMenuItem_SilenceMode(void)
{
  int current_profile;
      char mute;
      REQUEST_PROFILE_GETACTIVEPROFILE(SYNC, &current_profile);
      REQUEST_SETTING_SILENCE_GET(SYNC, current_profile, &mute); //получаем настройки режима "без звука"
      if(mute == 1)
      {  //если режим "без звука" включен
        REQUEST_SETTING_SILENCE_SET(SYNC,(u16)current_profile,(u16)0);
      }
      else
      if(mute == 0)
      {  //если режим "без звука" выключен
        REQUEST_SETTING_SILENCE_SET(SYNC,(u16)current_profile,(u16)1); 
      }
}

void SelectMenuItem_FlashLight(void)
{
  SetLampLevel(1);
}

void SelectMenuItem_SelectProfile(int NumProfile)
{
  Profile_SetActive(NumProfile, NumProfile);
}

void GuiOnEnterPressed(BOOK* book,GUI_LIST* gui)
{
  switch(ListMenu_GetSelectedItem(gui))
  {
    case 0: 
      {
        SelectMenuItem_Reboot(book);
        break;
      }
    case 1: 
      {
        SelectMenuItem_Shutdown(book);
        break;
      }
    case 2:
      {
        SelectMenuItem_KeyLock();
        GuiBack(book, gui);
        break;
      }
    case 3:
      {
        SelectMenuItem_SilenceMode();
        GuiBack(book, gui);
        break;
      }
    case 4:
      {
        SelectMenuItem_FlashLight();
        GuiBack(book, gui);
        break;
      }
    case 5:
      {
        GuiBack(book, gui);
        break;
      }
    case 6:
      {
        SelectMenuItem_SelectProfile(0);
        GuiBack(book, gui);
        break;
      }
    case 7:
      {
        SelectMenuItem_SelectProfile(1);
        GuiBack(book, gui);
        break;
      }
    case 8:
      {
        SelectMenuItem_SelectProfile(2);
        GuiBack(book, gui);
        break;
      }
    case 9:
      {
        SelectMenuItem_SelectProfile(3);
        GuiBack(book, gui);
        break;
      }
    case 10:
      {
        SelectMenuItem_SelectProfile(4);
        GuiBack(book, gui);
        break;
      }
    case 11:
      {
        SelectMenuItem_SelectProfile(5);
        GuiBack(book, gui);
        break;
      }
    case 12:
      {
        SelectMenuItem_SelectProfile(6);
        GuiBack(book, gui);
        break;
      }
  }
   //GuiBack(book, gui);
}

//=========* aiaaaeyai iacaaiey *===============================================
int GuiOnLBMessage(GUI_MESSAGE* msg)
{
  int index;
  switch(msg->__msg)
  {
    case 1:
    index = GUIonMessage_GetCreatedItemIndex(msg);
    if(index == 3)
    {
      int current_profile;
      char mute;
      REQUEST_PROFILE_GETACTIVEPROFILE(SYNC, &current_profile);
      REQUEST_SETTING_SILENCE_GET(SYNC, current_profile, &mute); //получаем настройки режима "без звука"
      if(mute == 1)
      {  //если режим "без звука" включен
        GUIonMessage_SetMenuItemText(msg, TextID_Create(L"Откл. беззвучный", ENC_UCS2,TEXTID_ANY_LEN));
      }
      else
      {  //если режим "без звука" выключен
        GUIonMessage_SetMenuItemText(msg, TextID_Create(L"Вкл. беззвучный", ENC_UCS2,TEXTID_ANY_LEN)); 
      }
    }
    else
    {
      GUIonMessage_SetMenuItemText(msg, names_textid[index]);
    }
    GUIonMessage_SetMenuItemIcon(msg, 0, imageid[index]);
    break;
  }
  return(1);
}

//==============================================================================

MyBOOK * Create_QuickAccessMenuBook()
{
  mbk = new MyBOOK;
  CreateBook(&(mbk->book), NULL, NULL, QUICKACCESS_MENU_BOOK_NAME, -1, NULL);
  return(mbk);
}


//=========* Запускаем наше меню *==============================================

void Create_QuickAccessMenu()
{
  if( !FindBook(isMyQABook) )
  {
    Create_QuickAccessMenuBook();
    QuickAccess_menu(0,&(mbk->book),mbk->gui); // gui.c
  }
}
//------------------------------------------------------------------------------
void onTimer(u16 timerID , LPARAM gui)
{
  DATETIME dt;
  int sec, min, hour, year, mon, day;
  REQUEST_DATEANDTIME_GET(0,&dt);
  hour = dt.time.hour;
  min = dt.time.min;
  sec = dt.time.sec;
  year = dt.date.year;
  mon = dt.date.mon;
  day = dt.date.day;
  wchar_t info[256];
  snwprintf(info,255,L"%i-%i-%i | %i:%i:%i", day, mon, year, hour, min, sec );
  GuiObject_SetTitleText((GUI*)gui, TextID_Create( info, ENC_UCS2,TEXTID_ANY_LEN));
  Timer_ReSet(&timer,1000,onTimer,gui);
}

//==============================================================================
void QuickAccess_menu( void* r0,BOOK* bk,GUI_LIST* gui )
{
  for(int i = 0; i < 6; i++)
  {
    names_textid[i] = TextID_Create(names_str[i], ENC_UCS2,TEXTID_ANY_LEN);
  }
  
  TEXTID_DATA utf8str;
  wchar_t SetName[0x10];
  utf8str.ptr = SetName;
  char error;  
  for(int i = 0,y = 6; i<7; i++, y++)
  { 
    REQUEST_PROFILE_GETPROFILENAME( SYNC, i, &utf8str, &error ); 
    names_textid[y] = TextID_Create(&utf8str, ENC_UT, utf8str.lenght);
  } 

  gui = CreateListMenu( bk, 0);
  //timer = Timer_Set(1000, onTimer, (LPARAM*)gui);
  ListMenu_SetItemCount(gui, LIST_ITEM_COUNT);
  ListMenu_SetOnMessage(gui, GuiOnLBMessage);
  SetCursorToItem(gui,0);
  SetMenuItemStyle(gui, 0);   //
  GUIObject_SetStyle(gui, 2);  //Full screen   4
  GuiObject_SetTitleText(gui, TextID_Create(L"QuickAccessMenu", ENC_UCS2,TEXTID_ANY_LEN));
  GUIObject_SoftKeys_SetAction(gui, ACTION_BACK,GuiBack);
  GUIObject_SoftKeys_SetAction(gui, ACTION_LONG_BACK,GuiBack);
  GUIObject_SoftKeys_SetAction(gui, ACTION_SELECT1,GuiOnEnterPressed);
  GUIObject_Show(gui);
}

int KeyPr ( int key, int r1, int mode, LPARAM lparam, DISP_OBJ*db )
{
  
  if(key==0x28 && mode==KBD_LONG_PRESS && !(isKeylocked()))
  {
    Create_QuickAccessMenu();
    return -1;
  }
  //--------------------------------
  if(key == KEY_UP && mode == KBD_SHORT_PRESS && !(isKeylocked()) && (Display_GetTopBook(0)==FindBookEx(isBook,(int*)QUICKACCESS_MENU_BOOK_NAME)))
  {
    GUI* gui = DispObject_GetGUI(db);
    if(ListMenu_GetSelectedItem(gui)==6)
      ListMenu_SetCursorToItem(gui, 5);
  }
  if(key == KEY_DOWN && mode == KBD_SHORT_PRESS && !(isKeylocked()) && (Display_GetTopBook(0)==FindBookEx(isBook,(int*)QUICKACCESS_MENU_BOOK_NAME)))
  {
    GUI* gui = DispObject_GetGUI(db);
    if(ListMenu_GetSelectedItem(gui)==4)
      ListMenu_SetCursorToItem(gui, 5);
  }
  //---------------------------------
  
  
  if(key == KEY_DIGITAL_0+1 && mode == KBD_SHORT_PRESS && !(isKeylocked()) && (Display_GetTopBook(0)==FindBookEx(isBook,(int*)QUICKACCESS_MENU_BOOK_NAME)))
  {
    SelectMenuItem_Reboot(Display_GetTopBook(0));
  }
     
  if(key == KEY_DIGITAL_0+2 && mode == KBD_SHORT_PRESS && !(isKeylocked()) && (Display_GetTopBook(0)==FindBookEx(isBook,(int*)QUICKACCESS_MENU_BOOK_NAME)))
  {
    SelectMenuItem_Shutdown(Display_GetTopBook(0));
  }
  
  if(key == KEY_DIGITAL_0+3 && mode == KBD_SHORT_PRESS && !(isKeylocked()) && (Display_GetTopBook(0)==FindBookEx(isBook,(int*)QUICKACCESS_MENU_BOOK_NAME)))
  {
    SelectMenuItem_KeyLock();
  }
     
  if(key == KEY_DIGITAL_0+4 && mode == KBD_SHORT_PRESS && !(isKeylocked()) && (Display_GetTopBook(0)==FindBookEx(isBook,(int*)QUICKACCESS_MENU_BOOK_NAME)))
  {
    SelectMenuItem_SilenceMode();
  }
     
  if(key == KEY_DIGITAL_0+5 && mode == KBD_SHORT_PRESS && !(isKeylocked()) && (Display_GetTopBook(0)==FindBookEx(isBook,(int*)QUICKACCESS_MENU_BOOK_NAME)))
  {
    SelectMenuItem_FlashLight();
  }
  // profile   
  if(key == KEY_DIGITAL_0+6 && mode == KBD_SHORT_PRESS && !(isKeylocked()) && (Display_GetTopBook(0)==FindBookEx(isBook,(int*)QUICKACCESS_MENU_BOOK_NAME)))
  {
     SelectMenuItem_SelectProfile(0);
  }
  if(key == KEY_DIGITAL_0+7 && mode == KBD_SHORT_PRESS && !(isKeylocked()) && (Display_GetTopBook(0)==FindBookEx(isBook,(int*)QUICKACCESS_MENU_BOOK_NAME)))
  {
     SelectMenuItem_SelectProfile(1);
  }
  if(key == KEY_DIGITAL_0+8 && mode == KBD_SHORT_PRESS && !(isKeylocked()) && (Display_GetTopBook(0)==FindBookEx(isBook,(int*)QUICKACCESS_MENU_BOOK_NAME)))
  {
     SelectMenuItem_SelectProfile(2);
  }
  if(key == KEY_DIGITAL_0+9 && mode == KBD_SHORT_PRESS && !(isKeylocked()) && (Display_GetTopBook(0)==FindBookEx(isBook,(int*)QUICKACCESS_MENU_BOOK_NAME)))
  {
     SelectMenuItem_SelectProfile(3);
  }
  if(key == KEY_STAR && mode == KBD_SHORT_PRESS && !(isKeylocked()) && (Display_GetTopBook(0)==FindBookEx(isBook,(int*)QUICKACCESS_MENU_BOOK_NAME)))
  {
     SelectMenuItem_SelectProfile(4);
  }
  if(key == KEY_DIGITAL_0 && mode == KBD_SHORT_PRESS && !(isKeylocked()) && (Display_GetTopBook(0)==FindBookEx(isBook,(int*)QUICKACCESS_MENU_BOOK_NAME)))
  {
     SelectMenuItem_SelectProfile(5);
  }
  if(key == KEY_DIEZ && mode == KBD_SHORT_PRESS && !(isKeylocked()) && (Display_GetTopBook(0)==FindBookEx(isBook,(int*)QUICKACCESS_MENU_BOOK_NAME)))
  {
     SelectMenuItem_SelectProfile(6);
  }
  /*
  if(key==0x28 && mode==KBD_LONG_PRESS && (isKeylocked()))
  {
    UI_Event(UI_SLEEPMODE_DEACTIVATE_EVENT);
    UI_Event(UI_KEYLOCK_DEACTIVATE_EVENT);
    return -1;
  } */
  
  if(key==0x28 && mode==KBD_SHORT_RELEASE && !(isKeylocked()))
  {
    UI_Event(UI_KEYLOCK_ACTIVATE_EVENT);
    UI_Event(UI_SLEEPMODE_ACTIVATE_EVENT);
    return -1;
  }

  return 0;
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
  snwprintf(info,255,L"%s \nv.%s\n(c)Metaler\n%s",ELF_NAME,ELF_VER,__DATE__);
  MessageBox(EMPTY_TEXTID,TextID_Create(info,ENC_UCS2,TEXTID_ANY_LEN),NOIMAGE,1,0,msg->book);
  return(1);
}

const PAGE_MSG QuickAccess_PageEvents[]@ "DYN_PAGE" ={
  ELF_TERMINATE_EVENT , TerminateElf,
  ELF_SHOW_INFO_EVENT  , ShowAuthorInfo,
  0,0
};

PAGE_DESC base_page = {"QuickAccess_BasePage",0,QuickAccess_PageEvents};

void elf_exit(void)

{
  kill_data(&ELF_BEGIN, (void(*)(void*))mfree_adr());
}

void OnClose_QuickAccessBook(BOOK * book)
{
  if (book)
  {
    ModifyKeyHook( KeyPr,0,0 );
    SUBPROC(elf_exit);
  }
}

//Проверяем, а не запущен ли наш эльф?------------------------------------------
int Find_QuickAccessBook(BOOK* book)
{
  if(!strcmp(book->xbook->name,ELF_NAME))
    return(1);
  return(0);
}

BOOK * Create_QuickAccessBook()
{
  QuickAccessBook = new BOOK;
  CreateBook(QuickAccessBook, OnClose_QuickAccessBook, &base_page, ELF_NAME, -1, 0);
  return(QuickAccessBook);
}

int main (void)
{
  if (FindBook(Find_QuickAccessBook))
  {
    MessageBox(EMPTY_TEXTID,STR("Ну хватит меня тыкать ;("),NOIMAGE,1,5000,0);
    SUBPROC(elf_exit);
  }
  else
  {
    Create_QuickAccessBook();
    ModifyKeyHook( KeyPr, KEY_HOOK_ADD, NULL );
    return(0);
  }
}
