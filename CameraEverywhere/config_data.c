#include "..\\include\cfg_items.h"
#include "config_data.h"

#pragma diag_suppress = Pe177
//
//
//####################################  Begin Level - Knopka1 ########################################################################################
//****************************************************************************************************************************************************
CFGVAR CFG_HDR cfghdr1 = { CFG_LEVEL ,"Кнопка 1" , 1 , 0}; // arg3 = Begin Level >>>LevelName=Knopka1;

	//---[Check Box]----------------------------------------------------------------------------------[Check Box]
	CFGVAR CFG_HDR cfghdr2 = {CFG_CHECKBOX , "Использовать" , 0 , 0 }; 
	CFGVAR int BCFG_use1 = 1; // Default (True). 
	
	//---[Key Press]-------------------------------------------------------------------------------------[Key Press]
	CFGVAR CFG_HDR cfghdr3 = {CFG_KEYCODE , "Кнопка", 0 , 0};
	CFGVAR int BCFG_k1_KeyCode = 0x41; // Default -> Camera Open Cover. 
	CFGVAR int BCFG_k1_KeyMode = 0; // Default -> Short Press.
	
	//---[Check Box]----------------------------------------------------------------------------------[Check Box]
	CFGVAR CFG_HDR cfghdr4 = {CFG_CHECKBOX , "Игнор. блок. клав." , 0 , 0 }; 
	CFGVAR int BCFG_keylock1 = 1; // Default (True). 
	
	//---[Check Box]----------------------------------------------------------------------------------[Check Box]
	CFGVAR CFG_HDR cfghdr5 = {CFG_CHECKBOX , "Вибро" , 0 , 0 }; 
	CFGVAR int BCFG_vibro1 = 1; // Default (True). 
	
	//---[Number - Integer (signed)]---------------------------------------------------------[Number - Integer (signed)]
	CFGVAR CFG_HDR cfghdr6 = { CFG_INT , "Время одной вибры" , 0 , 500};
	CFGVAR signed int BCFG_vibratime1 = 100; // Default
	
	//---[Number - Integer (signed)]---------------------------------------------------------[Number - Integer (signed)]
	CFGVAR CFG_HDR cfghdr7 = { CFG_INT , "Пауза" , 0 , 250};
	CFGVAR signed int BCFG_pausetime1 = 50; // Default
	
	//---[Number - Integer (signed)]---------------------------------------------------------[Number - Integer (signed)]
	CFGVAR CFG_HDR cfghdr8 = { CFG_INT , "Общее время вибры" , 0 , 1000};
	CFGVAR signed int BCFG_totaltime1 = 250; // Default
	
CFGVAR CFG_HDR cfghdr10 = {CFG_LEVEL , "" , 0 , 0 }; // arg3 = End Level
//****************************************************************************************************************************************************
//####################################  End Level - Knopka1 ##########################################################################################
//
//

//
//
//####################################  Begin Level - Knopka2 ########################################################################################
//****************************************************************************************************************************************************
CFGVAR CFG_HDR cfghdr9 = { CFG_LEVEL ,"Кнопка 2" , 1 , 0}; // arg3 = Begin Level >>>LevelName=Knopka2;

	//---[Check Box]----------------------------------------------------------------------------------[Check Box]
	CFGVAR CFG_HDR cfghdr11 = {CFG_CHECKBOX , "Использовать" , 0 , 0 }; 
	CFGVAR int BCFG_use2 = 0; // Default (True). 
	
	//---[Key Press]-------------------------------------------------------------------------------------[Key Press]
	CFGVAR CFG_HDR cfghdr12 = {CFG_KEYCODE , "Кнопка", 0 , 0};
	CFGVAR int BCFG_k2_KeyCode = 35; // Default -> Camera Shot. 
	CFGVAR int BCFG_k2_KeyMode = 0; // Default -> Short Press.
	
	//---[Check Box]----------------------------------------------------------------------------------[Check Box]
	CFGVAR CFG_HDR cfghdr13 = {CFG_CHECKBOX , "Игнор. блок. клав." , 0 , 0 }; 
	CFGVAR int BCFG_keylock2 = 0; // Default (False). 
	
	//---[Check Box]----------------------------------------------------------------------------------[Check Box]
	CFGVAR CFG_HDR cfghdr14 = {CFG_CHECKBOX , "Вибро" , 0 , 0 }; 
	CFGVAR int BCFG_vibro2 = 1; // Default (True). 
	
	//---[Number - Integer (signed)]---------------------------------------------------------[Number - Integer (signed)]
	CFGVAR CFG_HDR cfghdr15 = { CFG_INT , "Время одной вибры" , 0 , 500};
	CFGVAR signed int BCFG_vibratime2 = 100; // Default
	
	//---[Number - Integer (signed)]---------------------------------------------------------[Number - Integer (signed)]
	CFGVAR CFG_HDR cfghdr16 = { CFG_INT , "Пауза" , 0 , 250};
	CFGVAR signed int BCFG_pausetime2 = 50; // Default
	
	//---[Number - Integer (signed)]---------------------------------------------------------[Number - Integer (signed)]
	CFGVAR CFG_HDR cfghdr17 = { CFG_INT , "Общее время вибры" , 0 , 1000};
	CFGVAR signed int BCFG_totaltime2 = 250; // Default
	
CFGVAR CFG_HDR cfghdr19 = {CFG_LEVEL , "" , 0 , 0 }; // arg3 = End Level
//****************************************************************************************************************************************************
//####################################  End Level - Knopka2 ##########################################################################################
//
//

//
//
//####################################  Begin Level - Knopka3 ########################################################################################
//****************************************************************************************************************************************************
CFGVAR CFG_HDR cfghdr18 = { CFG_LEVEL ,"Кнопка 3" , 1 , 0}; // arg3 = Begin Level >>>LevelName=Knopka3;

	//---[Check Box]----------------------------------------------------------------------------------[Check Box]
	CFGVAR CFG_HDR cfghdr20 = {CFG_CHECKBOX , "Использовать" , 0 , 0 }; 
	CFGVAR int BCFG_use3 = 0; // Default (True). 
	
	//---[Key Press]-------------------------------------------------------------------------------------[Key Press]
	CFGVAR CFG_HDR cfghdr21 = {CFG_KEYCODE , "Кнопка", 0 , 0};
	CFGVAR int BCFG_k3_KeyCode = 35; // Default -> Camera Shot. 
	CFGVAR int BCFG_k3_KeyMode = 0; // Default -> Long Press.
	
	//---[Check Box]----------------------------------------------------------------------------------[Check Box]
	CFGVAR CFG_HDR cfghdr22 = {CFG_CHECKBOX , "Игнор. блок. клав." , 0 , 0 }; 
	CFGVAR int BCFG_keylock3 = 0; // Default (False). 
	
	//---[Check Box]----------------------------------------------------------------------------------[Check Box]
	CFGVAR CFG_HDR cfghdr23 = {CFG_CHECKBOX , "Вибро" , 0 , 0 }; 
	CFGVAR int BCFG_vibro3 = 0; // Default (True). 
	
	//---[Number - Integer (signed)]---------------------------------------------------------[Number - Integer (signed)]
	CFGVAR CFG_HDR cfghdr24 = { CFG_INT , "Время одной вибры" , 0 , 500};
	CFGVAR signed int BCFG_vibratime3 = 100; // Default
	
	//---[Number - Integer (signed)]---------------------------------------------------------[Number - Integer (signed)]
	CFGVAR CFG_HDR cfghdr25 = { CFG_INT , "Пауза" , 0 , 250};
	CFGVAR signed int BCFG_pausetime3 = 50; // Default
	
	//---[Number - Integer (signed)]---------------------------------------------------------[Number - Integer (signed)]
	CFGVAR CFG_HDR cfghdr26 = { CFG_INT , "Общее время вибры" , 0 , 1000};
	CFGVAR signed int BCFG_totaltime3 = 250; // Default
	
CFGVAR CFG_HDR cfghdr27 = {CFG_LEVEL , "" , 0 , 0 }; // arg3 = End Level
//****************************************************************************************************************************************************
//####################################  End Level - Knopka3 ##########################################################################################
//
//
