#ifndef _MAIN_H
#define _MAIN_H

#define FREE_GUI(a) if (a) a=GUIObject_Destroy(a)


typedef struct
{
  BOOK book;
  GUI_LIST * gui;

}MyBOOK;


extern MyBOOK*mbk;

#endif 
