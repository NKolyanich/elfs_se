#include "..\\include\cfg_items.h"
#include "config_data.h"

#pragma diag_suppress = Pe177

//==========================---------------=====================================

CFGVAR CFG_HDR cfghdr1 = { CFG_LEVEL ,"Books and Java" , 1 , 0};
//////////////////// 
   CFGVAR CFG_HDR cfghdr1_1 = { CFG_STR_WIN1251 , "Book 1" , 0 , 31};
	CFGVAR char  __BCFG_BOOK_NAME_1[32] = ""; 
//------------------------------------------------------------------------------	
   CFGVAR CFG_HDR cfghdr1_2 = { CFG_STR_WIN1251 , "Book 2" , 0 , 31};
	CFGVAR char __BCFG_BOOK_NAME_2[32] = "";	
//------------------------------------------------------------------------------ 		
   CFGVAR CFG_HDR cfghdr1_3 = { CFG_STR_WIN1251 , "Book 3" , 0 , 31};
	CFGVAR char __BCFG_BOOK_NAME_3[32] = "";
//------------------------------------------------------------------------------
   CFGVAR CFG_HDR cfghdr1_4 = { CFG_STR_WIN1251 , "Book 4" , 0 , 31};
	CFGVAR char __BCFG_BOOK_NAME_4[32] = "";
//------------------------------------------------------------------------------    
   CFGVAR CFG_HDR cfghdr1_5 = { CFG_STR_WIN1251 , "Book 5" , 0 , 31};
	CFGVAR char __BCFG_BOOK_NAME_5[32] = "";
///////////////////
CFGVAR CFG_HDR cfghdr2 = { CFG_LEVEL ,"" , 0, 0};

//---[Check Box]----------------------------------------------------------------------------------[Check Box]
CFGVAR CFG_HDR cfghdr3 = {CFG_CHECKBOX , "Доб. # к коду цвета?" , 0 , 0 };
CFGVAR int BCFG_add_diez2color = 0; // Default (False).
