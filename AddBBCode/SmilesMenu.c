#include "..\\include\Lib_Clara.h"
#include "..\\include\Dir.h"
#include "..\\include\Colors.h"
#include "conf_loader.h"
#include "config_data.h"
#include "header\gui.h"
#include "header\colorGUI.h"
#include "header\SmileSMenu.h"

#if defined(LNG_RUS)
    #include "header\LANGUAGE_RUS.h"
#elif defined(LNG_ENG)
    #include "header\LANGUAGE_ENG.h"
#endif

//==============================================================================
// таймер перерисовки отключен, перерисовка после нажатия клавиши

int h_cut_table_i=0; // количество строк таблицы вырезки фреймов
const int w_table_j=7;    // количество столбцов таблицы вырезки фреймов

int h_draw_table_i=0;// количество строк таблицы отрисовки фреймов
int w_draw_table_j=0;   // количество столбцов таблицы отрисовки фреймов

int number_smile=0;   // общее количество смайлов
int frame_size=0;     // размер фрейма

int image_width;   // ширина изобр.
int image_height;
wchar_t imgID=0;
int read_frame_size=0;  // флаг прочтения размера фрейма

int DisplayWidth=0;
int DisplayHeight=0;

//============= прототипы функций ==============================================
void Send_RELEASE_REDRAW(void);
void (*Old_Redraw)( DISP_OBJ *, int r1, int r2, int r3 );
void DrawSmileMenu( DISP_OBJ * db, int r1, int r2, int r3 );
void termSmileMenu(void);
wchar_t * SmileStrCode( wchar_t * code );
void SmileMenuOnEnterPress( BOOK* bk, GUI_LIST* gui );
int LoadSmileSource(void);
//==============================================================================
// Структуры
// табличка координат вырезки фреймов
struct
{
  u16 x;
  u16 y;
} table_cut_img[224];

// табличка координат отрисовки фреймов
struct
{
  u16 x;
  u16 y;
} table_draw_img[224];

// названия и коды смайлов (фреймов)
struct
{
  wchar_t smile_name[32];
  wchar_t smile_code[32];
} smiles_stc[224];

//---------- перересовка -------------------------------------------------------------------------

void Send_RELEASE_REDRAW()
{
  // посылаем всем  мессагу со старым и своим методами Redraw
  REDRAW_RELEASE_MESSAGE * sbm= new REDRAW_RELEASE_MESSAGE;
  memset(sbm,0,sizeof(REDRAW_RELEASE_MESSAGE));
  sbm->SB_OldOnRedraw=Old_Redraw;
  sbm->SB_NewOnRedraw=DrawSmileMenu;
  UI_Event_wData(SBY_REDRAW_RELEASE_EVENT ,sbm,(void (*)(void*))mfree_adr());
}
// ============== чтение из smiles.ini =========================================
// и так ясно..
void win12512unicode(wchar_t *ws, const char *s, int len)
{
  int c;
  while((c=*s++)&&((len--)>0))
  {
    if (c==0xA8) c=0x401;
    if (c==0xAA) c=0x404;
    if (c==0xAF) c=0x407;
    if (c==0xB8) c=0x451;
    if (c==0xBA) c=0x454;
    if (c==0xBF) c=0x457;
    if ((c>=0xC0)&&(c<0x100)) c+=0x350;
    *ws++=c;
  }
  *ws=0;
}

int atoi(char *s)
{
  int i, n;
  n = 0;
  for (i = 0; s[i] >= '0' && s[i] <= '9';++i)
    n = 10 * n + (s[i] - '0');
  return n;
}

// для void readconfig()
char* read(char* p)
{
  int file;
  FSTAT _fstat;
  wchar_t path_card[256];
  wchar_t path_usb[256];
  char * buf=0;
  char* param=0;
  wstrcpy(path_card,GetDir(DIR_ELFS_CONFIG | MEM_EXTERNAL));
  wstrcat(path_card,L"/AddBBCode");
  wstrcpy(path_usb,GetDir(DIR_ELFS_CONFIG | MEM_INTERNAL));
  wstrcat(path_usb,L"/AddBBCode");
  if(fstat(path_card, L"smiles.ini",&_fstat)>=0)
  {
    if ((file=_fopen(path_card,L"smiles.ini",0x001,0x180,0))>=0)
    {
      buf=new char[_fstat.fsize+1];
      buf[fread(file,buf,_fstat.fsize)]=0;
      param = manifest_GetParam(buf, p, 0);
      delete buf;
      fclose(file);
    }
  }
  else if(fstat(path_usb, L"smiles.ini",&_fstat)>=0)
  {
    if ((file=_fopen(path_usb,L"smiles.ini",0x001,0x180,0))>=0)
    {
      buf=new char[_fstat.fsize+1];
      buf[fread(file,buf,_fstat.fsize)]=0;
      param = manifest_GetParam(buf, p, 0);
      delete buf;
      fclose(file);
    }
  }
  if (param)  return param;
  else return 0;
}
//Читаем значения из конфига и записываем их в структуру.
void readconfig()
{
  if( read_frame_size == 0 )
  {
    char framesize[]="[FRAME_SIZE]";
    frame_size = atoi( read(framesize) );
    read_frame_size=1;
  }
  if( read_frame_size == 1 )
  {
    char smilename[32];
    char smilecode[32];
    for(int i = 0; i < number_smile; i++)
    {
      sprintf(smilename,"[SMILE_NAME_%d]",i);
      sprintf(smilecode,"[SMILE_CODE_%d]",i);
      win12512unicode(smiles_stc[i].smile_name, read(smilename), strlen(read(smilename)));
      win12512unicode(smiles_stc[i].smile_code, read(smilecode), strlen(read(smilecode)));
    }
  }
}
// ============== чтение из smiles.ini  END  ===================================


//=============== считаем координаты и пишем в структуру =======================
void LoadXY_Smile()
{
  // грузим координаты для вырезки смайлов (154x154)
  u16 x=0;
  u16 y=0;
  int p=0;
  for( int i=0; i < h_cut_table_i; i++ ) // строки
  {
    for( int j=0; j < w_table_j; j++ )  // столбцы
    {
      table_cut_img[p].x = x;
      table_cut_img[p].y = y;
      p++;
      x+=frame_size;
    }
    x=0;
    y+=frame_size;
  }
  
// -----------------------------------------------------------------------------
  h_draw_table_i = (DisplayHeight-70)/frame_size;
  w_draw_table_j = (DisplayWidth-0)/frame_size;
  int n = (((DisplayWidth-15)%frame_size)+10)/h_draw_table_i;
  u16 w=5;   // начальная позиция x отрисовки
  u16 h=40;   // начальная позиция y отрисовки
  u16 ind=frame_size+n; // отступ между смайлами


 // грузим координаты для отрисовки смайлов
  u16 xn=0;
  u16 yn=0;
  p=0;
  for( int i=0; i<h_draw_table_i; i++ ) //  строки
  {
    for( int j=0; j<w_draw_table_j; j++ )  // столбцы
    {
      table_draw_img[p].x=w+xn;
      table_draw_img[p].y=h+yn;
      p++;
      xn+=ind;
    }
    xn=0;
    yn+=ind;
  }
}
//=============== считаем координаты и пишем в структуру  END  =================

// =============================================================================
// рисуем шконки пунктов (смайлы)
GC* hMGC=NULL;
GVI_GC imggc=NULL;

GVI_GC gvigcdisp=NULL;

void DrawItemImage()
{
  #define putchar_(a,b,c,d,e,f) if (f && f!=NOIMAGE) \
                              GC_PutChar(a,b,c,d,e,f)

    GC *GCanvas=(GC*)get_DisplayGC();
  if(imggc==0)
  {
    hMGC = GC_CreateMemoryGC(image_width, image_height, 24,0,0,0);
    CANVAS_Get_GviGC(hMGC->pcanvas ,&imggc);
    putchar_(hMGC,0,0,0,0,imgID);
  }
  CANVAS_Get_GviGC(GCanvas->pcanvas,&gvigcdisp);

 int p=0;
for( int i=0; i<h_draw_table_i; i++ )
  {
    for( int j=0; j<w_draw_table_j; j++ )
    {
        GVI_BitBlt(gvigcdisp,
                    table_draw_img[p].x,
                    table_draw_img[p].y,
                    frame_size,frame_size,
                    imggc,
                    table_cut_img[p].x,
                    table_cut_img[p].y,
                    204, 0, 0, 0);
        p++;
    }
  }
}


//----------------- рисуем курсор -------------------------------------------------------------

void DrawMenuCursor(DISP_OBJ * db, int x)
{
  int y=0;
  int p=0;
  for( int i=0; i<h_draw_table_i; i++ )
  {
    for( int j=0; j<w_draw_table_j; j++ )
    {
      if(y==x)
      {
        DrawRect(table_draw_img[p].x,//-img_struct.curs_plus,
                 table_draw_img[p].y,//-img_struct.curs_plus,
                 table_draw_img[p].x+28,//+img_struct.curs_plus,
                 table_draw_img[p].y+28,//+img_struct.curs_plus,
                 0xff0000ff, 0x00000000 );
        p++;
       // void GC_DrawRoundRect( GC* gc, RECT*, int arcWidth, int arcHeight, int border_flag, int fill_flag );
      }
      y++;
    }
  }
}


void DrawSmileMenu(DISP_OBJ * db,int r1, int r2,int r3)
{
  // вызываем родной onRedraw.
  Old_Redraw(db,r1,r2,r3);
  DrawRect(0, 0, DisplayWidth, DisplayHeight, clBlack, clBlack ); // сделаем чёрный фон
  DrawItemImage();
  // Draw Cursor ---------------------------------------------------------------
  int sitem=ListMenu_GetSelectedItem( DispObject_GetGUI(db) );
  DrawMenuCursor(db, sitem);
  //============================
/*  GC * gc = (GC*)get_DisplayGC();
  GC_SetPenColor( gc, 0xFF0000FF );
  GC_DrawLine( gc, 128, 0, 128, 160);
  GC_DrawLine( gc, 0, 160, 128, 160); */
}
// =============================================================================
inline void SetHeaderText(int item)
{
  DispObject_InvalidateRect(mbk->disp_obj,0);
  GUIObject_SetTitleText(mbk->smile_gui, TextID_Create(smiles_stc[item].smile_name, ENC_UCS2,TEXTID_ANY_LEN));
}

void SmileMenuOnKey(DISP_OBJ *db,int key,int a,int b,int type)
{  
  int sItem=ListMenu_GetSelectedItem(DispObject_GetGUI(db));

  if((key==KEY_DOWN || key==KEY_DIGITAL_0+8) && type==KBD_SHORT_PRESS)
  {
    switch(sItem)
    {
      case 42: { SetCursorToItem(DispObject_GetGUI(db), 1); SetHeaderText(1); break; }
      case 43: { SetCursorToItem(DispObject_GetGUI(db), 2); SetHeaderText(2); break; }
      case 44: { SetCursorToItem(DispObject_GetGUI(db), 3); SetHeaderText(3); break; }
      case 45: { SetCursorToItem(DispObject_GetGUI(db), 4); SetHeaderText(4); break; }
      case 46: { SetCursorToItem(DispObject_GetGUI(db), 5); SetHeaderText(5); break; }
      case 47: { SetCursorToItem(DispObject_GetGUI(db), 6); SetHeaderText(6); break; }
      case 48: { SetCursorToItem(DispObject_GetGUI(db), 0); SetHeaderText(0); break; }
      default: { SetCursorToItem(DispObject_GetGUI(db), sItem+7); SetHeaderText(sItem+7); break; }
    }
  }
  
  if((key==KEY_UP || key==KEY_DIGITAL_0+2) && type==KBD_SHORT_PRESS)
  {
    switch(sItem)
    {
      case 0: { SetCursorToItem(DispObject_GetGUI(db), 48); SetHeaderText(48); break; }
      case 1: { SetCursorToItem(DispObject_GetGUI(db), 42); SetHeaderText(42); break; }
      case 2: { SetCursorToItem(DispObject_GetGUI(db), 43); SetHeaderText(43); break; }
      case 3: { SetCursorToItem(DispObject_GetGUI(db), 44); SetHeaderText(44); break; }
      case 4: { SetCursorToItem(DispObject_GetGUI(db), 45); SetHeaderText(45); break; }
      case 5: { SetCursorToItem(DispObject_GetGUI(db), 46); SetHeaderText(46); break; }
      case 6: { SetCursorToItem(DispObject_GetGUI(db), 47); SetHeaderText(47); break; }
      default: { SetCursorToItem(DispObject_GetGUI(db), sItem-7); SetHeaderText(sItem-7); break; }
    }
  }
  
  if((key==KEY_LEFT || key==KEY_DIGITAL_0+4) && type==KBD_SHORT_PRESS)
  {
    if(sItem==0) { SetCursorToItem(DispObject_GetGUI(db), 48); SetHeaderText(48); }
    else { SetCursorToItem(DispObject_GetGUI(db), sItem-1); SetHeaderText(sItem-1); }
  }
  
  if((key==KEY_RIGHT || key==KEY_DIGITAL_0+6) && type==KBD_SHORT_PRESS)
  {
    if(sItem==48)  { SetCursorToItem(DispObject_GetGUI(db), 0); SetHeaderText(0); }
    else { SetCursorToItem(DispObject_GetGUI(db), sItem+1);  SetHeaderText(sItem+1); }
  }
  
  if(key==KEY_DIGITAL_0+5 && type==KBD_SHORT_PRESS)
      SmileMenuOnEnterPress(&(mbk->book),mbk->smile_gui);
      
}

// =============================================================================
void SmileMenuBack(BOOK* bk,GUI_LIST* gui)
{
  termSmileMenu();
  if(gui)
  {
    GUIObject_Destroy(gui);
    gui=0;
  }
  if(imgID )ImageID_Free(imgID);
  GuiCreateGuiList(0,&(mbk->book),mbk->main_gui);
}


void termSmileMenu(void)
{
  hMGC=NULL;
  imggc=NULL;
  gvigcdisp=NULL;
  DISP_DESC_SetOnRedraw(DispObject_GetDESC(mbk->disp_obj),Old_Redraw);
  Send_RELEASE_REDRAW();
}


wchar_t * SmileStrCode( wchar_t * code )
{
  u16 slen1;
  wchar_t *wstr_new = new wchar_t[wstrlen(code)+1];
  wchar_t wstr1[2]=L" ";
  wchar_t wstr2[2]=L" ";
  slen1=wstrlen(wstr1);
  wstrcpy(wstr_new,wstr1);
  wstr_new[slen1]='\0';
  wstrcat(wstr_new, code);
  wstr_new[slen1+wstrlen(code)]='\0';
  slen1=wstrlen(wstr_new);
  wstrcat(wstr_new, wstr2);
  wstr_new[slen1+wstrlen(wstr2)]='\0';

  return(wstr_new);
}


void SmileMenuOnEnterPress(BOOK* bk,GUI_LIST* gui)
{
  termSmileMenu();
  int item = ListMenu_GetSelectedItem(mbk->smile_gui);
  if(item >= 0) TextCopi(bk, mbk->smile_gui, SmileStrCode(smiles_stc[item].smile_code), wstrlen(smiles_stc[item].smile_code)+2);
}

/*
void ShowMSG(BOOK* bk,GUI_LIST* gui)
{
  wchar_t info[256];
  snwprintf(info,255,L"%ls\n\n%ls",smile_struct[0].smilename,smile_struct[0].smilecode);
  MessageBox(EMPTY_TEXTID,TextID_Create(info,ENC_UCS2,TEXTID_ANY_LEN),NOIMAGE,1,0,0);
}
*/
// =============================================================================
int ExecuteCutTable( void )
{
  if( LoadSmileSource() )  // если загрузили картинку смайлов
  {
    image_width = GetImageWidth( imgID );   // ширина изобр.
    image_height = GetImageHeight( imgID ); // высота изобр.
    h_cut_table_i = image_height / frame_size;    // количество строк таблицы вырезки фреймов
    //w_cut_table_j = image_width / frame_size;  // количество столбцов таблицы вырезки фреймов
    number_smile = h_cut_table_i * w_table_j;// общее количество смайлов
    return 1; // грузим коды из smiles.ini
  }
  return 0; // шлём нахер...
}

int LoadSmileSource(void)
{
  FSTAT _fstat;
  wchar_t path_card[256];
  wchar_t path_usb[256];

  wstrcpy(path_card,GetDir(DIR_ELFS_CONFIG | MEM_EXTERNAL));
  wstrcat(path_card,L"/AddBBCode");
  wstrcpy(path_usb,GetDir(DIR_ELFS_CONFIG | MEM_INTERNAL));
  wstrcat(path_usb,L"/AddBBCode");
  if(fstat(path_card, L"smiles.png",&_fstat)>=0)
  {
    ImageID_Get(path_card,L"smiles.png",&imgID);
  }
  else if(fstat(path_usb, L"smiles.png",&_fstat)>=0)
  {
    ImageID_Get(path_usb,L"smiles.png",&imgID);
  }
  return 1;
}

// =============================================================================
void SmileMenuCreate(void* r0,BOOK* bk,GUI_LIST* gui)
{ 
 // ------  на все экраны ;)  -------------------------------------------------
  DisplayWidth = Display_GetWidth(0);
  DisplayHeight = Display_GetHeight(0);
  LoadXY_Smile();
//------------------------------------------------------------------------------
  mbk->current_gui = mbk->smile_gui=CreateListMenu(bk, 0);
  GUIObject_SetTitleText(mbk->smile_gui, TextID_Create(smiles_stc[0].smile_name, ENC_UCS2,TEXTID_ANY_LEN));
  ListMenu_SetItemCount(mbk->smile_gui, number_smile);
  SetCursorToItem(mbk->smile_gui,0);
  SetMenuItemStyle(mbk->smile_gui, 6); //10
  GUIObject_SetStyle(mbk->smile_gui, 4);
  
  GUIObject_SoftKeys_SetAction(mbk->smile_gui, ACTION_BACK,SmileMenuBack);
  GUIObject_SoftKeys_SetAction(mbk->smile_gui, ACTION_LONG_BACK,MainMenuGUIBack);
  GUIObject_SoftKeys_SetAction(mbk->smile_gui, ACTION_SELECT1,SmileMenuOnEnterPress);
   
  DispObject_SetScrollBarColor( GUIObject_GetDispObject(mbk->smile_gui), clAlpha );
  DispObject_SetScrollBarBackgroundColor (GUIObject_GetDispObject(mbk->smile_gui), clAlpha );
  //---------
   //GUIObject_SoftKeys_SetAction(mbk->smile_gui,ACTION_MORE,ShowMSG);
   //GUIObject_SoftKeys_SetText(mbk->smile_gui,ACTION_MORE,TextID_Create(L"Test",ENC_UCS2,TEXTID_ANY_LEN));
  //----------
  mbk->disp_obj=GUIObject_GetDispObject(mbk->smile_gui);
  Old_Redraw=DispObject_GetOnRedraw(mbk->disp_obj);
  DISP_DESC_SetOnRedraw(DispObject_GetDESC(mbk->disp_obj),DrawSmileMenu);
  mbk->disp_desc=DispObject_GetDESC ( GUIObject_GetDispObject(mbk->smile_gui) );
  DISP_DESC_SetOnKey(mbk->disp_desc, SmileMenuOnKey);
  GUIObject_Show(mbk->smile_gui);
}






//==============================================================================
//==============================================================================



