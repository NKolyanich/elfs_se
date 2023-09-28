#include "..\\include\Lib_Clara.h"
#include "..\\include\Colors.h"
#include "header\gui.h"
#include "header\main.h"
#include "header\colorGUI.h"
/*
#if defined(LNG_RUS)
    #include "header\LANGUAGE_RUS.h"
#elif defined(LNG_ENG)
    #include "header\LANGUAGE_ENG.h"
#endif
*/
//==============================================================================
// таймер перерисовки отключен, перерисовка после нажатия клавиши

//u16 ftimer;
int indent_left, indent_top;
const int stArr_i=6, stArr_j=8;
int _add_diez2color;


int left_align;

//============= прототипы функций ============================================================
void (*SIonRedraw)(DISP_OBJ *,int r1,int r2,int r3);
void Draw(DISP_OBJ * db,int r1, int r2,int r3);
void ColorGuiOnEnterPress(BOOK* bk,GUI_LIST* gui);
//-------------------------------------------------

struct drawitem
{// коор. кв. пунктов меню
  int x1,y1;
  int x2,y2;
// коор. строки и прямоуг. выбранного цвета
  int x1_str,y1_str;
  int x2_str,y2_str;
  int x1_rect,y1_rect;
  int x2_rect,y2_rect;
  
  int dw, dh; // ширина/высота экрана
  int sq_w, sq_h; // ширина/высота пунктов

} drawitem[stArr_i][stArr_j],draw;


int  HexColorArr[stArr_i][stArr_j]=
{
  {0xFFFFCCFF, 0xFFCCFFFF, 0xFF99FFFF, 0xFF99FF99, 0xFFFFFF99, 0xFFFFCC99, 0xFFFCCCCC, 0xFFFFFFFF},
  {0xFFCC66CC, 0xFF33CCFF, 0xFF66CCCC, 0xFF33FF33, 0xFFFFCC66, 0xFFFF9900, 0xFFFF0000, 0xFFC0C0C0},
  {0xFFCC33CC, 0xFF3366FF, 0xFF00CCCC, 0xFF33CC00, 0xFFFFCC33, 0xFFFF6600, 0xFFCC0000, 0xFF999999},
  {0xFF993399, 0xFF3333FF, 0xFF339999, 0xFF009900, 0xFFCC9933, 0xFFCC6600, 0xFF990000, 0xFF666666},
  {0xFF663366, 0xFF000099, 0xFF336666, 0xFF006600, 0xFF996633, 0xFF993300, 0xFF660000, 0xFF333333},
  {0xFF330033, 0xFF000066, 0xFF003333, 0xFF003300, 0xFF663333, 0xFF663300, 0xFF330000, 0xFF000000}
};
//-------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------
wchar_t * int2wstr(int i)
{  // + удаление альфа-канала
  wchar_t *wstr_old = new wchar_t[64];
  snwprintf(wstr_old,63,L"%X",i);
  wchar_t *wstr=0;
  wstr = wstr_old+2;
  delete(wstr_old);
  wstr[6]='\0';
  if(_add_diez2color==1)
  {
    wchar_t src[8]=L"#";
    wstrcat(src, wstr);
    wstrncpy(wstr, src, 7);
    wstr[7]='\0';
  }
  return (wstr);
}

int SearchHexColor(int x)
{
  int y=0;
  for( int i=0; i<stArr_i; i++ )
  {
    for( int j=0; j<stArr_j; j++ )
    {
       if(y==x) return HexColorArr[i][j];
       y++;
    }
  }
  return 0;
}

wchar_t * ColorCode(wchar_t*color)
{
  u16 slen1;
  wchar_t wstr1[8]=L"[color=";
  wchar_t wstr2[10]=L"][/color]";
  wchar_t *wstr_new = new wchar_t[wstrlen(color)+wstrlen(wstr1)+wstrlen(wstr2)+1];
  slen1=wstrlen(wstr1);
  wstrcpy(wstr_new,wstr1);
  wstr_new[slen1]='\0';
  wstrcat(wstr_new, color);
  wstr_new[slen1+wstrlen(color)]='\0';
  slen1=wstrlen(wstr_new);
  wstrcat(wstr_new, wstr2);
  wstr_new[slen1+wstrlen(wstr2)]='\0';

  return(wstr_new);
}
//--------------------------------


int inverterHexColor(int color)
{
  int r,g,b,a;
  r = COLOR_GET_R( color );
	g = COLOR_GET_G( color );
	b = COLOR_GET_B( color );
	a = COLOR_GET_A( color );
  return COLOR_RGBA( 0xFF-r, 0xFF-g, 0xFF-b, a );
}


//=============== считаем координаты и пишем в структуру drawitem ==================
/*
void LoadXY(int dw, int dh)
{
  int X_N, Y_N;
// wiht 240
if(dw==240)
{
  draw.sq_w=(dw-16)/8;        //=28 ширина прямоугольника
  draw.sq_h=(dh-152)/6;       //=28 высота прямоугольника
  indent_left=4;
  indent_top=60;
  left_align=29; // -
//------------------------------------------------------------------------------
  draw.X1=indent_left; // 4
  draw.Y1=indent_top-28;
  draw.X2=draw.X1+draw.sq_w; // 32
  draw.Y2=draw.Y1+draw.sq_h;  // 59
//------------------------------------------------------------------------------
  draw.x1_rect=4;
  draw.y1_rect=draw.Y1+(draw.sq_h+1)*7+6;
  draw.x2_rect=dw-5;
  draw.y2_rect=draw.y1_rect+30;

  draw.x1_str=draw.x1_rect+15;
  draw.y1_str=draw.y1_rect;
	draw.x2_str=dw/2;//-30
  draw.y2_str=draw.y2_rect;//-16;
}
//==============================================================================
// 176x220

if(dw==176)
{
  draw.sq_w=(dw-16)/8;        //=20 ширина прямоугольника
  draw.sq_h=(dh-100)/6;       //=20 высота прямоугольника
  indent_left=2;
  indent_top=35;
  left_align=19; // -
//------------------------------------------------------------------------------
  draw.X1=indent_left; // 4
  draw.Y1=indent_top-21;
  draw.X2=draw.X1+draw.sq_w; // 25
  draw.Y2=draw.Y1+draw.sq_h;  // 40
//------------------------------------------------------------------------------
  draw.x1_rect=indent_left+3;
  draw.y1_rect=draw.Y1+(draw.sq_h+1)*7+6;
  draw.x2_rect=dw-5;
  draw.y2_rect=draw.y1_rect+22;
//------------------------------------------------------------------------------
  draw.x1_str=draw.x1_rect+9;
  draw.y1_str=draw.y1_rect-2;
	draw.x2_str=dw/2+5;
  draw.y2_str=draw.y2_rect-16;
}
//------------------------------------------------------------------------------
// 128x160

if(dw==128)
{
  draw.sq_w=(dw-16)/8;        //=14 ширина прямоугольника
  draw.sq_h=(dh-84)/6;       //=14 высота прямоугольника
  indent_left=2;
  indent_top=35;
  left_align=13; // -
//------------------------------------------------------------------------------
  draw.X1=indent_left; // 2
  draw.Y1=indent_top-14;
  draw.X2=draw.X1+draw.sq_w; // 25
  draw.Y2=draw.Y1+draw.sq_h;  // 40
//------------------------------------------------------------------------------
  draw.x1_rect=indent_left+2;
  draw.y1_rect=draw.Y1+(draw.sq_h+1)*7+6;
  draw.x2_rect=dw-5;
  draw.y2_rect=draw.y1_rect+16;

  draw.x1_str=draw.x1_rect+7;
  draw.y1_str=draw.y1_rect-5;
	draw.x2_str=dw/2+15;
  draw.y2_str=draw.y2_rect;
}

//------------------------------------------------------------------------------
  X_N=1; Y_N=1;
  for( int i=0; i<stArr_i; i++ )
  {
    for( int j=0; j<stArr_j; j++ )
    {
      drawitem[i][j].x1=draw.X1+(draw.sq_w+1)*X_N-left_align; //15 //21 //29
      drawitem[i][j].y1=draw.Y1+(draw.sq_h+1)*Y_N;
      drawitem[i][j].x2=draw.X2+(draw.sq_w+1)*X_N-left_align;
      drawitem[i][j].y2=draw.Y2+(draw.sq_h+1)*Y_N;
      X_N++;
    }
    X_N=1;  Y_N++;
  }
}
*/
void LoadXY(int dw, int dh)
{
// wiht 240
if(dw==240)
{
  draw.sq_w=(dw-16)/8;        //=28 ширина прямоугольника
  draw.sq_h=(dh-152)/6;       //=28 высота прямоугольника
//------------------------------------------------------------------------------
  draw.x1_rect=4;
  draw.y1_rect=32+(draw.sq_h+1)*7+6;
  draw.x2_rect=dw-5;
  draw.y2_rect=draw.y1_rect+30;

  draw.x1_str=draw.x1_rect+15;
  draw.y1_str=draw.y1_rect;
	draw.x2_str=dw/2;//-30
  draw.y2_str=draw.y2_rect;//-16;
}
//==============================================================================
// 176x220

if(dw==176)
{
  draw.sq_w=(dw-16)/8;        //=20 ширина прямоугольника
  draw.sq_h=(dh-100)/6;       //=20 высота прямоугольника
  indent_left=2;
  indent_top=35;
  left_align=19; // -
//------------------------------------------------------------------------------
  draw.x1_rect=indent_left+3;
  draw.y1_rect=314+(draw.sq_h+1)*7+6;
  draw.x2_rect=dw-5;
  draw.y2_rect=draw.y1_rect+22;
//------------------------------------------------------------------------------
  draw.x1_str=draw.x1_rect+9;
  draw.y1_str=draw.y1_rect-2;
	draw.x2_str=dw/2+5;
  draw.y2_str=draw.y2_rect-16;
}
//------------------------------------------------------------------------------
// 128x160

if(dw==128)
{
  draw.sq_w=(dw-16)/8;        //=14 ширина прямоугольника
  draw.sq_h=(dh-84)/6;       //=14 высота прямоугольника
  indent_left=2;
  indent_top=35;
  left_align=13; // -
//------------------------------------------------------------------------------
  draw.x1_rect=indent_left+2;
  draw.y1_rect=21+(draw.sq_h+1)*7+6;
  draw.x2_rect=dw-5;
  draw.y2_rect=draw.y1_rect+16;

  draw.x1_str=draw.x1_rect+7;
  draw.y1_str=draw.y1_rect-5;
	draw.x2_str=dw/2+15;
  draw.y2_str=draw.y2_rect;
}
// -----------------------------------------------------------------------------
  u16 w=0;   // начальная позиция x отрисовки
  u16 h=0;   // начальная позиция y отрисовки
  u16 ind=0; // отступ между смайлами
  switch (dw) // поправочка под экраны
  {
    case 240: { w=4; h=60; ind=29; break; }
    case 176: { w=2;  h=35; ind=21; break; }
    case 128: { w=2;  h=35; ind=15; break; }  //??
    default:  { w=20; h=60; ind=29; break; } /* 240 */
  }
  u16 xn=0;
  u16 yn=0;
  for( int i=0; i<stArr_i; i++ ) //  столбцы
  {
    for( int j=0; j<stArr_j; j++ )  // строки
    {
      drawitem[i][j].x1=w+xn;
      drawitem[i][j].y1=h+yn;
      drawitem[i][j].x2=drawitem[i][j].x1+ind-1;
      drawitem[i][j].y2=drawitem[i][j].y1+ind-1;
      xn+=ind;
    }
    xn=0;
    yn+=ind;
  }
}
//---------- перересовка -------------------------------------------------------------------------

void Send_REDRAW_RELEASE()
{
  // посылаем всем  мессагу со старым и своим методами Redraw
  REDRAW_RELEASE_MESSAGE * sbm= new REDRAW_RELEASE_MESSAGE;
  memset(sbm,0,sizeof(REDRAW_RELEASE_MESSAGE));
  sbm->SB_OldOnRedraw=SIonRedraw;
  sbm->SB_NewOnRedraw=Draw;
  UI_Event_wData(SBY_REDRAW_RELEASE_EVENT ,sbm,(void (*)(void*))mfree_adr());
}
//


/*
void onfTimer (u16, LPARAM)
{
  if(Display_GetFocusedDispObject(0)==mbk->disp_obj)
  {   debug_printf("\n    <font color=#0000ff> НУЖНЫЙ ДИСП ОБЖ!!!! РИСУЕМ\n</font>");
   DispObject_InvalidateRect(mbk->disp_obj,0);
   Timer_ReSet(&ftimer,35,onfTimer,0);
  }
  else{  debug_printf("\n------  <font color=#0000ff> НЕ НАШЛИ ДИСП ОБЖ (((\n</font>");
     Timer_ReSet(&ftimer,35,onfTimer,0);
     }
};
*/

void DrawSquare()
{
  for( int i=0; i<stArr_i; i++ )
  {
    for( int j=0; j<stArr_j; j++ )
    {
      DrawRect(drawitem[i][j].x1, drawitem[i][j].y1, drawitem[i][j].x2, drawitem[i][j].y2, clBorder, HexColorArr[i][j] );
    }
  }
}


//----------------- рисуем курсор -------------------------------------------------------------

void DrawCursor(DISP_OBJ * db, int x)
{
  int y=0;
  GC * gc = (GC*)get_DisplayGC();;

  for( int i=0; i<stArr_i; i++ )
  {
    for( int j=0; j<stArr_j; j++ )
    {
      if(y==x)
      {
        
        DrawRect(drawitem[i][j].x1+2, drawitem[i][j].y1+2, drawitem[i][j].x2-2, drawitem[i][j].y2-2, inverterHexColor( HexColorArr[i][j] ), clAlpha );
        GC_SetPenColor( gc, inverterHexColor( HexColorArr[i][j] ) );
        GC_DrawLine( gc,drawitem[i][j].x1+2, drawitem[i][j].y1+2, drawitem[i][j].x2-4, drawitem[i][j].y2-4);
        GC_DrawLine( gc,drawitem[i][j].x2-3, drawitem[i][j].y1+2, drawitem[i][j].x1+2, drawitem[i][j].y2-3);
        
        DrawRect(draw.x1_rect, draw.y1_rect, draw.x2_rect, draw.y2_rect, clBorder, HexColorArr[i][j] );
        //рисуем строку, цвет обводки.
        TEXTID SIDtime;
        SIDtime=TextID_Create(int2wstr( SearchHexColor(x) ),ENC_UCS2,TEXTID_ANY_LEN);
        DrawString(SIDtime,0, draw.x1_str, draw.y1_str, draw.x2_str, draw.y2_str, 0, 0x05,
                   inverterHexColor( HexColorArr[i][j] ),
                   inverterHexColor( HexColorArr[i][j] ) );
        TextID_Destroy(SIDtime);
      }
      y++;
    }
  }
}

void Draw(DISP_OBJ * db,int r1, int r2,int r3)
{
  // вызываем родной onRedraw.
  SIonRedraw(db,r1,r2,r3);
  DrawRect(0, 0, draw.dw, draw.dh, clBlack, clBlack );
  DrawSquare();
  // Draw Cursor ---------------------------------------------------------------
  int sitem=ListMenu_GetSelectedItem( DispObject_GetGUI(db) );
  DrawCursor(db, sitem);
}


inline void RedrawDisplay()
{
  DispObject_InvalidateRect(mbk->disp_obj,0);
}


void myOnKey(DISP_OBJ *db,int key,int a,int b,int type)
{  
  int sItem=ListMenu_GetSelectedItem(DispObject_GetGUI(db));

  if((key==KEY_DOWN || key==KEY_DIGITAL_0+8) && type==KBD_SHORT_PRESS)
  {
    switch(sItem)
    {
      case 40: { SetCursorToItem(DispObject_GetGUI(db), 1); RedrawDisplay(); break; }
      case 41: { SetCursorToItem(DispObject_GetGUI(db), 2); RedrawDisplay(); break; }
      case 42: { SetCursorToItem(DispObject_GetGUI(db), 3); RedrawDisplay(); break; }
      case 43: { SetCursorToItem(DispObject_GetGUI(db), 4); RedrawDisplay(); break; }
      case 44: { SetCursorToItem(DispObject_GetGUI(db), 5); RedrawDisplay(); break; }
      case 45: { SetCursorToItem(DispObject_GetGUI(db), 6); RedrawDisplay(); break; }
      case 46: { SetCursorToItem(DispObject_GetGUI(db), 7); RedrawDisplay(); break; }
      case 47: { SetCursorToItem(DispObject_GetGUI(db), 0); RedrawDisplay(); break; }
      default: { SetCursorToItem(DispObject_GetGUI(db), sItem+8); RedrawDisplay(); break; }
    }
  }
  
  if((key==KEY_UP || key==KEY_DIGITAL_0+2) && type==KBD_SHORT_PRESS)
  {
    switch(sItem)
    {
      case 0: { SetCursorToItem(DispObject_GetGUI(db), 47); RedrawDisplay(); break; }
      case 1: { SetCursorToItem(DispObject_GetGUI(db), 40); RedrawDisplay(); break; }
      case 2: { SetCursorToItem(DispObject_GetGUI(db), 41); RedrawDisplay(); break; }
      case 3: { SetCursorToItem(DispObject_GetGUI(db), 42); RedrawDisplay(); break; }
      case 4: { SetCursorToItem(DispObject_GetGUI(db), 43); RedrawDisplay(); break; }
      case 5: { SetCursorToItem(DispObject_GetGUI(db), 44); RedrawDisplay(); break; }
      case 6: { SetCursorToItem(DispObject_GetGUI(db), 45); RedrawDisplay(); break; }
      case 7: { SetCursorToItem(DispObject_GetGUI(db), 46); RedrawDisplay(); break; }
      default: { SetCursorToItem(DispObject_GetGUI(db), sItem-8); RedrawDisplay(); break; }
    }
  }
  
  if((key==KEY_LEFT || key==KEY_DIGITAL_0+4) && type==KBD_SHORT_PRESS)
  {
    if(sItem==0) { SetCursorToItem(DispObject_GetGUI(db), 47); RedrawDisplay(); }
    else { SetCursorToItem(DispObject_GetGUI(db), sItem-1); RedrawDisplay(); }
  }
  
  if((key==KEY_RIGHT || key==KEY_DIGITAL_0+6) && type==KBD_SHORT_PRESS)
  {
    if(sItem==47) { SetCursorToItem(DispObject_GetGUI(db), 0); RedrawDisplay(); }
    else  { SetCursorToItem(DispObject_GetGUI(db), sItem+1); RedrawDisplay(); }
  }
  
  if(key==KEY_DIGITAL_0+5 && type==KBD_SHORT_PRESS)
    ColorGuiOnEnterPress(&(mbk->book),mbk->color_gui);
}
//---------
void ColorGuiBack(BOOK* bk,GUI_LIST* gui)
{
  termColorGUI();
  if(gui)
  {
    GUIObject_Destroy(gui);
    gui=0;
  }
  GuiCreateGuiList(0,&(mbk->book),mbk->main_gui);
}


void termColorGUI(void)
{
 // if(ftimer)Timer_Kill(&ftimer);
  DISP_DESC_SetOnRedraw(DispObject_GetDESC(mbk->disp_obj),SIonRedraw);
  Send_REDRAW_RELEASE();
}


void ColorGuiOnEnterPress(BOOK* bk,GUI_LIST* gui)
{
  termColorGUI();
  int colorlen=14;
  int item = ListMenu_GetSelectedItem(mbk->color_gui);
  if(_add_diez2color==1) colorlen++;
  if(item >= 0) TextCopi(bk, mbk->color_gui, ColorCode( int2wstr( SearchHexColor(item) ) ), colorlen);
}

/*
void ShowMSG(BOOK* bk,GUI_LIST* gui)
{
  wchar_t info[256];
  snwprintf(info,255,L"str_X_1->%i\nstr_Y_1->%i\nstr_X_2->%i\nstr_Y_2->%i",draw.x1_str, draw.y1_str, draw.x2_str, draw.y2_str);
  MessageBox(EMPTY_TEXTID,TextID_Create(info,ENC_UCS2,TEXTID_ANY_LEN),NOIMAGE,1,0,0);
}
*/

void ColorGuiCreate(void* r0,BOOK* bk,GUI_LIST* gui)
{ 
 // ------  на все экраны ;)  -------------------------------------------------
  draw.dw=Display_GetWidth(0);
  draw.dh=Display_GetHeight(0);
  LoadXY(draw.dw,draw.dh);
//------------------------------------------------------------------------------
  mbk->current_gui = mbk->color_gui=CreateListMenu(bk, 0);
  GUIObject_SetTitleText(mbk->color_gui, TextID_Create(LNG_HEADER_COLORGUI_TEXT, ENC_UCS2,TEXTID_ANY_LEN));
  ListMenu_SetItemCount(mbk->color_gui, 48);
  SetCursorToItem(mbk->color_gui,0);
  SetMenuItemStyle(mbk->color_gui, 6); //10
  GUIObject_SetStyle(mbk->color_gui, 4);
  
  GUIObject_SoftKeys_SetAction(mbk->color_gui, ACTION_BACK,ColorGuiBack);
  GUIObject_SoftKeys_SetAction(mbk->color_gui, ACTION_LONG_BACK,MainMenuGUIBack);
  GUIObject_SoftKeys_SetAction(mbk->color_gui, ACTION_SELECT1,ColorGuiOnEnterPress);
   
  DispObject_SetScrollBarColor( GUIObject_GetDispObject(mbk->color_gui), clAlpha );
  DispObject_SetScrollBarBackgroundColor (GUIObject_GetDispObject(mbk->color_gui), clAlpha );
  //---------
  // GUIObject_SoftKeys_SetAction(mbk->color_gui,ACTION_MORE,ShowMSG);
  // GUIObject_SoftKeys_SetText(mbk->color_gui,ACTION_MORE,TextID_Create(L"Test",ENC_UCS2,TEXTID_ANY_LEN));
  //----------
 // ftimer=Timer_Set(35,onfTimer,0);
  mbk->disp_obj=GUIObject_GetDispObject(mbk->color_gui);
  SIonRedraw=DispObject_GetOnRedraw(mbk->disp_obj);
  DISP_DESC_SetOnRedraw(DispObject_GetDESC(mbk->disp_obj),Draw);
  mbk->disp_desc=DispObject_GetDESC ( GUIObject_GetDispObject(mbk->color_gui) );
  DISP_DESC_SetOnKey(mbk->disp_desc, myOnKey);
  GUIObject_Show(mbk->color_gui);
}






//==============================================================================
//==============================================================================



