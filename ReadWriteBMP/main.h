
#include "..\\include\Lib_Clara.h"
#include "..\\include\Dir.h"
#include "..\\include\Types.h"

#define BOOKNAME "ImageConverter"
#define ELF_VER "1.0"

typedef int FILE;

#pragma pack(push, 1)
typedef struct tagBITMAPFILEHEADER 
{ 
  u16             bfType;        // смещение 0 байт от начала файла
  unsigned int    bfSize;        // смещение 2 байта от начала файла, длина 4 байта
  u16             bfReserved1;   // 0 
  u16             bfReserved2;   // 0
  unsigned int    bfOffBits;     // смещение 10 байт от начала файла, длина 4 байта
} BITMAPFILEHEADER, *PBITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER
{
  unsigned int    biSize;           // Размер данной структуры в байтах.
  unsigned long   biWidth;          // Ширина изображения в пикселях.
  unsigned long   biHeight;         // Высота изображения в пикселях. Если значение отрицательное — изображение записано сверху-вниз (нулевой пиксель в верхнем левом углу изображения).  
  u16   biPlanes;                   // Количество цветовых плоскостей и в формате BMP содержит единицу.
  u16   biBitCount;                 // Количество бит на пиксель. 
  unsigned int   biCompression;     // Тип сжатия для сжатых изображений
  unsigned long  biSizeImage;       // Размер изображения в байтах.
  long           biXPelsPerMeter;   // Горизонтальное разрешение в пикселях на метр для целевого устройства. 
  long           biYPelsPerMeter;   // Вертикальное разрешение в пикселях на метр для целевого устройства.
  unsigned int   biClrUsed;         // Количество используемых цветовых индексов в палитре.  
  unsigned int   biClrImportant;    // Количество элементов палитры, необходимых для отображения изображения.
} BITMAPINFOHEADER, *PBITMAPINFOHEADER;

typedef struct tagRGBTRIPLE 
 {
   u16    rgbBlue; 
   u16    rgbGreen; 
   u16    rgbRed;  
 } RGBTRIPLE;
 
#pragma pack(pop)

/*
  BI_RGB=0,	  //несжатое изображение
	BI_RLE8=1,	//сжатие RLE для 8-битных изображений
	BI_RLE4=2,	//сжатие RLE для 4-битных изображений
	BI_BITFIELDS=3,	//изображение не сжато, палитра содержит три 4-байтные маски для красной, зелёной и синей компонент цвета. Используется для 16- и 32-битных изображений
	BI_JPEG=4,	//Win98/Me/2000/XP: JPEG-сжатие
	BI_PNG=5,	//Win98/Me/2000/XP: PNG-сжатие
	BI_ALPHABITFIELDS=6	//WinCE:  //изображение не сжато, палитра содержит четыре 4-байтные маски для красной, зелёной, синей 
*/


