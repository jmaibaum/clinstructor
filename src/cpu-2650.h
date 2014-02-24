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

#ifndef CPU_2650_H
#define CPU_2650_H

/* The compiler (or the operating system's memory management on Mac OSX) seems
   to allocate some more bytes than specified in main.c (probably due to machine
   word boundaries?!). So the program does not throw an error, if memory a
   little above 0x7FFF gets adressed (like 0x8000 or 0x8001). Therefore, all
   memory access should only be through the following macro, GET_MEMORY(), which
   wraps addresses > 0x7FFF around. Feels a little hacky, but I have not come to
   a better solution, yet. */
#define MEMORY( address ) ( ( address ) % 0x8000 )


/* Enums, Definitions, and Macros for managing the PSW. */
typedef enum PSU_Masks {

  /* 
     Program Status Upper:
     |-----------------------------------------------|
     |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
     |-----------------------------------------------|
     |  S  |  F  |  II |  -  |  -  | SP2 | SP1 | SP0 |
     |-----------------------------------------------|
  */

  PSU_SP = 0x07, /* Stack pointer (3 least significant bits) */
  PSU_II = 0x20, /* Interrupt inhibit */
  PSU_F  = 0x40, /* Flag */
  PSU_S  = 0x80  /* Sense */
} PSU_Masks;

typedef enum PSL_Masks {

  /* 
     Program Status Lower:
     |-----------------------------------------------|
     |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
     |-----------------------------------------------|
     | CC1 | CC0 | IDC |  RS |  WC | OVF | COM |  C  |
     |-----------------------------------------------|
  */

  PSL_C   = 0x01, /* Carry/borrow */
  PSL_COM = 0x02, /* Logical/arithmetical compare */
  PSL_OVF = 0x04, /* Overflow */
  PSL_WC  = 0x08, /* With/without carry */
  PSL_RS  = 0x10, /* Register bank select */
  PSL_IDC = 0x20, /* Interdigit carry */
  PSL_CC  = 0xC0  /* Condition code (2 most significant bits) */
} PSL_Masks;

typedef enum CC_VALS {
  CC_ZERO     = 0x00,
  CC_POSITIVE = 0x40,
  CC_NEGATIVE = 0x80,
  CC_EQUAL    = 0x00,
  CC_GREATER  = 0x40,
  CC_LESS     = 0x80
} CC_VALS;

/* Macros to get a single flag value. */
#define STACK_POINTER ( cpu->psu & PSU_SP )
#define IR_INHIBIT    ( cpu->psu & PSU_II )
#define FLAG          ( cpu->psu & PSU_F )
#define SENSE         ( cpu->psu & PSU_S )

#define CARRY         ( cpu->psl & PSL_C )
#define COMPARE       ( cpu->psl & PSL_COM )
#define OVERFLOW      ( cpu->psl & PSL_OVF )
#define WITH_CARRY    ( cpu->psl & PSL_WC )
#define REGISTER_BANK ( cpu->psl & PSL_RS )
#define ID_CARRY      ( cpu->psl & PSL_IDC )
#define C_CODE        ( cpu->psl & PSL_CC )

/* Clear CC. This has to be done in advance to any CC manipulation. */
#define CLEAR_CC ( cpu->psl &= ~PSL_CC )

/* Decide if a value should be interpreted logically or arithmetically. */
#define LOG_OR_ARI( value )			\
  ( COMPARE ? (value) : (signed char) (value) )

/* Get the correct value for CC after any instruction that affects a
   register. */
#define CC_REG( data_byte )				\
  ( ( (data_byte) != CC_ZERO )				\
    ? ( ( (data_byte) < CC_NEGATIVE )			\
	? CC_POSITIVE : CC_NEGATIVE ) : CC_ZERO )

/* Get the correct value for CC after a compare instruction. */
#define CC_COM( first_byte, second_byte )			\
  (first_byte) != (second_byte) ?				\
    ( LOG_OR_ARI(first_byte) < LOG_OR_ARI(second_byte) ?	\
      CC_LESS : CC_GREATER ) : CC_EQUAL


/* Typedef for Address Mode Masking */
typedef enum AddressMasks {
  INDIRECT = 0x80,
  R_OFFSET = 0x7F,
  I_HIGH_B = 0x7F, /* Indirect high byte is only lower 7 bits. */
  INDEXING = 0x60, /* Indexing mode. */
  A_HIGH_N = 0x1F, /* High order address "byte" in "normal" instructions. */
  A_HIGH_B = 0x7F  /* High order address "byte" in branch instructions. */
} AddressMasks;

/* Macros for relative indexing. */

/* Get 7 bit long two's complement for ofsetting relative addressing. */
#define RELATIVE_OFFSET( offset )		\
  ( (signed char) ( (offset) << 1 ) >> 1 )

/* Compute Address for relative addressing. */
#define RELATIVE_ADDRESS( iar, off )		\
  ( ( (iar) + 1 ) + RELATIVE_OFFSET(off) )

/* Compute Address for indirect relative addressing. */
#define RELATIVE_ADDRESS_INDIRECT( iar, off )				\
  ( ( ( memory[MEMORY( ( (iar) + 1 ) +					\
		       RELATIVE_OFFSET(off) )] << 8 ) & I_HIGH_B) +	\
    memory[MEMORY( ( (iar) + 2 ) + RELATIVE_OFFSET(off) )] )

/* In a branch instruction, the above macros would point one memory address too
   far, therefore, we have to subtract one. */
#define BRANCH_TO( too_far )			\
  ( (too_far) - 1 )

/* Macros for absolute addressing. */

typedef enum IndexingModes {
  NO_INDEXING     = 0x00,
  INCREMENT       = 0x20,
  DECREMENT       = 0x40,
  SIMPLE_INDEXING = 0x60
} IndexingModes;

#define ABSOLUTE_ADDRESS( high, low )		\
  ( ( ( (high) & A_HIGH_N ) << 8 ) + (low) )

#define ABSOLUTE_ADDRESS_INDIRECT( hpart, lpart )                              \
  ( ( ( memory[MEMORY( ABSOLUTE_ADDRESS(hpart, lpart) )] << 8 ) & I_HIGH_B ) + \
    memory[MEMORY( ABSOLUTE_ADDRESS(hpart, (lpart) + 1) )] )

#define ABSOLUTE_ADDRESS_INDEX( index, hpart, lpart )	\
  ( ABSOLUTE_ADDRESS( hpart, lpart ) + (index) )

#define ABSOLUTE_ADDRESS_INDEX_INDIRECT( index, hbyte, lbyte )	\
  ( ABSOLUTE_ADDRESS_INDIRECT( hbyte, lbyte ) + (index) )


/* Typedef for all the 2650's opcodes. */
typedef enum Opcodes {
  /* Load register zero. */
  LODZ_0 = 0x00, /* Officially, this is illegal, but it does work. */
  LODZ_1 = 0x01,
  LODZ_2 = 0x02,
  LODZ_3 = 0x03,

  /* Load register, immediate. */
  LODI_0 = 0x04,
  LODI_1 = 0x05,
  LODI_2 = 0x06,
  LODI_3 = 0x07,

  /* Load register, relative. */
  LODR_0 = 0x08,
  LODR_1 = 0x09,
  LODR_2 = 0x0A,
  LODR_3 = 0x0B,

  /* Load register, absolute. */
  LODA_0 = 0x0C,
  LODA_1 = 0x0D,
  LODA_2 = 0x0E,
  LODA_3 = 0x0F,

  /* Store Program Status Upper/Lower. */
  /* 0x10 is illegal. */
  /* 0x11 is illegal. */
  SPSU   = 0x12,
  SPSL   = 0x13,

  /* Return from subroutine, conditional. */
  RETC_0 = 0x14,
  RETC_1 = 0x15,
  RETC_2 = 0x16,
  RETC_3 = 0x17,

  /* Branch on condition true, realtive. */
  BCTR_0 = 0x18,
  BCTR_1 = 0x19,
  BCTR_2 = 0x1A,
  BCTR_3 = 0x1B,

  /* Branch on condition true, absolute. */
  BCTA_0 = 0x1C,
  BCTA_1 = 0x1D,
  BCTA_2 = 0x1E,
  BCTA_3 = 0x1F,

  /* Exclusive-OR to register zero. */
  EORZ_0 = 0x20,
  EORZ_1 = 0x21,
  EORZ_2 = 0x22,
  EORZ_3 = 0x23,

  /* Exclusive-OR, immediate. */
  EORI_0 = 0x24,
  EORI_1 = 0x25,
  EORI_2 = 0x26,
  EORI_3 = 0x27,

  /* Exclusive-OR, relative. */
  EORR_0 = 0x28,
  EORR_1 = 0x29,
  EORR_2 = 0x2A,
  EORR_3 = 0x2B,

  /* Exclusive-OR, absolute. */
  EORA_0 = 0x2C,
  EORA_1 = 0x2D,
  EORA_2 = 0x2E,
  EORA_3 = 0x2F,

  /* Read control. */
  REDC_0 = 0x30,
  REDC_1 = 0x31,
  REDC_2 = 0x32,
  REDC_3 = 0x33,

  /* Return from subroutine and enable interrupt, conditional. */
  RETE_0 = 0x34,
  RETE_1 = 0x35,
  RETE_2 = 0x36,
  RETE_3 = 0x37,

  /* Branch to subroutine on condition true, relative. */
  BSTR_0 = 0x38,
  BSTR_1 = 0x39,
  BSTR_2 = 0x3A,
  BSTR_3 = 0x3B,

  /* Branch to subroutine on contition true, absolute. */
  BSTA_0 = 0x3C,
  BSTA_1 = 0x3D,
  BSTA_2 = 0x3E,
  BSTA_3 = 0x3F,

  /* AND to register zero. */
  HALT   = 0x40, /* Halt, enter wait state. */
  ANDZ_1 = 0x41,
  ANDZ_2 = 0x42,
  ANDZ_3 = 0x43,

  /* AND immediate. */
  ANDI_0 = 0x44,
  ANDI_1 = 0x45,
  ANDI_2 = 0x46,
  ANDI_3 = 0x47,

  /* AND relative. */
  ANDR_0 = 0x48,
  ANDR_1 = 0x49,
  ANDR_2 = 0x4A,
  ANDR_3 = 0x4B,

  /* AND absolute. */
  ANDA_0 = 0x4C,
  ANDA_1 = 0x4D,
  ANDA_2 = 0x4E,
  ANDA_3 = 0x4F,

  /* Rotate register right w/wo carry. */
  RRR_0  = 0x50,
  RRR_1  = 0x51,
  RRR_2  = 0x52,
  RRR_3  = 0x53,

  /* Read extended. */
  REDE_0 = 0x54,
  REDE_1 = 0x55,
  REDE_2 = 0x56,
  REDE_3 = 0x57,

  /* Branch on register non-zero, relative. */
  BRNR_0 = 0x58,
  BRNR_1 = 0x59,
  BRNR_2 = 0x5A,
  BRNR_3 = 0x5B,

  /* Branch on register non-zero, absolute. */
  BRNA_0 = 0x5C,
  BRNA_1 = 0x5D,
  BRNA_2 = 0x5E,
  BRNA_3 = 0x5F,

  /* Inclusive-OR to register zero. */
  IORZ_0 = 0x60,
  IORZ_1 = 0x61,
  IORZ_2 = 0x62,
  IORZ_3 = 0x63,

  /* Inclusive-OR, immediate. */
  IORI_0 = 0x64,
  IORI_1 = 0x65,
  IORI_2 = 0x66,
  IORI_3 = 0x67,

  /* Inclusive-OR, relative. */
  IORR_0 = 0x68,
  IORR_1 = 0x69,
  IORR_2 = 0x6A,
  IORR_3 = 0x6B,

  /* Inclusive-OR, absolute. */
  IORA_0 = 0x6C,
  IORA_1 = 0x6D,
  IORA_2 = 0x6E,
  IORA_3 = 0x6F,

  /* Read data. */
  REDD_0 = 0x70,
  REDD_1 = 0x71,
  REDD_2 = 0x72,
  REDD_3 = 0x73,

  /* Clear/Preset Program Status Upper/Lower, masked. */
  CPSU   = 0x74,
  CPSL   = 0x75,
  PPSU   = 0x76,
  PPSL   = 0x77,

  /* Branch to subroutine on non-zero register, relative. */
  BSNR_0 = 0x78,
  BSNR_1 = 0x79,
  BSNR_2 = 0x7A,
  BSNR_3 = 0x7B,

  /* Branch to subroutine on non-zero register, absolute. */
  BSNA_0 = 0x7C,
  BSNA_1 = 0x7D,
  BSNA_2 = 0x7E,
  BSNA_3 = 0x7F,

  /* ADD to register zero w/wo carry. */
  ADDZ_0 = 0x80,
  ADDZ_1 = 0x81,
  ADDZ_2 = 0x82,
  ADDZ_3 = 0x83,

  /* ADD immediate w/wo carry. */
  ADDI_0 = 0x84,
  ADDI_1 = 0x85,
  ADDI_2 = 0x86,
  ADDI_3 = 0x87,

  /* ADD relative w/wo carry. */
  ADDR_0 = 0x88,
  ADDR_1 = 0x89,
  ADDR_2 = 0x8A,
  ADDR_3 = 0x8B,

  /* ADD absolute w/wo carry. */
  ADDA_0 = 0x8C,
  ADDA_1 = 0x8D,
  ADDA_2 = 0x8E,
  ADDA_3 = 0x8F,

  /* Load Program Status Upper/Lower. */
  /* 0x90 is illegal. */
  /* 0x91 is illegal. */
  LPSU   = 0x92,
  LPSL   = 0x93,

  /* Decimal adjust register. */
  DAR_0  = 0x94,
  DAR_1  = 0x95,
  DAR_2  = 0x96,
  DAR_3  = 0x97,

  /* Branch on condition false, relative. */
  BCFR_0 = 0x98,
  BCFR_1 = 0x99,
  BCFR_2 = 0x9A,
  ZBRR   = 0x9B, /* Zero branch relative, unconditional. */

  /* Branch on condition false, absolute. */
  BCFA_0 = 0x9C,
  BCFA_1 = 0x9D,
  BCFA_2 = 0x9E,
  BXA    = 0x9F, /* Branch indexed absolute, unconditional. */

  /* Subtract from register zero w/wo borrow. */
  SUBZ_0 = 0xA0,
  SUBZ_1 = 0xA1,
  SUBZ_2 = 0xA2,
  SUBZ_3 = 0xA3,

  /* Subtract immediate w/wo borrow. */
  SUBI_0 = 0xA4,
  SUBI_1 = 0xA5,
  SUBI_2 = 0xA6,
  SUBI_3 = 0xA7,

  /* Subtract relative w/wo borrow. */
  SUBR_0 = 0xA8,
  SUBR_1 = 0xA9,
  SUBR_2 = 0xAA,
  SUBR_3 = 0xAB,

  /* Subtract absolute w/wo borrow. */
  SUBA_0 = 0xAC,
  SUBA_1 = 0xAD,
  SUBA_2 = 0xAE,
  SUBA_3 = 0xAF,

  /* Write control. */
  WRTC_0 = 0xB0,
  WRTC_1 = 0xB1,
  WRTC_2 = 0xB2,
  WRTC_3 = 0xB3,

  /* Test Program Status Upper/Lower. */
  TPSU   = 0xB4,
  TPSL   = 0xB5,
  /* 0xB6 is illegal. */
  /* 0xB7 is illegal. */

  /* Branch to subroutine on condition false, relative. */
  BSFR_0 = 0xB8,
  BSFR_1 = 0xB9,
  BSFR_2 = 0xBA,
  ZBSR   = 0xBB, /* Zero branch to subroutine relative, unconditional. */

  /* Branch to subroutine on condition false, absolute. */
  BSFA_0 = 0xBC,
  BSFA_1 = 0xBD,
  BSFA_2 = 0xBE,
  BSXA   = 0xBF, /* Branch to subroutine, indexed, absolute, unconditional. */

  /* Store register zero. */
  NOP    = 0xC0, /* No operation. */
  STRZ_1 = 0xC1,
  STRZ_2 = 0xC2,
  STRZ_3 = 0xC3,

  /* Store immediate is not implemented. */
  /* 0xC4 is illegal. */
  /* 0xC5 is illegal. */
  /* 0xC6 is illegal. */
  /* 0xC7 is illegal. */

  /* Store relative. */
  STRR_0 = 0xC8,
  STRR_1 = 0xC9,
  STRR_2 = 0xCA,
  STRR_3 = 0xCB,

  /* Store absolute. */
  STRA_0 = 0xCC,
  STRA_1 = 0xCD,
  STRA_2 = 0xCE,
  STRA_3 = 0xCF,

  /* Rotate register left w/wo carry. */
  RRL_0  = 0xD0,
  RRL_1  = 0xD1,
  RRL_2  = 0xD2,
  RRL_3  = 0xD3,

  /* Write extended. */
  WRTE_0 = 0xD4,
  WRTE_1 = 0xD5,
  WRTE_2 = 0xD6,
  WRTE_3 = 0xD7,

  /* Branch on incrementing register, relative. */
  BIRR_0 = 0xD8,
  BIRR_1 = 0xD9,
  BIRR_2 = 0xDA,
  BIRR_3 = 0xDB,

  /* Branch on incrementing register, absolute. */
  BIRA_0 = 0xDC,
  BIRA_1 = 0xDD,
  BIRA_2 = 0xDE,
  BIRA_3 = 0xDF,

  /* Compare to register zero, arithmetic/logical. */
  COMZ_0 = 0xE0,
  COMZ_1 = 0xE1,
  COMZ_2 = 0xE2,
  COMZ_3 = 0xE3,

  /* Compare immediate, arithmetic/logical. */
  COMI_0 = 0xE4,
  COMI_1 = 0xE5,
  COMI_2 = 0xE6,
  COMI_3 = 0xE7,

  /* Compare relative, arithmetic/logical. */
  COMR_0 = 0xE8,
  COMR_1 = 0xE9,
  COMR_2 = 0xEA,
  COMR_3 = 0xEB,

  /* Compare absolute, arithmetic/logical. */
  COMA_0 = 0xEC,
  COMA_1 = 0xED,
  COMA_2 = 0xEE,
  COMA_3 = 0xEF,

  /* Write data. */
  WRTD_0 = 0xF0,
  WRTD_1 = 0xF1,
  WRTD_2 = 0xF2,
  WRTD_3 = 0xF3,

  /* Test under mask, immediate. */
  TMI_0  = 0xF4,
  TMI_1  = 0xF5,
  TMI_2  = 0xF6,
  TMI_3  = 0xF7,

  /* Branch on decrementing register, relative. */
  BDRR_0 = 0xF8,
  BDRR_1 = 0xF9,
  BDRR_2 = 0xFA,
  BDRR_3 = 0xFB,

  /* Branch on decrementing register, absolute. */
  BDRA_0 = 0xFC,
  BDRA_1 = 0xFD,
  BDRA_2 = 0xFE,
  BDRA_3 = 0xFF
} Opcodes;

typedef struct Cpu {

  /* General purpose registers */
  unsigned char register_0;
  unsigned char register_1;
  unsigned char register_2;
  unsigned char register_3;
  unsigned char register_4;
  unsigned char register_5;
  unsigned char register_6;

  /* Program status word */
  unsigned char psu;
  unsigned char psl;

  /* Instruction Address Register */
  unsigned short iar;

  /* Data-bus register */
  unsigned char dbr;

  /* Instruction Register */
  unsigned char ir;

  /* Holding Register */
  unsigned char hr;

  /* Convenience variables */
  int rel_off;
  int indexing;
  int cc;
} Cpu;

/* Function prototypes */
void cpu_init( Cpu *cpu );

int cpu_loop( Cpu *cpu, char *memory );

#endif /* CPU_2650_H */
