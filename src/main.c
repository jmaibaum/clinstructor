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
  int i;

  /* Check command line arguments. */
  if ( argc > 1 ) {
    if ( (fp = fopen( argv[1], "r" )) ) { 
      parse_hex_file( fp, memory );
      fclose( fp );
    }
  } else {
    printf( "You have not specified any source files, so I will quit.\n" );
    return 0;
  }

  Cpu cpu; /* Data structure that represents the Signetics 2650. */

  /* From here on, this is just test code, to prove the concept. */
  init_cpu( &cpu );

  /* To check the hex parser, print out the first ten bytes in memory. */
  for ( i = 0; i < 16; ++i )
    printf( "Value at memory location 0x%04X: 0x%02X.\n",
	    i, (unsigned char) memory[i] );

  return 0;
}
