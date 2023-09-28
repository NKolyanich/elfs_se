#include "..\\include\Lib_Clara.h"
#include "..\\include\Dir.h"

int hour, min; //время
int day, mon, year; //дата
int heap;     // хип
int silent;   // без. режим
int d_height, d_width; // размеры дисплея
 //  парамеры АКБ
char dest,state; 
int Voltage_Battery;  // напряжение на батарее
int Voltage_Charger;  // напряжение з\у
int Current_Charger;  // ток, получаемый от з\у
int ToBattery_Current;  // ток зарядки
int Temperature_Battery;  // темпер. батареи в 0 Ц
int Temperature_System;   // темпер. телефона в 0 Ц
int Dissipation_Power;  //  потеря мощности

wchar_t ws[0x400]; 

DATETIME dt;
BATT batt;

void elf_exit(void)
   {
     kill_data(&ELF_BEGIN, (void(*)(void*))mfree_adr());
   }

int main(void)
 
    {
     
      // время-----------------------       
   REQUEST_DATEANDTIME_GET(0,&dt);
   hour=dt.time.hour;
   min=dt.time.min;
   // дата------------------------
   day=dt.date.day;
   mon=dt.date.mon;
   year=dt.date.year;
    
// включенный профиль-----------------------------------------------------------
   int pr;
   char*profile;  
   REQUEST_PROFILE_GETACTIVEPROFILE(SYNC,&pr);
    {
      if (pr==0)  { profile = "Обычный";}                                        
      else if (pr==1) { profile = "Совещание";}                                    
      else if (pr==2) { profile = "В автомобиле";}                                     
      else if (pr==3) { profile = "На улице";}                                       
      else if (pr==4) { profile = "Аудиоуст.";}                                 
      else if (pr==5) { profile = "Дома";}
      else if (pr==6) { profile = "На работе";}                                                 
    }
      
// узнаём платформу-------------------------------------------------------------
   char*platform;
   platform="а хз";
   switch ( GetChipID()&CHIPID_MASK ) 
    {
      case CHIPID_DB2000: platform="db2000"; break;
      case CHIPID_DB2010: platform="db2010"; break;
      case CHIPID_DB2020: platform="db2020"; break;
      case CHIPID_PNX5230: platform="pnx5230"; break;
      case CHIPID_DB3150: platform="db3150"; break;
      case CHIPID_DB3200: platform="db3200"; break;
      case CHIPID_DB3210: platform="db3210"; break;
      case CHIPID_DB3350: platform="db3350"; break;
     } 

// узнаем хип( в Кб :) )--------------------------------------------------------     
    heap=(GetFreeBytesOnHeap()/1024);

// узнаем залочена ли клава-----------------------------------------------------
   char*keylock;
   if ( isKeylocked()==0 ) {keylock="выкл."; }                                           
   if ( isKeylocked()==1 ) { keylock="вкл."; }                                                        
   
// узнаем включен режим "без звука" или нет------------------------------------- 
   char*silent;
   if ( GetSilent() ) { silent ="вкл.";}                                                       
   if ( !GetSilent() ) { silent="выкл.";} 
   
/*/ узнаем включен зуб или неt---------------------------------------------------
   char*Blue;
   if ( Bluetooth_GetState()==1 ) { Blue="вкл.";}                                               
   if ( Bluetooth_GetState()==0 ) { Blue="выкл.";} 
//irda--------------------------------------------------------------------------   
   char*state;
   char*Irda;
   IrDa_GetState(state);
   //if (state) {Irda="вкл";}
   //else {Irda="выкл";}     1612603520
   if ( IrDa_GetState(Irda)==1)  { Irda="вкл.";}                                                
     if ( IrDa_GetState(state)==0) { Irda="выкл.";} */
   
// узнаем подключена гарнитура или нет------------------------------------------
   char*PHF;
   if ( PHF_GetState()==1 ) { PHF="подкл.";}                                                 
   if ( PHF_GetState()==0 ) { PHF="откл.";}                                            
   
// узнаем подключен кабель или нет----------------------------------------------
   char*USB;
   if ( USB_isConnected() ) { USB="подкл.";}                                              
   if ( !USB_isConnected() ) {USB="откл.";}                                   
     
// узнаем ширину и высоту диспл-------------------------------------------------
   d_height = Display_GetWidth(0);
   d_width = Display_GetHeight(0);

// яркость подсветки------------------------------------------------------------
 int brightness=Display_GetBrightness(0);
 
// Узнаем память----------------------------------------------------------------
   VOLUMESIZE vol1;
   VOLUMESIZE vol2;
   GetVolumeSize((wchar_t*)L"/card/",&vol1);
   GetVolumeSize((wchar_t*)L"/tpa/",&vol2);
   
// Узнаем gprs------------------------------------------------------------------
   GPRS_SESSION_INFO gprs;
   GPRS_GetLastSessionInfo(0,&gprs);
   
 
// узнаем параметры батареи-----------------------------------------------------
   GetBatteryState(NULL,&batt);
   Voltage_Battery = batt.BatteryVoltage; // напряжение на батарее 
   Voltage_Charger = batt.ChargerVoltage; // напряжение з\у
   Current_Charger = batt.ChargerCurrent; // ток, получаемый от з\у 
   ToBattery_Current = batt.CurrentToBattery; // ток зарядки
   Temperature_Battery = batt.BatteryTemperature; // темпер. батареи в 0 Ц 
   Temperature_System = batt.SystemTemperature;   // темпер. телефона в 0 Ц
   Dissipation_Power=batt.PowerDissipation;  //  потеря мощности
         
// пишем инфу в буфер-----------------------------------------------------------
 snwprintf(ws,0x400,L"Время: %02d:%02d \nДата: %02d-%02d-%04d \nПрофиль: %s \nРежим 'Без звука': %s \n\nБлокировка клавы: %s \nГарнитура: %s \nUSB-кабель: %s \n\nДисплей: %dx%d \nЯркость: %d%%\nПлатформа: %s\nСвободный heap: %d Kb\n\nТемпер. телефона: %d°C\nТемпер. батареи: %d°C\nПроцент заряда: %d%% \n\nНапряжение на батарее: %dmV \nНапряжение з/у: %dmV \nТок, получаемый от з/у: %dmA \nТок зарядки:  %dmA \nПотеря мощности: %ddB \n\nПамять Memory Stick:\nВсего: %d Mb\nСвободно: %d Mb\nЗанято: %d Mb\nПроцент занятого: %d%%\n\nПамять телефона:\nВсего: %d Mb\nСвободно: %d Mb\nЗанято: %d Mb\nПроцент занятого: %d%%\n\nПосл. GPRS сессия:\nДлительность: %d:%d:%d\nПередано: %d Kb\nПринято: %d Kb\nIMSI - %d\n------\n(c)Metaler", 

    hour, min, day, mon, year, profile, silent, 
    keylock, PHF, USB, 
    d_height, d_width, brightness, platform, heap, 
    Temperature_System, Temperature_Battery, batt.RemainingCapacityInPercent, 
    Voltage_Battery,Voltage_Charger,Current_Charger,ToBattery_Current, Dissipation_Power,
    //pamyat ms   
     (unsigned long int)vol1.TotalSpace/1048576,(unsigned long int)vol1.FreeSpace/1048576,
  ((unsigned long int)vol1.TotalSpace-(unsigned long int)vol1.FreeSpace)/1048576,
  100-((unsigned long int)vol1.FreeSpace/((unsigned long int)vol1.TotalSpace/100)),
  //Память на теле
  vol2.TotalSpace/1048576,vol2.FreeSpace/1048576,
  (vol2.TotalSpace-vol2.FreeSpace)/1048576,
  100-(vol2.FreeSpace/(vol2.TotalSpace/100)),
  //Сессия GPRS
  gprs.SesTime/60/60,gprs.SesTime/60%60,gprs.SesTime%60,gprs.SentBytes/1024,gprs.RcvBytes/1024,GetIMSI());
     
//выводим инфу------------------------------------------------------------------      
   MessageBox(STR("AllInfo"),TextID_Create(ws,ENC_UCS2,TEXTID_ANY_LEN), NOIMAGE, 2, 0 , NULL);
   SUBPROC(elf_exit);
      
      return(0);
}

