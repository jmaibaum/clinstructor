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

#include "cpu-2650.h"

int main( void )
{
  Cpu cpu; /* Data structure that represents the Signetics 2650. */
  unsigned char memory[0x7FFF]; /* We have 32.768 bytes of memory. */

  /* From here on, this is just test code, to prove the concept. */
  init_cpu( &cpu );

  memory[ cpu.pc ] = 255;

  printf( "PC: 0x%04X; Value at that memory location: 0x%02X.\n",
	  cpu.pc, memory[ cpu.pc ] );

  return 0;
}
