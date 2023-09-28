#ifndef _MAIN_GUI_H
#define _MAIN_GUI_H

#define FREE_GUI(a) if (a) a=GUIObject_Destroy(a)

extern BOOK* findbook(const char* name);
extern BOOK * BBCodeGUIBook;
extern void MainMenuGUIBack(BOOK* bk,GUI_LIST* gui);
extern void GuiCreateGuiList(void*, BOOK * bk, GUI* gui);
extern void TextCopi(BOOK* bk,GUI_LIST* gui,wchar_t* bbcode,int len);
extern void GuiOnEnterPressed(BOOK* bk,GUI_LIST* gui);
extern wchar_t* bbcode[];
extern int len[];
extern wchar_t img[27];
extern int ImgLoad();
extern int ImgUpload();
extern int GuiKeyHook(int key, int r1, int mode, LPARAM, DISP_OBJ* dispobj);
extern void CreateStringInput(wchar_t * editable_strID, wchar_t * fixed_strID, int mode, int MAX_LEN );
extern int MainMenuKeyHook(int key, int r1, int mode, LPARAM, DISP_OBJ* dispobj);

typedef struct
{
  BOOK book;
  GUI_LIST* main_gui;
  GUI * color_gui;
  GUI * smile_gui;
  GUI_LIST * picture_gui;
  GUI_LIST* font_gui;
  GUI * current_gui;
  GUI * StringInputVA;
  wchar_t* bbcode;
  int bbcode_pos;
  int bbstrlen;
  int flag;

  
  int main_menu_SetCursorToItem;
  int picture_gui_SetCursorToItem;
  DISP_OBJ * disp_obj;
  DISP_DESC * disp_desc;

}MyBOOK;


extern MyBOOK*mbk;

#endif //_MAIN_GUI_H
