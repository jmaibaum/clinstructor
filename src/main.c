/*
  This file is part of CLInstructor, a free Instructor 50 Emulator.
  Copyright (C) 2014  Johannes Maibaum <jmaibaum@googlemail.com>.

  CLInstructor is free software: you can redistribute it and/or modify it under
  the terms of the GNU General Public License as published by the Free Software
  Foundation, either version 3 of the License, or (at your option) any later
  version.

  CLInstructor is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
  details.

  You should have received a copy of the GNU General Public License along with
  CLInstructor.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>

#include "cpu-2650.h"
#include "parse-hex.h"

int main( int argc, char **argv )
{
  FILE *fp;
  char memory[0x7FFF]; /* We have 32.768 bytes of memory. */
  int err;

  /* Check command line arguments. */
  if ( argc > 1 ) {
    if ( (fp = fopen( argv[1], "r" )) ) { 
      if ( parse_hex_file( fp, memory ) ) {
	printf( "Warning: Emulated memory is full, "
		"but hex file still contains data.\n" );
      }

      fclose( fp );
    } else {
      printf( "Error: Could not open hex file \"%s\".\n", argv[1] );
      return EXIT_FAILURE;
    }
  } else {
    printf( "You have not specified any source files, so I will quit.\n" );
    return EXIT_SUCCESS;
  }

  Cpu cpu; /* Data structure that represents the Signetics 2650. */

  /* Initialize cpu and enter emulation loop. */
  cpu_init( &cpu );

  err = cpu_loop( &cpu, memory );

  if ( err ) {
    printf( "CPU-DUMP:\n"
	    "/----------------------------\\\n"
	    "|IAR:%04X\tIR:%02X        |\n"
	    "|----------------------------|\n"
	    "|R0:%02X\tR1:%02X\tR2:%02X\tR3:%02X|\n"
	    "|\tR4:%02X\tR5:%02X\tR6:%02X|\n"
	    "|----------------------------|\n"
	    "|PSW:%02X%02X                    |\n"
	    "\\----------------------------/\n",
	    cpu.iar,
	    cpu.ir,
	    cpu.register_0,
	    cpu.register_1,
	    cpu.register_2,
	    cpu.register_3,
	    cpu.register_4,
	    cpu.register_5,
	    cpu.register_6,
	    cpu.psu,
	    cpu.psl );
  }

  return err;
}
