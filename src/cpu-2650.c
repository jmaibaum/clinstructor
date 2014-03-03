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

/* #include <stdio.h> */
#include <stdlib.h>

#include "cpu-2650.h"

void cpu_init( Cpu *cpu )
{
  cpu->register_0 =
  cpu->register_1 =
  cpu->register_2 =
  cpu->register_3 =
  cpu->register_4 =
  cpu->register_5 =
  cpu->register_6 =

  cpu->psu =
  cpu->psl =

  cpu->iar = 0;
}

int cpu_loop( Cpu *cpu, unsigned char *memory )
{
  int cpu_error = 0;

  while ( !cpu_error ) {
    cpu->ir = memory[MEMORY( cpu->iar )];

    switch( cpu->ir ) {

    case LODZ_0: /* 00 */

      cpu_error = 1;

      break;


    case LODZ_1: /* 01 */

      /* Set register value. */
      cpu->register_0 = REGISTER_BANK ?	cpu->register_4 : cpu->register_1;

      /* Set CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->register_0 );

      break;


    case LODZ_2: /* 02 */

      /* Set register value. */
      cpu->register_0 = REGISTER_BANK ?	cpu->register_5 : cpu->register_2;

      /* Set CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->register_0 );

      break;


    case LODZ_3: /* 03 */

      /* Set register value. */
      cpu->register_0 = REGISTER_BANK ?	cpu->register_6 : cpu->register_3;

      /* Set CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->register_0 );

      break;


    case LODI_0: /* 04 */

      /* Set register value. */
      cpu->register_0 = memory[MEMORY( ++cpu->iar )];

      /* Set CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->register_0 );

      break;


    case LODI_1: /* 05 */

      /* Set register value. */
      if ( REGISTER_BANK )
	cpu->register_4 = memory[MEMORY( ++cpu->iar )];
      else
	cpu->register_1 = memory[MEMORY( ++cpu->iar )];

      /* Set CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_REG( REGISTER_BANK ? cpu->register_4 : cpu->register_1 );

      break;


    case LODI_2: /* 06 */

      /* Set register value. */
      if ( REGISTER_BANK )
	cpu->register_5 = memory[MEMORY( ++cpu->iar )];
      else
	cpu->register_2 = memory[MEMORY( ++cpu->iar )];

      /* Set CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_REG( REGISTER_BANK ? cpu->register_5 : cpu->register_2 );

      break;


    case LODI_3: /* 07 */

      /* Set register value. */
      if ( REGISTER_BANK )
	cpu->register_6 = memory[MEMORY( ++cpu->iar )];
      else
	cpu->register_3 = memory[MEMORY( ++cpu->iar )];

      /* Set CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_REG( REGISTER_BANK ? cpu->register_6 : cpu->register_3 );

      break;


    case LODR_0: /* 08 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Indirect or direct addressing? */
      if ( cpu->dbr & INDIRECT ) {
	/* Set register value. */
	cpu->register_0 =
	  memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar, cpu->rel_off) )];
      } else {
	/* Set register value. */
	cpu->register_0 =
	  memory[MEMORY( RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )];
      }

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->register_0 );

      break;


    case LODR_1: /* 09 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Indirect or direct addressing? */
      if ( cpu->dbr & INDIRECT ) {
	/* Set register value. */
	if ( REGISTER_BANK )
	  cpu->register_4 =
	    memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
						      cpu->rel_off) )];
	else
	  cpu->register_1 =
	    memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
						      cpu->rel_off) )];
      } else {
	/* Set register value. */
	if ( REGISTER_BANK )
	  cpu->register_4 =
	    memory[MEMORY( RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )];
	else
	  cpu->register_1 =
	    memory[MEMORY( RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )];
      }

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( REGISTER_BANK ? cpu->register_4 : cpu->register_1 );

      break;


    case LODR_2: /* 0A */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Indirect or direct addressing? */
      if ( cpu->dbr & INDIRECT ) {
	/* Set register value. */
	if ( REGISTER_BANK )
	  cpu->register_5 =
	    memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
						      cpu->rel_off) )];
	else
	  cpu->register_2 =
	    memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
						      cpu->rel_off) )];
      } else {
	/* Set register value. */
	if ( REGISTER_BANK )
	  cpu->register_5 =
	    memory[MEMORY( RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )];
	else
	  cpu->register_2 =
	    memory[MEMORY( RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )];
      }

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( REGISTER_BANK ? cpu->register_5 : cpu->register_2 );

      break;


    case LODR_3: /* 0B */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Indirect or direct addressing? */
      if ( cpu->dbr & INDIRECT ) {
	/* Set register value. */
	if ( REGISTER_BANK )
	  cpu->register_6 =
	    memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
						      cpu->rel_off) )];
	else
	  cpu->register_3 =
	    memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
						      cpu->rel_off) )];
      } else {
	/* Set register value. */
	if ( REGISTER_BANK )
	  cpu->register_6 =
	    memory[MEMORY( RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )];
	else
	  cpu->register_3 =
	    memory[MEMORY( RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )];
      }

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( REGISTER_BANK ? cpu->register_6 : cpu->register_3 );

      break;


    case LODA_0: /* 0C */

      /* Get high order address byte into holding register and low order address
	 byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];
      cpu->indexing = cpu->hr & INDEXING;

      if ( cpu->indexing ) {

	/* Increment/decrement index register. */
	if ( cpu->indexing != SIMPLE_INDEXING ) {
	  (cpu->indexing == INCREMENT) ? ++cpu->register_0 : --cpu->register_0;
	}

	if ( cpu->hr & INDIRECT ) {
	  cpu->register_0 =
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT( cpu->register_0,
							    cpu->hr,
							    cpu->dbr) )];
	} else {
	  cpu->register_0 =
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDEX( cpu->register_0,
						   cpu->hr,
						   cpu->dbr ) )];
	}
      } else {
	if ( cpu->hr & INDIRECT ) {
	  cpu->register_0 =
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )];
	} else {
	  cpu->register_0 = memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr,
							     cpu->dbr ) )];
	}
      }

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->register_0 );

      break;


    case LODA_1: /* 0D */

      /* Get high order address byte into holding register and low order address
	 byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];
      cpu->indexing = cpu->hr & INDEXING;

      if ( cpu->indexing ) {

	/* Increment/decrement index register. */
	if ( cpu->indexing != SIMPLE_INDEXING ) {
	  (cpu->indexing == INCREMENT) ?
	    ( (REGISTER_BANK) ? ++cpu->register_4 : ++cpu->register_1 ) :
	    ( (REGISTER_BANK) ? --cpu->register_4 : --cpu->register_1 );
	}

	if ( cpu->hr & INDIRECT ) {
	  cpu->register_0 =
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT(
		        ( REGISTER_BANK ? cpu->register_4 : cpu->register_1 ),
							    cpu->hr,
							    cpu->dbr) )];
	} else {
	  cpu->register_0 =
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDEX(
	       ( REGISTER_BANK ? cpu->register_4 : cpu->register_1 ),
						   cpu->hr,
						   cpu->dbr ) )];
	}

	/* Set CC. */
	CLEAR_CC;
	cpu->psl |= CC_REG( cpu->register_0 );

      } else {

	if ( REGISTER_BANK ) {
	  cpu->register_4 = ( cpu->hr & INDIRECT ) ?
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )] :
	    memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )];
	} else {
	  cpu->register_1 = ( cpu->hr & INDIRECT ) ?
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )] :
	    memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )];
	}

	/* Set CC. */
	CLEAR_CC;
	cpu->psl |= CC_REG( REGISTER_BANK ? cpu->register_4 : cpu->register_1 );
      }

      break;


    case LODA_2: /* 0E */

      /* Get high order address byte into holding register and low order address
	 byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];
      cpu->indexing = cpu->hr & INDEXING;

      if ( cpu->indexing ) {

	/* Increment/decrement index register. */
	if ( cpu->indexing != SIMPLE_INDEXING ) {
	  (cpu->indexing == INCREMENT) ?
	    ( (REGISTER_BANK) ? ++cpu->register_5 : ++cpu->register_2 ) :
	    ( (REGISTER_BANK) ? --cpu->register_5 : --cpu->register_2 );
	}

	if ( cpu->hr & INDIRECT ) {
	  cpu->register_0 =
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT(
		        ( REGISTER_BANK ? cpu->register_5 : cpu->register_2 ),
							    cpu->hr,
							    cpu->dbr) )];
	} else {
	  cpu->register_0 =
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDEX(
	       ( REGISTER_BANK ? cpu->register_5 : cpu->register_2 ),
						   cpu->hr,
						   cpu->dbr ) )];
	}

	/* Set CC. */
	CLEAR_CC;
	cpu->psl |= CC_REG( cpu->register_0 );

      } else {

	if ( REGISTER_BANK ) {
	  cpu->register_5 = ( cpu->hr & INDIRECT ) ?
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )] :
	    memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )];
	} else {
	  cpu->register_2 = ( cpu->hr & INDIRECT ) ?
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )] :
	    memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )];
	}

	/* Set CC. */
	CLEAR_CC;
	cpu->psl |= CC_REG( REGISTER_BANK ? cpu->register_5 : cpu->register_2 );
      }

      break;


    case LODA_3: /* 0F */

      /* Get high order address byte into holding register and low order address
	 byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];
      cpu->indexing = cpu->hr & INDEXING;

      if ( cpu->indexing ) {

	/* Increment/decrement index register. */
	if ( cpu->indexing != SIMPLE_INDEXING ) {
	  (cpu->indexing == INCREMENT) ?
	    ( (REGISTER_BANK) ? ++cpu->register_6 : ++cpu->register_3 ) :
	    ( (REGISTER_BANK) ? --cpu->register_6 : --cpu->register_3 );
	}

	if ( cpu->hr & INDIRECT ) {
	  cpu->register_0 =
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT(
		        ( REGISTER_BANK ? cpu->register_6 : cpu->register_3 ),
							    cpu->hr,
							    cpu->dbr) )];
	} else {
	  cpu->register_0 =
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDEX(
	       ( REGISTER_BANK ? cpu->register_6 : cpu->register_3 ),
						   cpu->hr,
						   cpu->dbr ) )];
	}

	/* Set CC. */
	CLEAR_CC;
	cpu->psl |= CC_REG( cpu->register_0 );

      } else {

	if ( REGISTER_BANK ) {
	  cpu->register_6 = ( cpu->hr & INDIRECT ) ?
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )] :
	    memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )];
	} else {
	  cpu->register_3 = ( cpu->hr & INDIRECT ) ?
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )] :
	    memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )];
	}

	/* Set CC. */
	CLEAR_CC;
	cpu->psl |= CC_REG( REGISTER_BANK ? cpu->register_6 : cpu->register_3 );
      }

      break;


    case SPSU: /* 12 */

      /* Set register value. */
      cpu->register_0 = cpu->psu;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->register_0 );

      break;


    case SPSL: /* 13 */

      /* Set register value. */
      cpu->register_0 = cpu->psl;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->register_0 );

      break;


    case BCTR_0: /* 18 */
    case BCTR_1: /* 19 */
    case BCTR_2: /* 1A */
    case BCTR_3: /* 1B */
      /* Extract CC code from Opcode and scale it to PSL format for
	 comparison. */
      cpu->cc = ( cpu->ir & 0x3 ) << 6;

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( cpu->cc == C_CODE || cpu->cc == PSL_CC ) {
	cpu->rel_off = cpu->dbr & R_OFFSET;

	/* Indirect or direct addressing? */
	if ( cpu->dbr & INDIRECT ) {
	  /* Branch to specified address. */
	  cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
								   cpu->rel_off
								   ) ) );
	} else {
	  /* Branch to specified address. */
	  cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS( cpu->iar,
							  cpu->rel_off ) ) );
	}

      }

      /* No setting of CC required. */

      break;


    case BCTA_0: /* 1C */
    case BCTA_1: /* 1D */
    case BCTA_2: /* 1E */
    case BCTA_3: /* 1F */
      /* Extract CC code from Opcode and scale it to PSL format for
	 comparison. */
      cpu->cc = ( cpu->ir & 0x3 ) << 6;

      /* Get high order address byte into holding register and low order address
	 byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( cpu->cc == C_CODE || cpu->cc == PSL_CC ) {
	cpu->iar = (cpu->hr & INDIRECT) ?
	  MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) ) :
	  MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) );
      }

      /* No setting of CC required. */

      break;


    case EORZ_0: /* 20 */

      /* Set register value. */
      cpu->register_0 ^= cpu->register_0;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->register_0 );

      break;


    case EORZ_1: /* 21 */

      /* Set register value. */
      cpu->register_0 ^= REGISTER_BANK ? cpu->register_4 : cpu->register_1;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->register_0 );

      break;


    case EORZ_2: /* 22 */

      /* Set register value. */
      cpu->register_0 ^= REGISTER_BANK ? cpu->register_5 : cpu->register_2;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->register_0 );

      break;


    case EORZ_3: /* 23 */

      /* Set register value. */
      cpu->register_0 ^= REGISTER_BANK ? cpu->register_6 : cpu->register_3;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->register_0 );

      break;


    case EORI_0: /* 24 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* Set register value. */
      cpu->register_0 ^= cpu->dbr;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->register_0 );

      break;


    case EORI_1: /* 25 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* Set register value. */
      if ( REGISTER_BANK )
	cpu->register_4 ^= cpu->dbr;
      else
	cpu->register_1 ^= cpu->dbr;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( REGISTER_BANK ? cpu->register_4 : cpu->register_1 );

      break;


    case EORI_2: /* 26 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* Set register value. */
      if ( REGISTER_BANK )
	cpu->register_5 ^= cpu->dbr;
      else
	cpu->register_2 ^= cpu->dbr;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( REGISTER_BANK ? cpu->register_5 : cpu->register_2 );

      break;


    case EORI_3: /* 27 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* Set register value. */
      if ( REGISTER_BANK )
	cpu->register_6 ^= cpu->dbr;
      else
	cpu->register_3 ^= cpu->dbr;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( REGISTER_BANK ? cpu->register_6 : cpu->register_3 );

      break;


    case EORR_0: /* 28 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Set register value */
      cpu->register_0 ^= (cpu->dbr & INDIRECT) ?
	memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar, cpu->rel_off ) )] :
	memory[MEMORY( RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )];

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->register_0 );

      break;


    case EORR_1: /* 29 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Set register value */
      if ( REGISTER_BANK ) {
	cpu->register_4 ^= (cpu->dbr & INDIRECT) ?
	  memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
						    cpu->rel_off ) )] :
	  memory[MEMORY( RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )];
      } else {
	cpu->register_1 ^= (cpu->dbr & INDIRECT) ?
	  memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
						    cpu->rel_off ) )] :
	  memory[MEMORY( RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )];
      }

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( REGISTER_BANK ? cpu->register_4 : cpu->register_1 );

      break;


    case EORR_2: /* 2A */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Set register value */
      if ( REGISTER_BANK ) {
	cpu->register_5 ^= (cpu->dbr & INDIRECT) ?
	  memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
						    cpu->rel_off ) )] :
	  memory[MEMORY( RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )];
      } else {
	cpu->register_2 ^= (cpu->dbr & INDIRECT) ?
	  memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
						    cpu->rel_off ) )] :
	  memory[MEMORY( RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )];
      }

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( REGISTER_BANK ? cpu->register_5 : cpu->register_2 );

      break;


    case EORR_3: /* 2B */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Set register value */
      if ( REGISTER_BANK ) {
	cpu->register_6 ^= (cpu->dbr & INDIRECT) ?
	  memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
						    cpu->rel_off ) )] :
	  memory[MEMORY( RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )];
      } else {
	cpu->register_3 ^= (cpu->dbr & INDIRECT) ?
	  memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
						    cpu->rel_off ) )] :
	  memory[MEMORY( RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )];
      }

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( REGISTER_BANK ? cpu->register_6 : cpu->register_3 );

      break;


    case EORA_0: /* 2C */

      /* Get high order address byte into holding register and low order address
	 byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];
      cpu->indexing = cpu->hr & INDEXING;

      if ( cpu->indexing ) {

	/* Increment/decrement index register. */
	if ( cpu->indexing != SIMPLE_INDEXING ) {
	  (cpu->indexing == INCREMENT) ? ++cpu->register_0 : --cpu->register_0;
	}

	if ( cpu->hr & INDIRECT ) {
	  cpu->register_0 ^=
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT( cpu->register_0,
							    cpu->hr,
							    cpu->dbr) )];
	} else {
	  cpu->register_0 ^=
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDEX( cpu->register_0, cpu->hr,
						   cpu->dbr ) )];
	}

      } else {
	cpu->register_0 ^= ( cpu->hr & INDIRECT ) ?
	  memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )] :
	  memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )];
      }

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->register_0 );

      break;


    case EORA_1: /* 2D */

      /* Get high order address byte into holding register and low order address
	 byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];
      cpu->indexing = cpu->hr & INDEXING;

      if ( cpu->indexing ) {

	/* Increment/decrement index register. */
	if ( cpu->indexing != SIMPLE_INDEXING ) {
	  (cpu->indexing == INCREMENT) ?
	    ( (REGISTER_BANK) ? ++cpu->register_4 : ++cpu->register_1 ) :
	    ( (REGISTER_BANK) ? --cpu->register_4 : --cpu->register_1 );
	}

	if ( cpu->hr & INDIRECT ) {
	  cpu->register_0 ^=
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT(
		        ( REGISTER_BANK ? cpu->register_4 : cpu->register_1 ),
							    cpu->hr,
							    cpu->dbr) )];
	} else {
	  cpu->register_0 ^=
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDEX(
	       ( REGISTER_BANK ? cpu->register_4 : cpu->register_1 ),
						   cpu->hr, cpu->dbr ) )];
	}

	/* Set CC. */
	CLEAR_CC;
	cpu->psl |= CC_REG( cpu->register_0 );

      } else {

	if ( REGISTER_BANK ) {
	  cpu->register_4 ^= ( cpu->hr & INDIRECT ) ?
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )] :
	    memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )];
	} else {
	  cpu->register_1 ^= ( cpu->hr & INDIRECT ) ?
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )] :
	    memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )];
	}

	/* Set CC. */
	CLEAR_CC;
	cpu->psl |= CC_REG( REGISTER_BANK ? cpu->register_4 : cpu->register_1 );
      }

      break;


    case EORA_2: /* 2E */

      /* Get high order address byte into holding register and low order address
	 byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];
      cpu->indexing = cpu->hr & INDEXING;

      if ( cpu->indexing ) {

	/* Increment/decrement index register. */
	if ( cpu->indexing != SIMPLE_INDEXING ) {
	  (cpu->indexing == INCREMENT) ?
	    ( (REGISTER_BANK) ? ++cpu->register_5 : ++cpu->register_2 ) :
	    ( (REGISTER_BANK) ? --cpu->register_5 : --cpu->register_2 );
	}

	if ( cpu->hr & INDIRECT ) {
	  cpu->register_0 ^=
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT(
		        ( REGISTER_BANK ? cpu->register_5 : cpu->register_2 ),
							    cpu->hr,
							    cpu->dbr) )];
	} else {
	  cpu->register_0 ^=
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDEX(
	       ( REGISTER_BANK ? cpu->register_5 : cpu->register_2 ),
						   cpu->hr, cpu->dbr ) )];
	}

	/* Set CC. */
	CLEAR_CC;
	cpu->psl |= CC_REG( cpu->register_0 );

      } else {

	if ( REGISTER_BANK ) {
	  cpu->register_4 ^= ( cpu->hr & INDIRECT ) ?
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )] :
	    memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )];
	} else {
	  cpu->register_1 ^= ( cpu->hr & INDIRECT ) ?
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )] :
	    memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )];
	}

	/* Set CC. */
	CLEAR_CC;
	cpu->psl |= CC_REG( REGISTER_BANK ? cpu->register_5 : cpu->register_2 );
      }

      break;


    case EORA_3: /* 2F */

      /* Get high order address byte into holding register and low order address
	 byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];
      cpu->indexing = cpu->hr & INDEXING;

      if ( cpu->indexing ) {

	/* Increment/decrement index register. */
	if ( cpu->indexing != SIMPLE_INDEXING ) {
	  (cpu->indexing == INCREMENT) ?
	    ( (REGISTER_BANK) ? ++cpu->register_6 : ++cpu->register_3 ) :
	    ( (REGISTER_BANK) ? --cpu->register_6 : --cpu->register_3 );
	}

	if ( cpu->hr & INDIRECT ) {
	  cpu->register_0 ^=
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT(
		        ( REGISTER_BANK ? cpu->register_6 : cpu->register_3 ),
							    cpu->hr,
							    cpu->dbr) )];
	} else {
	  cpu->register_0 ^=
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDEX(
	       ( REGISTER_BANK ? cpu->register_6 : cpu->register_3 ),
						   cpu->hr, cpu->dbr ) )];
	}

	/* Set CC. */
	CLEAR_CC;
	cpu->psl |= CC_REG( cpu->register_0 );

      } else {

	if ( REGISTER_BANK ) {
	  cpu->register_4 ^= ( cpu->hr & INDIRECT ) ?
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )] :
	    memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )];
	} else {
	  cpu->register_1 ^= ( cpu->hr & INDIRECT ) ?
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )] :
	    memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )];
	}

	/* Set CC. */
	CLEAR_CC;
	cpu->psl |= CC_REG( REGISTER_BANK ? cpu->register_6 : cpu->register_3 );
      }

      break;


    case HALT: /* 40 */

      cpu_error = 1;

      break;


    case ANDZ_1: /* 41 */

      /* Set register value. */
      cpu->register_0 &= REGISTER_BANK ? cpu->register_4 : cpu->register_1;

      /* Set CC value. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->register_0 );

      break;


    case ANDZ_2: /* 42 */

      /* Set register value. */
      cpu->register_0 &= REGISTER_BANK ? cpu->register_5 : cpu->register_2;

      /* Set CC value. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->register_0 );

      break;


    case ANDZ_3: /* 43 */

      /* Set register value. */
      cpu->register_0 &= REGISTER_BANK ? cpu->register_6 : cpu->register_3;

      /* Set CC value. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->register_0 );

      break;


    case ANDI_0: /* 44 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* Set register value. */
      cpu->register_0 &= cpu->dbr;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->register_0 );

      break;


    case ANDI_1: /* 45 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* Set register value. */
      if ( REGISTER_BANK )
	cpu->register_4 &= cpu->dbr;
      else
	cpu->register_1 &= cpu->dbr;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( REGISTER_BANK ? cpu->register_4 : cpu->register_1 );

      break;


    case ANDI_2: /* 46 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* Set register value. */
      if ( REGISTER_BANK )
	cpu->register_5 &= cpu->dbr;
      else
	cpu->register_2 &= cpu->dbr;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( REGISTER_BANK ? cpu->register_5 : cpu->register_2 );

      break;


    case ANDI_3: /* 47 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* Set register value. */
      if ( REGISTER_BANK )
	cpu->register_6 &= cpu->dbr;
      else
	cpu->register_3 &= cpu->dbr;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( REGISTER_BANK ? cpu->register_6 : cpu->register_3 );

      break;


    case ANDR_0: /* 48 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Set register value */
      cpu->register_0 &= (cpu->dbr & INDIRECT) ?
	memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar, cpu->rel_off ) )] :
	memory[MEMORY( RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )];

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->register_0 );

      break;


    case ANDR_1: /* 49 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Set register value */
      if ( REGISTER_BANK ) {
	cpu->register_4 &= (cpu->dbr & INDIRECT) ?
	  memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
						    cpu->rel_off ) )] :
	  memory[MEMORY( RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )];
      } else {
	cpu->register_1 &= (cpu->dbr & INDIRECT) ?
	  memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
						    cpu->rel_off ) )] :
	  memory[MEMORY( RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )];
      }

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( REGISTER_BANK ? cpu->register_4 : cpu->register_1 );

      break;


    case ANDR_2: /* 4A */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Set register value */
      if ( REGISTER_BANK ) {
	cpu->register_5 &= (cpu->dbr & INDIRECT) ?
	  memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
						    cpu->rel_off ) )] :
	  memory[MEMORY( RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )];
      } else {
	cpu->register_2 &= (cpu->dbr & INDIRECT) ?
	  memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
						    cpu->rel_off ) )] :
	  memory[MEMORY( RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )];
      }

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( REGISTER_BANK ? cpu->register_5 : cpu->register_2 );

      break;


    case ANDR_3: /* 4B */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Set register value */
      if ( REGISTER_BANK ) {
	cpu->register_6 &= (cpu->dbr & INDIRECT) ?
	  memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
						    cpu->rel_off ) )] :
	  memory[MEMORY( RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )];
      } else {
	cpu->register_3 &= (cpu->dbr & INDIRECT) ?
	  memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
						    cpu->rel_off ) )] :
	  memory[MEMORY( RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )];
      }

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( REGISTER_BANK ? cpu->register_6 : cpu->register_3 );

      break;


    case ANDA_0: /* 4C */

      /* Get high order address byte into holding register and low order address
	 byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];
      cpu->indexing = cpu->hr & INDEXING;

      if ( cpu->indexing ) {

	/* Increment/decrement index register. */
	if ( cpu->indexing != SIMPLE_INDEXING ) {
	  (cpu->indexing == INCREMENT) ? ++cpu->register_0 : --cpu->register_0;
	}

	if ( cpu->hr & INDIRECT ) {
	  cpu->register_0 &=
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT( cpu->register_0,
							    cpu->hr,
							    cpu->dbr) )];
	} else {
	  cpu->register_0 &=
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDEX( cpu->register_0, cpu->hr,
						   cpu->dbr ) )];
	}

      } else {
	cpu->register_0 &= ( cpu->hr & INDIRECT ) ?
	  memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )] :
	  memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )];
      }

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->register_0 );

      break;


    case ANDA_1: /* 4D */

      /* Get high order address byte into holding register and low order address
	 byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];
      cpu->indexing = cpu->hr & INDEXING;

      if ( cpu->indexing ) {

	/* Increment/decrement index register. */
	if ( cpu->indexing != SIMPLE_INDEXING ) {
	  (cpu->indexing == INCREMENT) ?
	    ( (REGISTER_BANK) ? ++cpu->register_4 : ++cpu->register_1 ) :
	    ( (REGISTER_BANK) ? --cpu->register_4 : --cpu->register_1 );
	}

	if ( cpu->hr & INDIRECT ) {
	  cpu->register_0 &=
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT(
		        ( REGISTER_BANK ? cpu->register_4 : cpu->register_1 ),
							    cpu->hr,
							    cpu->dbr) )];
	} else {
	  cpu->register_0 &=
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDEX(
	       ( REGISTER_BANK ? cpu->register_4 : cpu->register_1 ),
						   cpu->hr, cpu->dbr ) )];
	}

	/* Set CC. */
	CLEAR_CC;
	cpu->psl |= CC_REG( cpu->register_0 );

      } else {

	if ( REGISTER_BANK ) {
	  cpu->register_4 &= ( cpu->hr & INDIRECT ) ?
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )] :
	    memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )];
	} else {
	  cpu->register_1 &= ( cpu->hr & INDIRECT ) ?
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )] :
	    memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )];
	}

	/* Set CC. */
	CLEAR_CC;
	cpu->psl |= CC_REG( REGISTER_BANK ? cpu->register_4 : cpu->register_1 );
      }

      break;


    case ANDA_2: /* 4E */

      /* Get high order address byte into holding register and low order address
	 byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];
      cpu->indexing = cpu->hr & INDEXING;

      if ( cpu->indexing ) {

	/* Increment/decrement index register. */
	if ( cpu->indexing != SIMPLE_INDEXING ) {
	  (cpu->indexing == INCREMENT) ?
	    ( (REGISTER_BANK) ? ++cpu->register_5 : ++cpu->register_2 ) :
	    ( (REGISTER_BANK) ? --cpu->register_5 : --cpu->register_2 );
	}

	if ( cpu->hr & INDIRECT ) {
	  cpu->register_0 &=
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT(
		        ( REGISTER_BANK ? cpu->register_5 : cpu->register_2 ),
							    cpu->hr,
							    cpu->dbr) )];
	} else {
	  cpu->register_0 &=
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDEX(
	       ( REGISTER_BANK ? cpu->register_5 : cpu->register_2 ),
						   cpu->hr, cpu->dbr ) )];
	}

	/* Set CC. */
	CLEAR_CC;
	cpu->psl |= CC_REG( cpu->register_0 );

      } else {

	if ( REGISTER_BANK ) {
	  cpu->register_4 &= ( cpu->hr & INDIRECT ) ?
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )] :
	    memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )];
	} else {
	  cpu->register_1 &= ( cpu->hr & INDIRECT ) ?
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )] :
	    memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )];
	}

	/* Set CC. */
	CLEAR_CC;
	cpu->psl |= CC_REG( REGISTER_BANK ? cpu->register_5 : cpu->register_2 );
      }

      break;


    case ANDA_3: /* 4F */

      /* Get high order address byte into holding register and low order address
	 byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];
      cpu->indexing = cpu->hr & INDEXING;

      if ( cpu->indexing ) {

	/* Increment/decrement index register. */
	if ( cpu->indexing != SIMPLE_INDEXING ) {
	  (cpu->indexing == INCREMENT) ?
	    ( (REGISTER_BANK) ? ++cpu->register_6 : ++cpu->register_3 ) :
	    ( (REGISTER_BANK) ? --cpu->register_6 : --cpu->register_3 );
	}

	if ( cpu->hr & INDIRECT ) {
	  cpu->register_0 &=
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT(
		        ( REGISTER_BANK ? cpu->register_6 : cpu->register_3 ),
							    cpu->hr,
							    cpu->dbr) )];
	} else {
	  cpu->register_0 &=
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDEX(
	       ( REGISTER_BANK ? cpu->register_6 : cpu->register_3 ),
						   cpu->hr, cpu->dbr ) )];
	}

	/* Set CC. */
	CLEAR_CC;
	cpu->psl |= CC_REG( cpu->register_0 );

      } else {

	if ( REGISTER_BANK ) {
	  cpu->register_4 &= ( cpu->hr & INDIRECT ) ?
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )] :
	    memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )];
	} else {
	  cpu->register_1 &= ( cpu->hr & INDIRECT ) ?
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )] :
	    memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )];
	}

	/* Set CC. */
	CLEAR_CC;
	cpu->psl |= CC_REG( REGISTER_BANK ? cpu->register_6 : cpu->register_3 );
      }

      break;


    case BRNR_0: /* 58 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( cpu->register_0 ) {
	cpu->rel_off = cpu->dbr & R_OFFSET;

	/* Indirect or direct addressing? */
	if ( cpu->dbr & INDIRECT ) {
	  /* Branch to specified address. */
	  cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
								   cpu->rel_off
								   ) ) );
	} else {
	  /* Branch to specified address. */
	  cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS( cpu->iar,
							  cpu->rel_off ) ) );
	}

      }

      /* No setting of CC required. */

      break;


    case BRNR_1: /* 59 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( (REGISTER_BANK ? cpu->register_4 : cpu->register_1) ) {
	cpu->rel_off = cpu->dbr & R_OFFSET;

	/* Indirect or direct addressing? */
	if ( cpu->dbr & INDIRECT ) {
	  /* Branch to specified address. */
	  cpu->iar =
	    MEMORY( BRANCH_TO( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
							  cpu->rel_off ) ) );
	} else {
	  /* Branch to specified address. */
	  cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS( cpu->iar,
							  cpu->rel_off ) ) );
	}

      }

      /* No setting of CC required. */

      break;


    case BRNR_2: /* 5A */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( (REGISTER_BANK ? cpu->register_5 : cpu->register_2) ) {
	cpu->rel_off = cpu->dbr & R_OFFSET;

	/* Indirect or direct addressing? */
	if ( cpu->dbr & INDIRECT ) {
	  /* Branch to specified address. */
	  cpu->iar =
	    MEMORY( BRANCH_TO( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
							  cpu->rel_off ) ) );
	} else {
	  /* Branch to specified address. */
	  cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS( cpu->iar,
							  cpu->rel_off ) ) );
	}

      }

      /* No setting of CC required. */

      break;


    case BRNR_3: /* 5B */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( (REGISTER_BANK ? cpu->register_6 : cpu->register_3) ) {
	cpu->rel_off = cpu->dbr & R_OFFSET;

	/* Indirect or direct addressing? */
	if ( cpu->dbr & INDIRECT ) {
	  /* Branch to specified address. */
	  cpu->iar =
	    MEMORY( BRANCH_TO( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
							  cpu->rel_off ) ) );
	} else {
	  /* Branch to specified address. */
	  cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS( cpu->iar,
							  cpu->rel_off ) ) );
	}

      }

      /* No setting of CC required. */

      break;


    case BRNA_0: /* 5C */

      /* Get high order address byte into holding register and low order address
	 byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( cpu->register_0 ) {
	cpu->iar = (cpu->hr & INDIRECT) ?
	  MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) ) :
	  MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) );
      }

      /* No setting of CC required. */

      break;


    case BRNA_1: /* 5D */

      /* Get high order address byte into holding register and low order address
	 byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( (REGISTER_BANK ? cpu->register_4 : cpu->register_1) ) {
	cpu->iar = (cpu->hr & INDIRECT) ?
	  MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) ) :
	  MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) );
      }

      /* No setting of CC required. */

      break;


    case BRNA_2: /* 5E */

      /* Get high order address byte into holding register and low order address
	 byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( (REGISTER_BANK ? cpu->register_5 : cpu->register_2) ) {
	cpu->iar = (cpu->hr & INDIRECT) ?
	  MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) ) :
	  MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) );
      }

      /* No setting of CC required. */

      break;


    case BRNA_3: /* 5F */

      /* Get high order address byte into holding register and low order address
	 byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( (REGISTER_BANK ? cpu->register_6 : cpu->register_3) ) {
	cpu->iar = (cpu->hr & INDIRECT) ?
	  MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) ) :
	  MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) );
      }

      /* No setting of CC required. */

      break;


    case IORZ_0: /* 60 */

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

      /* Set register value. */
      cpu->register_0 |= ( REGISTER_BANK ? cpu->register_4 : cpu->register_1 );

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->register_0 );

      break;


    case IORZ_2: /* 62 */

      /* Set register value. */
      cpu->register_0 |= ( REGISTER_BANK ? cpu->register_5 : cpu->register_2 );

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->register_0 );

      break;


    case IORZ_3: /* 63 */

      /* Set register value. */
      cpu->register_0 |= ( REGISTER_BANK ? cpu->register_6 : cpu->register_3 );

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->register_0 );

      break;


    case IORI_0: /* 64 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* Set register value. */
      cpu->register_0 |= cpu->dbr;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->register_0 );

      break;


    case IORI_1: /* 65 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* Set register value. */
      if ( REGISTER_BANK )
	cpu->register_4 |= cpu->dbr;
      else
	cpu->register_1 |= cpu->dbr;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( REGISTER_BANK ? cpu->register_4 : cpu->register_1 );

      break;


    case IORI_2: /* 66 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* Set register value. */
      if ( REGISTER_BANK )
	cpu->register_5 |= cpu->dbr;
      else
	cpu->register_2 |= cpu->dbr;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( REGISTER_BANK ? cpu->register_5 : cpu->register_2 );

      break;


    case IORI_3: /* 67 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* Set register value. */
      if ( REGISTER_BANK )
	cpu->register_6 |= cpu->dbr;
      else
	cpu->register_3 |= cpu->dbr;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( REGISTER_BANK ? cpu->register_6 : cpu->register_3 );

      break;


    case IORR_0: /* 68 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Set register value */
      cpu->register_0 |= (cpu->dbr & INDIRECT) ?
	memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar, cpu->rel_off ) )] :
	memory[MEMORY( RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )];

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->register_0 );

      break;


    case IORR_1: /* 69 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Set register value */
      if ( REGISTER_BANK ) {
	cpu->register_4 |= (cpu->dbr & INDIRECT) ?
	  memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
						    cpu->rel_off ) )] :
	  memory[MEMORY( RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )];
      } else {
	cpu->register_1 |= (cpu->dbr & INDIRECT) ?
	  memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
						    cpu->rel_off ) )] :
	  memory[MEMORY( RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )];
      }

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( REGISTER_BANK ? cpu->register_4 : cpu->register_1 );

      break;


    case IORR_2: /* 6A */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Set register value */
      if ( REGISTER_BANK ) {
	cpu->register_5 |= (cpu->dbr & INDIRECT) ?
	  memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
						    cpu->rel_off ) )] :
	  memory[MEMORY( RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )];
      } else {
	cpu->register_2 |= (cpu->dbr & INDIRECT) ?
	  memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
						    cpu->rel_off ) )] :
	  memory[MEMORY( RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )];
      }

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( REGISTER_BANK ? cpu->register_5 : cpu->register_2 );

      break;


    case IORR_3: /* 6B */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Set register value */
      if ( REGISTER_BANK ) {
	cpu->register_6 |= (cpu->dbr & INDIRECT) ?
	  memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
						    cpu->rel_off ) )] :
	  memory[MEMORY( RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )];
      } else {
	cpu->register_3 |= (cpu->dbr & INDIRECT) ?
	  memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
						    cpu->rel_off ) )] :
	  memory[MEMORY( RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )];
      }

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( REGISTER_BANK ? cpu->register_6 : cpu->register_3 );

      break;


    case IORA_0: /* 6C */

      /* Get high order address byte into holding register and low order address
	 byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];
      cpu->indexing = cpu->hr & INDEXING;

      if ( cpu->indexing ) {

	/* Increment/decrement index register. */
	if ( cpu->indexing != SIMPLE_INDEXING ) {
	  (cpu->indexing == INCREMENT) ? ++cpu->register_0 : --cpu->register_0;
	}

	if ( cpu->hr & INDIRECT ) {
	  cpu->register_0 |=
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT( cpu->register_0,
							    cpu->hr,
							    cpu->dbr) )];
	} else {
	  cpu->register_0 |=
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDEX( cpu->register_0, cpu->hr,
						   cpu->dbr ) )];
	}

      } else {
	cpu->register_0 |= ( cpu->hr & INDIRECT ) ?
	  memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )] :
	  memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )];
      }

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->register_0 );

      break;


    case IORA_1: /* 6D */

      /* Get high order address byte into holding register and low order address
	 byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];
      cpu->indexing = cpu->hr & INDEXING;

      if ( cpu->indexing ) {

	/* Increment/decrement index register. */
	if ( cpu->indexing != SIMPLE_INDEXING ) {
	  (cpu->indexing == INCREMENT) ?
	    ( (REGISTER_BANK) ? ++cpu->register_4 : ++cpu->register_1 ) :
	    ( (REGISTER_BANK) ? --cpu->register_4 : --cpu->register_1 );
	}

	if ( cpu->hr & INDIRECT ) {
	  cpu->register_0 |=
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT(
		        ( REGISTER_BANK ? cpu->register_4 : cpu->register_1 ),
							    cpu->hr,
							    cpu->dbr) )];
	} else {
	  cpu->register_0 |=
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDEX(
	       ( REGISTER_BANK ? cpu->register_4 : cpu->register_1 ),
						   cpu->hr, cpu->dbr ) )];
	}

	/* Set CC. */
	CLEAR_CC;
	cpu->psl |= CC_REG( cpu->register_0 );

      } else {

	if ( REGISTER_BANK ) {
	  cpu->register_4 |= ( cpu->hr & INDIRECT ) ?
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )] :
	    memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )];
	} else {
	  cpu->register_1 |= ( cpu->hr & INDIRECT ) ?
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )] :
	    memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )];
	}

	/* Set CC. */
	CLEAR_CC;
	cpu->psl |= CC_REG( REGISTER_BANK ? cpu->register_4 : cpu->register_1 );
      }

      break;


    case IORA_2: /* 6E */

      /* Get high order address byte into holding register and low order address
	 byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];
      cpu->indexing = cpu->hr & INDEXING;

      if ( cpu->indexing ) {

	/* Increment/decrement index register. */
	if ( cpu->indexing != SIMPLE_INDEXING ) {
	  (cpu->indexing == INCREMENT) ?
	    ( (REGISTER_BANK) ? ++cpu->register_5 : ++cpu->register_2 ) :
	    ( (REGISTER_BANK) ? --cpu->register_5 : --cpu->register_2 );
	}

	if ( cpu->hr & INDIRECT ) {
	  cpu->register_0 |=
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT(
		        ( REGISTER_BANK ? cpu->register_5 : cpu->register_2 ),
							    cpu->hr,
							    cpu->dbr) )];
	} else {
	  cpu->register_0 |=
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDEX(
	       ( REGISTER_BANK ? cpu->register_5 : cpu->register_2 ),
						   cpu->hr, cpu->dbr ) )];
	}

	/* Set CC. */
	CLEAR_CC;
	cpu->psl |= CC_REG( cpu->register_0 );

      } else {

	if ( REGISTER_BANK ) {
	  cpu->register_4 |= ( cpu->hr & INDIRECT ) ?
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )] :
	    memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )];
	} else {
	  cpu->register_1 |= ( cpu->hr & INDIRECT ) ?
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )] :
	    memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )];
	}

	/* Set CC. */
	CLEAR_CC;
	cpu->psl |= CC_REG( REGISTER_BANK ? cpu->register_5 : cpu->register_2 );
      }

      break;


    case IORA_3: /* 6F */

      /* Get high order address byte into holding register and low order address
	 byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];
      cpu->indexing = cpu->hr & INDEXING;

      if ( cpu->indexing ) {

	/* Increment/decrement index register. */
	if ( cpu->indexing != SIMPLE_INDEXING ) {
	  (cpu->indexing == INCREMENT) ?
	    ( (REGISTER_BANK) ? ++cpu->register_6 : ++cpu->register_3 ) :
	    ( (REGISTER_BANK) ? --cpu->register_6 : --cpu->register_3 );
	}

	if ( cpu->hr & INDIRECT ) {
	  cpu->register_0 |=
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT(
		        ( REGISTER_BANK ? cpu->register_6 : cpu->register_3 ),
							    cpu->hr,
							    cpu->dbr) )];
	} else {
	  cpu->register_0 |=
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDEX(
	       ( REGISTER_BANK ? cpu->register_6 : cpu->register_3 ),
						   cpu->hr, cpu->dbr ) )];
	}

	/* Set CC. */
	CLEAR_CC;
	cpu->psl |= CC_REG( cpu->register_0 );

      } else {

	if ( REGISTER_BANK ) {
	  cpu->register_4 |= ( cpu->hr & INDIRECT ) ?
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )] :
	    memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )];
	} else {
	  cpu->register_1 |= ( cpu->hr & INDIRECT ) ?
	    memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )] :
	    memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )];
	}

	/* Set CC. */
	CLEAR_CC;
	cpu->psl |= CC_REG( REGISTER_BANK ? cpu->register_6 : cpu->register_3 );
      }

      break;


    case CPSU: /* 74 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* Data byte is used to clear selective (logically NAND) selective
	 bits in the PSU. All other bits should be left untouched. */
      cpu->psu &= ~cpu->dbr;

      /* No setting of CC required. */

      break;


    case CPSL: /* 75 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* Data byte is used to clear selective (logically NAND) selective bits in
	 the PSL. All other bits should be left untouched. */
      cpu->psl &= ~cpu->dbr;

      /* No setting of CC required. */

      break;


    case PPSU: /* 76 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /*
	Data byte is used to turn on (logically OR) selective bits in the
	PSU. All other bits should be left untouched.

	It is not really clear from the instruction manual (p. 70) if bits 3 and
	4 of the PSU, which are normally unused, can be set to one with this
	instruction. For the time being, assume that this is not the case and
	mask them out via the PSU() macro.
      */
      cpu->psu |= PSU( cpu->dbr );

      /* No setting of CC required. */

      break;


    case PPSL: /* 77 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* Data byte is used to turn on (logically OR) selective bits in the
	 PSL. All other bits should be left untouched. */
      cpu->psl |= cpu->dbr;

      /* No setting of CC required. */

      break;


    case LPSU: /* 92 */

      /*
	From the Instruction Manual, p. 68:

	  "Bits #4 and #3 of the PSU are unassigned and will always be regarded
	  as containing zeroes."

        Thus, we have to mask the PSU with PSU_NU, which is 0b11100111.
       */
      cpu->psu = PSU( cpu->register_0 );

      break;


    case LPSL: /* 93 */

      cpu->psl = cpu->register_0;

      break;


    case BCFR_0: /* 98 */
    case BCFR_1: /* 99 */
    case BCFR_2: /* 9A */
      /* Extract CC code from Opcode and scale it to PSL format for
	 comparison. */
      cpu->cc = ( cpu->ir & 0x3 ) << 6;

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( cpu->cc != C_CODE ) {
	cpu->rel_off = cpu->dbr & R_OFFSET;

	/* Indirect or direct addressing? */
	if ( cpu->dbr & INDIRECT ) {
	  /* Branch to specified address. */
	  cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
								   cpu->rel_off
								   ) ) );
	} else {
	  /* Branch to specified address. */
	  cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS( cpu->iar,
							  cpu->rel_off ) ) );
	}

      }

      /* No setting of CC required. */

      break;


    case ZBRR: /* 9B */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      cpu->iar = (cpu->dbr & INDIRECT) ?
	MEMORY( BRANCH_TO( ZERO_BRANCH_INDIRECT( cpu->rel_off ) ) ):
	BRANCH_TO( ZERO_BRANCH( cpu->rel_off ) );

      /* No setting of CC required. */

      break;


    case BCFA_0: /* 9C */
    case BCFA_1: /* 9D */
    case BCFA_2: /* 9E */
      /* Extract CC code from Opcode and scale it to PSL format for
	 comparison. */
      cpu->cc = ( cpu->ir & 0x3 ) << 6;

      /* Get high order address byte into holding register and low order address
	 byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( cpu->cc != C_CODE ) {
	cpu->iar = (cpu->hr & INDIRECT) ?
	  MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) ) :
	  MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) );
      }

      /* No setting of CC required. */

      break;


    case BXA: /* 9F */

      /* Get high order address byte into holding register and low order address
	 byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /*
	Implicit index register is #3/#6.

	The instruction set manual is not clear about index control in BXA/BSXA
	(cf. p. 49), however, it feels reasonable to assume simple indexing
	(i.e. no auto increment/decrement).
      */
      cpu->iar = MEMORY( ( (cpu->hr & INDIRECT) ?
			   BRANCH_TO_ABSOLUTE_ADDRESS_INDIRECT( cpu->hr,
								cpu->dbr ) :
			   BRANCH_TO_ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )
			 + (REGISTER_BANK ? cpu->register_6 : cpu->register_3)
			 );

      /* No setting of CC required. */

      break;


    case TPSU: /* B4 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /*
	Data byte is used to check if selective bits in the PSU are set or not.
	CC Code is set afterwards to indicate if all checks were positive, then
	CC=0 else CC=2.

	It is not really clear from the instruction manual (p. 72) if bits 3 and
	4 are really tested with this instruction or not even if they are
	otherwise unused. For the time being, mask them out of the test byte
	with the PSU() macro.

	It is also not clear what the result of CC will be, if tested with 0x00
	and the current contents of the PSU are 0x00 as well. For now, We assume
	that this would mean a positive test and therefore CC gets cleared in
	this case, too.
      */
      cpu->psl |= ( cpu->psu != PSU( cpu->dbr ) ) ?
	(CLEAR_CC | CC_LESS) : CLEAR_CC;

      break;


    case TPSL: /* B5 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /*
	Data byte is used to check if selective bits in the PSL are set or not.
	CC Code is set afterwards to indicate if all checks were positive, then
	CC=0 else CC=2.

	It is also not clear what the result of CC will be, if tested with 0x00
	and the current contents of the PSL are 0x00 as well. For now, We assume
	that this would mean a positive test and therefore CC gets cleared in
	this case, too.
      */
      cpu->psl |= (cpu->psl != cpu->dbr) ? (CLEAR_CC | CC_LESS) : CLEAR_CC;

      break;


    case NOP: /* C0 */

      break;


    case STRZ_1: /* C1 */

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

      /* Set register value. */
      if ( REGISTER_BANK )
	cpu->register_6 = cpu->register_0;
      else
	cpu->register_3 = cpu->register_0;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( REGISTER_BANK ? cpu->register_6 : cpu->register_3 );

      break;


      /* Note: There are no 'STRI' operations. Consequently, opcodes C4 to C7 do
	 not exist. */


    case STRR_0: /* C8 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Store contents of R0 in memory address calculated from relative
	 offset. */
      memory[(cpu->dbr & INDIRECT) ?
	     MEMORY(RELATIVE_ADDRESS_INDIRECT( cpu->iar, cpu->rel_off ) ) :
	     MEMORY(RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )]
	= cpu->register_0;

      /* No setting of CC required. */

      break;


    case STRR_1: /* C9 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Store contents of R1/4 in memory address calculated from relative
	 offset. */
      memory[(cpu->dbr & INDIRECT) ?
	     MEMORY(RELATIVE_ADDRESS_INDIRECT( cpu->iar, cpu->rel_off ) ) :
	     MEMORY(RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )]
	= (REGISTER_BANK) ? cpu->register_4 : cpu->register_1;

      /* No setting of CC required. */

      break;


    case STRR_2: /* CA */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Store contents of R2/5 in memory address calculated from relative
	 offset. */
      memory[(cpu->dbr & INDIRECT) ?
	     MEMORY(RELATIVE_ADDRESS_INDIRECT( cpu->iar, cpu->rel_off ) ) :
	     MEMORY(RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )]
	= (REGISTER_BANK) ? cpu->register_5 : cpu->register_2;

      /* No setting of CC required. */

      break;


    case STRR_3: /* CB */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Store contents of R3/6 in memory address calculated from relative
	 offset. */
      memory[(cpu->dbr & INDIRECT) ?
	     MEMORY(RELATIVE_ADDRESS_INDIRECT( cpu->iar, cpu->rel_off ) ) :
	     MEMORY(RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )]
	= (REGISTER_BANK) ? cpu->register_6 : cpu->register_3;

      /* No setting of CC required. */

      break;


    case STRA_0: /* CC */

      /* Get high order address byte into holding register and low order address
	 byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];
      cpu->indexing = cpu->hr & INDEXING;

      if ( cpu->indexing ) {

	/* Increment/decrement index register. */
	if ( cpu->indexing != SIMPLE_INDEXING ) {
	  (cpu->indexing == INCREMENT) ? ++cpu->register_0 : --cpu->register_0;
	}

	memory[(cpu->hr & INDIRECT) ?
	       MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT( cpu->register_0,
							cpu->hr, cpu->dbr) ) :
	       MEMORY( ABSOLUTE_ADDRESS_INDEX( cpu->register_0, cpu->hr,
					       cpu->dbr ) )]
	  = cpu->register_0;

      } else {
	memory[(cpu->hr & INDIRECT) ?
	       MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) ) :
	       MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )]
	  = cpu->register_0;
      }

      /* No setting of CC required. */

      break;


    case STRA_1: /* CD */

      /* Get high order address byte into holding register and low order address
	 byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];
      cpu->indexing = cpu->hr & INDEXING;

      if ( cpu->indexing ) {

	/* Increment/decrement index register. */
	if ( cpu->indexing != SIMPLE_INDEXING ) {
	  (cpu->indexing == INCREMENT) ?
	    ( (REGISTER_BANK) ? ++cpu->register_4 : ++cpu->register_1 ) :
	    ( (REGISTER_BANK) ? --cpu->register_4 : --cpu->register_1 );
	}

	/* Store contents of R0 into memory location specified by absolute
	   address + index in R1/4. */
	memory[(cpu->hr & INDIRECT) ?
	       MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT(
			  ((REGISTER_BANK) ? cpu->register_4 : cpu->register_1),
						        cpu->hr, cpu->dbr) ) :
	       MEMORY( ABSOLUTE_ADDRESS_INDEX(
			  ((REGISTER_BANK) ? cpu->register_4 : cpu->register_1),
                                               cpu->hr,cpu->dbr ) )]
	  = cpu->register_0;

      } else {
	/* Store contents of R1/4 into memory location specified by absolute
	   address. */
	memory[(cpu->hr & INDIRECT) ?
	       MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) ) :
	       MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )]
	  = (REGISTER_BANK) ? cpu->register_4 : cpu->register_1;
      }

      /* No setting of CC required. */

      break;


    case STRA_2: /* CE */

      /* Get high order address byte into holding register and low order address
	 byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];
      cpu->indexing = cpu->hr & INDEXING;

      if ( cpu->indexing ) {

	/* Increment/decrement index register. */
	if ( cpu->indexing != SIMPLE_INDEXING ) {
	  (cpu->indexing == INCREMENT) ?
	    ( (REGISTER_BANK) ? ++cpu->register_5 : ++cpu->register_2 ) :
	    ( (REGISTER_BANK) ? --cpu->register_5 : --cpu->register_2 );
	}

	/* Store contents of R0 into memory location specified by absolute
	   address + index in R2/5. */
	memory[(cpu->hr & INDIRECT) ?
	       MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT(
			  ((REGISTER_BANK) ? cpu->register_5 : cpu->register_2),
						        cpu->hr, cpu->dbr) ) :
	       MEMORY( ABSOLUTE_ADDRESS_INDEX(
			  ((REGISTER_BANK) ? cpu->register_5 : cpu->register_2),
                                               cpu->hr,cpu->dbr ) )]
	  = cpu->register_0;

      } else {
	/* Store contents of R2/5 into memory location specified by absolute
	   address. */
	memory[(cpu->hr & INDIRECT) ?
	       MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) ) :
	       MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )]
	  = (REGISTER_BANK) ? cpu->register_5 : cpu->register_2;
      }

      /* No setting of CC required. */

      break;


    case STRA_3: /* CF */

      /* Get high order address byte into holding register and low order address
	 byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];
      cpu->indexing = cpu->hr & INDEXING;

      if ( cpu->indexing ) {

	/* Increment/decrement index register. */
	if ( cpu->indexing != SIMPLE_INDEXING ) {
	  (cpu->indexing == INCREMENT) ?
	    ( (REGISTER_BANK) ? ++cpu->register_6 : ++cpu->register_3 ) :
	    ( (REGISTER_BANK) ? --cpu->register_6 : --cpu->register_3 );
	}

	/* Store contents of R0 into memory location specified by absolute
	   address + index in R3/6. */
	memory[(cpu->hr & INDIRECT) ?
	       MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT(
			  ((REGISTER_BANK) ? cpu->register_6 : cpu->register_3),
						        cpu->hr, cpu->dbr) ) :
	       MEMORY( ABSOLUTE_ADDRESS_INDEX(
			  ((REGISTER_BANK) ? cpu->register_6 : cpu->register_3),
                                               cpu->hr,cpu->dbr ) )]
	  = cpu->register_0;

      } else {
	/* Store contents of R3/6 into memory location specified by absolute
	   address. */
	memory[(cpu->hr & INDIRECT) ?
	       MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) ) :
	       MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )]
	  = (REGISTER_BANK) ? cpu->register_6 : cpu->register_3;
      }

      /* No setting of CC required. */

      break;


    case BIRR_0: /* D8 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( ++cpu->register_0 ) {
	cpu->rel_off = cpu->dbr & R_OFFSET;

	/* Indirect or direct addressing? */
	if ( cpu->dbr & INDIRECT ) {
	  /* Branch to specified address. */
	  cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
								   cpu->rel_off
								   ) ) );
	} else {
	  /* Branch to specified address. */
	  cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS( cpu->iar,
							  cpu->rel_off ) ) );
	}

      }

      /* No setting of CC required. */

      break;


    case BIRR_1: /* D9 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( (REGISTER_BANK ? ++cpu->register_4 : ++cpu->register_1) ) {
	cpu->rel_off = cpu->dbr & R_OFFSET;

	/* Indirect or direct addressing? */
	if ( cpu->dbr & INDIRECT ) {
	  /* Branch to specified address. */
	  cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
								   cpu->rel_off
								   ) ) );
	} else {
	  /* Branch to specified address. */
	  cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS( cpu->iar,
							  cpu->rel_off ) ) );
	}

      }

      /* No setting of CC required. */

      break;


    case BIRR_2: /* DA */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( (REGISTER_BANK ? ++cpu->register_5 : ++cpu->register_2) ) {
	cpu->rel_off = cpu->dbr & R_OFFSET;

	/* Indirect or direct addressing? */
	if ( cpu->dbr & INDIRECT ) {
	  /* Branch to specified address. */
	  cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
								   cpu->rel_off
								   ) ) );
	} else {
	  /* Branch to specified address. */
	  cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS( cpu->iar,
							  cpu->rel_off ) ) );
	}

      }

      /* No setting of CC required. */

      break;


    case BIRR_3: /* DB */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( (REGISTER_BANK ? ++cpu->register_6 : ++cpu->register_3) ) {
	cpu->rel_off = cpu->dbr & R_OFFSET;

	/* Indirect or direct addressing? */
	if ( cpu->dbr & INDIRECT ) {
	  /* Branch to specified address. */
	  cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
								   cpu->rel_off
								   ) ) );
	} else {
	  /* Branch to specified address. */
	  cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS( cpu->iar,
							  cpu->rel_off ) ) );
	}

      }

      /* No setting of CC required. */

      break;


    case BIRA_0: /* DC */

      /* Get high order address byte into holding register and low order address
	 byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( ++cpu->register_0 ) {
	cpu->iar = (cpu->hr & INDIRECT) ?
	  MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) ) :
	  MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) );
      }

      /* No setting of CC required. */

      break;


    case BIRA_1: /* DD */

      /* Get high order address byte into holding register and low order address
	 byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( (REGISTER_BANK ? ++cpu->register_4 : ++cpu->register_1) ) {
	cpu->iar = (cpu->hr & INDIRECT) ?
	  MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) ) :
	  MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) );
      }

      /* No setting of CC required. */

      break;


    case BIRA_2: /* DE */

      /* Get high order address byte into holding register and low order address
	 byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( (REGISTER_BANK ? ++cpu->register_5 : ++cpu->register_2) ) {
	cpu->iar = (cpu->hr & INDIRECT) ?
	  MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) ) :
	  MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) );
      }

      /* No setting of CC required. */

      break;


    case BIRA_3: /* DF */

      /* Get high order address byte into holding register and low order address
	 byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( (REGISTER_BANK ? ++cpu->register_6 : ++cpu->register_3) ) {
	cpu->iar = (cpu->hr & INDIRECT) ?
	  MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) ) :
	  MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) );
      }

      /* No setting of CC required. */

      break;


    case COMZ_0: /* E0 */

      /* Set CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_COM( cpu->register_0, cpu->register_0 );

      break;


    case COMZ_1: /* E1 */

      /* Set CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_COM( cpu->register_0,
			  REGISTER_BANK ? cpu->register_4 : cpu->register_1 );

      break;


    case COMZ_2: /* E2 */

      /* Set CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_COM( cpu->register_0,
			  REGISTER_BANK ? cpu->register_5 : cpu->register_2 );

      break;


    case COMZ_3: /* E3 */

      /* Set CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_COM( cpu->register_0,
			  REGISTER_BANK ? cpu->register_6 : cpu->register_3 );

      break;


    case COMI_0: /* E4 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* SET CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_COM( cpu->register_0, cpu->dbr );

      break;


    case COMI_1: /* E5 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* SET CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_COM( REGISTER_BANK ? cpu->register_4 : cpu->register_1,
			  cpu->dbr );

      break;


    case COMI_2: /* E6 */

      /* Get next byte from memory into Data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* SET CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_COM( REGISTER_BANK ? cpu->register_5 : cpu->register_2,
			  cpu->dbr );

      break;


    case COMI_3: /* E7 */

      /* Get next byte from memory into Data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* SET CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_COM( REGISTER_BANK ? cpu->register_6 : cpu->register_3,
			  cpu->dbr );

      break;


    case COMR_0: /* E8 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];
      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* SET CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_COM( cpu->register_0, (cpu->dbr & INDIRECT) ?
			  memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
								    cpu->rel_off
								    ) )] :
			  memory[MEMORY( RELATIVE_ADDRESS( cpu->iar,
							   cpu->rel_off ) )]);

      break;


    case COMR_1: /* E9 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];
      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* SET CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_COM( REGISTER_BANK ? cpu->register_4 : cpu->register_1,
			  (cpu->dbr & INDIRECT) ?
			  memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
								    cpu->rel_off
								    ) )] :
			  memory[MEMORY( RELATIVE_ADDRESS( cpu->iar,
							   cpu->rel_off ) )]);

      break;


    case COMR_2: /* EA */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];
      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* SET CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_COM( REGISTER_BANK ? cpu->register_5 : cpu->register_2,
			  (cpu->dbr & INDIRECT) ?
			  memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
								    cpu->rel_off
								    ) )] :
			  memory[MEMORY( RELATIVE_ADDRESS( cpu->iar,
							   cpu->rel_off ) )]);

      break;


    case COMR_3: /* EB */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];
      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* SET CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_COM( REGISTER_BANK ? cpu->register_6 : cpu->register_3,
			  (cpu->dbr & INDIRECT) ?
			  memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
								    cpu->rel_off
								    ) )] :
			  memory[MEMORY( RELATIVE_ADDRESS( cpu->iar,
							   cpu->rel_off ) )]);

      break;


    case COMA_0: /* EC */

      /* Get high order address byte into holding register and low order address
	 byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];
      cpu->indexing = cpu->hr & INDEXING;

      /* Set CC flags. */
      CLEAR_CC;

      if ( cpu->indexing ) {

	/* Increment/decrement index register. */
	if ( cpu->indexing != SIMPLE_INDEXING ) {
	  (cpu->indexing == INCREMENT) ? ++cpu->register_0 : --cpu->register_0;
	}

	cpu->psl |= CC_COM( cpu->register_0, (cpu->hr & INDIRECT) ?
	  memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT( cpu->register_0,
							  cpu->hr,
							  cpu->dbr ) )] :
	  memory[MEMORY( ABSOLUTE_ADDRESS_INDEX( cpu->register_0, cpu->hr,
						 cpu->dbr ) )] );
      } else {
	cpu->psl |= CC_COM( cpu->register_0, ( cpu->hr & INDIRECT ) ?
	  memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )] :
	  memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )] );
      }

      break;


    case COMA_1: /* ED */

      /* Get high order address byte into holding register and low order address
	 byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];
      cpu->indexing = cpu->hr & INDEXING;

      /* Set CC flags. */
      CLEAR_CC;

      if ( cpu->indexing ) {

	/* Increment/decrement index register. */
	if ( cpu->indexing != SIMPLE_INDEXING ) {
	  (cpu->indexing == INCREMENT) ?
	    ( (REGISTER_BANK) ? ++cpu->register_4 : ++cpu->register_1 ) :
	    ( (REGISTER_BANK) ? --cpu->register_4 : --cpu->register_1 );
	}

	cpu->psl |= CC_COM( cpu->register_0, (cpu->hr & INDIRECT) ?
	  memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT(
	    (REGISTER_BANK ? cpu->register_4 : cpu->register_1 ),
	    cpu->hr, cpu->dbr ) )] :
	  memory[MEMORY( ABSOLUTE_ADDRESS_INDEX(
	    (REGISTER_BANK ? cpu->register_4 : cpu->register_1 ),
	    cpu->hr, cpu->dbr ) )] );

      } else {
	cpu->psl |= CC_COM( REGISTER_BANK ? cpu->register_4 : cpu->register_1,
			    (cpu->hr & INDIRECT) ?
			    memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr,
								      cpu->dbr )
					   )] :
			    memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr )
					   )] );
      }

      break;


    case COMA_2: /* EE */

      /* Get high order address byte into holding register and low order address
	 byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];
      cpu->indexing = cpu->hr & INDEXING;

      /* Set CC flags. */
      CLEAR_CC;

      if ( cpu->indexing ) {

	/* Increment/decrement index register. */
	if ( cpu->indexing != SIMPLE_INDEXING ) {
	  (cpu->indexing == INCREMENT) ?
	    ( (REGISTER_BANK) ? ++cpu->register_5 : ++cpu->register_2 ) :
	    ( (REGISTER_BANK) ? --cpu->register_5 : --cpu->register_2 );
	}

	cpu->psl |= CC_COM( cpu->register_0, (cpu->hr & INDIRECT) ?
	  memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT(
	    (REGISTER_BANK ? cpu->register_5 : cpu->register_2 ),
	    cpu->hr, cpu->dbr ) )] :
	  memory[MEMORY( ABSOLUTE_ADDRESS_INDEX(
	    (REGISTER_BANK ? cpu->register_5 : cpu->register_2 ),
	    cpu->hr, cpu->dbr ) )] );

      } else {
	cpu->psl |= CC_COM( REGISTER_BANK ? cpu->register_5 : cpu->register_2,
			    (cpu->hr & INDIRECT) ?
			    memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr,
								      cpu->dbr )
					   )] :
			    memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr )
					   )] );
      }

      break;


    case COMA_3: /* EF */

      /* Get high order address byte into holding register and low order address
	 byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];
      cpu->indexing = cpu->hr & INDEXING;

      /* Set CC flags. */
      CLEAR_CC;

      if ( cpu->indexing ) {

	/* Increment/decrement index register. */
	if ( cpu->indexing != SIMPLE_INDEXING ) {
	  (cpu->indexing == INCREMENT) ?
	    ( (REGISTER_BANK) ? ++cpu->register_6 : ++cpu->register_3 ) :
	    ( (REGISTER_BANK) ? --cpu->register_6 : --cpu->register_3 );
	}

	cpu->psl |= CC_COM( cpu->register_0, (cpu->hr & INDIRECT) ?
	  memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT(
	    (REGISTER_BANK ? cpu->register_6 : cpu->register_3 ),
	    cpu->hr, cpu->dbr ) )] :
	  memory[MEMORY( ABSOLUTE_ADDRESS_INDEX(
	    (REGISTER_BANK ? cpu->register_6 : cpu->register_3 ),
	    cpu->hr, cpu->dbr ) )] );

      } else {
	cpu->psl |= CC_COM( REGISTER_BANK ? cpu->register_6 : cpu->register_3,
			    (cpu->hr & INDIRECT) ?
			    memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr,
								      cpu->dbr )
					   )] :
			    memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr )
					   )] );
      }

      break;


    case BDRR_0: /* F8 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( --cpu->register_0 ) {
	cpu->rel_off = cpu->dbr & R_OFFSET;

	/* Indirect or direct addressing? */
	if ( cpu->dbr & INDIRECT ) {
	  /* Branch to specified address. */
	  cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
								   cpu->rel_off
								   ) ) );
	} else {
	  /* Branch to specified address. */
	  cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS( cpu->iar,
							  cpu->rel_off ) ) );
	}

      }

      /* No setting of CC required. */

      break;


    case BDRR_1: /* F9 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( (REGISTER_BANK ? --cpu->register_4 : --cpu->register_1) ) {
	cpu->rel_off = cpu->dbr & R_OFFSET;

	/* Indirect or direct addressing? */
	if ( cpu->dbr & INDIRECT ) {
	  /* Branch to specified address. */
	  cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
								   cpu->rel_off
								   ) ) );
	} else {
	  /* Branch to specified address. */
	  cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS( cpu->iar,
							  cpu->rel_off ) ) );
	}

      }

      /* No setting of CC required. */

      break;


    case BDRR_2: /* FA */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( (REGISTER_BANK ? --cpu->register_5 : --cpu->register_2) ) {
	cpu->rel_off = cpu->dbr & R_OFFSET;

	/* Indirect or direct addressing? */
	if ( cpu->dbr & INDIRECT ) {
	  /* Branch to specified address. */
	  cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
								   cpu->rel_off
								   ) ) );
	} else {
	  /* Branch to specified address. */
	  cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS( cpu->iar,
							  cpu->rel_off ) ) );
	}

      }

      /* No setting of CC required. */

      break;


    case BDRR_3: /* FB */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( (REGISTER_BANK ? --cpu->register_6 : --cpu->register_3) ) {
	cpu->rel_off = cpu->dbr & R_OFFSET;

	/* Indirect or direct addressing? */
	if ( cpu->dbr & INDIRECT ) {
	  /* Branch to specified address. */
	  cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
								   cpu->rel_off
								   ) ) );
	} else {
	  /* Branch to specified address. */
	  cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS( cpu->iar,
							  cpu->rel_off ) ) );
	}

      }

      /* No setting of CC required. */

      break;


    case BDRA_0: /* FC */

      /* Get high order address byte into holding register and low order address
	 byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( --cpu->register_0 ) {
	cpu->iar = (cpu->hr & INDIRECT) ?
	  MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) ) :
	  MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) );
      }

      break;


    case BDRA_1: /* FD */

      /* Get high order address byte into holding register and low order address
	 byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( (REGISTER_BANK ? --cpu->register_4 : --cpu->register_1) ) {
	cpu->iar = (cpu->hr & INDIRECT) ?
	  MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) ) :
	  MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) );
      }

      /* No setting of CC required. */

      break;


    case BDRA_2: /* FE */

      /* Get high order address byte into holding register and low order address
	 byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( (REGISTER_BANK ? --cpu->register_5 : --cpu->register_2) ) {
	cpu->iar = (cpu->hr & INDIRECT) ?
	  MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) ) :
	  MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) );
      }

      /* No setting of CC required. */

      break;


    case BDRA_3: /* FF */

      /* Get high order address byte into holding register and low order address
	 byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( (REGISTER_BANK ? --cpu->register_6 : --cpu->register_3) ) {
	cpu->iar = (cpu->hr & INDIRECT) ?
	  MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) ) :
	  MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) );
      }

      /* No setting of CC required. */

      break;


    default:

      cpu_error = 2;

    }

    ++cpu->iar;
  }

  return cpu_error;
}
