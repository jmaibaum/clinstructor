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
#include "debug.h"
#include "machine.h"
#include "parse-hex.h"
#include "os.h"
#include "os-timer.h"

int main( int argc, char **argv )
{
  FILE *fp;

  long cycles, cpu_cycles, real_time;
  int m;
  unsigned char *memory;

  double emu_time, speed;

  /* Allocate space for emulated memory. */
  memory = (unsigned char*) calloc( 0x7FFF, sizeof(unsigned char) );
  if ( memory == NULL ) {
    puts( "Error: Could not allocate space for emulated memory.\n" );
    goto error;
  }

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

    if ( argv[2] ) {
      m = atoi( argv[2] );

      if ( m > 0x7F00 ) {
        m = 0x7F00;
        printf( "Warning: Memory dump start address is too high, "
                "reset to 32512 (0x7F00).\n" );
      } else if ( m < 0 ) {
        m = 0;
        printf( "Warning: Memory dump start address is negative, "
                "reset to 0.\n" );
      }

    } else {
      m = 0;
    }

  } else {
    printf( "You have not specified any source files, so I will quit.\n" );
    return EXIT_SUCCESS;
  }

  /* Initialize cpu and enter emulation loop. */
  Cpu cpu;
  cpu_init( &cpu );

  timer_start();
  cycles = cpu_loop( &cpu, memory );
  timer_stop();

  if ( cpu.error ) {

    if ( cpu.error == 2 ) {
      printf( "Error: Opcode %02X is not implemented, yet.\n\n", cpu.ir );
    }

    CPU_AND_MEMORY_DUMP( m );

    timer_warn();

    cpu_cycles = cycles / 3;
    real_time = timer_elapsed_microsecs();
    emu_time = (1.f / CPU_CLOCK) * cycles * MICRO_SECONDS;
    speed = (emu_time * 100) / real_time;

    printf( "Emulated %ld CPU cycles. Real time: %ld%ss.\n"
            "Emulation time: %.02f%ss. Speed: %.02f%%.\n",
            cpu_cycles, real_time, MICRO_SIGN, emu_time, MICRO_SIGN, speed );

  }

  /* Free dynamic memory. */
  free( memory );

 error:
  return cpu.error;
}
