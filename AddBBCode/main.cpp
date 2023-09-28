

#include "header\softkeys.h"
#include "header\main.h"


//------------------------------------------------------------------------------
//==========* книги и гуи *=====================================================
TEXTID SoftkeyNameID;
BOOK * curn_book=0;  //флаг нужной книги
u16 timer;  // таймер добавлени€ софта
MyBOOK * mbk; //книга дл€ моего гу€
BOOK * AddBBCodeBook;  //книга дл€ букмана
GUI * addSoftkey_gui;  //указатель на GUI дл€ убийства софта
wchar_t Softkey_ElfAction;
char* __BOOK_NAME_1;
char* __BOOK_NAME_2;
char* __BOOK_NAME_3;
char* __BOOK_NAME_4;
char* __BOOK_NAME_5;

void MainMenuCreate(BOOK* bk, GUI_LIST* gui);
//===================================================================================================
// дл€ букмана //
typedef struct //
{              //
  BOOK * book; //
}MSG;          //
/////////////////

// ======================== вс€ка€ служебна€ ерунда ===========================================
#if defined(DEBUG)
void LogStr2(char* str,char* str2)
{
  int file;
  if((file=w_fopen(L"card/addbbcode_Log.txt", WA_Create+WA_Append, 0x1FF, 0))>-1)
  {
    char str0[256];
    sprintf(str0," *mess--> %s\nfunc----> %s\n\n",str,str2);
    w_fwrite(file, str0, strlen(str0));
    w_fclose(file);
  }
}
#endif

void LoadBookName()
{
  __BOOK_NAME_1 = (char*)__BCFG_BOOK_NAME_1;
  __BOOK_NAME_2 = (char*)__BCFG_BOOK_NAME_2;
  __BOOK_NAME_3 = (char*)__BCFG_BOOK_NAME_3;
  __BOOK_NAME_4 = (char*)__BCFG_BOOK_NAME_4;
  __BOOK_NAME_5 = (char*)__BCFG_BOOK_NAME_5;
  _add_diez2color = BCFG_add_diez2color;
}
/*
GUI *BookObj_GetGUI(BOOK *book)
{
  return((GUI *)List_Get(book->xguilist->guilist, 0));
}
*/
int isMM_BrowserTopLevelBook( BOOK* book )
{
  return 0 == strcmp( book->xbook->name, MM_BROWSERTOPLEVELBOOK );
}

int isAddBBCode( BOOK* book )
{
  return 0 == strcmp( book->xbook->name, LNG_ELF_NAME );
}

int GetDB()
{
  switch(GetChipID()&CHIPID_MASK)
  {
    case CHIPID_DB2010:
    case CHIPID_DB2020:
    case CHIPID_PNX5230: return 1;
    case CHIPID_DB3150:
    case CHIPID_DB3200:
    case CHIPID_DB3210:
    case CHIPID_DB3350: return 2;
    default: return 1;
  }
}

//----- »щем книгу по названию + java ---------------------------------------------------------------

BOOK* findbook(const char* name)
{
#if defined(DEBUG)
    debug_printf("\nф”Ќ ÷»я -  <font color=#0000ff> findbook \n</font>");
#endif

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
      if(!strcmp(book->xbook->name, name))  return book;
      //java
      TextID_GetString( BookObj_GetSession(book)->name, javaname, MAXELEMS(javaname) );
      if(!strcmp(javaname, name))  return book;
    }   
  }
  return NULL; 
}

//=================================================================

void Create_SoftkeysElfs( GUI*  gui )
{
  GUI *list_menu = (GUI*)gui;

  wchar_t SoftkeyAction_BBCode = Softkey_ElfAction = Softkeys_GetFreeAction(list_menu);
  GUIObject_SoftKeys_SetAction(list_menu, SoftkeyAction_BBCode, MainMenuCreate);
  StringInput_MenuItem_SetPriority( list_menu, 2, SoftkeyAction_BBCode );
  GUIObject_SoftKeys_SetText(list_menu, SoftkeyAction_BBCode, TextID_Create(LNG_SOFTKEY_NAME,ENC_UCS2,TEXTID_ANY_LEN));
  GUIObject_SoftKeys_SetInfoText( list_menu, SoftkeyAction_BBCode, TextID_Create(LNG_SOFTKEY_INFO_TEXT,ENC_UCS2,TEXTID_ANY_LEN));
  GUIObject_SoftKeys_SetVisible(list_menu, SoftkeyAction_BBCode, true);
}
//=================================================================
//  а не топлевел ли?
bool isTopLevelBook(BOOK * fbk)
{
  if(fbk!=FindBook(isMM_BrowserTopLevelBook))
    return (false);
  else
    return (true);
}

GUI* BookList_FindGUI(void)
{
#if defined(DEBUG)
    debug_printf("\nф”Ќ ÷»я -  <font color=#0000ff> %s. провер€ем в какой книге сейчас  и возвращаем гуи \n</font>",(char*)__FUNCTION__);
#endif

  BOOK * fbk = Display_GetTopBook(0);
  if( !isTopLevelBook(fbk) )
    if( (  fbk == findbook( __BOOK_NAME_1 ))
         || (fbk == findbook( __BOOK_NAME_2 ))
         || (fbk == findbook( __BOOK_NAME_3 ))
         || (fbk == findbook( __BOOK_NAME_4 ))
         || (fbk == findbook( __BOOK_NAME_5 )) )
    {
      GUI *gui=FindGuiInBook(fbk, "StringInput");
      if(gui!=0)
      {
        curn_book=fbk;
        return gui;
      }
    }
  return (0);
}
//====================== надо ли добавл€ть софт? ================================================

//-------- “аймер ---------------------------------------------------------------------------------
void onTimer (u16 timerID , LPARAM n)
{
  if(!findbook(BBCODEGUI))
  {
    GUI* gui=BookList_FindGUI();
    if( gui!=0 )
    {
      if ( Softkeys_FindInList( gui, SoftkeyNameID ) != 1 )
      {
        addSoftkey_gui=gui;
        Create_SoftkeysElfs(gui);
        goto timer_reset;
      }
    }
   /* else
    {
      #if defined(DEBUG)
        debug_printf("\nф”Ќ ÷»я - %s <font color=#0000ff>----------- не добавл€ем! \n</font>",(char*)__FUNCTION__);
      #endif
      goto timer_reset;
    } */
  }
 // else goto timer_reset;
  
 timer_reset:
 {
   curn_book=0;
   Timer_ReSet(&timer,800,onTimer,n);
 }
}


//=========* разные нужные штуки *==============================================
void elf_exit(void)
{
#if defined(DEBUG)
  debug_printf("\n ф”Ќ ÷»я <font color=#0000ff> elf_exit начало\n</font>");
#endif

  kill_data(&ELF_BEGIN, (void(*)(void*))mfree_adr());
  
#if defined(DEBUG)
   debug_printf("<font color=#0000ff> \n\n-----------\n”Ѕ»Ћ» ЁЋ№‘!! » ќ—¬ќЅќƒ»Ћ» ѕјћя“№\n</font>\n</pre></body></html>");
#endif
}


int TerminateElf(void * ,BOOK* book)
{
#if defined(DEBUG)
  debug_printf("\n ф”Ќ ÷»я -  <font color=#0000ff> TerminateElf \n</font>");
#endif

  if(book) FreeBook(book); 
  return(1);
}


//---------------- инфа о авторе ------------------------------------------------------------------

int ShowAuthorInfo(void *mess ,BOOK* book)
{
  MSG * msg = (MSG*)mess;
  wchar_t info[256];
#if defined(NDEBUG)
  snwprintf(info,255,L"%s \n%s\n%s",LNG_ELF_NAME,LNG_ELF_VERSION,LNG_ELF_AUTHOR);
#elif defined(DEBUG)
  snwprintf(info,255,L"AddBBCode_debag\ndedug\n(c)Metaler");
#endif
  MessageBox(EMPTY_TEXTID,TextID_Create(info,ENC_UCS2,TEXTID_ANY_LEN),NOIMAGE,1,6000,msg->book);
  return(1);
}

//================================================================================
//------------- открытие конфига в букмане --------------------------------------------------------

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
    MessageBox(0x6FFFFFFF, STR(LNG_NOT_FOUND_BCFGEDIT_ELF), NOIMAGE, 1 ,5000, 0);
    return (1);
  }
  wstrcat(path,L"/BcfgEdit.elf");
  elfload(path,(void*)successed_config_path,(void*)successed_config_name,0);
  return (1);
}

static int ReconfigElf(void *mess ,BOOK *book)
{
  RECONFIG_EVENT_DATA *reconf=(RECONFIG_EVENT_DATA *)mess;
  int result=0;
  if (wstrcmpi(reconf->path,successed_config_path)==0 && wstrcmpi(reconf->name,successed_config_name)==0)
   {
    InitConfig();
    result=1;
   }
  LoadBookName();
  return(result);
}

//========* ивенты *============================================================

const PAGE_MSG AddBBCode_PageEvents[]@ "DYN_PAGE" ={
  ELF_TERMINATE_EVENT, TerminateElf,
  ELF_SHOW_INFO_EVENT, ShowAuthorInfo,
  ELF_RECONFIG_EVENT , ReconfigElf,
  ELF_BCFG_CONFIG_EVENT, onBcfgConfig,
  NIL_EVENT_TAG, NULL
};

PAGE_DESC base_page ={"AddBBCode_BasePage",0,AddBBCode_PageEvents}; 
//======*  создаЄм книгу дл€ моего гуи *========================================

MyBOOK * Create_BBCodeGUIBook()
{
#if defined(DEBUG)
  debug_printf("\nф”Ќ ÷»я -  <font color=#0000ff> Create_BBCodeGUIBook. создаЄм книгу дл€ гуи \n</font>");
#endif

  mbk = new MyBOOK;
  CreateBook(&(mbk->book),NULL,NULL,BBCODEGUI,-1,0);
  return(mbk);
}


//=========* «апускаем наше меню *==============================================

void MainMenuCreate(BOOK* bk, GUI_LIST* )
{  
  if(!findbook(BBCODEGUI))
  {
    #if defined(DEBUG)
      debug_printf("\nф”Ќ ÷»я -  <font color=#0000ff> MainMenuCreate. создаЄм GUI  \n</font>");
    #endif
    
    Create_BBCodeGUIBook();
    mbk->main_menu_SetCursorToItem=0;
    GuiCreateGuiList(0,&(mbk->book),mbk->main_gui); // gui.c
  }
}


//======* закрываем книгу дл€ букмана *==============================================
void onCloseAddBBCodeBook(BOOK * book)
{   
#if defined(DEBUG)
  debug_printf("\nф”Ќ ÷»я -  <font color=#0000ff> onCloseAddBBCodeBook. убиваем основную книгу \n</font>");
#endif

  if(book)
  { 
    ImgUpload();
    if(timer) Timer_Kill(&timer);
    if(findbook(BBCODEGUI)) MainMenuGUIBack(&mbk->book, mbk->current_gui); //------------------
    if(addSoftkey_gui) GUIObject_SoftKeys_RemoveItem( addSoftkey_gui, Softkey_ElfAction );
    SUBPROC(elf_exit);
  }
}

//=======* создаЄм книгу дл€ букмана *==========================================

BOOK * CreateAddBBCodeBook()
{
#if defined(DEBUG)
  debug_printf("\nф”Ќ ÷»я -  <font color=#0000ff> CreateMYBook. создаЄм основную книгу \n</font>");
#endif

  AddBBCodeBook = new BOOK;
  CreateBook(AddBBCodeBook,onCloseAddBBCodeBook,&base_page,LNG_ELF_NAME,-1,0);
  return(AddBBCodeBook);
}


int main (void)
{ 
  if ( !FindBook(isAddBBCode))
  {
    #if defined(DEBUG)
      debug_printf("<html><body bgcolor=#000000 text=#00dd00><pre>  \nф”Ќ ÷»я -  <font color=#0000ff> main. запускаем это чудо..\n</font> ");
    #endif
    
    InitConfig();
    CreateAddBBCodeBook();
    SoftkeyNameID = TextID_Create( SOFTKEYNAMEID, ENC_UCS2,TEXTID_ANY_LEN );
    LoadBookName();
    timer=Timer_Set(800,onTimer,30);
    ImgLoad();  //gui.c
    readconfig();
    if( ExecuteCutTable() )
      readconfig();
  }
  else
  {
    #if defined(DEBUG)
        debug_printf("\nф”Ќ ÷»я -  <font color=#0000ff> main. если уже запущен то....\n</font>");
    #endif

    MessageBox(EMPTY_TEXTID,STR(LNG_ELF_ALREADY_WORKS),NOIMAGE,1,5000,0);
    SUBPROC(elf_exit); 
  }
  return(0);
}

