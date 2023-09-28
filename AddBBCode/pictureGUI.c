#include "..\\include\Lib_Clara.h"
#include "header\gui.h"
#include "header\pictureGUI.h"

#if defined(LNG_RUS)
    #include "header\LANGUAGE_RUS.h"
#elif defined(LNG_ENG)
    #include "header\LANGUAGE_ENG.h"
#endif
//------------------------------------------------------------------------------
wchar_t* picname[]= {
  LNG_ITEM_IMAGEGUI_NAME_0,
  LNG_ITEM_IMAGEGUI_NAME_1,
  LNG_ITEM_IMAGEGUI_NAME_2,
};

wchar_t* piccode[]=
{
  L"[img][/img]",
  L"[img align=right][/img]",
  L"[img align=left][/img]"//картинка
};

int piclen[]={ 5, 17, 16 };


void PictureGuiBack(BOOK* bk,GUI_LIST* gui)
{  
  if(gui)
  {
    ModifyKeyHook(MainMenuKeyHook,KEY_HOOK_REMOVE,0);
    ListMenu_DestroyItems( gui );
    FREE_GUI( gui );
    gui=0;
  }
  GuiCreateGuiList(0,&(mbk->book),gui);
}

int PictureGuiOnMessage(GUI_MESSAGE * msg)
{
  int index;  
  switch(GUIonMessage_GetMsg(msg)) //получаем тип сообщения
  {
  case LISTMSG_GetItem:
    index = GUIonMessage_GetCreatedItemIndex(msg); //получаем номер только что созданного пункта
    GUIonMessage_SetMenuItemText(msg, TextID_Create(picname[index],ENC_UCS2,TEXTID_ANY_LEN) ); //устанавливаем имена пунктам
    index+=24;
    GUIonMessage_SetMenuItemIcon(msg, 0, img[index]);
    break;
  }
  return(1);
}

void PictureGuiOnEnterPress(BOOK* book,GUI_LIST* gui)
{
  int item=ListMenu_GetSelectedItem(mbk->picture_gui);
  if(item >= 0)
  {
    mbk->picture_gui_SetCursorToItem=item;
    mbk->bbcode=piccode[item];
    mbk->bbcode_pos=piclen[item];
    mbk->flag=2;
    //mbk->link_flag=0;
    CreateStringInput(L"http://", LNG_VAR_STRINP_FIXED_TEXT_IMG, 6, 2024 );
  }
}


void PictureGuiCreate(void* r0,BOOK* bk,GUI_LIST* gui)
{
   mbk->current_gui = mbk->picture_gui = CreateListMenu( bk,0 );
   ModifyKeyHook(MainMenuKeyHook,KEY_HOOK_ADD,NULL);
   GuiObject_SetTitleText(mbk->picture_gui, TextID_Create(LNG_HEADER_IMAGEGUI_TEXT, ENC_UCS2,TEXTID_ANY_LEN));
   ListMenu_SetOnMessage(mbk->picture_gui, PictureGuiOnMessage );
   SetCursorToItem(mbk->picture_gui, mbk->picture_gui_SetCursorToItem );
   ListMenu_SetItemCount(mbk->picture_gui, 3 );
   SetMenuItemStyle(mbk->picture_gui, 0);
   
   GUIObject_SoftKeys_SetAction(mbk->picture_gui, ACTION_BACK,PictureGuiBack);
   GUIObject_SoftKeys_SetAction(mbk->picture_gui, ACTION_LONG_BACK,MainMenuGUIBack);
   GUIObject_SoftKeys_SetAction(mbk->picture_gui, ACTION_SELECT1,PictureGuiOnEnterPress);
   GUIObject_Show(mbk->picture_gui);
}
