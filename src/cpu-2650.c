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
  cpu->psl = 0;

  cpu->iar = 0;
}

int cpu_loop( Cpu *cpu, char *memory )
{
  int cpu_error = 0;

  while ( !cpu_error ) {
    cpu->ir = memory[MEMORY( cpu->iar )];

    switch( cpu->ir ) {

    case LODZ_0: /* 00 */

      printf( "LODZ_0.\n" );

      cpu_error = 1;

      break;


    case LODZ_1: /* 01 */

      printf( "LODZ_1.\n" );

      /* Set register value. */
      cpu->register_0 = REGISTER_BANK ?	cpu->register_4 : cpu->register_1;

      /* Set CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->register_0 );

      break;


    case LODZ_2: /* 02 */

      printf( "LODZ_2.\n" );

      /* Set register value. */
      cpu->register_0 = REGISTER_BANK ?	cpu->register_5 : cpu->register_2;

      /* Set CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->register_0 );

      break;


    case LODZ_3: /* 03 */

      printf( "LODZ_3.\n" );

      /* Set register value. */
      cpu->register_0 = REGISTER_BANK ?	cpu->register_6 : cpu->register_3;

      /* Set CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->register_0 );

      break;


    case LODI_0: /* 04 */

      printf( "LODI_0.\n" );

      /* Set register value. */
      cpu->register_0 = memory[MEMORY( ++cpu->iar )];

      /* Set CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->register_0 );

      break;


    case LODI_1: /* 05 */

      printf( "LODI_1.\n" );

      /* Set register value. */
      if ( REGISTER_BANK )
	cpu->register_4 = memory[MEMORY( ++cpu->iar )];
      else
	cpu->register_1 = memory[MEMORY( ++cpu->iar )];

      /* Set CC flags. */
      CLEAR_CC;
      cpu->psl |= REGISTER_BANK ?
	CC_REG( cpu->register_4 ) : CC_REG( cpu->register_1 );

      break;


    case LODI_2: /* 06 */

      printf( "LODI_2.\n" );

      /* Set register value. */
      if ( REGISTER_BANK )
	cpu->register_5 = memory[MEMORY( ++cpu->iar )];
      else
	cpu->register_2 = memory[MEMORY( ++cpu->iar )];

      /* Set CC flags. */
      CLEAR_CC;
      cpu->psl |= REGISTER_BANK ?
	CC_REG( cpu->register_5 ) : CC_REG( cpu->register_2 );

      break;


    case LODI_3: /* 07 */

      printf( "LODI_3.\n" );

      /* Set register value. */
      if ( REGISTER_BANK )
	cpu->register_6 = memory[MEMORY( ++cpu->iar )];
      else
	cpu->register_3 = memory[MEMORY( ++cpu->iar )];

      /* Set CC flags. */
      CLEAR_CC;
      cpu->psl |= REGISTER_BANK ?
	CC_REG( cpu->register_6 ) : CC_REG( cpu->register_3 );

      break;


    case EORZ_0: /* 20 */

      printf( "EORZ_0.\n" );

      /* Set register value. */
      cpu->register_0 ^= cpu->register_0;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->register_0 );

      break;


    case EORZ_1: /* 21 */

      printf( "EORZ_1.\n" );

      /* Set register value. */
      cpu->register_0 ^= REGISTER_BANK ? cpu->register_4 : cpu->register_1;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->register_0 );

      break;


    case EORZ_2: /* 22 */

      printf( "EORZ_2.\n" );

      /* Set register value. */
      cpu->register_0 ^= REGISTER_BANK ? cpu->register_5 : cpu->register_2;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->register_0 );

      break;


    case EORZ_3: /* 23 */

      printf( "EORZ_3.\n" );

      /* Set register value. */
      cpu->register_0 ^= REGISTER_BANK ? cpu->register_6 : cpu->register_3;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->register_0 );

      break;


    case HALT: /* 40 */

      printf( "CPU is now in HALT state.\n" );
      cpu_error = 1;

      break;


    case ANDZ_1: /* 41 */

      printf( "ANDZ_1.\n" );

      /* Set register value. */
      cpu->register_0 &= REGISTER_BANK ? cpu->register_4 : cpu->register_1;

      /* Set CC value. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->register_0 );

      break;


    case ANDZ_2: /* 42 */

      printf( "ANDZ_2.\n" );

      /* Set register value. */
      cpu->register_0 &= REGISTER_BANK ? cpu->register_5 : cpu->register_2;

      /* Set CC value. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->register_0 );

      break;


    case ANDZ_3: /* 43 */

      printf( "ANDZ_3.\n" );

      /* Set register value. */
      cpu->register_0 &= REGISTER_BANK ? cpu->register_6 : cpu->register_3;

      /* Set CC value. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->register_0 );

      break;


    case IORZ_0: /* 60 */

      printf( "IORZ_0.\n" );

      /*
	Set register value is not necessary, since this:

	  cpu->register_0 |= cpu->register_0;

	does not change the value of Reg 0.
      */

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->register_0 );

      break;


    case IORZ_1: /* 61 */

      printf( "IORZ_1.\n" );

      /* Set register value. */
      cpu->register_0 |= ( REGISTER_BANK ? cpu->register_4 : cpu->register_1 );

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->register_0 );

      break;


    case IORZ_2: /* 62 */

      printf( "IORZ_2.\n" );

      /* Set register value. */
      cpu->register_0 |= ( REGISTER_BANK ? cpu->register_5 : cpu->register_2 );

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->register_0 );

      break;


    case IORZ_3: /* 63 */

      printf( "IORZ_3.\n" );

      /* Set register value. */
      cpu->register_0 |= ( REGISTER_BANK ? cpu->register_6 : cpu->register_3 );

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->register_0 );

      break;


    case LPSU: /* 92 */

      printf( "LPSU.\n" );

      /*
	From the Instruction Manual, p. 68:

	  "Bits #4 and #3 of the PSU are unassigned and will always be regarded
	  as containing zeroes."

        Thus, we have to mask the PSU with 0xE7, which is 0b11100111.
       */
      cpu->psu = ( cpu->register_0 & 0xE7 );

      break;


    case LPSL: /* 93 */

      printf( "LPSL.\n" );

      cpu->psl = cpu->register_0;

      break;


    case NOP: /* C0 */

      printf( "NOP.\n" );

      break;


    case STRZ_1: /* C1 */

      printf( "STRZ_1.\n" );

      /* Set register value. */
      if ( REGISTER_BANK )
	cpu->register_4 = cpu->register_0;
      else
	cpu->register_1 = cpu->register_0;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( REGISTER_BANK ? cpu->register_4 : cpu->register_1 );

      break;


    case STRZ_2: /* C2 */

      printf( "STRZ_2.\n" );

      /* Set register value. */
      if ( REGISTER_BANK )
	cpu->register_5 = cpu->register_0;
      else
	cpu->register_2 = cpu->register_0;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( REGISTER_BANK ? cpu->register_5 : cpu->register_2 );

      break;


    case STRZ_3: /* C3 */

      printf( "STRZ_3.\n" );

      /* Set register value. */
      if ( REGISTER_BANK )
	cpu->register_6 = cpu->register_0;
      else
	cpu->register_3 = cpu->register_0;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( REGISTER_BANK ? cpu->register_6 : cpu->register_3 );

      break;


    case COMZ_0: /* E0 */

      printf( "COMZ_0.\n" );

      /* Set CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_COM( cpu->register_0, cpu->register_0 );

      break;


    case COMZ_1: /* E1 */

      printf( "COMZ_1.\n" );

      /* Set CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_COM( cpu->register_0,
			  REGISTER_BANK ? cpu->register_4 : cpu->register_1 );

      break;


    case COMZ_2: /* E2 */

      printf( "COMZ_2.\n" );

      /* Set CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_COM( cpu->register_0,
			  REGISTER_BANK ? cpu->register_5 : cpu->register_2 );

      break;


    case COMZ_3: /* E3 */

      printf( "COMZ_3.\n" );

      /* Set CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_COM( cpu->register_0,
			  REGISTER_BANK ? cpu->register_6 : cpu->register_3 );

      break;


    case COMI_0: /* E4 */

      printf( "COMI_0.\n" );

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* SET CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_COM( cpu->register_0, cpu->dbr );

      break;


    case COMI_1: /* E5 */

      printf( "COMI_1.\n" );

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* SET CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_COM( REGISTER_BANK ? cpu->register_4 : cpu->register_1,
			  cpu->dbr );

      break;


    case COMI_2: /* E6 */

      printf( "COMI_2.\n" );

      /* Get next byte from memory into Data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* SET CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_COM( REGISTER_BANK ? cpu->register_5 : cpu->register_2,
			  cpu->dbr );

      break;


    case COMI_3: /* E7 */

      printf( "COMI_3.\n" );

      /* Get next byte from memory into Data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* SET CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_COM( REGISTER_BANK ? cpu->register_6 : cpu->register_3,
			  cpu->dbr );

      break;


    default:

      fprintf( stderr, "Error: Opcode 0x%02X is not implemented yet.\n.",
	       cpu->ir );
      cpu_error = 1;

    }

    ++cpu->iar;
  }

  return cpu_error;
}
