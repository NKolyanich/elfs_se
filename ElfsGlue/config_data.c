#include "..\\include\cfg_items.h"
#include "config_data.h"

#pragma diag_suppress = Pe177
//
//
//####################################  Begin Level - Knopka1 ########################################################################################
//****************************************************************************************************************************************************

   CFGVAR CFG_HDR cfghdr1 = {CFG_CHECKBOX , "Do not start elfs" , 0 , 0 }; 
    CFGVAR int BCFG_elfstart = 0;

//---[Text - UTF-16]-------------------------------------------
CFGVAR CFG_HDR cfghdr2 = { CFG_LEVEL ,"Elf 1" , 1 , 0};
   CFGVAR CFG_HDR cfghdr2_1 = { CFG_UTF16_STRING , "Elf" , 0 , 200};
   CFGVAR wchar_t BCFG_elf_1 [201] = L""; // Default.
   CFGVAR CFG_HDR cfghdr2_2 = {CFG_CHECKBOX , "Use?" , 0 , 0 }; 
   CFGVAR int BCFG_elfstart_1 = 1;   
CFGVAR CFG_HDR cfghdr3 = {CFG_LEVEL,"",0,0};
//------------------------------------------------------------------------------   
CFGVAR CFG_HDR cfghdr4 = { CFG_LEVEL ,"Elf 2" , 1 , 0};   
   CFGVAR CFG_HDR cfghdr4_1 = { CFG_UTF16_STRING , "Elf" , 0 , 200};
   CFGVAR wchar_t BCFG_elf_2 [201] = L"";
   CFGVAR CFG_HDR cfghdr4_2 = {CFG_CHECKBOX , "Use?" , 0 , 0 }; 
   CFGVAR int BCFG_elfstart_2 = 1;   
CFGVAR CFG_HDR cfghdr5 = {CFG_LEVEL,"",0,0};
//------------------------------------------------------------------------------
CFGVAR CFG_HDR cfghdr6 = { CFG_LEVEL ,"Elf 3" , 1 , 0};   
   CFGVAR CFG_HDR cfghdr6_1 = { CFG_UTF16_STRING , "Elf" , 0 , 200};
   CFGVAR wchar_t BCFG_elf_3 [201] = L"";
   CFGVAR CFG_HDR cfghdr6_2 = {CFG_CHECKBOX , "Use?" , 0 , 0 }; 
   CFGVAR int BCFG_elfstart_3 = 1;   
CFGVAR CFG_HDR cfghdr7 = {CFG_LEVEL,"",0,0};
//------------------------------------------------------------------------------
CFGVAR CFG_HDR cfghdr8 = { CFG_LEVEL ,"Elf 4" , 1 , 0};   
   CFGVAR CFG_HDR cfghdr8_1 = { CFG_UTF16_STRING , "Elf" , 0 , 200};
   CFGVAR wchar_t BCFG_elf_4 [201] = L"";
   CFGVAR CFG_HDR cfghdr8_2 = {CFG_CHECKBOX , "Use?" , 0 , 0 }; 
   CFGVAR int BCFG_elfstart_4 = 1;   
CFGVAR CFG_HDR cfghdr9 = {CFG_LEVEL,"",0,0};
//------------------------------------------------------------------------------
CFGVAR CFG_HDR cfghdr10 = { CFG_LEVEL ,"Elf 5" , 1 , 0};   
   CFGVAR CFG_HDR cfghdr10_1 = { CFG_UTF16_STRING , "Elf" , 0 , 200};
   CFGVAR wchar_t BCFG_elf_5 [201] = L"";
   CFGVAR CFG_HDR cfghdr10_2 = {CFG_CHECKBOX , "Use?" , 0 , 0 }; 
   CFGVAR int BCFG_elfstart_5 = 1;   
CFGVAR CFG_HDR cfghdr11 = {CFG_LEVEL,"",0,0};
//------------------------------------------------------------------------------
CFGVAR CFG_HDR cfghdr12 = { CFG_LEVEL ,"Elf 6" , 1 , 0};   
   CFGVAR CFG_HDR cfghdr12_1 = { CFG_UTF16_STRING , "Elf" , 0 , 200};
   CFGVAR wchar_t BCFG_elf_6 [201] = L"";
   CFGVAR CFG_HDR cfghdr12_2 = {CFG_CHECKBOX , "Use?" , 0 , 0 }; 
   CFGVAR int BCFG_elfstart_6 = 1;   
CFGVAR CFG_HDR cfghdr13 = {CFG_LEVEL,"",0,0};
//------------------------------------------------------------------------------
CFGVAR CFG_HDR cfghdr14 = { CFG_LEVEL ,"Elf 7" , 1 , 0};   
   CFGVAR CFG_HDR cfghdr14_1 = { CFG_UTF16_STRING , "Elf" , 0 , 200};
   CFGVAR wchar_t BCFG_elf_7 [201] = L"";
   CFGVAR CFG_HDR cfghdr14_2 = {CFG_CHECKBOX , "Use?" , 0 , 0 }; 
   CFGVAR int BCFG_elfstart_7 = 1;   
CFGVAR CFG_HDR cfghdr15 = {CFG_LEVEL,"",0,0};
//------------------------------------------------------------------------------
CFGVAR CFG_HDR cfghdr16 = { CFG_LEVEL ,"Elf 8" , 1 , 0};   
   CFGVAR CFG_HDR cfghdr16_1 = { CFG_UTF16_STRING , "Elf" , 0 , 200};
   CFGVAR wchar_t BCFG_elf_8 [201] = L"";
   CFGVAR CFG_HDR cfghdr16_2 = {CFG_CHECKBOX , "Use?" , 0 , 0 }; 
   CFGVAR int BCFG_elfstart_8 = 1;   
CFGVAR CFG_HDR cfghdr17 = {CFG_LEVEL,"",0,0};
//------------------------------------------------------------------------------
CFGVAR CFG_HDR cfghdr18 = { CFG_LEVEL ,"Elf 9" , 1 , 0};   
   CFGVAR CFG_HDR cfghdr18_1 = { CFG_UTF16_STRING , "Elf" , 0 , 200};
   CFGVAR wchar_t BCFG_elf_9 [201] = L"";
   CFGVAR CFG_HDR cfghdr18_2 = {CFG_CHECKBOX , "Use?" , 0 , 0 }; 
   CFGVAR int BCFG_elfstart_9 = 1;   
CFGVAR CFG_HDR cfghdr19 = {CFG_LEVEL,"",0,0};
//------------------------------------------------------------------------------
CFGVAR CFG_HDR cfghdr20 = { CFG_LEVEL ,"Elf 10" , 1 , 0};   
   CFGVAR CFG_HDR cfghdr20_1 = { CFG_UTF16_STRING , "Elf" , 0 , 200};
   CFGVAR wchar_t BCFG_elf_10 [201] = L"";
   CFGVAR CFG_HDR cfghdr20_2 = {CFG_CHECKBOX , "Use?" , 0 , 0 }; 
   CFGVAR int BCFG_elfstart_10 = 1;   
CFGVAR CFG_HDR cfghdr21 = {CFG_LEVEL,"",0,0};
//------------------------------------------------------------------------------
CFGVAR CFG_HDR cfghdr22 = { CFG_LEVEL ,"Elf 11" , 1 , 0};   
   CFGVAR CFG_HDR cfghdr22_1 = { CFG_UTF16_STRING , "Elf" , 0 , 200};
   CFGVAR wchar_t BCFG_elf_11 [201] = L"";
   CFGVAR CFG_HDR cfghdr22_2 = {CFG_CHECKBOX , "Use?" , 0 , 0 }; 
   CFGVAR int BCFG_elfstart_11 = 1;   
CFGVAR CFG_HDR cfghdr23 = {CFG_LEVEL,"",0,0};
//------------------------------------------------------------------------------
CFGVAR CFG_HDR cfghdr24 = { CFG_LEVEL ,"Elf 12" , 1 , 0};   
   CFGVAR CFG_HDR cfghdr24_1 = { CFG_UTF16_STRING , "Elf" , 0 , 200};
   CFGVAR wchar_t BCFG_elf_12 [201] = L"";
   CFGVAR CFG_HDR cfghdr24_2 = {CFG_CHECKBOX , "Use?" , 0 , 0 }; 
   CFGVAR int BCFG_elfstart_12 = 1;   
CFGVAR CFG_HDR cfghdr25 = {CFG_LEVEL,"",0,0};
//------------------------------------------------------------------------------
CFGVAR CFG_HDR cfghdr26 = { CFG_LEVEL ,"Elf 13" , 1 , 0};   
   CFGVAR CFG_HDR cfghdr26_1 = { CFG_UTF16_STRING , "Elf" , 0 , 200};
   CFGVAR wchar_t BCFG_elf_13 [201] = L"";
   CFGVAR CFG_HDR cfghdr26_2 = {CFG_CHECKBOX , "Use?" , 0 , 0 }; 
   CFGVAR int BCFG_elfstart_13 = 1;   
CFGVAR CFG_HDR cfghdr27 = {CFG_LEVEL,"",0,0};
//------------------------------------------------------------------------------
CFGVAR CFG_HDR cfghdr28 = { CFG_LEVEL ,"Elf 14" , 1 , 0};   
   CFGVAR CFG_HDR cfghdr28_1 = { CFG_UTF16_STRING , "Elf" , 0 , 200};
   CFGVAR wchar_t BCFG_elf_14 [201] = L"";
   CFGVAR CFG_HDR cfghdr28_2 = {CFG_CHECKBOX , "Use?" , 0 , 0 }; 
   CFGVAR int BCFG_elfstart_14 = 1;   
CFGVAR CFG_HDR cfghdr29 = {CFG_LEVEL,"",0,0};
//------------------------------------------------------------------------------
CFGVAR CFG_HDR cfghdr30 = { CFG_LEVEL ,"Elf 15" , 1 , 0};   
   CFGVAR CFG_HDR cfghdr30_1 = { CFG_UTF16_STRING , "Elf" , 0 , 200};
   CFGVAR wchar_t BCFG_elf_15 [201] = L"";
   CFGVAR CFG_HDR cfghdr30_2 = {CFG_CHECKBOX , "Use?" , 0 , 0 }; 
   CFGVAR int BCFG_elfstart_15 = 1;   
CFGVAR CFG_HDR cfghdr31 = {CFG_LEVEL,"",0,0};
   

//
