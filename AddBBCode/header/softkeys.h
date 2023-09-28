#ifndef _SOFTKEYS_H_
#define _SOFTKEYS_H_

#include "..\include\Lib_Clara.h"
//#include "..\classlib\cl.h"

void QSort(wchar_t items[], int count);

wchar_t Softkeys_GetFreeAction(GUI *gui);
wchar_t Softkeys_FindAction(GUI *gui, TEXTID text_id);
void Softkeys_SetItemAction(GUI *gui, wchar_t action, int item);
int Softkeys_FindInList( GUI* gui, TEXTID text_id);
GUI *FindGuiInBook(BOOK *bk, char *name);

#endif
