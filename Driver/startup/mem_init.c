/***********************************************************************//** 
 * \file  mem_init.c
 * \brief memery initialization before excecuing main()
 * \copyright Copyright (C) 2015-2024 @ APTCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2024-7 <td>V1.0 <td>WNN     <td>new STDLib
 * </table>
 * *********************************************************************
*/
 
#include <string.h>

extern char _end_rodata[];
extern char _start_data[];
extern char _end_data[];

extern char _bss_start[];
extern char _ebss[];


void __main( void ) 
{

  char *dst = _start_data;
  char *src = _end_rodata;

  /* if the start of data (dst)
     is not equal to end of text (src) then
     copy it, else it's already in the right place
     */
  if( _start_data != _end_rodata ) {
//    __memcpy_fast( dst, src, (_end_data - _start_data));
    memcpy( dst, src, (_end_data - _start_data));
  }

  /* zero the bss 
   */
  if( _ebss - _bss_start ) {
//    __memset_fast( _bss_start, 0x00, ( _ebss - _bss_start ));
    memset( _bss_start, 0x00, ( _ebss - _bss_start ));
  }

	
}

/******************* (C) COPYRIGHT 2024 APT Chip *****END OF FILE****/