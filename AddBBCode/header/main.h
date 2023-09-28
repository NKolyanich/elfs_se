#ifndef _MAIN_H
#define _MAIN_H


#include "..\\include\Lib_Clara.h"
#include "..\\include\Dir.h"
#include "..\\include\cfg_items.h"
#include "conf_loader.h"
#include "config_data.h"
#include "header\main.h"
#include "header\gui.h"
#include "header\SmilesMenu.h"
#include "header\colorGUI.h"
#define ELF_BCFG_CONFIG_EVENT 994

#if defined(LNG_RUS)
    #include "header\LANGUAGE_RUS.h"
#elif defined(LNG_ENG)
    #include "header\LANGUAGE_ENG.h"
#endif
//------------------------------------------------------------------------------
#define MM_BROWSERTOPLEVELBOOK "MM_BrowserTopLevelBook"
#define SOFTKEYNAMEID "BB-коды"

#define BBCODEGUI "BBCodeMenu"


extern int GetDB();


#endif //_MAIN_H
