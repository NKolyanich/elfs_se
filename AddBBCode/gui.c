#include "..\\include\Lib_Clara.h"
#include "..\\include\Dir.h"
#include "..\\include\var_arg.h"
#include "header\main.h"
#include "header\gui.h"
#include "header\pictureGUI.h"
#include "header\fontGUI.h"
#include "header\colorGUI.h"
#include "header\SmilesMenu.h"


#if defined(LNG_RUS)
    #include "header\LANGUAGE_RUS.h"
#elif defined(LNG_ENG)
    #include "header\LANGUAGE_ENG.h"
#endif

//------------------------------------------------------------------------------
void CreateStringInput(wchar_t * editable_strID, wchar_t *  fixed_strID, int mode, int MAX_LEN );

wchar_t img[27];
//==----------------------------------------------------------------------------
 wchar_t* iconname[27]=
{ 
  L"bold.png",
  L"incline.png",
  L"underlined.png",
  L"strikethrough.png",
  L"dash.png",
  L"url.png",
  L"hide.png",
  L"size.png",
  L"list.png",
  L"line.png",
  L"link.png",
  L"img.png",
  L"quote.png",
  L"vkp.png",
  L"code.png",
  L"spoiler.png",
  L"color.png",
  L"smile.png", //
  L"size_xx-s.png",
  L"size_x-s.png",
  L"size_s.png",
  L"size_m.png",
  L"size_l.png",
  L"size_x-l.png",
  L"img_c.png",
  L"img_r.png",
  L"img_l.png"
};
//-------------------------------------------------------
int ImgLoad()
{
  FSTAT _fstat;
  wchar_t path_card[256];
  wchar_t path_usb[256];
  wchar_t path[256];
  wstrcpy(path_card,GetDir(DIR_ELFS_CONFIG | MEM_EXTERNAL));
  wstrcat(path_card,L"/AddBBCode");
  wstrcpy(path_usb,GetDir(DIR_ELFS_CONFIG | MEM_INTERNAL));
  wstrcat(path_usb,L"/AddBBCode");
  int i;
  for(i=0;i<27;i++)
  {
    if( fstat( path_card, iconname[i],&_fstat)>=0 )
    {
      wstrcpy( path, path_card );
    }
    else if( fstat( path_usb, iconname[i], &_fstat)>=0 )
    {
      wstrcpy( path, path_usb );
    }
    else 
    {
      mkdir( (wchar_t*)path_card );
      mkdir( (wchar_t*)path_usb );
    }
    ImageID_Get(path,iconname[i],&img[i]);
  }
 return 0;
}
//---------------------------------------------------------------

int ImgUpload()
{
  for(int i=0;i<27;i++)
  { 
    ImageID_Free(img[i]);
  }
  return 0;   
}
//----------------------------------------------------------------------

wchar_t* names[]= { // начинается с нуля
 LNG_ITEM_MAINGUI_NAME_0,
 LNG_ITEM_MAINGUI_NAME_1,
 LNG_ITEM_MAINGUI_NAME_2,
 LNG_ITEM_MAINGUI_NAME_3,
 LNG_ITEM_MAINGUI_NAME_4,
 LNG_ITEM_MAINGUI_NAME_5,
 LNG_ITEM_MAINGUI_NAME_6,
 LNG_ITEM_MAINGUI_NAME_7,
 LNG_ITEM_MAINGUI_NAME_8,
 LNG_ITEM_MAINGUI_NAME_9,
 LNG_ITEM_MAINGUI_NAME_10,
 LNG_ITEM_MAINGUI_NAME_11,
 LNG_ITEM_MAINGUI_NAME_12,
 LNG_ITEM_MAINGUI_NAME_13,
 LNG_ITEM_MAINGUI_NAME_14,
 LNG_ITEM_MAINGUI_NAME_15,
 LNG_ITEM_MAINGUI_NAME_16,
 LNG_ITEM_MAINGUI_NAME_17
};

wchar_t* bbcode[]= {
 L"[b][/b]",  //жирный
 L"[i][/i]",  //наклонный
 L"[u][/u]",  //подчёркнутый
 L"[s][/s]",  //зачёркнутый
 L"\n-----------\n",   // прочерк
 L"http://",           //ссылка
 L"[hide][/hide]",     //скрытый
 ///.....
 L"",  //размер
 ////.........
 L"[list][/list]",       // список
 L"\n[hr]\n",              // линия
 L"[url=][/url]",  //URL
 ///......
 L"",  //поз. картинки
 ////.............
 L"[quote][/quote]",      //цитата
 L"[vkp][/vkp]",          //Vkp
 L"[code][/code]",        //C-код
 L"[spoiler=][/spoiler]"  //спойлер
 ///..........
//коды цветов
 ///.........
};

int len[]= {
  3,
  3,
  3,
  3,
  13,
  7,
  6,
 //..
  0,
 //...
  6,
  6,  //6
  5,
 //..
  0,
 //...
  7,
  5,
  6,
  9
 ///...

};

//======* при нажатии "назад" *=================================================

void MainMenuGUIBack(BOOK* bk,GUI* gui)
{
  if(gui==mbk->color_gui) termColorGUI(); //убиваем таймер и перерисовку
  else if(gui==mbk->smile_gui) termSmileMenu();
    else
    if(gui!=mbk->StringInputVA)
      if(gui) ListMenu_DestroyItems(gui);

  FREE_GUI(gui);
  gui=0;
  ModifyKeyHook(MainMenuKeyHook,KEY_HOOK_REMOVE,0);
  if(findbook(BBCODEGUI)) FreeBook(bk);        // убиваем бук
}


//===========* ф-я вставки тега *=======================================
void TextCopi(BOOK* bk,GUI_LIST* gui,wchar_t* bbcode,int len)
{
  MainMenuGUIBack(&(mbk->book), gui);
//------------------------------------------------------------------------------
  u16 pos;  // текущая позиция курсора
  char _zero; // нуль
  u16 strlen; // длинна строки из StringInput'а
  wchar_t* oldstring=0; // строка из StringInput'а
  StringInput_GetCursorPosition( DispObject_GetGUI(Display_GetFocusedDispObject(0) ), &pos,  &_zero );  //                                     
  StringInput_GetStringAndLen( DispObject_GetGUI(Display_GetFocusedDispObject(0) ), &oldstring, &strlen); //
  
  int k;
  if(GetDB()==2) k=0; //?????????
  else if(pos==0) k=0;
       else k=1;
// получаем первую часть строки, до позиции курсора
  wchar_t *src=new wchar_t[strlen+wstrlen( bbcode )+4];
  wstrncpy(src, oldstring, pos+k);                          
  src[pos+k]='\0';
    
  int lenstr=wstrlen(src);
   
// получаем вторую часть, после позиции курсора 
  wchar_t *secondtext=0; 
  secondtext = oldstring+pos+k; 
  secondtext[strlen-pos+k]='\0';               
  // соединяем   
  wstrcat(src, bbcode);                
  src[pos+k + wstrlen(bbcode)]='\0'; 
  wstrcat(src, secondtext);         
  src[strlen + wstrlen(bbcode)]='\0';     
 // вставляем обратно в StringInput
  StringInput_DispObject_SetText( Display_GetFocusedDispObject(0) ,TextID_Create( src, ENC_UCS2,TEXTID_ANY_LEN));                  
  delete src;
 //ставим курсор куда положено 
  u16 _curspos; //lenstr,
  int _unk=0;
  if(GetDB()==1) _unk=1;
  else if(GetDB()==2) _unk=0;
  else _unk=1;
  _curspos=lenstr+len;
  StringInput_SetCursorPosition( DispObject_GetGUI( Display_GetFocusedDispObject(0) ), _curspos, _unk);
}

//==============================================================================
int MainMenuKeyHook(int key, int r1, int mode, LPARAM, DISP_OBJ* dispobj)
{
  char StringInput[]="StringInput";//"ListObject";
  int strinp = strcmp(DispObject_GetName(dispobj),StringInput);
  if( !(isKeylocked()) && (Display_GetTopBook(0)== findbook(BBCODEGUI) ) && (strinp!=0) )
  {
    if( key==KEY_DIGITAL_0+2 && mode==KBD_SHORT_PRESS )
    {
      return(KEY_UP);
    }
    if( key==KEY_DIGITAL_0+8 && mode==KBD_SHORT_PRESS )
    {
      return(KEY_DOWN);
    }
    if( key==KEY_DIGITAL_0+5 && mode==KBD_SHORT_PRESS )
    {
      return(KEY_ENTER);
    }
    if( key==KEY_DIGITAL_0+4 && mode==KBD_SHORT_PRESS )
    {
      return(KEY_LEFT);
    }
    if( key==KEY_DIGITAL_0+6 && mode==KBD_SHORT_PRESS )
    {
      return(KEY_RIGHT);
    }
    return(0);
  }
  return 0;
}

//========* при выборе пункта меню *============================================
void MainGUIDestroy(GUI_LIST* maingui)
{
  if(maingui)
  {
    ModifyKeyHook(MainMenuKeyHook,KEY_HOOK_REMOVE,0);
    ListMenu_DestroyItems(maingui); //убиваем лист меню
    GUIObject_Destroy(maingui);
    maingui=0;
  }
}

void GuiOnEnterPressed(BOOK* bk,GUI_LIST* gui)
{
  switch(ListMenu_GetSelectedItem(gui))
   { 
    case 0: TextCopi(bk, gui, bbcode[0], len[0]); break;
    case 1: TextCopi(bk, gui, bbcode[1], len[1]); break;
    case 2: TextCopi(bk, gui, bbcode[2], len[2]); break;
    case 3: TextCopi(bk, gui, bbcode[3], len[3]); break;
    case 4: TextCopi(bk, gui, bbcode[4], len[4]); break;
    
    case 5: {  mbk->main_menu_SetCursorToItem=5;
               mbk->flag=0;
               CreateStringInput(L"http://", LNG_VAR_STRINP_FIXED_TEXT_LINK, 6, 2024 );
              break;
            }

    case 6: TextCopi(bk, gui, bbcode[6], len[6]); break;
    
    case 7: {
              mbk->main_menu_SetCursorToItem=7;
              MainGUIDestroy(gui);
              FontGuiCreate(0, bk, gui); break;
            }                                    //font //bbcode[8], len[8]
    
    case 8: TextCopi(bk, gui, bbcode[8], len[8]); break;
    case 9: TextCopi(bk, gui, bbcode[9], len[9]); break;

    case 10: {
               mbk->main_menu_SetCursorToItem=10;
               mbk->bbcode=bbcode[10];
               mbk->bbcode_pos=len[10];
               mbk->flag=1;
               CreateStringInput(L"http://", LNG_VAR_STRINP_FIXED_TEXT_LINK, 6, 2024 );
               break;
             }
    case 11: {
               mbk->main_menu_SetCursorToItem=11;
               mbk->picture_gui_SetCursorToItem=0;
               MainGUIDestroy(gui);
               PictureGuiCreate(0, bk, gui); break; 
             }                                     // pic // bbcode[12], len[12]
    
    case 12: TextCopi(bk, gui, bbcode[12], len[12]); break;
    case 13: TextCopi(bk, gui, bbcode[13], len[13]); break;
    case 14: TextCopi(bk, gui, bbcode[14], len[14]); break;
    case 15: { mbk->main_menu_SetCursorToItem=15;
               mbk->bbcode=bbcode[15];
               mbk->bbcode_pos=len[15];
               mbk->flag=1;
               CreateStringInput(L"", LNG_VAR_STRINP_FIXED_TEXT_SPOILER, 1, 128 );
               break;
             }
    
    case 16: {
               mbk->main_menu_SetCursorToItem=16;
               MainGUIDestroy(gui);
               ColorGuiCreate(0, bk, gui); break; 
             }
    case 17:{
               mbk->main_menu_SetCursorToItem=17;
               MainGUIDestroy(gui);
               SmileMenuCreate(0, bk, gui); break;
            }
   }    
}
//==============================================================================
/* ========================================================================== */
          // StringInputVA
//==============================================================================

void ExitAction(BOOK * bk)
{
  if (mbk->current_gui)
  {
    GUIObject_Destroy(mbk->current_gui);
    mbk->bbcode=0;
    mbk->bbcode_pos=0;
    mbk->current_gui=0;
    mbk->StringInputVA=0;
    GuiCreateGuiList(0,&(mbk->book),mbk->main_gui);
  }
  if(findbook(BBCODEGUI)) FreeBook(bk);
}

int DestroyStringInput()
{
  if (mbk->current_gui)
  {
    GUIObject_Destroy(mbk->current_gui);
    mbk->bbcode=0;
    mbk->bbcode_pos=0;
    mbk->current_gui=0;
    mbk->StringInputVA=0;
    if(mbk->flag==2) PictureGuiCreate(0, &(mbk->book), mbk->picture_gui);
    else GuiCreateGuiList(0,&(mbk->book),mbk->main_gui);
  }
  return(0);
}


wchar_t* VAStringGlue(wchar_t * bbcode, int paste_pos, wchar_t* string2insert )
{
  // получаем первую часть строки, до позиции курсора
  wchar_t *src=new wchar_t[wstrlen(string2insert)+wstrlen( bbcode )+1];
  wstrncpy(src,  bbcode, paste_pos);
  src[paste_pos]='\0';

  int lenstr=wstrlen(src);
  if(mbk->flag!=2) mbk->bbstrlen=paste_pos+wstrlen(string2insert)+1;
// получаем вторую часть, после позиции курсора
  wchar_t *secondtext=0;
  secondtext = bbcode+paste_pos;
  secondtext[wstrlen(bbcode)-paste_pos]='\0';
  // соединяем
  wstrcat(src, string2insert);
  src[paste_pos + wstrlen(string2insert)]='\0';
  wstrcat(src, secondtext);
  src[wstrlen(bbcode) + wstrlen(string2insert)]='\0';

  return src;

}


void AcceptAction_BBCode(BOOK * bk,wchar_t * string,int len)
{
  if ( wstrlen(string)!=0 )
  {
    if(mbk->flag==1)
    {
      string=VAStringGlue(mbk->bbcode, mbk->bbcode_pos, string );
      mbk->flag=0;
    }
    else if(mbk->flag==2)
         {
           string=VAStringGlue(mbk->bbcode, mbk->bbcode_pos, string );
           mbk->flag=0;
           mbk->bbstrlen=wstrlen(string);
         }
         else  mbk->bbstrlen=wstrlen(string);
         
    wchar_t * src=new wchar_t[wstrlen(string)+1];
    wstrncpy(src, string, wstrlen(string));
    src[wstrlen(string)]='\0';
    TextCopi(bk, mbk->current_gui, src, mbk->bbstrlen);
  }
  else
  {
    MessageBox(EMPTY_TEXTID,STR(LNG_ERROR_VAR_INPUT),NOIMAGE,1,0,0);
    DestroyStringInput();
  }
}



void CreateStringInput(wchar_t * editable_strID, wchar_t * fixed_strID, int mode, int MAX_LEN )
{
  mbk->current_gui = mbk->StringInputVA = CreateStringInputVA(0,
                                         VAR_BOOK(&(mbk->book)),
                                         VAR_OK_PROC(AcceptAction_BBCode),
                                         VAR_PREV_ACTION_PROC(DestroyStringInput),
                                         VAR_LONG_BACK_PROC(ExitAction),
                                         VAR_STRINP_MODE( mode ),
                                         VAR_HEADER_TEXT(STR(LNG_VAR_HEADER_TEXT)),
                                         VAR_STRINP_NEW_LINE(1),
                                         VAR_STRINP_FIXED_TEXT(TextID_Create(fixed_strID,ENC_UCS2,TEXTID_ANY_LEN)),
                                         VAR_STRINP_TEXT(TextID_Create(editable_strID,ENC_UCS2,TEXTID_ANY_LEN)),
                                         VAR_STRINP_MIN_LEN(0),
                                         VAR_STRINP_MAX_LEN(MAX_LEN),
                                        0);
}

//=========* добавляем названия *===============================================
int MainMenuGuiOnMessage(GUI_MESSAGE* msg)
{
  int item;
  switch(msg->__msg)
  {
    case 1:
      item = GUIonMessage_GetCreatedItemIndex(msg);
      GUIonMessage_SetMenuItemText(msg,TextID_Create(names[item],ENC_UCS2,TEXTID_ANY_LEN));
      GUIonMessage_SetMenuItemIcon(msg, 0, img[item]);
    break;
   }
   return(1);
} 

//========* создаём лист гуя *==================================================
void GuiCreateGuiList(void*r0, BOOK* bk, GUI* gui)
{
  mbk->current_gui = mbk->main_gui = CreateListMenu(&(mbk->book), 0);
  ModifyKeyHook(MainMenuKeyHook,KEY_HOOK_ADD,NULL);
  //------------------------
  GuiObject_SetTitleText(mbk->main_gui, TextID_Create( LNG_HEADER_MAINGUI_TEXT, ENC_UCS2,TEXTID_ANY_LEN));
  ListMenu_SetItemCount(mbk->main_gui, 18);
  ListMenu_SetOnMessage(mbk->main_gui, MainMenuGuiOnMessage);
  SetCursorToItem(mbk->main_gui,mbk->main_menu_SetCursorToItem);
  SetMenuItemStyle(mbk->main_gui, 0);
  GUIObject_SoftKeys_SetAction(mbk->main_gui, ACTION_BACK, MainMenuGUIBack);
  GUIObject_SoftKeys_SetAction(mbk->main_gui, ACTION_LONG_BACK,MainMenuGUIBack);
  GUIObject_SoftKeys_SetAction(mbk->main_gui, ACTION_SELECT1,GuiOnEnterPressed);
  GUIObject_Show(mbk->main_gui);
 
}
