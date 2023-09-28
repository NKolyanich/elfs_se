
#include "..\\include\Lib_Clara.h"
#include "iconattach.h"

void elf_exit(void)
{
  kill_data(&ELF_BEGIN, (void(*)(void*))mfree_adr());
}


int main(void)
{
  if( iconattach()==0)
  {
    MessageBox(EMPTY_TEXTID,STR("IconAttach elf\n\n(c)Tartes for PC\n(p)Metaler for ElfPack\n\nAll done!"),NOIMAGE,1,8000,0);
    SUBPROC(elf_exit);
    return(0);
  }
  else
  {
    MessageBox(EMPTY_TEXTID,STR("Error!\nCheck the settings and restart the elf. Support only png format"),NOIMAGE,1,5000,0);
    SUBPROC(elf_exit);
    return(0);
  }
}

