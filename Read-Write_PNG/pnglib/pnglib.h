#include "png.h"

#define PNG_DLL_FILE_NAME L"pnglib.dll"

typedef struct pnglib_dll_t _pnglib_dll_t;

#define OLD_PNG_EXPORT PNG_EXPORT
#undef PNG_EXPORT

#define PNG_FPTR(type, name) type (*name)
#define PNG_EXPORT PNG_FPTR

typedef struct pnglib_dll_t {
	wchar_t *dll_name;
	wchar_t *dll_info;
	int version;

	PNG_EXPORT(png_structp,png_create_read_struct_2)
		PNGARG((png_const_charp user_png_ver, png_voidp error_ptr,
		png_error_ptr error_fn, png_error_ptr warn_fn, png_voidp mem_ptr,
		png_malloc_ptr malloc_fn, png_free_ptr free_fn)) PNG_ALLOCATED;

	PNG_EXPORT(int,png_sig_cmp) PNGARG((png_bytep sig, png_size_t start,
		png_size_t num_to_check));

	PNG_EXPORT(png_infop,png_create_info_struct)
		PNGARG((png_structp png_ptr)) PNG_ALLOCATED;

	PNG_EXPORT(void,png_set_read_fn) PNGARG((png_structp png_ptr,
		png_voidp io_ptr, png_rw_ptr read_data_fn));

	PNG_EXPORT(void,png_set_sig_bytes) PNGARG((png_structp png_ptr,
		int num_bytes));

	PNG_EXPORT(void,png_read_info) PNGARG((png_structp png_ptr,
		png_infop info_ptr));

	PNG_EXPORT(png_uint_32,png_get_IHDR) PNGARG((png_structp png_ptr,
		png_infop info_ptr, png_uint_32 *width, png_uint_32 *height,
		int *bit_depth, int *color_type, int *interlace_method,
		int *compression_method, int *filter_method));

	PNG_EXPORT(void,png_set_strip_16) PNGARG((png_structp png_ptr));

	PNG_EXPORT(void,png_set_palette_to_rgb) PNGARG((png_structp png_ptr));

	PNG_EXPORT(void,png_set_gray_to_rgb) PNGARG((png_structp png_ptr));

	PNG_EXPORT(png_uint_32,png_get_gAMA) PNGARG((png_structp png_ptr,
		png_infop info_ptr, double *file_gamma));

	PNG_EXPORT(void,png_set_gamma) PNGARG((png_structp png_ptr,
		double screen_gamma, double default_file_gamma));

	PNG_EXPORT(void,png_read_update_info) PNGARG((png_structp png_ptr,
		png_infop info_ptr));

	PNG_EXPORT(png_size_t,png_get_rowbytes) PNGARG((png_structp png_ptr,
		png_infop info_ptr));

	PNG_EXPORT(void,png_read_image) PNGARG((png_structp png_ptr,
		png_bytepp image));

	PNG_EXPORT(void,png_destroy_read_struct) PNGARG((png_structpp
		png_ptr_ptr, png_infopp info_ptr_ptr, png_infopp end_info_ptr_ptr));

	PNG_EXPORT(png_structp,png_create_write_struct_2)
		PNGARG((png_const_charp user_png_ver, png_voidp error_ptr,
		png_error_ptr error_fn, png_error_ptr warn_fn, png_voidp mem_ptr,
		png_malloc_ptr malloc_fn, png_free_ptr free_fn)) PNG_ALLOCATED;

	PNG_EXPORT(png_structp,png_create_write_struct)
		PNGARG((png_const_charp user_png_ver, png_voidp error_ptr,
		png_error_ptr error_fn, png_error_ptr warn_fn)) PNG_ALLOCATED;

	PNG_EXPORT(png_voidp,png_get_io_ptr) PNGARG((png_structp png_ptr));

	PNG_EXPORT(void,png_destroy_write_struct)
		PNGARG((png_structpp png_ptr_ptr, png_infopp info_ptr_ptr));

	PNG_EXPORT(void,png_set_write_fn) PNGARG((png_structp png_ptr,
		png_voidp io_ptr, png_rw_ptr write_data_fn, png_flush_ptr output_flush_fn));

	PNG_EXPORT(void,png_set_IHDR) PNGARG((png_structp png_ptr,
		png_infop info_ptr, png_uint_32 width, png_uint_32 height, int bit_depth,
		int color_type, int interlace_method, int compression_method,
		int filter_method));

	PNG_EXPORT(void,png_set_compression_level) PNGARG((png_structp png_ptr,
		int level));

	PNG_EXPORT(void,png_write_info) PNGARG((png_structp png_ptr,
		png_infop info_ptr));

	PNG_EXPORT(void,png_write_row) PNGARG((png_structp png_ptr,
		png_bytep row));

	PNG_EXPORT(void,png_write_end) PNGARG((png_structp png_ptr,
		png_infop info_ptr));
		
	PNG_EXPORT(void,png_set_strip_alpha) PNGARG((png_structp png_ptr));
  
  //==================================================
      
  
 /* Returns image width in pixels. */
  PNG_EXPORT(png_uint_32, png_get_image_width) PNGARG((png_structp
   png_ptr, png_infop info_ptr));

/* Returns image height in pixels. */
  PNG_EXPORT(png_uint_32, png_get_image_height) PNGARG((png_structp
   png_ptr, png_infop info_ptr));

/* Returns image bit_depth. */
  PNG_EXPORT(png_byte, png_get_bit_depth) PNGARG((png_structp
   png_ptr, png_infop info_ptr));

/* Returns image color_type. */
  PNG_EXPORT(png_byte, png_get_color_type) PNGARG((png_structp
   png_ptr, png_infop info_ptr));

/* Returns image filter_type. */
  PNG_EXPORT(png_byte, png_get_filter_type) PNGARG((png_structp
   png_ptr, png_infop info_ptr));

/* Returns image interlace_type. */
  PNG_EXPORT(png_byte, png_get_interlace_type) PNGARG((png_structp
   png_ptr, png_infop info_ptr));

/* Returns image compression_type. */
  PNG_EXPORT(png_byte, png_get_compression_type) PNGARG((png_structp
   png_ptr, png_infop info_ptr));

  PNG_EXPORT(int,png_set_interlace_handling) PNGARG((png_structp png_ptr));
  
  PNG_EXPORT(png_bytepp,png_get_rows) PNGARG((png_structp png_ptr,
   png_infop info_ptr));
  
  PNG_EXPORT(void,png_set_rows) PNGARG((png_structp png_ptr,
   png_infop info_ptr, png_bytepp row_pointers));
   
  PNG_EXPORT(void, png_write_png) PNGARG((png_structp png_ptr,
                                          png_infop info_ptr,
                                          int transforms,
                                          png_voidp params));

  PNG_EXPORT(void, png_read_png) PNGARG((png_structp png_ptr,
                                         png_infop info_ptr,
                                         int transforms,
                                         png_voidp params));
  
  PNG_EXPORT(void,png_write_image) PNGARG((png_structp png_ptr,
   png_bytepp image));
  
} _pnglib_dll_t;

#undef PNG_FPTR
#undef PNG_EXPORT
#define PNG_EXPORT OLD_PNG_EXPORT
#undef OLD_PNG_EXPORT

