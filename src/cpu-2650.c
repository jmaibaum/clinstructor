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

void cpu_init( Cpu *cpu )
{
  cpu->register_0 = 0;
  cpu->register_1 = 0;
  cpu->register_2 = 0;
  cpu->register_3 = 0;
  cpu->register_4 = 0;
  cpu->register_5 = 0;
  cpu->register_6 = 0;

  cpu->psu = 0;
  cpu->psl = 0x10;

  cpu->iar = 0x0000;
}

int cpu_loop( Cpu *cpu, char *memory )
{
  int cpu_error = 0;

  while ( !cpu_error ) {
    cpu->ir = GET_MEMORY( cpu->iar );

    switch( cpu->ir ) {
    case LODZ_0:
      printf( "LODZ_0.\n" );
      break;

    case LODZ_1:
      printf( "LODZ_1.\n" );
      if ( cpu->psl & 0x10 )
	cpu->register_0 = cpu->register_4;
      else
	cpu->register_0 = cpu->register_1;
      break;

    case LODZ_2:
      printf( "LODZ_2.\n" );
      if ( cpu->psl & 0x10 )
	cpu->register_0 = cpu->register_5;
      else
	cpu->register_0 = cpu->register_2;
      break;

    case LODZ_3:
      printf( "LODZ_3.\n" );
      if ( cpu->psl & 0x10 )
	cpu->register_0 = cpu->register_6;
      else
	cpu->register_0 = cpu->register_3;
      break;

    case HALT:
      printf( "CPU is now in HALT state.\n" );
      cpu_error = 1;
      break;

    case NOP:
      printf( "NOP.\n" );
      break;

    default:
      fprintf( stderr, "Error: Opcode 0x%02X is not implemented yet.\n.",
	       cpu->ir );
      cpu_error = 1;
    }

    ++cpu->iar;
  }

  return EXIT_SUCCESS;
}
