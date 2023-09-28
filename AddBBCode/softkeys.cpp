#include "header\softkeys.h"
#include "header\main.h"

void qs(wchar_t *items, int left, int right);

void QSort(wchar_t items[], int count)
{
  qs(items, 0, count-1);
}

void qs(wchar_t items[], int left, int right)
{
  register int i, j;
  wchar_t x, y;

  i = left; j = right;
  x = items[(left+right)/2];

  do {
    while((items[i] < x) && (i < right)) i++;
    while((x < items[j]) && (j > left)) j--;

    if(i <= j) {
      y = items[i];
      items[i] = items[j];
      items[j] = y;
      i++; j--;
    }
  } while(i <= j);

  if(left < j) qs(items, left, j);
  if(i < right) qs(items, i, right);
}


wchar_t Softkeys_GetFreeAction(GUI *gui)
{
  int i;
  wchar_t ret = 0xFFFF;
  LIST *lst = DispObject_SoftKeys_GetList( GUIObject_GetDispObject(gui),GUIObject_GetBook(gui), 0);
  if(lst)
  {
    wchar_t * actionlist = new wchar_t[lst->FirstFree];
    for(int k=0;k<lst->FirstFree;k++)
      actionlist[k]=((SOFTKEY_DESC *)List_Get(lst,k))->action;
    QSort(actionlist,lst->FirstFree);
    for(i=0;i<lst->FirstFree;i++)
    {
      if(actionlist[i]>=ACTION_MORE) break;
    }
    i--;
    for(int k=0;k<=i-1;k++)
    {
      if(actionlist[k]+1 != actionlist[k+1])
      {
        ret=actionlist[k]+1;
        break;
      }
    }
    if(!ret) ret=actionlist[i]+1;
    delete(actionlist);
  }
  return(ret);
}

SOFTKEY_DESC *SoftkeyAction_GetSoftkeyDesc(GUI *gui, wchar_t action)
{
  LIST *lst = DispObject_SoftKeys_GetList(GUIObject_GetDispObject(gui), GUIObject_GetBook(gui), 0);
  for(int k=0; k<lst->FirstFree; k++)
  {
    SOFTKEY_DESC *sd = (SOFTKEY_DESC *)List_Get(lst,k);
    if(sd->action == action) return(sd);
  }
  return(0);
}


void Softkeys_SetItemAction(GUI *gui, wchar_t action, int item)
{
  LIST *lst = DispObject_SoftKeys_GetList(GUIObject_GetDispObject(gui), GUIObject_GetBook(gui), 0);
  SOFTKEY_DESC *def_sd = SoftkeyAction_GetSoftkeyDesc(gui, action);

  int cur_pos = List_IndexOf(lst, def_sd);
  List_RemoveAt(lst, cur_pos);
  List_Insert(lst, item, def_sd);
}

// функция для поиска нужного softkey в списке

int Softkeys_FindInList( GUI* gui, TEXTID text_id)
{
  LIST *lst = DispObject_SoftKeys_GetList( GUIObject_GetDispObject(gui), GUIObject_GetBook(gui), 0);
  for(int k=0;k<lst->FirstFree;k++)
  {
    SOFTKEY_DESC * sd = (SOFTKEY_DESC*) List_Get(lst,k);
    if((sd->ButtonText == text_id)) return 1;
    else
    {
      wchar_t s1[32],s2[32];
      TextID_GetWString(text_id,s1,MAXELEMS(s1));
      TextID_GetWString(sd->ButtonText,s2,MAXELEMS(s2));
      if(!wstrcmp(s1,s2)) return 1;
    }
  }
  return(0);
}

//функция для поиска нужного gui в book
GUI *FindGuiInBook(BOOK *bk, char *name)
{
  LIST *lst = bk->xguilist->guilist;
  for (int x=0;x<lst->FirstFree;x++)
  {
    GUI *gui = (GUI*)List_Get(lst,x);
    if(gui)
      if (strcmp(DispObject_GetName(GUIObject_GetDispObject(gui)),name)==0)
        return gui;
  }
  return(0);
}

