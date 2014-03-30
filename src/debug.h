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

#ifndef DEBUG_H
#define DEBUG_H

#define GET_BIT_FROM_BYTE( byte, bit )	\
  (((byte) & (EIGHT_BIT & (1 << (bit)))) >> (bit))

#define CPU_DUMP					\
  printf( "CPU-DUMP:\n"					\
	  "/----------------------------\\\n"		\
	  "|IAR:%04X\tIR:%02X        |\n"		\
	  "|----------------------------|\n"		\
	  "|R0:%02X\tR1:%02X\tR2:%02X\tR3:%02X|\n"	\
	  "|\tR4:%02X\tR5:%02X\tR6:%02X|\n"		\
	  "|----------------------------|\n"		\
	  "|PSW:                        |\n"		\
	  "| Upper:                     |\n"		\
  	  "| |S|F|I|-|-|Stack|          |\n"		\
	  "| |%d|%d|%d|%d|%d|%d|%d|%d|          |\n"	\
	  "|                            |\n"		\
	  "| Lower:                     |\n"		\
  	  "| |CC |c|R|W|O|m|C|          |\n"		\
	  "| |%d|%d|%d|%d|%d|%d|%d|%d|          |\n"	\
	  "|----------------------------|\n"		\
	  "|RAS:                        |\n"		\
	  "| 0:%04X 1:%04X 2:%04X 3:%04X|\n"		\
	  "| 4:%04X 5:%04X 6:%04X 7:%04X|\n"		\
	  "\\----------------------------/\n",		\
	  cpu.iar,					\
	  cpu.ir,					\
	  cpu.register_0,				\
	  cpu.register_1,				\
	  cpu.register_2,				\
	  cpu.register_3,				\
	  cpu.register_4,				\
	  cpu.register_5,				\
	  cpu.register_6,				\
	  GET_BIT_FROM_BYTE( cpu.psu, 7 ),		\
	  GET_BIT_FROM_BYTE( cpu.psu, 6 ),		\
	  GET_BIT_FROM_BYTE( cpu.psu, 5 ),		\
	  GET_BIT_FROM_BYTE( cpu.psu, 4 ),		\
	  GET_BIT_FROM_BYTE( cpu.psu, 3 ),		\
	  GET_BIT_FROM_BYTE( cpu.psu, 2 ),		\
	  GET_BIT_FROM_BYTE( cpu.psu, 1 ),		\
	  GET_BIT_FROM_BYTE( cpu.psu, 0 ),		\
	  GET_BIT_FROM_BYTE( cpu.psl, 7 ),		\
	  GET_BIT_FROM_BYTE( cpu.psl, 6 ),		\
	  GET_BIT_FROM_BYTE( cpu.psl, 5 ),		\
	  GET_BIT_FROM_BYTE( cpu.psl, 4 ),		\
	  GET_BIT_FROM_BYTE( cpu.psl, 3 ),		\
	  GET_BIT_FROM_BYTE( cpu.psl, 2 ),		\
	  GET_BIT_FROM_BYTE( cpu.psl, 1 ),		\
	  GET_BIT_FROM_BYTE( cpu.psl, 0 ),		\
	  cpu.ras[0],					\
	  cpu.ras[1],					\
	  cpu.ras[2],					\
	  cpu.ras[3],					\
	  cpu.ras[4],					\
	  cpu.ras[5],					\
	  cpu.ras[6],					\
	  cpu.ras[7] );					\

#endif /* DEBUG_H */
