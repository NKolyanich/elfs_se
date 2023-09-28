#include "..\\include\Lib_Clara.h"
#include "..\\include\Dir.h"

int hour, min; //�����
int day, mon, year; //����
int heap;     // ���
int silent;   // ���. �����
int d_height, d_width; // ������� �������
 //  �������� ���
char dest,state; 
int Voltage_Battery;  // ���������� �� �������
int Voltage_Charger;  // ���������� �\�
int Current_Charger;  // ���, ���������� �� �\�
int ToBattery_Current;  // ��� �������
int Temperature_Battery;  // ������. ������� � 0 �
int Temperature_System;   // ������. �������� � 0 �
int Dissipation_Power;  //  ������ ��������

wchar_t ws[0x400]; 

DATETIME dt;
BATT batt;

void elf_exit(void)
   {
     kill_data(&ELF_BEGIN, (void(*)(void*))mfree_adr());
   }

int main(void)
 
    {
     
      // �����-----------------------       
   REQUEST_DATEANDTIME_GET(0,&dt);
   hour=dt.time.hour;
   min=dt.time.min;
   // ����------------------------
   day=dt.date.day;
   mon=dt.date.mon;
   year=dt.date.year;
    
// ���������� �������-----------------------------------------------------------
   int pr;
   char*profile;  
   REQUEST_PROFILE_GETACTIVEPROFILE(SYNC,&pr);
    {
      if (pr==0)  { profile = "�������";}                                        
      else if (pr==1) { profile = "���������";}                                    
      else if (pr==2) { profile = "� ����������";}                                     
      else if (pr==3) { profile = "�� �����";}                                       
      else if (pr==4) { profile = "��������.";}                                 
      else if (pr==5) { profile = "����";}
      else if (pr==6) { profile = "�� ������";}                                                 
    }
      
// ����� ���������-------------------------------------------------------------
   char*platform;
   platform="� ��";
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

// ������ ���( � �� :) )--------------------------------------------------------     
    heap=(GetFreeBytesOnHeap()/1024);

// ������ �������� �� �����-----------------------------------------------------
   char*keylock;
   if ( isKeylocked()==0 ) {keylock="����."; }                                           
   if ( isKeylocked()==1 ) { keylock="���."; }                                                        
   
// ������ ������� ����� "��� �����" ��� ���------------------------------------- 
   char*silent;
   if ( GetSilent() ) { silent ="���.";}                                                       
   if ( !GetSilent() ) { silent="����.";} 
   
/*/ ������ ������� ��� ��� ��t---------------------------------------------------
   char*Blue;
   if ( Bluetooth_GetState()==1 ) { Blue="���.";}                                               
   if ( Bluetooth_GetState()==0 ) { Blue="����.";} 
//irda--------------------------------------------------------------------------   
   char*state;
   char*Irda;
   IrDa_GetState(state);
   //if (state) {Irda="���";}
   //else {Irda="����";}     1612603520
   if ( IrDa_GetState(Irda)==1)  { Irda="���.";}                                                
     if ( IrDa_GetState(state)==0) { Irda="����.";} */
   
// ������ ���������� ��������� ��� ���------------------------------------------
   char*PHF;
   if ( PHF_GetState()==1 ) { PHF="�����.";}                                                 
   if ( PHF_GetState()==0 ) { PHF="����.";}                                            
   
// ������ ��������� ������ ��� ���----------------------------------------------
   char*USB;
   if ( USB_isConnected() ) { USB="�����.";}                                              
   if ( !USB_isConnected() ) {USB="����.";}                                   
     
// ������ ������ � ������ �����-------------------------------------------------
   d_height = Display_GetWidth(0);
   d_width = Display_GetHeight(0);

// ������� ���������------------------------------------------------------------
 int brightness=Display_GetBrightness(0);
 
// ������ ������----------------------------------------------------------------
   VOLUMESIZE vol1;
   VOLUMESIZE vol2;
   GetVolumeSize((wchar_t*)L"/card/",&vol1);
   GetVolumeSize((wchar_t*)L"/tpa/",&vol2);
   
// ������ gprs------------------------------------------------------------------
   GPRS_SESSION_INFO gprs;
   GPRS_GetLastSessionInfo(0,&gprs);
   
 
// ������ ��������� �������-----------------------------------------------------
   GetBatteryState(NULL,&batt);
   Voltage_Battery = batt.BatteryVoltage; // ���������� �� ������� 
   Voltage_Charger = batt.ChargerVoltage; // ���������� �\�
   Current_Charger = batt.ChargerCurrent; // ���, ���������� �� �\� 
   ToBattery_Current = batt.CurrentToBattery; // ��� �������
   Temperature_Battery = batt.BatteryTemperature; // ������. ������� � 0 � 
   Temperature_System = batt.SystemTemperature;   // ������. �������� � 0 �
   Dissipation_Power=batt.PowerDissipation;  //  ������ ��������
         
// ����� ���� � �����-----------------------------------------------------------
 snwprintf(ws,0x400,L"�����: %02d:%02d \n����: %02d-%02d-%04d \n�������: %s \n����� '��� �����': %s \n\n���������� �����: %s \n���������: %s \nUSB-������: %s \n\n�������: %dx%d \n�������: %d%%\n���������: %s\n��������� heap: %d Kb\n\n������. ��������: %d�C\n������. �������: %d�C\n������� ������: %d%% \n\n���������� �� �������: %dmV \n���������� �/�: %dmV \n���, ���������� �� �/�: %dmA \n��� �������:  %dmA \n������ ��������: %ddB \n\n������ Memory Stick:\n�����: %d Mb\n��������: %d Mb\n������: %d Mb\n������� ��������: %d%%\n\n������ ��������:\n�����: %d Mb\n��������: %d Mb\n������: %d Mb\n������� ��������: %d%%\n\n����. GPRS ������:\n������������: %d:%d:%d\n��������: %d Kb\n�������: %d Kb\nIMSI - %d\n------\n(c)Metaler", 

    hour, min, day, mon, year, profile, silent, 
    keylock, PHF, USB, 
    d_height, d_width, brightness, platform, heap, 
    Temperature_System, Temperature_Battery, batt.RemainingCapacityInPercent, 
    Voltage_Battery,Voltage_Charger,Current_Charger,ToBattery_Current, Dissipation_Power,
    //pamyat ms   
     (unsigned long int)vol1.TotalSpace/1048576,(unsigned long int)vol1.FreeSpace/1048576,
  ((unsigned long int)vol1.TotalSpace-(unsigned long int)vol1.FreeSpace)/1048576,
  100-((unsigned long int)vol1.FreeSpace/((unsigned long int)vol1.TotalSpace/100)),
  //������ �� ����
  vol2.TotalSpace/1048576,vol2.FreeSpace/1048576,
  (vol2.TotalSpace-vol2.FreeSpace)/1048576,
  100-(vol2.FreeSpace/(vol2.TotalSpace/100)),
  //������ GPRS
  gprs.SesTime/60/60,gprs.SesTime/60%60,gprs.SesTime%60,gprs.SentBytes/1024,gprs.RcvBytes/1024,GetIMSI());
     
//������� ����------------------------------------------------------------------      
   MessageBox(STR("AllInfo"),TextID_Create(ws,ENC_UCS2,TEXTID_ANY_LEN), NOIMAGE, 2, 0 , NULL);
   SUBPROC(elf_exit);
      
      return(0);
}

