#ifndef _COLOR_GUI_H
#define _COLOR_GUI_H

#define clAlpha 0x00000000
#define clBorder 0xFFCCCCCC

#define COLOR_GET_A(x) ((unsigned int)x>>24)
#define COLOR_GET_R(x) (((unsigned int)x>>16)&0xFF)
#define COLOR_GET_G(x) (((unsigned int)x>>8)&0xFF)
#define COLOR_GET_B(x) ((unsigned int)x&0xFF)

#define COLOR_RGBA(r,g,b,a) (((unsigned int)r<<16)|((unsigned int)g<<8)|((unsigned int)b)|((unsigned int)a<<24))


extern void termColorGUI();
extern void ColorGuiCreate(void* r0,BOOK* bk,GUI_LIST* gui);
extern int _add_diez2color;


#endif //_COLORGUI_H


