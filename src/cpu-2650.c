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

int cpu_loop( Cpu *cpu, char *memory )
{
  int cpu_error = 0;

  while ( !cpu_error ) {
    cpu->ir = memory[MEMORY( cpu->iar )];

    switch( cpu->ir ) {

    case LODZ_0: /* 00 */

      /* cpu_error = 1; */

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
      cpu->psl |= REGISTER_BANK ?
	CC_REG( cpu->register_4 ) : CC_REG( cpu->register_1 );

      break;


    case LODI_2: /* 06 */

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
      cpu->psl |= REGISTER_BANK ?
	CC_REG( cpu->register_4 ) : CC_REG( cpu->register_1 );

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
      cpu->psl |= REGISTER_BANK ?
	CC_REG( cpu->register_5 ) : CC_REG( cpu->register_2 );

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
      cpu->psl |= REGISTER_BANK ?
	CC_REG( cpu->register_6 ) : CC_REG( cpu->register_3 );

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
	  cpu->register_0 = (cpu->indexing == INCREMENT) ?
	    ++cpu->register_0 : --cpu->register_0;
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
	  if ( REGISTER_BANK ) {
	    cpu->register_4 = (cpu->indexing == INCREMENT) ?
	      ++cpu->register_4 : --cpu->register_4;
	  } else {
	    cpu->register_1 = (cpu->indexing == INCREMENT) ?
	      ++cpu->register_1 : --cpu->register_1;
	  }
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
	cpu->psl |= REGISTER_BANK ?
	  CC_REG( cpu->register_4 ) : CC_REG( cpu->register_1 );
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
	  if ( REGISTER_BANK ) {
	    cpu->register_5 = (cpu->indexing == INCREMENT) ?
	      ++cpu->register_5 : --cpu->register_5;
	  } else {
	    cpu->register_2 = (cpu->indexing == INCREMENT) ?
	      ++cpu->register_2 : --cpu->register_2;
	  }
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
	cpu->psl |= REGISTER_BANK ?
	  CC_REG( cpu->register_5 ) : CC_REG( cpu->register_2 );
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
	  if ( REGISTER_BANK ) {
	    cpu->register_6 = (cpu->indexing == INCREMENT) ?
	      ++cpu->register_6 : --cpu->register_6;
	  } else {
	    cpu->register_3 = (cpu->indexing == INCREMENT) ?
	      ++cpu->register_3 : --cpu->register_3;
	  }
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
	cpu->psl |= REGISTER_BANK ?
	  CC_REG( cpu->register_6 ) : CC_REG( cpu->register_3 );
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


    case BRNR_0: /* 58 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( cpu->register_0 != 0 ) {
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

      break;


    case BRNR_1: /* 59 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( REGISTER_BANK ) {

	if ( cpu->register_4 != 0 ) {
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

      } else {

	if ( cpu->register_1 != 0 ) {
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

      }

      break;


    case BRNR_2: /* 5A */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( REGISTER_BANK ) {

	if ( cpu->register_5 != 0 ) {
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

      } else {

	if ( cpu->register_2 != 0 ) {
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

      }

      break;


    case BRNR_3: /* 5B */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( REGISTER_BANK ) {

	if ( cpu->register_6 != 0 ) {
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

      } else {

	if ( cpu->register_3 != 0 ) {
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

      }

      break;


    case BRNA_0: /* 5C */

      /* Get high order address byte into holding register and low order address
	 byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( cpu->register_0 != 0 ) {
	cpu->iar = (cpu->hr & INDIRECT) ?
	  MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) ) :
	  MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) );
      }

      break;


    case BRNA_1: /* 5D */

      /* Get high order address byte into holding register and low order address
	 byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( REGISTER_BANK ) {

	if ( cpu->register_4 != 0 ) {
	  cpu->iar = (cpu->hr & INDIRECT) ?
	    MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) ) :
	    MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) );
	}

      } else {

	if ( cpu->register_1 != 0 ) {
	  cpu->iar = (cpu->hr & INDIRECT) ?
	    MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) ) :
	    MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) );
	}

      }

      break;


    case BRNA_2: /* 5E */

      /* Get high order address byte into holding register and low order address
	 byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( REGISTER_BANK ) {

	if ( cpu->register_5 != 0 ) {
	  cpu->iar = (cpu->hr & INDIRECT) ?
	    MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) ) :
	    MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) );
	}

      } else {

	if ( cpu->register_2 != 0 ) {
	  cpu->iar = (cpu->hr & INDIRECT) ?
	    MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) ) :
	    MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) );
	}

      }

      break;


    case BRNA_3: /* 5F */

      /* Get high order address byte into holding register and low order address
	 byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( REGISTER_BANK ) {

	if ( cpu->register_6 != 0 ) {
	  cpu->iar = (cpu->hr & INDIRECT) ?
	    MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) ) :
	    MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) );
	}

      } else {

	if ( cpu->register_3 != 0 ) {
	  cpu->iar = (cpu->hr & INDIRECT) ?
	    MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) ) :
	    MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) );
	}

      }

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


    case LPSU: /* 92 */

      /*
	From the Instruction Manual, p. 68:

	  "Bits #4 and #3 of the PSU are unassigned and will always be regarded
	  as containing zeroes."

        Thus, we have to mask the PSU with 0xE7, which is 0b11100111.
       */
      cpu->psu = ( cpu->register_0 & 0xE7 );

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


    default:

      cpu_error = 2;

    }

    ++cpu->iar;
  }

  return cpu_error;
}
