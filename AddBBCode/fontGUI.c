///*--------------- *///
//*  Size Font GUI  *//
//////////////////////
#include "..\\include\Lib_Clara.h"
#include "header\gui.h"
#include "header\fontGUI.h"

#if defined(LNG_RUS)
    #include "header\LANGUAGE_RUS.h"
#elif defined(LNG_ENG)
    #include "header\LANGUAGE_ENG.h"
#endif
//------------------------------------------------------------------------------
wchar_t* sizename[]= {
  LNG_ITEM_FONTGUI_NAME_0,
  LNG_ITEM_FONTGUI_NAME_1,
  LNG_ITEM_FONTGUI_NAME_2,
  LNG_ITEM_FONTGUI_NAME_3,
  LNG_ITEM_FONTGUI_NAME_4,
  LNG_ITEM_FONTGUI_NAME_5
};

wchar_t* sizecode[]=
{
  L"[size=xx-small][/size]",
  L"[size=x-small][/size]",
  L"[size=small][/size]",
  L"[size=medium][/size]",
  L"[size=large][/size]",
  L"[size=x-large][/size]"
};


int sizelen[]={ 15, 14, 12, 13, 12, 14 };


void FontGuiBack(BOOK* bk,GUI_LIST* gui)
{  
  if(gui)
  {
    ModifyKeyHook(MainMenuKeyHook,KEY_HOOK_REMOVE,0);
    ListMenu_DestroyItems(gui);
    FREE_GUI(gui);
    gui=0;
  }
  GuiCreateGuiList(NULL,&(mbk->book),mbk->main_gui);
}


int FontGuiOnMessage( GUI_MESSAGE * msg )
{
  int index;  
  switch( GUIonMessage_GetMsg( msg ) ) //получаем тип сообщения
  {
    case LISTMSG_GetItem:
      index = GUIonMessage_GetCreatedItemIndex( msg ); //получаем номер только что созданного пункта
      GUIonMessage_SetMenuItemText( msg , TextID_Create(sizename[index],ENC_UCS2,TEXTID_ANY_LEN) ); //устанавливаем имена пунктам
      index+=18;
      GUIonMessage_SetMenuItemIcon(msg, 0, img[index] );
      break;
  }
  return(1);
}


void FontGuiOnEnterPress(BOOK* bk,GUI_LIST* gui)
{
  int item = ListMenu_GetSelectedItem(mbk->font_gui);
  if(item >= 0)  TextCopi(bk, mbk->font_gui, sizecode[item], sizelen[item]);
}


void FontGuiCreate(void* r0,BOOK* bk,GUI_LIST* gui)
{
   mbk->current_gui = mbk->font_gui=CreateListMenu(bk, 0);
   ModifyKeyHook(MainMenuKeyHook,KEY_HOOK_ADD,NULL);
   GuiObject_SetTitleText(mbk->font_gui, TextID_Create(LNG_HEADER_FONTGUI_TEXT, ENC_UCS2,TEXTID_ANY_LEN));
   ListMenu_SetItemCount(mbk->font_gui, 6);
   ListMenu_SetOnMessage(mbk->font_gui, FontGuiOnMessage);
   SetCursorToItem(mbk->font_gui,0);
   SetMenuItemStyle(mbk->font_gui, 0);
   GUIObject_SoftKeys_SetAction(mbk->font_gui, ACTION_BACK,FontGuiBack);
   GUIObject_SoftKeys_SetAction(mbk->font_gui, ACTION_LONG_BACK,MainMenuGUIBack);
   GUIObject_SoftKeys_SetAction(mbk->font_gui, ACTION_SELECT1,FontGuiOnEnterPress);
   GUIObject_Show(mbk->font_gui);
}
