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

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "parse-hex.h"

/* TODO: Should skip rest of line, allowing for comments in source file. */
int parse_hex_file( FILE *fp, unsigned char *mem )
{
  int bytecount = 0;
  char byte[3];      /* Because of the terminating null byte! */

  while ( fgets( byte, 3, fp ) ) {
    if ( isxdigit( byte[0] ) && isxdigit( byte[1] ) ) {
      if ( bytecount < 0x8000 ) {
        *mem++ = strtol( byte, NULL, 16 );
        ++bytecount;
      } else {
        return EXIT_FAILURE;
      }
    }
  }

  return EXIT_SUCCESS;
}
