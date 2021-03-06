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
  cpu->r0 =
  cpu->register_1 =
  cpu->register_2 =
  cpu->register_3 =
  cpu->register_4 =
  cpu->register_5 =
  cpu->register_6 =

  cpu->psu =
  cpu->psl =

  cpu->ras[0] =
  cpu->ras[1] =
  cpu->ras[2] =
  cpu->ras[3] =
  cpu->ras[4] =
  cpu->ras[5] =
  cpu->ras[6] =
  cpu->ras[7] =

  cpu->iar = 0;

  SELECT_REGISTER_BANK1;
}

int cpu_loop( Cpu *cpu, unsigned char *memory )
{
  long cycle_count = 0;

  cpu->error = 0;

  while ( !cpu->error ) {
    cpu->ir = memory[MEMORY( cpu->iar )];

    switch( cpu->ir ) {

    case LODZ_0: /* 00 */

      cpu->error = 1;

      TWO_CPU_CYCLES;

      break;


    case LODZ_1: /* 01 */

      /* Set register value. */
      cpu->r0 = *cpu->r1;

      /* Set CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->r0 );

      TWO_CPU_CYCLES;

      break;


    case LODZ_2: /* 02 */

      /* Set register value. */
      cpu->r0 = *cpu->r2;

      /* Set CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->r0 );

      TWO_CPU_CYCLES;

      break;


    case LODZ_3: /* 03 */

      /* Set register value. */
      cpu->r0 = *cpu->r3;

      /* Set CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->r0 );

      TWO_CPU_CYCLES;

      break;


    case LODI_0: /* 04 */

      /* Set register value. */
      cpu->r0 = memory[MEMORY( ++cpu->iar )];

      /* Set CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->r0 );

      TWO_CPU_CYCLES;

      break;


    case LODI_1: /* 05 */

      /* Set register value. */
      *cpu->r1 = memory[MEMORY( ++cpu->iar )];

      /* Set CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_REG( *cpu->r1 );

      break;


    case LODI_2: /* 06 */

      /* Set register value. */
      *cpu->r2 = memory[MEMORY( ++cpu->iar )];

      /* Set CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_REG( *cpu->r2 );

      TWO_CPU_CYCLES;

      break;


    case LODI_3: /* 07 */

      /* Set register value. */
      *cpu->r3 = memory[MEMORY( ++cpu->iar )];

      /* Set CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_REG( *cpu->r3 );

      TWO_CPU_CYCLES;

      break;


    case LODR_0: /* 08 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Indirect or direct addressing? */
      if ( cpu->dbr & INDIRECT ) {
        /* Set register value. */
        cpu->r0 =
          memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar, cpu->rel_off) )];

        TWO_CPU_CYCLES;
      } else {
        /* Set register value. */
        cpu->r0 = memory[MEMORY( RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )];
      }

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->r0 );

      THREE_CPU_CYCLES;

      break;


    case LODR_1: /* 09 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Indirect or direct addressing? */
      if ( cpu->dbr & INDIRECT ) {
        /* Set register value. */
        *cpu->r1 = memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
                                                             cpu->rel_off) )];

        TWO_CPU_CYCLES;
      } else {
        /* Set register value. */
        *cpu->r1 = memory[MEMORY( RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )];
      }

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( *cpu->r1 );

      THREE_CPU_CYCLES;

      break;


    case LODR_2: /* 0A */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Indirect or direct addressing? */
      if ( cpu->dbr & INDIRECT ) {
        /* Set register value. */
        *cpu->r2 = memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
                                                             cpu->rel_off) )];

        TWO_CPU_CYCLES;
      } else {
        /* Set register value. */
        *cpu->r2 = memory[MEMORY( RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )];
      }

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( *cpu->r2 );

      THREE_CPU_CYCLES;

      break;


    case LODR_3: /* 0B */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Indirect or direct addressing? */
      if ( cpu->dbr & INDIRECT ) {
        /* Set register value. */
        *cpu->r3 = memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
                                                             cpu->rel_off) )];

        TWO_CPU_CYCLES;
      } else {
        /* Set register value. */
        *cpu->r3 = memory[MEMORY( RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )];
      }

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( *cpu->r3 );

      THREE_CPU_CYCLES;

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
          (cpu->indexing == INCREMENT) ? ++cpu->r0 : --cpu->r0;
        }

        if ( cpu->hr & INDIRECT ) {
          cpu->r0 =
            memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT( cpu->r0, cpu->hr,
                                                            cpu->dbr) )];

          TWO_CPU_CYCLES;
        } else {
          cpu->r0 = memory[MEMORY( ABSOLUTE_ADDRESS_INDEX( cpu->r0, cpu->hr,
                                                           cpu->dbr ) )];
        }
      } else {
        if ( cpu->hr & INDIRECT ) {
          cpu->r0 =
            memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )];

          TWO_CPU_CYCLES;
        } else {
          cpu->r0 = memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )];
        }
      }

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->r0 );

      FOUR_CPU_CYCLES;

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
          (cpu->indexing == INCREMENT) ? ++*cpu->r1 : --*cpu->r1;
        }

        if ( cpu->hr & INDIRECT ) {
          cpu->r0 =
            memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT( *cpu->r1, cpu->hr,
                                                            cpu->dbr) )];

          TWO_CPU_CYCLES;
        } else {
          cpu->r0 = memory[MEMORY( ABSOLUTE_ADDRESS_INDEX( *cpu->r1, cpu->hr,
                                                           cpu->dbr ) )];
        }

        /* Set CC. */
        CLEAR_CC;
        cpu->psl |= CC_REG( cpu->r0 );

      } else {

        if ( cpu->hr & INDIRECT ) {
          *cpu->r1 = memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr,
                                                               cpu->dbr ) )];

          TWO_CPU_CYCLES;
        } else {
          *cpu->r1 = memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )];
        }

        /* Set CC. */
        CLEAR_CC;
        cpu->psl |= CC_REG( *cpu->r1 );
      }

      FOUR_CPU_CYCLES;

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
          (cpu->indexing == INCREMENT) ? ++*cpu->r2 : --*cpu->r2;
        }

        if ( cpu->hr & INDIRECT ) {
          cpu->r0 =
            memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT( *cpu->r2, cpu->hr,
                                                            cpu->dbr) )];

          TWO_CPU_CYCLES;
        } else {
          cpu->r0 =
            memory[MEMORY( ABSOLUTE_ADDRESS_INDEX( *cpu->r2, cpu->hr,
                                                   cpu->dbr ) )];
        }

        /* Set CC. */
        CLEAR_CC;
        cpu->psl |= CC_REG( cpu->r0 );

      } else {

        if ( cpu->hr & INDIRECT ) {
          *cpu->r2 = memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr,
                                                               cpu->dbr ) )];

          TWO_CPU_CYCLES;
        } else {
          *cpu->r2 = memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )];
        }

        /* Set CC. */
        CLEAR_CC;
        cpu->psl |= CC_REG( *cpu->r2 );
      }

      FOUR_CPU_CYCLES;

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
          (cpu->indexing == INCREMENT) ? ++*cpu->r3 : --*cpu->r3;
        }

        if ( cpu->hr & INDIRECT ) {
          cpu->r0 =
            memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT( *cpu->r3, cpu->hr,
                                                            cpu->dbr) )];

          TWO_CPU_CYCLES;
        } else {
          cpu->r0 = memory[MEMORY( ABSOLUTE_ADDRESS_INDEX( *cpu->r3, cpu->hr,
                                                           cpu->dbr ) )];
        }

        /* Set CC. */
        CLEAR_CC;
        cpu->psl |= CC_REG( cpu->r0 );

      } else {

        if ( cpu->hr & INDIRECT ) {
          *cpu->r3 = memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr,
                                                               cpu->dbr ) )];

          TWO_CPU_CYCLES;
        } else {
          *cpu->r3 = memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )];
        }

        /* Set CC. */
        CLEAR_CC;
        cpu->psl |= CC_REG( *cpu->r3 );
      }

      FOUR_CPU_CYCLES;

      break;


    case SPSU: /* 12 */

      /* Set register value. */
      cpu->r0 = cpu->psu;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->r0 );

      TWO_CPU_CYCLES;

      break;


    case SPSL: /* 13 */

      /* Set register value. */
      cpu->r0 = cpu->psl;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->r0 );

      TWO_CPU_CYCLES;

      break;


    case RETC_0: /* 14 */
    case RETC_1: /* 15 */
    case RETC_2: /* 16 */
    case RETC_3: /* 17 */

      /* Extract CC code from Opcode and scale it to PSL format for
         comparison. */
      cpu->cc = ( cpu->ir & 0x3 ) << 6;

      if ( cpu->cc == C_CODE || cpu->cc == PSL_CC ) {
        RAS_POP;
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

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

          TWO_CPU_CYCLES;
        } else {
          /* Branch to specified address. */
          cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS( cpu->iar,
                                                          cpu->rel_off ) ) );
        }
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

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
        if ( cpu->hr & INDIRECT ) {
          cpu->iar =
            MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) );

          TWO_CPU_CYCLES;
        } else {
          cpu->iar = MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) );
        }
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case EORZ_0: /* 20 */

      /* Set register value. */
      cpu->r0 ^= cpu->r0;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->r0 );

      TWO_CPU_CYCLES;

      break;


    case EORZ_1: /* 21 */

      /* Set register value. */
      cpu->r0 ^= *cpu->r1;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->r0 );

      TWO_CPU_CYCLES;

      break;


    case EORZ_2: /* 22 */

      /* Set register value. */
      cpu->r0 ^= *cpu->r2;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->r0 );

      TWO_CPU_CYCLES;

      break;


    case EORZ_3: /* 23 */

      /* Set register value. */
      cpu->r0 ^= *cpu->r3;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->r0 );

      TWO_CPU_CYCLES;

      break;


    case EORI_0: /* 24 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* Set register value. */
      cpu->r0 ^= cpu->dbr;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->r0 );

      TWO_CPU_CYCLES;

      break;


    case EORI_1: /* 25 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* Set register value. */
      *cpu->r1 ^= cpu->dbr;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( *cpu->r1 );

      TWO_CPU_CYCLES;

      break;


    case EORI_2: /* 26 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* Set register value. */
      *cpu->r2 ^= cpu->dbr;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( *cpu->r2 );

      TWO_CPU_CYCLES;

      break;


    case EORI_3: /* 27 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* Set register value. */
      *cpu->r3 ^= cpu->dbr;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( *cpu->r3 );

      TWO_CPU_CYCLES;

      break;


    case EORR_0: /* 28 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Set register value */
      if ( cpu->dbr & INDIRECT ) {
        cpu->r0 ^=
          memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar, cpu->rel_off ) )];

        TWO_CPU_CYCLES;
      } else {
        cpu->r0 ^= memory[MEMORY( RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )];
      }

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->r0 );

      THREE_CPU_CYCLES;

      break;


    case EORR_1: /* 29 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Set register value */
      if ( cpu->dbr & INDIRECT ) {
        *cpu->r1 ^= memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
                                                              cpu->rel_off ) )];

        TWO_CPU_CYCLES;
      } else {
        *cpu->r1 ^= memory[MEMORY( RELATIVE_ADDRESS( cpu->iar,
                                                     cpu->rel_off ) )];
      }

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( *cpu->r1 );

      THREE_CPU_CYCLES;

      break;


    case EORR_2: /* 2A */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Set register value */
      if ( cpu->dbr & INDIRECT ) {
        *cpu->r2 ^= memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
                                                              cpu->rel_off ) )];

        TWO_CPU_CYCLES;
      } else {
        *cpu->r2 ^= memory[MEMORY( RELATIVE_ADDRESS( cpu->iar,
                                                     cpu->rel_off ) )];
      }

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( *cpu->r2 );

      THREE_CPU_CYCLES;

      break;


    case EORR_3: /* 2B */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Set register value */
      if ( cpu->dbr & INDIRECT ) {
        *cpu->r3 ^= memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
                                                              cpu->rel_off ) )];

        TWO_CPU_CYCLES;
      } else {
        *cpu->r3 ^= memory[MEMORY( RELATIVE_ADDRESS( cpu->iar,
                                                     cpu->rel_off ) )];
      }

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( *cpu->r3 );

      THREE_CPU_CYCLES;

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
          (cpu->indexing == INCREMENT) ? ++cpu->r0 : --cpu->r0;
        }

        if ( cpu->hr & INDIRECT ) {
          cpu->r0 ^=
            memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT( cpu->r0, cpu->hr,
                                                            cpu->dbr ) )];

          TWO_CPU_CYCLES;
        } else {
          cpu->r0 ^= memory[MEMORY( ABSOLUTE_ADDRESS_INDEX( cpu->r0, cpu->hr,
                                                            cpu->dbr ) )];
        }
      } else {

        if ( cpu->hr & INDIRECT ) {
          cpu->r0 ^=
            memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )];

          TWO_CPU_CYCLES;
        } else {
          cpu->r0 ^= memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )];
        }
      }

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->r0 );

      FOUR_CPU_CYCLES;

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
          (cpu->indexing == INCREMENT) ? ++*cpu->r1 : --*cpu->r1;
        }

        if ( cpu->hr & INDIRECT ) {
          cpu->r0 ^=
            memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT( *cpu->r1, cpu->hr,
                                                            cpu->dbr) )];

          TWO_CPU_CYCLES;
        } else {
          cpu->r0 ^= memory[MEMORY( ABSOLUTE_ADDRESS_INDEX( *cpu->r1, cpu->hr,
                                                            cpu->dbr ) )];
        }

        /* Set CC. */
        CLEAR_CC;
        cpu->psl |= CC_REG( cpu->r0 );

      } else {

        if ( cpu->hr & INDIRECT ) {
          *cpu->r1 ^=
            memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )];

          TWO_CPU_CYCLES;
        } else {
          *cpu->r1 ^= memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )];
        }

        /* Set CC. */
        CLEAR_CC;
        cpu->psl |= CC_REG( *cpu->r1 );
      }

      FOUR_CPU_CYCLES;

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
          (cpu->indexing == INCREMENT) ? ++*cpu->r2 : --*cpu->r2;
        }

        if ( cpu->hr & INDIRECT ) {
          cpu->r0 ^=
            memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT( *cpu->r2, cpu->hr,
                                                            cpu->dbr) )];

          TWO_CPU_CYCLES;
        } else {
          cpu->r0 ^= memory[MEMORY( ABSOLUTE_ADDRESS_INDEX( *cpu->r2, cpu->hr,
                                                            cpu->dbr ) )];
        }

        /* Set CC. */
        CLEAR_CC;
        cpu->psl |= CC_REG( cpu->r0 );

      } else {

        if ( cpu->hr & INDIRECT ) {
          *cpu->r2 ^=
            memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )];

          TWO_CPU_CYCLES;
        } else {
          *cpu->r2 ^= memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )];
        }

        /* Set CC. */
        CLEAR_CC;
        cpu->psl |= CC_REG( *cpu->r2 );
      }

      FOUR_CPU_CYCLES;

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
          (cpu->indexing == INCREMENT) ? ++*cpu->r3 : --*cpu->r3;
        }

        if ( cpu->hr & INDIRECT ) {
          cpu->r0 ^=
            memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT( *cpu->r3, cpu->hr,
                                                            cpu->dbr) )];

          TWO_CPU_CYCLES;
        } else {
          cpu->r0 ^= memory[MEMORY( ABSOLUTE_ADDRESS_INDEX( *cpu->r3, cpu->hr,
                                                            cpu->dbr ) )];
        }

        /* Set CC. */
        CLEAR_CC;
        cpu->psl |= CC_REG( cpu->r0 );

      } else {

        if ( cpu->hr & INDIRECT ) {
          *cpu->r3 ^=
            memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )];

          TWO_CPU_CYCLES;
        } else {
          *cpu->r3 ^= memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )];
        }

        /* Set CC. */
        CLEAR_CC;
        cpu->psl |= CC_REG( *cpu->r3 );
      }

      FOUR_CPU_CYCLES;

      break;


    case RETE_0: /* 34 */
    case RETE_1: /* 35 */
    case RETE_2: /* 36 */
    case RETE_3: /* 37 */

      /* Extract CC code from Opcode and scale it to PSL format for
         comparison. */
      cpu->cc = ( cpu->ir & 0x3 ) << 6;

      if ( cpu->cc == C_CODE || cpu->cc == PSL_CC ) {
        RAS_POP;
      }

      /* Enable Interrupts */
      CLEAR_II;

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case BSTR_0: /* 38 */
    case BSTR_1: /* 39 */
    case BSTR_2: /* 3A */
    case BSTR_3: /* 3B */

      /* Extract CC code from Opcode and scale it to PSL format for
         comparison. */
      cpu->cc = ( cpu->ir & 0x3 ) << 6;

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( cpu->cc == C_CODE || cpu->cc == PSL_CC ) {
        cpu->rel_off = cpu->dbr & R_OFFSET;

        /* Push return address into stack */
        RAS_PUSH( cpu->iar + 1 );

        /* Indirect or direct addressing? */
        if ( cpu->dbr & INDIRECT ) {
          /* Branch to specified address. */
          cpu->iar =
            MEMORY( BRANCH_TO( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
                                                          cpu->rel_off ) ) );

          TWO_CPU_CYCLES;
        } else {
          /* Branch to specified address. */
          cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS( cpu->iar,
                                                          cpu->rel_off ) ) );
        }
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case BSTA_0: /* 3C */
    case BSTA_1: /* 3D */
    case BSTA_2: /* 3E */
    case BSTA_3: /* 3F */

      /* Extract CC code from Opcode and scale it to PSL format for
         comparison. */
      cpu->cc = ( cpu->ir & 0x3 ) << 6;

      /* Get high order address byte into holding register and low order address
         byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( cpu->cc == C_CODE || cpu->cc == PSL_CC ) {
        /* Push return address into stack */
        RAS_PUSH( cpu->iar + 1 );

        if ( cpu->hr & INDIRECT ) {
          cpu->iar =
            MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) );

          TWO_CPU_CYCLES;
        } else {
          cpu->iar = MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) );
        }
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case HALT: /* 40 */

      cpu->error = 1;

      ONE_CPU_CYCLE;

      break;


    case ANDZ_1: /* 41 */

      /* Set register value. */
      cpu->r0 &= *cpu->r1;

      /* Set CC value. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->r0 );

      TWO_CPU_CYCLES;

      break;


    case ANDZ_2: /* 42 */

      /* Set register value. */
      cpu->r0 &= *cpu->r2;

      /* Set CC value. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->r0 );

      TWO_CPU_CYCLES;

      break;


    case ANDZ_3: /* 43 */

      /* Set register value. */
      cpu->r0 &= *cpu->r3;

      /* Set CC value. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->r0 );

      TWO_CPU_CYCLES;

      break;


    case ANDI_0: /* 44 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* Set register value. */
      cpu->r0 &= cpu->dbr;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->r0 );

      TWO_CPU_CYCLES;

      break;


    case ANDI_1: /* 45 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* Set register value. */
      *cpu->r1 &= cpu->dbr;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( *cpu->r1 );

      TWO_CPU_CYCLES;

      break;


    case ANDI_2: /* 46 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* Set register value. */
      *cpu->r2 &= cpu->dbr;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( *cpu->r2 );

      TWO_CPU_CYCLES;

      break;


    case ANDI_3: /* 47 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* Set register value. */
      *cpu->r3 &= cpu->dbr;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( *cpu->r3 );

      TWO_CPU_CYCLES;

      break;


    case ANDR_0: /* 48 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Set register value */
      if (cpu->dbr & INDIRECT) {
        cpu->r0 &=
          memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar, cpu->rel_off ) )];

        TWO_CPU_CYCLES;
      } else {
        cpu->r0 &= memory[MEMORY( RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )];
      }

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->r0 );

      THREE_CPU_CYCLES;

      break;


    case ANDR_1: /* 49 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Set register value */
      if ( cpu->dbr & INDIRECT ) {
        *cpu->r1 &= memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
                                                              cpu->rel_off ) )];

        TWO_CPU_CYCLES;
      } else {
        *cpu->r1 &=
          memory[MEMORY( RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )];
      }

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( *cpu->r1 );

      THREE_CPU_CYCLES;

      break;


    case ANDR_2: /* 4A */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Set register value */
      if ( cpu->dbr & INDIRECT ) {
        *cpu->r2 &= memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
                                                              cpu->rel_off ) )];

        TWO_CPU_CYCLES;
      } else {
        *cpu->r2 &=
          memory[MEMORY( RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )];
      }

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( *cpu->r2 );

      THREE_CPU_CYCLES;

      break;


    case ANDR_3: /* 4B */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Set register value */
      if ( cpu->dbr & INDIRECT ) {
        *cpu->r3 &= memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
                                                              cpu->rel_off ) )];

        TWO_CPU_CYCLES;
      } else {
        *cpu->r3 &=
          memory[MEMORY( RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )];
      }

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( *cpu->r3 );

      THREE_CPU_CYCLES;

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
          (cpu->indexing == INCREMENT) ? ++cpu->r0 : --cpu->r0;
        }

        if ( cpu->hr & INDIRECT ) {
          cpu->r0 &=
            memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT( cpu->r0, cpu->hr,
                                                            cpu->dbr) )];

          TWO_CPU_CYCLES;
        } else {
          cpu->r0 &= memory[MEMORY( ABSOLUTE_ADDRESS_INDEX( cpu->r0, cpu->hr,
                                                            cpu->dbr ) )];
        }

      } else {
        if ( cpu->hr & INDIRECT ) {
          cpu->r0 &= memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr,
                                                               cpu->dbr ) )];

          TWO_CPU_CYCLES;
        } else {
          cpu->r0 &= memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )];
        }
      }

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->r0 );

      FOUR_CPU_CYCLES;

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
          (cpu->indexing == INCREMENT) ? ++*cpu->r1 : --*cpu->r1;
        }

        if ( cpu->hr & INDIRECT ) {
          cpu->r0 &=
            memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT( *cpu->r1, cpu->hr,
                                                            cpu->dbr) )];

          TWO_CPU_CYCLES;
        } else {
          cpu->r0 &= memory[MEMORY( ABSOLUTE_ADDRESS_INDEX( *cpu->r1, cpu->hr,
                                                            cpu->dbr ) )];
        }

        /* Set CC. */
        CLEAR_CC;
        cpu->psl |= CC_REG( cpu->r0 );

      } else {

        if ( cpu->hr & INDIRECT ) {
          *cpu->r1 &= memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr,
                                                                cpu->dbr ) )];

          TWO_CPU_CYCLES;
        } else {
          *cpu->r1 &= memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )];
        }

        /* Set CC. */
        CLEAR_CC;
        cpu->psl |= CC_REG( *cpu->r1 );
      }

      FOUR_CPU_CYCLES;

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
          (cpu->indexing == INCREMENT) ? ++*cpu->r2 : --*cpu->r2;
        }

        if ( cpu->hr & INDIRECT ) {
          cpu->r0 &=
            memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT( *cpu->r2, cpu->hr,
                                                            cpu->dbr) )];

          TWO_CPU_CYCLES;
        } else {
          cpu->r0 &= memory[MEMORY( ABSOLUTE_ADDRESS_INDEX( *cpu->r2, cpu->hr,
                                                            cpu->dbr ) )];
        }

        /* Set CC. */
        CLEAR_CC;
        cpu->psl |= CC_REG( cpu->r0 );

      } else {

        if ( cpu->hr & INDIRECT ) {
          *cpu->r2 &= memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr,
                                                                cpu->dbr ) )];

          TWO_CPU_CYCLES;
        } else {
          *cpu->r2 &= memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )];
        }

        /* Set CC. */
        CLEAR_CC;
        cpu->psl |= CC_REG( *cpu->r2 );
      }

      FOUR_CPU_CYCLES;

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
          (cpu->indexing == INCREMENT) ? ++*cpu->r3 : --*cpu->r3;
        }

        if ( cpu->hr & INDIRECT ) {
          cpu->r0 &=
            memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT( *cpu->r3, cpu->hr,
                                                            cpu->dbr) )];

          TWO_CPU_CYCLES;
        } else {
          cpu->r0 &= memory[MEMORY( ABSOLUTE_ADDRESS_INDEX( *cpu->r3, cpu->hr,
                                                            cpu->dbr ) )];
        }

        /* Set CC. */
        CLEAR_CC;
        cpu->psl |= CC_REG( cpu->r0 );

      } else {

        if ( cpu->hr & INDIRECT ) {
          *cpu->r3 &= memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr,
                                                                cpu->dbr ) )];

          TWO_CPU_CYCLES;
        } else {
          *cpu->r3 &= memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )];
        }

        /* Set CC. */
        CLEAR_CC;
        cpu->psl |= CC_REG( *cpu->r3 );
      }

      FOUR_CPU_CYCLES;

      break;


    case RRR_0: /* 50 */

      ROTATE_RIGHT( cpu->r0 );

      TWO_CPU_CYCLES;

      break;


    case RRR_1: /* 51 */

      ROTATE_RIGHT( *cpu->r1 );

      TWO_CPU_CYCLES;

      break;


    case RRR_2: /* 52 */

      ROTATE_RIGHT( *cpu->r2 );

      TWO_CPU_CYCLES;

      break;


    case RRR_3: /* 53 */

      ROTATE_RIGHT( *cpu->r3 );

      TWO_CPU_CYCLES;

      break;


    case BRNR_0: /* 58 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( cpu->r0 ) {
        cpu->rel_off = cpu->dbr & R_OFFSET;

        /* Indirect or direct addressing? */
        if ( cpu->dbr & INDIRECT ) {
          /* Branch to specified address. */
          cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
                                                                   cpu->rel_off
                                                                   ) ) );

          TWO_CPU_CYCLES;
        } else {
          /* Branch to specified address. */
          cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS( cpu->iar,
                                                          cpu->rel_off ) ) );
        }
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case BRNR_1: /* 59 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( *cpu->r1 ) {
        cpu->rel_off = cpu->dbr & R_OFFSET;

        /* Indirect or direct addressing? */
        if ( cpu->dbr & INDIRECT ) {
          /* Branch to specified address. */
          cpu->iar =
            MEMORY( BRANCH_TO( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
                                                          cpu->rel_off ) ) );

          TWO_CPU_CYCLES;
        } else {
          /* Branch to specified address. */
          cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS( cpu->iar,
                                                          cpu->rel_off ) ) );
        }
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case BRNR_2: /* 5A */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( *cpu->r2 ) {
        cpu->rel_off = cpu->dbr & R_OFFSET;

        /* Indirect or direct addressing? */
        if ( cpu->dbr & INDIRECT ) {
          /* Branch to specified address. */
          cpu->iar =
            MEMORY( BRANCH_TO( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
                cpu->rel_off ) ) );

          TWO_CPU_CYCLES;
        } else {
          /* Branch to specified address. */
          cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS( cpu->iar,
                                                          cpu->rel_off ) ) );
        }

      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case BRNR_3: /* 5B */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( *cpu->r3 ) {
        cpu->rel_off = cpu->dbr & R_OFFSET;

        /* Indirect or direct addressing? */
        if ( cpu->dbr & INDIRECT ) {
          /* Branch to specified address. */
          cpu->iar =
            MEMORY( BRANCH_TO( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
                                                          cpu->rel_off ) ) );

          TWO_CPU_CYCLES;
        } else {
          /* Branch to specified address. */
          cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS( cpu->iar,
                                                          cpu->rel_off ) ) );
        }

      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case BRNA_0: /* 5C */

      /* Get high order address byte into holding register and low order address
         byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( cpu->r0 ) {
        if ( cpu->hr & INDIRECT ) {
          cpu->iar =
            MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) );

          TWO_CPU_CYCLES;
        } else {
          cpu->iar = MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) );
        }
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case BRNA_1: /* 5D */

      /* Get high order address byte into holding register and low order address
         byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( *cpu->r1 ) {
        if ( cpu->hr & INDIRECT ) {
          cpu->iar =
            MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) );

          TWO_CPU_CYCLES;
        } else {
          cpu->iar = MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) );
        }
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case BRNA_2: /* 5E */

      /* Get high order address byte into holding register and low order address
         byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( *cpu->r2 ) {
        if ( cpu->hr & INDIRECT ) {
          cpu->iar =
            MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) );

          TWO_CPU_CYCLES;
        } else {
          cpu->iar = MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) );
        }
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case BRNA_3: /* 5F */

      /* Get high order address byte into holding register and low order address
         byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( *cpu->r3 ) {
        if ( cpu->hr & INDIRECT ) {
          cpu->iar =
            MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) );

          TWO_CPU_CYCLES;
        } else {
          cpu->iar = MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) );
        }
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case IORZ_0: /* 60 */

      /*
        Set register value is not necessary, since this:

        cpu->r0 |= cpu->r0;

        does not change the value of Reg 0.
      */

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->r0 );

      TWO_CPU_CYCLES;

      break;


    case IORZ_1: /* 61 */

      /* Set register value. */
      cpu->r0 |= ( *cpu->r1 );

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->r0 );

      TWO_CPU_CYCLES;

      break;


    case IORZ_2: /* 62 */

      /* Set register value. */
      cpu->r0 |= ( *cpu->r2 );

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->r0 );

      TWO_CPU_CYCLES;

      break;


    case IORZ_3: /* 63 */

      /* Set register value. */
      cpu->r0 |= ( *cpu->r3 );

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->r0 );

      TWO_CPU_CYCLES;

      break;


    case IORI_0: /* 64 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* Set register value. */
      cpu->r0 |= cpu->dbr;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->r0 );

      TWO_CPU_CYCLES;

      break;


    case IORI_1: /* 65 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* Set register value. */
      *cpu->r1 |= cpu->dbr;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( *cpu->r1 );

      TWO_CPU_CYCLES;

      break;


    case IORI_2: /* 66 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* Set register value. */
      *cpu->r2 |= cpu->dbr;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( *cpu->r2 );

      TWO_CPU_CYCLES;

      break;


    case IORI_3: /* 67 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* Set register value. */
      *cpu->r3 |= cpu->dbr;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( *cpu->r3 );

      TWO_CPU_CYCLES;

      break;


    case IORR_0: /* 68 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Set register value */
      if ( cpu->dbr & INDIRECT ) {
        cpu->r0 |= memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
                                                             cpu->rel_off ) )];

        TWO_CPU_CYCLES;
      } else {
        cpu->r0 |= memory[MEMORY( RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )];
      }

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->r0 );

      THREE_CPU_CYCLES;

      break;


    case IORR_1: /* 69 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Set register value */
      if ( cpu->dbr & INDIRECT ) {
        *cpu->r1 |= memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
                                                              cpu->rel_off ) )];

        TWO_CPU_CYCLES;
      } else {
        *cpu->r1 |= memory[MEMORY( RELATIVE_ADDRESS( cpu->iar,
                                                     cpu->rel_off ) )];
      }

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( *cpu->r1 );

      THREE_CPU_CYCLES;

      break;


    case IORR_2: /* 6A */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Set register value */
      if ( cpu->dbr & INDIRECT ) {
        *cpu->r2 |= memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
                                                              cpu->rel_off ) )];

        TWO_CPU_CYCLES;
      } else {
        *cpu->r2 |= memory[MEMORY( RELATIVE_ADDRESS( cpu->iar,
                                                     cpu->rel_off ) )];
      }

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( *cpu->r2 );

      THREE_CPU_CYCLES;

      break;


    case IORR_3: /* 6B */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Set register value */
      if ( cpu->dbr & INDIRECT ) {
        *cpu->r3 |= memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
                                                              cpu->rel_off ) )];

        TWO_CPU_CYCLES;
      } else {
        *cpu->r3 |= memory[MEMORY( RELATIVE_ADDRESS( cpu->iar,
                                                     cpu->rel_off ) )];
      }

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( *cpu->r3 );

      THREE_CPU_CYCLES;

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
          (cpu->indexing == INCREMENT) ? ++cpu->r0 : --cpu->r0;
        }

        if ( cpu->hr & INDIRECT ) {
          cpu->r0 |=
            memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT( cpu->r0, cpu->hr,
                                                            cpu->dbr) )];

          TWO_CPU_CYCLES;
        } else {
          cpu->r0 |= memory[MEMORY( ABSOLUTE_ADDRESS_INDEX( cpu->r0, cpu->hr,
                                                            cpu->dbr ) )];
        }

      } else {
        if ( cpu->hr & INDIRECT ) {
          cpu->r0 |= memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr,
                                                               cpu->dbr ) )];

          TWO_CPU_CYCLES;
        } else {
          cpu->r0 |= memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )];
        }
      }

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( cpu->r0 );

      FOUR_CPU_CYCLES;

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
          (cpu->indexing == INCREMENT) ? ++*cpu->r1 : --*cpu->r1;
        }

        if ( cpu->hr & INDIRECT ) {
          cpu->r0 |=
            memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT( *cpu->r1, cpu->hr,
                                                            cpu->dbr) )];

          TWO_CPU_CYCLES;
        } else {
          cpu->r0 |= memory[MEMORY( ABSOLUTE_ADDRESS_INDEX( *cpu->r1, cpu->hr,
                                                            cpu->dbr ) )];
        }

        /* Set CC. */
        CLEAR_CC;
        cpu->psl |= CC_REG( cpu->r0 );

      } else {

        if ( cpu->hr & INDIRECT ) {
          *cpu->r1 |= memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr,
                                                                cpu->dbr ) )];

          TWO_CPU_CYCLES;
        } else {
          *cpu->r1 |= memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )];
        }

        /* Set CC. */
        CLEAR_CC;
        cpu->psl |= CC_REG( *cpu->r1 );
      }

      FOUR_CPU_CYCLES;

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
          (cpu->indexing == INCREMENT) ? ++*cpu->r2 : --*cpu->r2;
        }

        if ( cpu->hr & INDIRECT ) {
          cpu->r0 |=
            memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT( *cpu->r2, cpu->hr,
                  cpu->dbr) )];

          TWO_CPU_CYCLES;
        } else {
          cpu->r0 |= memory[MEMORY( ABSOLUTE_ADDRESS_INDEX( *cpu->r2, cpu->hr,
                                                            cpu->dbr ) )];
        }

        /* Set CC. */
        CLEAR_CC;
        cpu->psl |= CC_REG( cpu->r0 );

      } else {

        if ( cpu->hr & INDIRECT ) {
          *cpu->r2 |= memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr,
                                                                cpu->dbr ) )];

          TWO_CPU_CYCLES;
        } else {
          *cpu->r2 |= memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )];
        }

        /* Set CC. */
        CLEAR_CC;
        cpu->psl |= CC_REG( *cpu->r2 );
      }

      FOUR_CPU_CYCLES;

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
          (cpu->indexing == INCREMENT) ? ++*cpu->r3 : --*cpu->r3;
        }

        if ( cpu->hr & INDIRECT ) {
          cpu->r0 |=
            memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT( *cpu->r3, cpu->hr,
                                                            cpu->dbr) )];

          TWO_CPU_CYCLES;
        } else {
          cpu->r0 |= memory[MEMORY( ABSOLUTE_ADDRESS_INDEX( *cpu->r3, cpu->hr,
                                                            cpu->dbr ) )];
        }

        /* Set CC. */
        CLEAR_CC;
        cpu->psl |= CC_REG( cpu->r0 );

      } else {

        if ( cpu->hr & INDIRECT ) {
          *cpu->r3 |= memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr,
                                                                cpu->dbr ) )];

          TWO_CPU_CYCLES;
        } else {
          *cpu->r3 |= memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )];
        }

        /* Set CC. */
        CLEAR_CC;
        cpu->psl |= CC_REG( *cpu->r3 );
      }

      FOUR_CPU_CYCLES;

      break;


    case CPSU: /* 74 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* Data byte is used to clear selective (logically NAND) selective
         bits in the PSU. All other bits should be left untouched. */
      cpu->psu &= ~cpu->dbr;

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case CPSL: /* 75 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* Register bank may change. */
      if ( REGISTER_BANK && (cpu->dbr & PSL_RS) ) {
        SELECT_REGISTER_BANK1;
      }

      /* Data byte is used to clear selective (logically NAND) selective bits in
         the PSL. All other bits should be left untouched. */
      cpu->psl &= ~cpu->dbr;

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

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

      THREE_CPU_CYCLES;

      break;


    case PPSL: /* 77 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* Register bank may change. */
      if ( !REGISTER_BANK && (cpu->dbr & PSL_RS) ) {
        SELECT_REGISTER_BANK2;
      }

      /* Data byte is used to turn on (logically OR) selective bits in the
         PSL. All other bits should be left untouched. */
      cpu->psl |= cpu->dbr;

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case BSNR_0: /* 78 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( cpu->r0 ) {
        cpu->rel_off = cpu->dbr & R_OFFSET;

        /* Push return address into stack */
        RAS_PUSH( cpu->iar + 1 );

        /* Indirect or direct addressing? */
        if ( cpu->dbr & INDIRECT ) {
          /* Branch to specified address. */
          cpu->iar =
            MEMORY( BRANCH_TO( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
                                                          cpu->rel_off ) ) );

          TWO_CPU_CYCLES;
        } else {
          /* Branch to specified address. */
          cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS( cpu->iar,
                                                          cpu->rel_off ) ) );
        }
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case BSNR_1: /* 79 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( *cpu->r1 ) {
        cpu->rel_off = cpu->dbr & R_OFFSET;

        /* Push return address into stack */
        RAS_PUSH( cpu->iar + 1 );

        /* Indirect or direct addressing? */
        if ( cpu->dbr & INDIRECT ) {
          /* Branch to specified address. */
          cpu->iar =
            MEMORY( BRANCH_TO( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
                                                          cpu->rel_off ) ) );

          TWO_CPU_CYCLES;
        } else {
          /* Branch to specified address. */
          cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS( cpu->iar,
                                                          cpu->rel_off ) ) );
        }
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case BSNR_2: /* 7A */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( *cpu->r2 ) {
        cpu->rel_off = cpu->dbr & R_OFFSET;

        /* Push return address into stack */
        RAS_PUSH( cpu->iar + 1 );

        /* Indirect or direct addressing? */
        if ( cpu->dbr & INDIRECT ) {
          /* Branch to specified address. */
          cpu->iar =
            MEMORY( BRANCH_TO( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
                                                          cpu->rel_off ) ) );

          TWO_CPU_CYCLES;
        } else {
          /* Branch to specified address. */
          cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS( cpu->iar,
                                                          cpu->rel_off ) ) );
        }
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case BSNR_3: /* 7B */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( *cpu->r2 ) {
        cpu->rel_off = cpu->dbr & R_OFFSET;

        /* Push return address into stack */
        RAS_PUSH( cpu->iar + 1 );

        /* Indirect or direct addressing? */
        if ( cpu->dbr & INDIRECT ) {
          /* Branch to specified address. */
          cpu->iar =
            MEMORY( BRANCH_TO( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
                                                          cpu->rel_off ) ) );

          TWO_CPU_CYCLES;
        } else {
          /* Branch to specified address. */
          cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS( cpu->iar,
                                                          cpu->rel_off ) ) );
        }
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case BSNA_0: /* 7C */

      /* Get high order address byte into holding register and low order address
         byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( cpu->r0 ) {
        /* Push return address into stack */
        RAS_PUSH( cpu->iar + 1 );

        if ( cpu->hr & INDIRECT ) {
          cpu->iar =
            MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) );

          TWO_CPU_CYCLES;
        } else {
          cpu->iar = MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) );
        }
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case BSNA_1: /* 7D */

      /* Get high order address byte into holding register and low order address
         byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( *cpu->r1 ) {
        /* Push return address into stack */
        RAS_PUSH( cpu->iar + 1 );

        if ( cpu->hr & INDIRECT ) {
          cpu->iar = MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS_INDIRECT( cpu->hr,
                                                                  cpu->dbr ) );

          TWO_CPU_CYCLES;
        } else {
          cpu->iar = MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) );
        }
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case BSNA_2: /* 7E */

      /* Get high order address byte into holding register and low order address
         byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( *cpu->r2 ) {
        /* Push return address into stack */
        RAS_PUSH( cpu->iar + 1 );

        if ( cpu->hr & INDIRECT ) {
          cpu->iar = MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS_INDIRECT( cpu->hr,
                                                                  cpu->dbr ) );

          TWO_CPU_CYCLES;
        } else {
          cpu->iar = MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) );
        }
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case BSNA_3: /* 7F */

      /* Get high order address byte into holding register and low order address
         byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( *cpu->r3 ) {
        /* Push return address into stack */
        RAS_PUSH( cpu->iar + 1 );

        if ( cpu->hr & INDIRECT ) {
          cpu->iar = MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS_INDIRECT( cpu->hr,
                                                                  cpu->dbr ) );

          TWO_CPU_CYCLES;
        } else {
          cpu->iar = MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) );
        }
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


      /*
        The following addition op codes all use the ADD() macro defined in
        cpu-2650.h, which is derived from WinArcadias (2650.c) add() inline
        function. This also sets all appropriate flags.
      */
    case ADDZ_0: /* 80 */

      ADD( cpu->r0, cpu->r0 );

      TWO_CPU_CYCLES;

      break;


    case ADDZ_1: /* 81 */

      ADD( cpu->r0, *cpu->r1 );

      TWO_CPU_CYCLES;

      break;


    case ADDZ_2: /* 82 */

      ADD( cpu->r0, *cpu->r2 );

      TWO_CPU_CYCLES;

      break;


    case ADDZ_3:

      ADD( cpu->r0, *cpu->r3 );

      TWO_CPU_CYCLES;

      break;


    case ADDI_0: /* 84 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      ADD( cpu->r0, cpu->dbr );

      TWO_CPU_CYCLES;

      break;


    case ADDI_1: /* 85 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      ADD( *cpu->r1, cpu->dbr );

      TWO_CPU_CYCLES;

      break;


    case ADDI_2: /* 86 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      ADD( *cpu->r2, cpu->dbr );

      TWO_CPU_CYCLES;

      break;


    case ADDI_3: /* 87 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      ADD( *cpu->r3, cpu->dbr );

      TWO_CPU_CYCLES;

      break;


    case ADDR_0: /* 88 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Temporarily store second operand for addition and flag checking. */
      if ( cpu->dbr & INDIRECT ) {
        cpu->second_op =
          memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar, cpu->rel_off ) )];

        TWO_CPU_CYCLES;
      } else {
        cpu->second_op = memory[MEMORY( RELATIVE_ADDRESS( cpu->iar,
                                                          cpu->rel_off ) )];
      }

      ADD( cpu->r0, cpu->second_op );

      THREE_CPU_CYCLES;

      break;


    case ADDR_1: /* 89 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Temporarily store second operand for addition and flag checking. */
      if ( cpu->dbr & INDIRECT ) {
        cpu->second_op =
          memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar, cpu->rel_off ) )];

        TWO_CPU_CYCLES;
      } else {
        cpu->second_op = memory[MEMORY( RELATIVE_ADDRESS( cpu->iar,
                                                          cpu->rel_off ) )];
      }

      ADD( *cpu->r1, cpu->second_op );

      THREE_CPU_CYCLES;

      break;


    case ADDR_2: /* 8A */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Temporarily store second operand for addition and flag checking. */
      if ( cpu->dbr & INDIRECT ) {
        cpu->second_op =
          memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar, cpu->rel_off ) )];

        TWO_CPU_CYCLES;
      } else {
        cpu->second_op = memory[MEMORY( RELATIVE_ADDRESS( cpu->iar,
                                                          cpu->rel_off ) )];
      }

      ADD( *cpu->r2, cpu->second_op );

      THREE_CPU_CYCLES;

      break;


    case ADDR_3: /* 8B */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Temporarily store second operand for addition and flag checking. */
      if ( cpu->dbr & INDIRECT ) {
        cpu->second_op =
          memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar, cpu->rel_off ) )];

        TWO_CPU_CYCLES;
      } else {
        cpu->second_op = memory[MEMORY( RELATIVE_ADDRESS( cpu->iar,
                                                          cpu->rel_off ) )];
      }

      ADD( *cpu->r3, cpu->second_op );

      THREE_CPU_CYCLES;

      break;


    case ADDA_0: /* 8C */

      /* Get high order address byte into holding register and low order address
         byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];
      cpu->indexing = cpu->hr & INDEXING;

      /* Get second operand and store it temporarily. */
      if ( cpu->indexing ) {

        /* Increment/decrement index register. */
        if ( cpu->indexing != SIMPLE_INDEXING ) {
          (cpu->indexing == INCREMENT) ? ++cpu->r0 : --cpu->r0;
        }

        if ( cpu->hr & INDIRECT ) {
          cpu->second_op =
            memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT( cpu->r0, cpu->hr,
                                                            cpu->dbr) )];

          TWO_CPU_CYCLES;
        } else {
          cpu->second_op = memory[MEMORY( ABSOLUTE_ADDRESS_INDEX( cpu->r0,
                                                                  cpu->hr,
                                                                  cpu->dbr ) )];
        }

      } else {
        cpu->second_op= ( cpu->hr & INDIRECT ) ?
          memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )] :
          memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )];
      }

      ADD( cpu->r0, cpu->second_op );

      FOUR_CPU_CYCLES;

      break;


    case ADDA_1: /* 8D */

      /* Get high order address byte into holding register and low order address
         byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];
      cpu->indexing = cpu->hr & INDEXING;

      /* Get second operand through absolute addressing. */
      if ( cpu->indexing ) {

        /* Increment/decrement index register. */
        if ( cpu->indexing != SIMPLE_INDEXING ) {
          (cpu->indexing == INCREMENT) ? ++*cpu->r1 : --*cpu->r1;
        }

        if ( cpu->hr & INDIRECT ) {
          cpu->second_op =
            memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT( *cpu->r1, cpu->hr,
                                                            cpu->dbr) )];

          TWO_CPU_CYCLES;
        } else {
          cpu->second_op =
            memory[MEMORY( ABSOLUTE_ADDRESS_INDEX( *cpu->r1, cpu->hr,
                                                   cpu->dbr ) )];
        }

        /* All indexing additions store result in R0. */
        ADD( cpu->r0, cpu->second_op );

      } else {

        if ( cpu->hr & INDIRECT ) {
          cpu->second_op =
            memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )];

          TWO_CPU_CYCLES;
        } else {
          cpu->second_op = memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr,
                                                            cpu->dbr ) )];
        }

        ADD( *cpu->r1, cpu->second_op );
      }

      FOUR_CPU_CYCLES;

      break;


    case ADDA_2: /* 8E */

      /* Get high order address byte into holding register and low order address
         byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];
      cpu->indexing = cpu->hr & INDEXING;

      /* Get second operand through absolute addressing. */
      if ( cpu->indexing ) {

        /* Increment/decrement index register. */
        if ( cpu->indexing != SIMPLE_INDEXING ) {
          (cpu->indexing == INCREMENT) ? ++*cpu->r2 : --*cpu->r2;
        }

        if ( cpu->hr & INDIRECT ) {
          cpu->second_op =
            memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT( *cpu->r2, cpu->hr,
                                                            cpu->dbr) )];

          TWO_CPU_CYCLES;
        } else {
          cpu->second_op =
            memory[MEMORY( ABSOLUTE_ADDRESS_INDEX( *cpu->r2, cpu->hr,
                                                   cpu->dbr ) )];
        }

        /* All indexing additions store result in R0. */
        ADD( cpu->r0, cpu->second_op );

      } else {

        if ( cpu->hr & INDIRECT ) {
          cpu->second_op =
            memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )];

          TWO_CPU_CYCLES;
        } else {
          cpu->second_op = memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr,
                                                            cpu->dbr ) )];
        }

        ADD( *cpu->r2, cpu->second_op );
      }

      FOUR_CPU_CYCLES;

      break;


    case ADDA_3: /* 8F */

      /* Get high order address byte into holding register and low order address
         byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];
      cpu->indexing = cpu->hr & INDEXING;

      /* Get second operand through absolute addressing. */
      if ( cpu->indexing ) {

        /* Increment/decrement index register. */
        if ( cpu->indexing != SIMPLE_INDEXING ) {
          (cpu->indexing == INCREMENT) ? ++*cpu->r3 : --*cpu->r3;
        }

        if ( cpu->hr & INDIRECT ) {
          cpu->second_op =
            memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT( *cpu->r3, cpu->hr,
                                                            cpu->dbr) )];

          TWO_CPU_CYCLES;
        } else {
          cpu->second_op =
            memory[MEMORY( ABSOLUTE_ADDRESS_INDEX( *cpu->r3, cpu->hr,
                                                   cpu->dbr ) )];
        }

        /* All indexing additions store result in R0. */
        ADD( cpu->r0, cpu->second_op );

      } else {

        if ( cpu->hr & INDIRECT ) {
          cpu->second_op =
            memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )];

          TWO_CPU_CYCLES;
        } else {
          cpu->second_op = memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr,
                                                            cpu->dbr ) )];
        }

        ADD( *cpu->r3, cpu->second_op );
      }

      FOUR_CPU_CYCLES;

      break;


    case LPSU: /* 92 */

      /*
        From the Instruction Manual, p. 68:

        "Bits #4 and #3 of the PSU are unassigned and will always be regarded
        as containing zeroes."

        Thus, we have to mask the PSU with PSU_NU, which is 0b11100111.
      */
      cpu->psu = PSU( cpu->r0 );

      TWO_CPU_CYCLES;

      break;


    case LPSL: /* 93 */

      /* Register bank may change. */
      if ( REGISTER_BANK && !(cpu->r0 & PSL_RS) ) {
        SELECT_REGISTER_BANK1;
      } else if ( !REGISTER_BANK && (cpu->r0 & PSL_RS) ) {
        SELECT_REGISTER_BANK2;
      }

      cpu->psl = cpu->r0;

      TWO_CPU_CYCLES;

      break;


      /*
        The following truth table indicates which value gets added to the
        affected register during a DAR instruction (from Instruction Manual, p.
        89) It is important to add A to each nibble separately (not causing any
        interdigit carries)!

        Carry | Inter Digit Carry | Added to Register r
        ------|-------------------|--------------------
            0 |                 0 |               0xAA
            0 |                 1 |               0xA0
            1 |                 0 |               0x0A
            1 |                 1 |               0x00
      */

    case DAR_0: /* 94 */

      /* See truth table above. */

      if ( cpu->psl != DAR_CHECK ) {

        if ( !CARRY ) {
          cpu->r0 += 0xA0;
        }

        if ( !ID_CARRY ) {
          cpu->r0 = (cpu->r0 & HIGH_NIBBLE) |
            ((cpu->r0 + 0x0A) & LOW_NIBBLE);
        }

      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case DAR_1: /* 95 */

      /* See truth table above. */

      if ( cpu->psl != DAR_CHECK ) {

        if ( !CARRY ) {
          *cpu->r1 += 0xA0;
        }

        if ( !ID_CARRY ) {
          *cpu->r1 = (*cpu->r1 & HIGH_NIBBLE) |
            ((*cpu->r1 + 0x0A) & LOW_NIBBLE);
        }
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case DAR_2: /* 96 */

      /* See truth table above. */

      if ( cpu->psl != DAR_CHECK ) {

        if ( !CARRY ) {
          *cpu->r2 += 0xA0;
        }

        if ( !ID_CARRY ) {
          *cpu->r2 = (*cpu->r2 & HIGH_NIBBLE) |
            ((*cpu->r2 + 0x0A) & LOW_NIBBLE);
        }
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case DAR_3: /* 97 */

      /* See truth table above. */

      if ( cpu->psl != DAR_CHECK ) {

        if ( !CARRY ) {
          *cpu->r3 += 0xA0;
        }

        if ( !ID_CARRY ) {
          *cpu->r3 = (*cpu->r3 & HIGH_NIBBLE) |
            ((*cpu->r3 + 0x0A) & LOW_NIBBLE);
        }
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

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
          cpu->iar =
            MEMORY( BRANCH_TO( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
                                                          cpu->rel_off ) ) );

          TWO_CPU_CYCLES;
        } else {
          /* Branch to specified address. */
          cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS( cpu->iar,
                                                          cpu->rel_off ) ) );
        }

      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case ZBRR: /* 9B */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      if ( cpu->dbr & INDIRECT ) {
        cpu->iar = MEMORY( BRANCH_TO( ZERO_BRANCH_INDIRECT( cpu->rel_off ) ) );

        TWO_CPU_CYCLES;
      } else {
        cpu->iar = BRANCH_TO( ZERO_BRANCH( cpu->rel_off ) );
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

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
        if ( cpu->hr & INDIRECT ) {
          cpu->iar = MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS_INDIRECT( cpu->hr,
                                                                  cpu->dbr ) );

          TWO_CPU_CYCLES;
        } else {
          cpu->iar = MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) );
        }
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case BXA: /* 9F */

      /* Get high order address byte into holding register and low order address
         byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /*
        Implicit index register is #3.

        The instruction set manual is not clear about index control in BXA/BSXA
        (cf. p. 49), however, it feels reasonable to assume simple indexing
        (i.e. no auto increment/decrement).
      */
      if ( cpu->hr & INDIRECT ) {
        cpu->iar = MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS_INDIRECT( cpu->hr,
                                                                cpu->dbr )
                           + *cpu->r3 );

        TWO_CPU_CYCLES;
      } else {
        cpu->iar = MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr )
                           + *cpu->r3 );
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


      /*
        The following subtraction op codes all use the SUB() macro defined in
        cpu-2650.h, which is derived from WinArcadias (2650.c) subtract() inline
        function. This also sets all appropriate flags.
      */
    case SUBZ_0: /* A0 */

      SUB( cpu->r0, cpu->r0 );

      TWO_CPU_CYCLES;

      break;


    case SUBZ_1: /* A1 */

      SUB( cpu->r0, *cpu->r1 );

      TWO_CPU_CYCLES;

      break;


    case SUBZ_2: /* A2 */

      SUB( cpu->r0, *cpu->r2 );

      TWO_CPU_CYCLES;

      break;


    case SUBZ_3: /* A3 */

      SUB( cpu->r0, *cpu->r3 );

      TWO_CPU_CYCLES;

      break;


    case SUBI_0: /* A4 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      SUB( cpu->r0, cpu->dbr );

      TWO_CPU_CYCLES;

      break;


    case SUBI_1: /* A5 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      SUB( *cpu->r1, cpu->dbr );

      TWO_CPU_CYCLES;

      break;


    case SUBI_2: /* A6 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      SUB( *cpu->r2, cpu->dbr );

      TWO_CPU_CYCLES;

      break;


    case SUBI_3: /* A7 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      SUB( *cpu->r3, cpu->dbr );

      TWO_CPU_CYCLES;

      break;


    case SUBR_0: /* A8 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Temporarily store second operand for addition and flag checking. */
      if ( cpu->dbr & INDIRECT ) {
        cpu->second_op =
          memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar, cpu->rel_off ) )];

        TWO_CPU_CYCLES;
      } else {
        cpu->second_op = memory[MEMORY( RELATIVE_ADDRESS( cpu->iar,
                                                          cpu->rel_off ) )];
      }

      SUB( cpu->r0, cpu->second_op );

      THREE_CPU_CYCLES;

      break;


    case SUBR_1: /* A9 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Temporarily store second operand for addition and flag checking. */
      if ( cpu->dbr & INDIRECT ) {
        cpu->second_op =
          memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar, cpu->rel_off ) )];

        TWO_CPU_CYCLES;
      } else {
        cpu->second_op = memory[MEMORY( RELATIVE_ADDRESS( cpu->iar,
                                                          cpu->rel_off ) )];
      }

      SUB( *cpu->r1, cpu->second_op );

      THREE_CPU_CYCLES;

      break;


    case SUBR_2: /* AA */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Temporarily store second operand for addition and flag checking. */
      if ( cpu->dbr & INDIRECT ) {
        cpu->second_op =
          memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar, cpu->rel_off ) )];

        TWO_CPU_CYCLES;
      } else {
        cpu->second_op = memory[MEMORY( RELATIVE_ADDRESS( cpu->iar,
                                                          cpu->rel_off ) )];
      }

      SUB( *cpu->r2, cpu->second_op );

      THREE_CPU_CYCLES;

      break;


    case SUBR_3: /* AB */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Temporarily store second operand for addition and flag checking. */
      if ( cpu->dbr & INDIRECT ) {
        cpu->second_op =
          memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar, cpu->rel_off ) )];

        TWO_CPU_CYCLES;
      } else {
        cpu->second_op = memory[MEMORY( RELATIVE_ADDRESS( cpu->iar,
                                                          cpu->rel_off ) )];
      }

      SUB( *cpu->r3, cpu->second_op );

      THREE_CPU_CYCLES;

      break;


    case SUBA_0: /* AC */

      /* Get high order address byte into holding register and low order address
         byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];
      cpu->indexing = cpu->hr & INDEXING;

      /* Get second operand and store it temporarily. */
      if ( cpu->indexing ) {

        /* Increment/decrement index register. */
        if ( cpu->indexing != SIMPLE_INDEXING ) {
          (cpu->indexing == INCREMENT) ? ++cpu->r0 : --cpu->r0;
        }

        if ( cpu->hr & INDIRECT ) {
          cpu->second_op =
            memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT( cpu->r0, cpu->hr,
                                                            cpu->dbr) )];

          TWO_CPU_CYCLES;
        } else {
          cpu->second_op =
            memory[MEMORY( ABSOLUTE_ADDRESS_INDEX( cpu->r0, cpu->hr,
                                                   cpu->dbr ) )];
        }

      } else {

        if ( cpu->hr & INDIRECT ) {
          cpu->second_op =
            memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )];

          TWO_CPU_CYCLES;
        } else {
          cpu->second_op = memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr,
                                                            cpu->dbr ) )];
        }

      }

      SUB( cpu->r0, cpu->second_op );

      FOUR_CPU_CYCLES;

      break;


    case SUBA_1: /* AD */

      /* Get high order address byte into holding register and low order address
         byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];
      cpu->indexing = cpu->hr & INDEXING;

      /* Get second operand through absolute addressing. */
      if ( cpu->indexing ) {

        /* Increment/decrement index register. */
        if ( cpu->indexing != SIMPLE_INDEXING ) {
          (cpu->indexing == INCREMENT) ? ++*cpu->r1 : --*cpu->r1;
        }

        if ( cpu->hr & INDIRECT ) {
          cpu->second_op =
            memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT( *cpu->r1, cpu->hr,
                                                            cpu->dbr) )];

          TWO_CPU_CYCLES;
        } else {
          cpu->second_op =
            memory[MEMORY( ABSOLUTE_ADDRESS_INDEX( *cpu->r1, cpu->hr,
                                                   cpu->dbr ) )];
        }

        /* All indexing operations store result in R0. */
        SUB( cpu->r0, cpu->second_op );

      } else {

        if ( cpu->hr & INDIRECT ) {
          cpu->second_op =
            memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )];

          TWO_CPU_CYCLES;
        } else {
          cpu->second_op = memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr,
                                                            cpu->dbr ) )];
        }

        SUB( *cpu->r1, cpu->second_op );
      }

      FOUR_CPU_CYCLES;

      break;


    case SUBA_2: /* AE */

      /* Get high order address byte into holding register and low order address
         byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];
      cpu->indexing = cpu->hr & INDEXING;

      /* Get second operand through absolute addressing. */
      if ( cpu->indexing ) {

        /* Increment/decrement index register. */
        if ( cpu->indexing != SIMPLE_INDEXING ) {
          (cpu->indexing == INCREMENT) ? ++*cpu->r2 : --*cpu->r2;
        }

        if ( cpu->hr & INDIRECT ) {
          cpu->second_op =
            memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT( *cpu->r2, cpu->hr,
                                                            cpu->dbr) )];

          TWO_CPU_CYCLES;
        } else {
          cpu->second_op =
            memory[MEMORY( ABSOLUTE_ADDRESS_INDEX( *cpu->r2, cpu->hr,
                                                   cpu->dbr ) )];
        }

        /* All indexing operations store result in R0. */
        SUB( cpu->r0, cpu->second_op );

      } else {

        if ( cpu->hr & INDIRECT ) {
          cpu->second_op =
            memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )];

          TWO_CPU_CYCLES;
        } else {
          cpu->second_op = memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr,
                                                            cpu->dbr ) )];
        }

        SUB( *cpu->r2, cpu->second_op );
      }

      FOUR_CPU_CYCLES;

      break;


    case SUBA_3: /* AD */

      /* Get high order address byte into holding register and low order address
         byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];
      cpu->indexing = cpu->hr & INDEXING;

      /* Get second operand through absolute addressing. */
      if ( cpu->indexing ) {

        /* Increment/decrement index register. */
        if ( cpu->indexing != SIMPLE_INDEXING ) {
          (cpu->indexing == INCREMENT) ? ++*cpu->r3 : --*cpu->r3;
        }

        if ( cpu->hr & INDIRECT ) {
          cpu->second_op =
            memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT( *cpu->r3, cpu->hr,
                                                            cpu->dbr) )];

          TWO_CPU_CYCLES;
        } else {
          cpu->second_op =
            memory[MEMORY( ABSOLUTE_ADDRESS_INDEX( *cpu->r3, cpu->hr,
                                                   cpu->dbr ) )];
        }

        /* All indexing operations store result in R0. */
        SUB( cpu->r0, cpu->second_op );

      } else {

        if ( cpu->hr & INDIRECT ) {
          cpu->second_op =
            memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )];

          TWO_CPU_CYCLES;
        } else {
          cpu->second_op = memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr,
                                                            cpu->dbr ) )];
        }

        SUB( *cpu->r3, cpu->second_op );
      }

      FOUR_CPU_CYCLES;

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

      CLEAR_CC;

      if ( (cpu->psu & PSU(cpu->dbr)) < cpu->dbr ) {
        cpu->psl |= CC_LESS;
      }

      THREE_CPU_CYCLES;

      break;


    case TPSL: /* B5 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /*
        Data byte is used to check if selective bits in the PSL are set or not.
        CC Code is set afterwards to indicate if all checks were positive, then
        CC=0 else CC=2.

        It is not clear what the result of CC will be, if tested with 0x00 and
        the current contents of the PSL are 0x00 as well. For now, We assume
        that this would mean a positive test and therefore CC gets cleared in
        this case, too.
      */

      if ( (cpu->psl & cpu->dbr) < cpu->dbr ) {
        CLEAR_CC;
        cpu->psl |=  CC_LESS;
      } else {
        CLEAR_CC;
      }

      THREE_CPU_CYCLES;

      break;


    case BSFR_0: /* B8 */
    case BSFR_1: /* B9 */
    case BSFR_2: /* BA */
      /* Extract CC code from Opcode and scale it to PSL format for
         comparison. */
      cpu->cc = ( cpu->ir & 0x3 ) << 6;

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( cpu->cc != C_CODE ) {
        cpu->rel_off = cpu->dbr & R_OFFSET;

        /* Push return address into stack */
        RAS_PUSH( cpu->iar + 1 );

        /* Indirect or direct addressing? */
        if ( cpu->dbr & INDIRECT ) {
          /* Branch to specified address. */
          cpu->iar =
            MEMORY( BRANCH_TO( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
                                                          cpu->rel_off ) ) );

          TWO_CPU_CYCLES;
        } else {
          /* Branch to specified address. */
          cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS( cpu->iar,
                                                          cpu->rel_off ) ) );
        }

      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case ZBSR: /* BB */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Push return address into stack */
      RAS_PUSH( cpu->iar + 1 );

      if ( cpu->dbr & INDIRECT ) {
        cpu->iar = MEMORY( BRANCH_TO( ZERO_BRANCH_INDIRECT( cpu->rel_off ) ) );

        TWO_CPU_CYCLES;
      } else {
        cpu->iar = BRANCH_TO( ZERO_BRANCH( cpu->rel_off ) );
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case BSFA_0: /* BC */
    case BSFA_1: /* BD */
    case BSFA_2: /* BE */
      /* Extract CC code from Opcode and scale it to PSL format for
         comparison. */
      cpu->cc = ( cpu->ir & 0x3 ) << 6;

      /* Get high order address byte into holding register and low order address
         byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( cpu->cc != C_CODE ) {
        /* Push return address into stack */
        RAS_PUSH( cpu->iar + 1 );

        if ( cpu->hr & INDIRECT ) {
          cpu->iar =
            MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) );

          TWO_CPU_CYCLES;
        } else {
          cpu->iar = MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) );
        }
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case BSXA: /* BF */

      /* Get high order address byte into holding register and low order address
         byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* Push return address into stack */
      RAS_PUSH( cpu->iar + 1 );

      /*
        Implicit index register is #3.

        The instruction set manual is not clear about index control in BXA/BSXA
        (cf. p. 49), however, it feels reasonable to assume simple indexing
        (i.e. no auto increment/decrement).
      */
      if (cpu->hr & INDIRECT) {
        cpu->iar = MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS_INDIRECT( cpu->hr,
                                                                cpu->dbr )
                           + *cpu->r3 );

        TWO_CPU_CYCLES;
      } else {
        cpu->iar = MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr )
                           + *cpu->r3 );
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case NOP: /* C0 */

      ONE_CPU_CYCLE;

      break;


    case STRZ_1: /* C1 */

      /* Set register value. */
      *cpu->r1 = cpu->r0;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( *cpu->r1 );

      TWO_CPU_CYCLES;

      break;


    case STRZ_2: /* C2 */

      /* Set register value. */
      *cpu->r2 = cpu->r0;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( *cpu->r2 );

      TWO_CPU_CYCLES;

      break;


    case STRZ_3: /* C3 */

      /* Set register value. */
      *cpu->r3 = cpu->r0;

      /* Set CC. */
      CLEAR_CC;
      cpu->psl |= CC_REG( *cpu->r3 );

      TWO_CPU_CYCLES;

      break;


      /* Note: There are no 'STRI' operations. Consequently, opcodes C4 to C7 do
         not exist. */


    case STRR_0: /* C8 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Store contents of R0 in memory address calculated from relative
         offset. */
      if ( cpu->dbr & INDIRECT ) {
        memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar, cpu->rel_off ) )]
          = cpu->r0;

        TWO_CPU_CYCLES;
      } else {
        memory[MEMORY(RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )] = cpu->r0;
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case STRR_1: /* C9 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Store contents of R1 in memory address calculated from relative
         offset. */
      if (cpu->dbr & INDIRECT) {
        memory[MEMORY(RELATIVE_ADDRESS_INDIRECT( cpu->iar, cpu->rel_off ) )]
          = *cpu->r1;

        TWO_CPU_CYCLES;
      } else {
        memory[MEMORY(RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )] = *cpu->r1;
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case STRR_2: /* CA */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Store contents of R2 in memory address calculated from relative
         offset. */
      if (cpu->dbr & INDIRECT) {
        memory[MEMORY(RELATIVE_ADDRESS_INDIRECT( cpu->iar, cpu->rel_off ) )]
          = *cpu->r2;

        TWO_CPU_CYCLES;
      } else {
        memory[MEMORY(RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )] = *cpu->r2;
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case STRR_3: /* CB */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* Store contents of R3 in memory address calculated from relative
         offset. */
      if (cpu->dbr & INDIRECT) {
        memory[MEMORY(RELATIVE_ADDRESS_INDIRECT( cpu->iar, cpu->rel_off ) )]
          = *cpu->r3;

        TWO_CPU_CYCLES;
      } else {
        memory[MEMORY(RELATIVE_ADDRESS( cpu->iar, cpu->rel_off ) )] = *cpu->r3;
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

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
          (cpu->indexing == INCREMENT) ? ++cpu->r0 : --cpu->r0;
        }

        if ( cpu->hr & INDIRECT ) {
          memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT( cpu->r0, cpu->hr,
                                                          cpu->dbr) )]
            = cpu->r0;

          TWO_CPU_CYCLES;
        } else {
          memory[MEMORY( ABSOLUTE_ADDRESS_INDEX( cpu->r0, cpu->hr, cpu->dbr ) )]
            = cpu->r0;
        }

      } else {
        if ( cpu->hr & INDIRECT ) {
          memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )]
            = cpu->r0;

          TWO_CPU_CYCLES;
        } else {
          memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )] = cpu->r0;
        }
      }

      /* No setting of CC required. */

      FOUR_CPU_CYCLES;

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
          (cpu->indexing == INCREMENT) ? ++*cpu->r1 : --*cpu->r1;
        }

        /* Store contents of R0 into memory location specified by absolute
           address + index in R1. */
        if ( cpu->hr & INDIRECT ) {
          memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT( *cpu->r1, cpu->hr,
                                                          cpu->dbr) )]
            = cpu->r0;

          TWO_CPU_CYCLES;
        } else {
          memory[MEMORY( ABSOLUTE_ADDRESS_INDEX( *cpu->r1, cpu->hr,
                                                 cpu->dbr ) )] = cpu->r0;
        }

      } else {
        /* Store contents of R1 into memory location specified by absolute
           address. */
        if ( cpu->hr & INDIRECT ) {
          memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )]
            = *cpu->r1;

          TWO_CPU_CYCLES;
        } else {
          memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )] = *cpu->r1;
        }
      }

      /* No setting of CC required. */

      FOUR_CPU_CYCLES;

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
          (cpu->indexing == INCREMENT) ? ++*cpu->r2 : --*cpu->r2;
        }

        /* Store contents of R0 into memory location specified by absolute
           address + index in R2. */
        if ( cpu->hr & INDIRECT ) {
          memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT( *cpu->r2, cpu->hr,
                                                          cpu->dbr) )]
            = cpu->r0;

          TWO_CPU_CYCLES;
        } else {
          memory[MEMORY( ABSOLUTE_ADDRESS_INDEX( *cpu->r2, cpu->hr,
                                                 cpu->dbr ) )] = cpu->r0;
        }

      } else {
        /* Store contents of R2 into memory location specified by absolute
           address. */
        if ( cpu->hr & INDIRECT ) {
          memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )]
            = *cpu->r2;

          TWO_CPU_CYCLES;
        } else {
          memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )] = *cpu->r2;
        }
      }

      /* No setting of CC required. */

      FOUR_CPU_CYCLES;

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
          (cpu->indexing == INCREMENT) ? ++*cpu->r3 : --*cpu->r3;
        }

        /* Store contents of R0 into memory location specified by absolute
           address + index in R3. */
        if ( cpu->hr & INDIRECT ) {
          memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT( *cpu->r3, cpu->hr,
                                                          cpu->dbr) )]
            = cpu->r0;

          TWO_CPU_CYCLES;
        } else {
          memory[MEMORY( ABSOLUTE_ADDRESS_INDEX( *cpu->r3, cpu->hr,
                                                 cpu->dbr ) )] = cpu->r0;
        }

      } else {
        /* Store contents of R3 into memory location specified by absolute
           address. */
        if ( cpu->hr & INDIRECT ) {
          memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )]
            = *cpu->r3;

          TWO_CPU_CYCLES;
        } else {
          memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )] = *cpu->r3;
        }
      }

      /* No setting of CC required. */

      FOUR_CPU_CYCLES;

      break;


    case RRL_0: /* D0 */

      ROTATE_LEFT( cpu->r0 );

      TWO_CPU_CYCLES;

      break;


    case RRL_1: /* D1 */

      ROTATE_LEFT( *cpu->r1 );

      TWO_CPU_CYCLES;

      break;


    case RRL_2: /* D2 */

      ROTATE_LEFT( *cpu->r2 );

      TWO_CPU_CYCLES;

      break;


    case RRL_3: /* D3 */

      ROTATE_LEFT( *cpu->r3 );

      TWO_CPU_CYCLES;

      break;


    case BIRR_0: /* D8 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( ++cpu->r0 ) {
        cpu->rel_off = cpu->dbr & R_OFFSET;

        /* Indirect or direct addressing? */
        if ( cpu->dbr & INDIRECT ) {
          /* Branch to specified address. */
          cpu->iar =
            MEMORY( BRANCH_TO( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
                                                          cpu->rel_off ) ) );

          TWO_CPU_CYCLES;
        } else {
          /* Branch to specified address. */
          cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS( cpu->iar,
                                                          cpu->rel_off ) ) );
        }
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case BIRR_1: /* D9 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( ++*cpu->r1 ) {
        cpu->rel_off = cpu->dbr & R_OFFSET;

        /* Indirect or direct addressing? */
        if ( cpu->dbr & INDIRECT ) {
          /* Branch to specified address. */
          cpu->iar =
            MEMORY( BRANCH_TO( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
                                                          cpu->rel_off ) ) );

          TWO_CPU_CYCLES;
        } else {
          /* Branch to specified address. */
          cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS( cpu->iar,
                                                          cpu->rel_off ) ) );
        }
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case BIRR_2: /* DA */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( ++*cpu->r2 ) {
        cpu->rel_off = cpu->dbr & R_OFFSET;

        /* Indirect or direct addressing? */
        if ( cpu->dbr & INDIRECT ) {
          /* Branch to specified address. */
          cpu->iar =
            MEMORY( BRANCH_TO( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
                                                          cpu->rel_off ) ) );

          TWO_CPU_CYCLES;
        } else {
          /* Branch to specified address. */
          cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS( cpu->iar,
                                                          cpu->rel_off ) ) );
        }
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case BIRR_3: /* DB */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( ++*cpu->r3 ) {
        cpu->rel_off = cpu->dbr & R_OFFSET;

        /* Indirect or direct addressing? */
        if ( cpu->dbr & INDIRECT ) {
          /* Branch to specified address. */
          cpu->iar =
            MEMORY( BRANCH_TO( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
                                                          cpu->rel_off ) ) );

          TWO_CPU_CYCLES;
        } else {
          /* Branch to specified address. */
          cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS( cpu->iar,
                                                          cpu->rel_off ) ) );
        }
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case BIRA_0: /* DC */

      /* Get high order address byte into holding register and low order address
         byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( ++cpu->r0 ) {
        if (cpu->hr & INDIRECT) {
          cpu->iar =
            MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) );

          TWO_CPU_CYCLES;
        } else {
          cpu->iar = MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) );
        }
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case BIRA_1: /* DD */

      /* Get high order address byte into holding register and low order address
         byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( ++*cpu->r1 ) {
        if (cpu->hr & INDIRECT) {
          cpu->iar =
            MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) );

          TWO_CPU_CYCLES;
        } else {
          cpu->iar = MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) );
        }
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case BIRA_2: /* DE */

      /* Get high order address byte into holding register and low order address
         byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( ++*cpu->r2 ) {
        if (cpu->hr & INDIRECT) {
          cpu->iar =
            MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) );

          TWO_CPU_CYCLES;
        } else {
          cpu->iar = MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) );
        }
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case BIRA_3: /* DF */

      /* Get high order address byte into holding register and low order address
         byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( ++*cpu->r3 ) {
        if (cpu->hr & INDIRECT) {
          cpu->iar =
            MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) );

          TWO_CPU_CYCLES;
        } else {
          cpu->iar = MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) );
        }
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case COMZ_0: /* E0 */

      /* Set CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_COM( cpu->r0, cpu->r0 );

      TWO_CPU_CYCLES;

      break;


    case COMZ_1: /* E1 */

      /* Set CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_COM( cpu->r0, *cpu->r1 );

      TWO_CPU_CYCLES;

      break;


    case COMZ_2: /* E2 */

      /* Set CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_COM( cpu->r0, *cpu->r2 );

      TWO_CPU_CYCLES;

      break;


    case COMZ_3: /* E3 */

      /* Set CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_COM( cpu->r0, *cpu->r3 );

      TWO_CPU_CYCLES;

      break;


    case COMI_0: /* E4 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* SET CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_COM( cpu->r0, cpu->dbr );

      TWO_CPU_CYCLES;

      break;


    case COMI_1: /* E5 */

      /* Get next byte from memory into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* SET CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_COM( *cpu->r1, cpu->dbr );

      TWO_CPU_CYCLES;

      break;


    case COMI_2: /* E6 */

      /* Get next byte from memory into Data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* SET CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_COM( *cpu->r2, cpu->dbr );

      TWO_CPU_CYCLES;

      break;


    case COMI_3: /* E7 */

      /* Get next byte from memory into Data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* SET CC flags. */
      CLEAR_CC;
      cpu->psl |= CC_COM( *cpu->r3, cpu->dbr );

      TWO_CPU_CYCLES;

      break;


    case COMR_0: /* E8 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];
      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* SET CC flags. */
      CLEAR_CC;

      if ( cpu->dbr & INDIRECT ) {
        cpu->psl |= CC_COM( cpu->r0,
                   memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
                                                             cpu->rel_off ) )]);

        TWO_CPU_CYCLES;
      } else {
        cpu->psl |= CC_COM( cpu->r0,
                            memory[MEMORY( RELATIVE_ADDRESS( cpu->iar,
                                                             cpu->rel_off ) )]);
      }

      THREE_CPU_CYCLES;

      break;


    case COMR_1: /* E9 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];
      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* SET CC flags. */
      CLEAR_CC;

      if ( cpu->dbr & INDIRECT ) {
        cpu->psl |= CC_COM( *cpu->r1,
                   memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
                                                             cpu->rel_off ) )]);

        TWO_CPU_CYCLES;
      } else {
        cpu->psl |= CC_COM( *cpu->r1,
                            memory[MEMORY( RELATIVE_ADDRESS( cpu->iar,
                                                             cpu->rel_off ) )]);
      }

      THREE_CPU_CYCLES;

      break;


    case COMR_2: /* EA */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];
      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* SET CC flags. */
      CLEAR_CC;

      if ( cpu->dbr & INDIRECT ) {
        cpu->psl |= CC_COM( *cpu->r2,
                   memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
                                                             cpu->rel_off ) )]);

        TWO_CPU_CYCLES;
      } else {
        cpu->psl |= CC_COM( *cpu->r2,
                            memory[MEMORY( RELATIVE_ADDRESS( cpu->iar,
                                                             cpu->rel_off ) )]);
      }

      THREE_CPU_CYCLES;

      break;


    case COMR_3: /* EB */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];
      cpu->rel_off = cpu->dbr & R_OFFSET;

      /* SET CC flags. */
      CLEAR_CC;

      if ( cpu->dbr & INDIRECT ) {
        cpu->psl |= CC_COM( *cpu->r3,
                   memory[MEMORY( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
                                                             cpu->rel_off ) )]);

        TWO_CPU_CYCLES;
      } else {
        cpu->psl |= CC_COM( *cpu->r3,
                            memory[MEMORY( RELATIVE_ADDRESS( cpu->iar,
                                                             cpu->rel_off ) )]);
      }

      THREE_CPU_CYCLES;

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
          (cpu->indexing == INCREMENT) ? ++cpu->r0 : --cpu->r0;
        }

        cpu->psl |= CC_COM( cpu->r0, (cpu->hr & INDIRECT) ?
               memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT( cpu->r0, cpu->hr,
                                                               cpu->dbr ) )] :
               memory[MEMORY( ABSOLUTE_ADDRESS_INDEX( cpu->r0, cpu->hr,
                                                      cpu->dbr ) )] );
      } else {
        cpu->psl |= CC_COM( cpu->r0, ( cpu->hr & INDIRECT ) ?
              memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )] :
              memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )] );
      }

      FOUR_CPU_CYCLES;

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
          (cpu->indexing == INCREMENT) ? ++*cpu->r1 : --*cpu->r1;
        }

        if (cpu->hr & INDIRECT) {
          cpu->psl |= CC_COM( cpu->r0,
              memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT( *cpu->r1, cpu->hr,
                                                              cpu->dbr ) )] );

          TWO_CPU_CYCLES;
        } else {
          cpu->psl |= CC_COM( cpu->r0,
                       memory[MEMORY( ABSOLUTE_ADDRESS_INDEX( *cpu->r1, cpu->hr,
                                                              cpu->dbr ) )] );
        }

      } else {
        if (cpu->hr & INDIRECT) {
          cpu->psl |= CC_COM( *cpu->r1,
             memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )] );

          TWO_CPU_CYCLES;
        } else {
          cpu->psl |= CC_COM( *cpu->r1,
                              memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr,
                                                               cpu->dbr ) )] );
        }
      }

      FOUR_CPU_CYCLES;

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
          (cpu->indexing == INCREMENT) ? ++*cpu->r2 : --*cpu->r2;
        }

        if (cpu->hr & INDIRECT) {
          cpu->psl |= CC_COM( cpu->r0,
              memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT( *cpu->r2, cpu->hr,
                                                              cpu->dbr ) )] );

          TWO_CPU_CYCLES;
        } else {
          cpu->psl |= CC_COM( cpu->r0,
                       memory[MEMORY( ABSOLUTE_ADDRESS_INDEX( *cpu->r2, cpu->hr,
                                                              cpu->dbr ) )] );
        }

      } else {
        if (cpu->hr & INDIRECT) {
          cpu->psl |= CC_COM( *cpu->r2,
             memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )] );

          TWO_CPU_CYCLES;
        } else {
          cpu->psl |= CC_COM( *cpu->r2,
                              memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr,
                                                               cpu->dbr ) )] );
        }
      }

      FOUR_CPU_CYCLES;

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
          (cpu->indexing == INCREMENT) ? ++*cpu->r3 : --*cpu->r3;
        }

        if (cpu->hr & INDIRECT) {
          cpu->psl |= CC_COM( cpu->r0,
              memory[MEMORY( ABSOLUTE_ADDRESS_INDEX_INDIRECT( *cpu->r3, cpu->hr,
                                                              cpu->dbr ) )] );

          TWO_CPU_CYCLES;
        } else {
          cpu->psl |= CC_COM( cpu->r0,
                       memory[MEMORY( ABSOLUTE_ADDRESS_INDEX( *cpu->r3, cpu->hr,
                                                              cpu->dbr ) )] );
        }

      } else {
        if (cpu->hr & INDIRECT) {
          cpu->psl |= CC_COM( *cpu->r3,
             memory[MEMORY( ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) )] );

          TWO_CPU_CYCLES;
        } else {
          cpu->psl |= CC_COM( *cpu->r3,
                      memory[MEMORY( ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) )] );
        }
      }

      FOUR_CPU_CYCLES;

      break;


    case TMI_0: /* F4 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* Set CC flags. */
      CLEAR_CC;

      if ( (cpu->r0 & cpu->dbr) < cpu->dbr ) {
        cpu->psl |= CC_LESS;
      }

      THREE_CPU_CYCLES;

      break;


    case TMI_1: /* F5 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* Set CC flags. */
      CLEAR_CC;

      if ( (*cpu->r1 & cpu->dbr) < cpu->dbr ) {
        cpu->psl |= CC_LESS;
      }

      THREE_CPU_CYCLES;

      break;


    case TMI_2: /* F6 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* Set CC flags. */
      CLEAR_CC;

      if ( (*cpu->r2 & cpu->dbr) < cpu->dbr ) {
        cpu->psl |= CC_LESS;
      }

      THREE_CPU_CYCLES;

      break;


    case TMI_3: /* F7 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      /* Set CC flags. */
      CLEAR_CC;

      if ( (*cpu->r3 & cpu->dbr) < cpu->dbr ) {
        cpu->psl |= CC_LESS;
      }

      THREE_CPU_CYCLES;

      break;


    case BDRR_0: /* F8 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( --cpu->r0 ) {
        cpu->rel_off = cpu->dbr & R_OFFSET;

        /* Indirect or direct addressing? */
        if ( cpu->dbr & INDIRECT ) {
          /* Branch to specified address. */
          cpu->iar =
            MEMORY( BRANCH_TO( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
                                                          cpu->rel_off ) ) );

          TWO_CPU_CYCLES;
        } else {
          /* Branch to specified address. */
          cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS( cpu->iar,
                                                          cpu->rel_off ) ) );
        }
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case BDRR_1: /* F9 */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( --*cpu->r1 ) {
        cpu->rel_off = cpu->dbr & R_OFFSET;

        /* Indirect or direct addressing? */
        if ( cpu->dbr & INDIRECT ) {
          /* Branch to specified address. */
          cpu->iar =
            MEMORY( BRANCH_TO( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
                                                          cpu->rel_off ) ) );

          TWO_CPU_CYCLES;
        } else {
          /* Branch to specified address. */
          cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS( cpu->iar,
                                                          cpu->rel_off ) ) );
        }
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case BDRR_2: /* FA */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( --*cpu->r2 ) {
        cpu->rel_off = cpu->dbr & R_OFFSET;

        /* Indirect or direct addressing? */
        if ( cpu->dbr & INDIRECT ) {
          /* Branch to specified address. */
          cpu->iar =
            MEMORY( BRANCH_TO( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
                                                          cpu->rel_off ) ) );

          TWO_CPU_CYCLES;
        } else {
          /* Branch to specified address. */
          cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS( cpu->iar,
                                                          cpu->rel_off ) ) );
        }
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case BDRR_3: /* FB */

      /* Get next memory byte into data bus register. */
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( --*cpu->r3 ) {
        cpu->rel_off = cpu->dbr & R_OFFSET;

        /* Indirect or direct addressing? */
        if ( cpu->dbr & INDIRECT ) {
          /* Branch to specified address. */
          cpu->iar =
            MEMORY( BRANCH_TO( RELATIVE_ADDRESS_INDIRECT( cpu->iar,
                                                          cpu->rel_off ) ) );

          TWO_CPU_CYCLES;
        } else {
          /* Branch to specified address. */
          cpu->iar = MEMORY( BRANCH_TO( RELATIVE_ADDRESS( cpu->iar,
                                                          cpu->rel_off ) ) );
        }
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case BDRA_0: /* FC */

      /* Get high order address byte into holding register and low order address
         byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( --cpu->r0 ) {
        if ( cpu->hr & INDIRECT ) {
          cpu->iar =
            MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) );

          TWO_CPU_CYCLES;
        } else {
          cpu->iar = MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) );
        }
      }

      THREE_CPU_CYCLES;

      break;


    case BDRA_1: /* FD */

      /* Get high order address byte into holding register and low order address
         byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( --*cpu->r1 ) {
        if ( cpu->hr & INDIRECT ) {
          cpu->iar =
            MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) );

          TWO_CPU_CYCLES;
        } else {
          cpu->iar = MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) );
        }
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case BDRA_2: /* FE */

      /* Get high order address byte into holding register and low order address
         byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( --*cpu->r2 ) {
        if ( cpu->hr & INDIRECT ) {
          cpu->iar =
            MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) );

          TWO_CPU_CYCLES;
        } else {
          cpu->iar = MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) );
        }
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    case BDRA_3: /* FF */

      /* Get high order address byte into holding register and low order address
         byte into data bus register. */
      cpu->hr = memory[MEMORY( ++cpu->iar )];
      cpu->dbr = memory[MEMORY( ++cpu->iar )];

      if ( --*cpu->r3 ) {
        if ( cpu->hr & INDIRECT ) {
          cpu->iar =
            MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS_INDIRECT( cpu->hr, cpu->dbr ) );

          TWO_CPU_CYCLES;
        } else {
          cpu->iar = MEMORY( BRANCH_TO_ABSOLUTE_ADDRESS( cpu->hr, cpu->dbr ) );
        }
      }

      /* No setting of CC required. */

      THREE_CPU_CYCLES;

      break;


    default:

      cpu->error = 2;

    }

    ++cpu->iar;
  }

  return cycle_count;
}
