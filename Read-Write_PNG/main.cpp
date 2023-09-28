#include "main.h"

int x, y;
pnglib_dll_t *dll;
png_uint_32 width, height;
png_byte color_type;
png_byte bit_depth;

png_structp png_read_ptr;
png_infop info_read_ptr;
png_structp png_write_ptr;
png_infop info_write_ptr;
png_bytep * row_pointers;

int ReadWrite( wchar_t *fpath, wchar_t *fname_read, wchar_t *fname_write );

void log(char* str)
{
	char str0[600];
  int file;
  if((file=w_fopen(L"card/test/png/Log.txt", WA_Create+WA_Append, 0x1FF, 0))>-1)
  {
    sprintf(str0,"\n---------------\n %s", str );
    w_fwrite(file, str0, strlen(str0));                       
    w_fclose(file);
  }
}

void elf_exit(void)
{
  kill_data(&ELF_BEGIN, (void(*)(void*))mfree_adr());
}

void png_user_read(png_structp png_ptr, png_bytep data, png_size_t size)
{
	
  int *f = (int*)png_ptr->io_ptr;
  fread(*f, data, size);
}

void png_user_write(png_structp png_ptr, png_bytep data, png_size_t size)
{
	//---------------------
	log("png_user_write");
  //---------------------
  int *f = (int*)png_ptr->io_ptr;
  fwrite(*f, data, size);
}

int main(void)
{
  log("\n---------------\n main");
  
    switch(ReadWrite(L"card/test/png/",L"test_input.png", L"test_output.png"))
    {
      case 1: MessageBox(EMPTY_TEXTID,STR("PNG file convert\nERROR!!!\n нет входного файла"),NOIMAGE,1,5000,0); break;
      case 2: MessageBox(EMPTY_TEXTID,STR("PNG file convert\nERROR!!!\n это не png"),NOIMAGE,1,5000,0); break;
      case 3: MessageBox(EMPTY_TEXTID,STR("PNG file convert\nERROR!!!\n нет структуры reed"),NOIMAGE,1,5000,0); break;
      case 4: MessageBox(EMPTY_TEXTID,STR("PNG file convert\nERROR!!!\n нет структуры reed inf"),NOIMAGE,1,5000,0); break;
      case 5: MessageBox(EMPTY_TEXTID,STR("PNG file convert\nERROR!!!\n нет выходного файла"),NOIMAGE,1,5000,0); break;
      case 6: MessageBox(EMPTY_TEXTID,STR("PNG file convert\nERROR!!!\n нет структуры write"),NOIMAGE,1,5000,0); break;
      case 7: MessageBox(EMPTY_TEXTID,STR("PNG file convert\nERROR!!!\n нет се. wr. inf"),NOIMAGE,1,5000,0); break;
      case 8: MessageBox(EMPTY_TEXTID,STR("PNG file convert\nERROR!!!\n нет входного файла"),NOIMAGE,1,5000,0); break;
      case 9: MessageBox(EMPTY_TEXTID,STR("PNG file convert\nERROR!!!\n нет DLL"),NOIMAGE,1,5000,0); break;
     default:  MessageBox(EMPTY_TEXTID,STR("PNG file convert ok"),NOIMAGE,1,5000,0); break;
    }  
    SUBPROC(elf_exit);
   return 0;
}
//==============================================================================
//==============================================================================
//==============================================================================

int ReadWrite( wchar_t *fpath, wchar_t *fname_read, wchar_t *fname_write )
{

	//---------------------
	log("ReadWrite");
  //---------------------
//------------------------------------------------  
  png_uint_32 width, height;
  int bit_depth, color_type, interlace_type;
  int compression_type, filter_method;

  FSTAT _fstat_0;
  if (fstat(GetDir(DIR_DLL),L"pnglib.dll",&_fstat_0)!=-1)
  {
    dll = (pnglib_dll_t *)LoadDLL(PNG_DLL_FILE_NAME);
    if (!dll)  return 9;
  }
  
  //------------------------------------------------
	//---------------------
	log("pnglib.dll");
  //---------------------
//------------------------------------------------

  int fpIn;
  int fpOut;


  FSTAT _fstat;
  //wchar_t path_card[256];
  //wstrcpy(path_card,GetDir(DIR_OTHER | MEM_EXTERNAL));
  //wstrcat(path_card,L"/test");
  if (fstat( fpath, fname_read, &_fstat)!=-1)
  {
    if (!((fpIn=_fopen(fpath, fname_read, WA_Read, 0x1FF,0))>=0))
        return 1;
  }
  else
    return 1;
    
	//---------------------
	log("fpIn=_fopen");
  //---------------------
  
  png_read_ptr = dll->png_create_read_struct_2(PNG_LIBPNG_VER_STRING,
        (png_voidp)0, 0, 0, (png_voidp)0, NULL, NULL);
  if (png_read_ptr == NULL)
      return 3;
  //---------------------
	log("dll->png_create_read_struct_2");
  //---------------------
  info_read_ptr = dll->png_create_info_struct(png_read_ptr);
  //---------------------
	log("dll->png_create_info_struct");
  //---------------------
  
  if (info_read_ptr == NULL)
  {
    fclose(fpIn);
    dll->png_destroy_read_struct(&png_read_ptr, 0, 0 );
    //---------------------
  	log("dll->png_destroy_read_struct");
    //---------------------
    return 4;
  }
   

  dll->png_set_read_fn(png_read_ptr, &fpIn, (png_rw_ptr)png_user_read );
  //---------------------
	log("dll->png_set_read_fn(png_read_ptr...");
  //---------------------
 
  dll->png_read_info(png_read_ptr, info_read_ptr);
  //---------------------
	log("dll->png_read_info(png_read_ptr, info_read_ptr)");
  //---------------------

  dll->png_get_IHDR(png_read_ptr, info_read_ptr, &width, &height, &bit_depth,
  	                 &color_type, &interlace_type, &compression_type, &filter_method);
  	                 
  //---------------------
	log("dll->png_get_IHDR(png_read_ptr...");
  //---------------------

  row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
  for (y=0; y<height; y++)
      row_pointers[y] = (png_byte*) malloc(dll->png_get_rowbytes(png_read_ptr,info_read_ptr));
       
  //---------------------
	log("row_pointers = (png_bytep*) malloc(...");
  //---------------------  

  dll->png_read_image(png_read_ptr, row_pointers);
  //---------------------
	log("dll->png_read_image(png_read_ptr...");
  //---------------------

  // освобождаем память выделенную для библиотеки libpng
  dll->png_destroy_read_struct(&png_read_ptr, 0, 0);
  //---------------------
	log("dll->png_destroy_read_struct(&png_read_ptr...");
  //---------------------
  
  fclose(fpIn);


  /*------ Запись png-файла -----*/

 
  if (!((fpOut=_fopen(fpath, fname_write, WA_Create+WA_Write, 0x1FF ,0))>=0))
        return 5;
        
  //---------------------
	log("fpOut=_fopen");
  //---------------------

  png_write_ptr = dll->png_create_write_struct_2(PNG_LIBPNG_VER_STRING,
                                   (png_voidp)0, 0, 0, (png_voidp)0, NULL, NULL);
  //---------------------
	log("png_write_ptr = dll->png_create_write_struct_2(PNG_LIB");
  //---------------------

  if (png_write_ptr == NULL)
  {
    fclose(fpOut);
    //---------------------
	  log("png_write_ptr == NULL");
    //---------------------
    return 6;
  }
   

  info_write_ptr = dll->png_create_info_struct(png_write_ptr);
  if (info_write_ptr == NULL)
  {
    fclose(fpOut);
    dll->png_destroy_read_struct(&png_write_ptr,  NULL, NULL);
    //---------------------
	  log("info_write_ptr == NULL)..");
    //---------------------
    return 7;
  }
  
  dll->png_set_write_fn(png_write_ptr, &fpOut, (png_rw_ptr)png_user_write, NULL);
  //---------------------
	log("dll->png_set_write_fn(png_write_ptr...");
  //---------------------

  
  dll->png_set_IHDR(png_write_ptr, info_write_ptr, width, height, bit_depth,
	                  color_type, interlace_type, compression_type, filter_method);
	//---------------------
	log("dll->png_set_IHDR(png_write_ptr...");
  //---------------------

  dll->png_write_info(png_write_ptr, info_write_ptr);
  //---------------------
	log("dll->png_write_info(png_writ...");
  //---------------------


  // write bytes 

  for(unsigned int i = 0; i < height; i++) // (unsigned int i = height; i > 0; --i)
  {
    dll->png_write_row(png_write_ptr, row_pointers[i]);
  }
  //---------------------
	log("(unsigned int i = height; i > 0; --i)");
  //---------------------
  
  dll->png_write_end(png_write_ptr, info_write_ptr);
  //---------------------
	log("dll->png_write_end(png_write_ptr, info_write_ptr);");
  //---------------------
     
  
  /* cleanup heap allocation */
  for(int i=0; i<height; i++) //(y=height; y > 0; --y)
    mfree(row_pointers[i]);
  mfree(row_pointers);
  //---------------------
//	log("mfree(row_pointers);");
  //---------------------

  dll->png_destroy_write_struct(&png_write_ptr, &info_write_ptr);
  //---------------------
	log("dll->png_destroy_write_struct(&png...");
  //---------------------
  
  fclose(fpOut);
 
  if(dll)
    UnLoadDLL(dll);

  return 0;
 }


