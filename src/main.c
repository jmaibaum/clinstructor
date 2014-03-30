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
#include <sys/time.h>

#include "cpu-2650.h"
#include "debug.h"
#include "parse-hex.h"

int main( int argc, char **argv )
{
  FILE *fp;
  unsigned char memory[0x7FFF]; /* We have 32.768 bytes of memory. */
  int err;
  struct timeval start;
  struct timeval stop;

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

  gettimeofday(&start, NULL);
  err = cpu_loop( &cpu, memory );
  gettimeofday(&stop, NULL);

  if ( err ) {

    if ( err == 2 ) {
      printf( "Error: Opcode %02X is not implemented, yet.\n\n", cpu.ir );
    }

    CPU_DUMP;

    if ( stop.tv_sec - start.tv_sec )
      printf( "Emulation lasted longer than one second. "
	      "The next line does\n not tell the truth.\n" );

    printf( "Time Elapsed: %d µs.\n", stop.tv_usec - start.tv_usec );
  }

  return err;
}
