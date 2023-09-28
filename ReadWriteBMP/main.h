
#include "..\\include\Lib_Clara.h"
#include "..\\include\Dir.h"
#include "..\\include\Types.h"

#define BOOKNAME "ImageConverter"
#define ELF_VER "1.0"

typedef int FILE;

#pragma pack(push, 1)
typedef struct tagBITMAPFILEHEADER 
{ 
  u16             bfType;        // �������� 0 ���� �� ������ �����
  unsigned int    bfSize;        // �������� 2 ����� �� ������ �����, ����� 4 �����
  u16             bfReserved1;   // 0 
  u16             bfReserved2;   // 0
  unsigned int    bfOffBits;     // �������� 10 ���� �� ������ �����, ����� 4 �����
} BITMAPFILEHEADER, *PBITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER
{
  unsigned int    biSize;           // ������ ������ ��������� � ������.
  unsigned long   biWidth;          // ������ ����������� � ��������.
  unsigned long   biHeight;         // ������ ����������� � ��������. ���� �������� ������������� � ����������� �������� ������-���� (������� ������� � ������� ����� ���� �����������).  
  u16   biPlanes;                   // ���������� �������� ���������� � � ������� BMP �������� �������.
  u16   biBitCount;                 // ���������� ��� �� �������. 
  unsigned int   biCompression;     // ��� ������ ��� ������ �����������
  unsigned long  biSizeImage;       // ������ ����������� � ������.
  long           biXPelsPerMeter;   // �������������� ���������� � �������� �� ���� ��� �������� ����������. 
  long           biYPelsPerMeter;   // ������������ ���������� � �������� �� ���� ��� �������� ����������.
  unsigned int   biClrUsed;         // ���������� ������������ �������� �������� � �������.  
  unsigned int   biClrImportant;    // ���������� ��������� �������, ����������� ��� ����������� �����������.
} BITMAPINFOHEADER, *PBITMAPINFOHEADER;

typedef struct tagRGBTRIPLE 
 {
   u16    rgbBlue; 
   u16    rgbGreen; 
   u16    rgbRed;  
 } RGBTRIPLE;
 
#pragma pack(pop)

/*
  BI_RGB=0,	  //�������� �����������
	BI_RLE8=1,	//������ RLE ��� 8-������ �����������
	BI_RLE4=2,	//������ RLE ��� 4-������ �����������
	BI_BITFIELDS=3,	//����������� �� �����, ������� �������� ��� 4-������� ����� ��� �������, ������ � ����� ��������� �����. ������������ ��� 16- � 32-������ �����������
	BI_JPEG=4,	//Win98/Me/2000/XP: JPEG-������
	BI_PNG=5,	//Win98/Me/2000/XP: PNG-������
	BI_ALPHABITFIELDS=6	//WinCE:  //����������� �� �����, ������� �������� ������ 4-������� ����� ��� �������, ������, ����� 
*/


