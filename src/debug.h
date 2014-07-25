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

int i, j;

#define MICRO_SECONDS (1000000)

#define GET_BIT_FROM_BYTE( byte, bit )              \
  (((byte) & (EIGHT_BIT & (1 << (bit)))) >> (bit))

#define CPU_DUMP                                      \
  printf( "CPU Dump:\n"                               \
          "/----------------------------\\\n"         \
          "|IAR:%04X\tIR:%02X        |\n"             \
          "|----------------------------|\n"          \
          "|R0:%02X\tR1:%02X\tR2:%02X\tR3:%02X|\n"    \
          "|\tR4:%02X\tR5:%02X\tR6:%02X|\n"           \
          "|----------------------------|\n"          \
          "|PSW:                        |\n"          \
          "| Upper:                     |\n"          \
          "| |S|F|I|-|-|Stack|          |\n"          \
          "| |%d|%d|%d|%d|%d|%d|%d|%d|          |\n"  \
          "|                            |\n"          \
          "| Lower:                     |\n"          \
          "| |CC |c|R|W|O|m|C|          |\n"          \
          "| |%d|%d|%d|%d|%d|%d|%d|%d|          |\n"  \
          "|----------------------------|\n"          \
          "|RAS:                        |\n"          \
          "| 0:%04X 1:%04X 2:%04X 3:%04X|\n"          \
          "| 4:%04X 5:%04X 6:%04X 7:%04X|\n"          \
          "\\----------------------------/\n",        \
          cpu.iar,                                    \
          cpu.ir,                                     \
          cpu.r0,                                     \
          cpu.register_1,                             \
          cpu.register_2,                             \
          cpu.register_3,                             \
          cpu.register_4,                             \
          cpu.register_5,                             \
          cpu.register_6,                             \
          GET_BIT_FROM_BYTE( cpu.psu, 7 ),            \
          GET_BIT_FROM_BYTE( cpu.psu, 6 ),            \
          GET_BIT_FROM_BYTE( cpu.psu, 5 ),            \
          GET_BIT_FROM_BYTE( cpu.psu, 4 ),            \
          GET_BIT_FROM_BYTE( cpu.psu, 3 ),            \
          GET_BIT_FROM_BYTE( cpu.psu, 2 ),            \
          GET_BIT_FROM_BYTE( cpu.psu, 1 ),            \
          GET_BIT_FROM_BYTE( cpu.psu, 0 ),            \
          GET_BIT_FROM_BYTE( cpu.psl, 7 ),            \
          GET_BIT_FROM_BYTE( cpu.psl, 6 ),            \
          GET_BIT_FROM_BYTE( cpu.psl, 5 ),            \
          GET_BIT_FROM_BYTE( cpu.psl, 4 ),            \
          GET_BIT_FROM_BYTE( cpu.psl, 3 ),            \
          GET_BIT_FROM_BYTE( cpu.psl, 2 ),            \
          GET_BIT_FROM_BYTE( cpu.psl, 1 ),            \
          GET_BIT_FROM_BYTE( cpu.psl, 0 ),            \
          cpu.ras[0],                                 \
          cpu.ras[1],                                 \
          cpu.ras[2],                                 \
          cpu.ras[3],                                 \
          cpu.ras[4],                                 \
          cpu.ras[5],                                 \
          cpu.ras[6],                                 \
          cpu.ras[7] );


#define MEMORY_DUMP( start )                                        \
  printf( "Memory Dump from 0x%04X to 0x%04X:\n"                    \
          "    + 0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n"  \
          "    /-----------------------------------------------\n", \
          (start), (start) + 255 );                                 \
                                                                    \
  for ( i = (start); i < ((start) + 256); i += 16 ) {               \
    printf( "%04X|%02X %02X %02X %02X %02X %02X %02X %02X "         \
            "%02X %02X %02X %02X %02X %02X %02X %02X\n",            \
            i,                                                      \
            memory[i],                                              \
            memory[i + 1],                                          \
            memory[i + 2],                                          \
            memory[i + 3],                                          \
            memory[i + 4],                                          \
            memory[i + 5],                                          \
            memory[i + 6],                                          \
            memory[i + 7],                                          \
            memory[i + 8],                                          \
            memory[i + 9],                                          \
            memory[i + 10],                                         \
            memory[i + 11],                                         \
            memory[i + 12],                                         \
            memory[i + 13],                                         \
            memory[i + 14],                                         \
            memory[i + 15] );                                       \
  }


#define NEXT_MEMORY_ROW( start )                          \
  j = (start) + (i * 16);                                 \
  printf( "%04X:%02X %02X %02X %02X %02X %02X %02X %02X " \
          "%02X %02X %02X %02X %02X %02X %02X %02X\n",    \
          j,                                              \
          memory[j],                                      \
          memory[j + 1],                                  \
          memory[j + 2],                                  \
          memory[j + 3],                                  \
          memory[j + 4],                                  \
          memory[j + 5],                                  \
          memory[j + 6],                                  \
          memory[j + 7],                                  \
          memory[j + 8],                                  \
          memory[j + 9],                                  \
          memory[j + 10],                                 \
          memory[j + 11],                                 \
          memory[j + 12],                                 \
          memory[j + 13],                                 \
          memory[j + 14],                                 \
          memory[j + 15] );                               \
  i++


#define CPU_AND_MEMORY_DUMP( start )                                \
  printf( "CPU dump:                  |"                            \
          "Memory dump from 0x%04X to 0x%04X:\n", (start),          \
          (start + 255) );                                          \
  printf( "IAR:%04X\tIR:%02X      |"                                \
          "    + 0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n", \
          cpu.iar, cpu.ir);                                         \
  i = 0;                                                            \
  printf( "                           |");                          \
  NEXT_MEMORY_ROW(start);                                           \
  printf( "R0:%02X  R1:%02X  R2:%02X  R3:%02X |", cpu.r0,           \
          cpu.register_1, cpu.register_2, cpu.register_3 );         \
  NEXT_MEMORY_ROW(start);                                           \
  printf( "       R4:%02X  R5:%02X  R6:%02X |", cpu.register_4,     \
          cpu.register_5, cpu.register_6 );                         \
  NEXT_MEMORY_ROW(start);                                           \
  printf( "                           |" );                         \
  NEXT_MEMORY_ROW(start);                                           \
  printf( "PSW:                       |" );                         \
  NEXT_MEMORY_ROW(start);                                           \
  printf( " Upper:                    |" );                         \
  NEXT_MEMORY_ROW(start);                                           \
  printf( " |S|F|I|-|-|Stack|         |" );                         \
  NEXT_MEMORY_ROW(start);                                           \
  printf( " |%d|%d|%d|%d|%d|%d|%d|%d|         |",                   \
          GET_BIT_FROM_BYTE(cpu.psu, 7),                            \
          GET_BIT_FROM_BYTE(cpu.psu, 6),                            \
          GET_BIT_FROM_BYTE(cpu.psu, 5),                            \
          GET_BIT_FROM_BYTE(cpu.psu, 4),                            \
          GET_BIT_FROM_BYTE(cpu.psu, 3),                            \
          GET_BIT_FROM_BYTE(cpu.psu, 2),                            \
          GET_BIT_FROM_BYTE(cpu.psu, 1),                            \
          GET_BIT_FROM_BYTE(cpu.psu, 0) );                          \
  NEXT_MEMORY_ROW(start);                                           \
  printf( "                           |" );                         \
  NEXT_MEMORY_ROW(start);                                           \
  printf( " Lower:                    |" );                         \
  NEXT_MEMORY_ROW(start);                                           \
  printf( " |CC |c|R|W|O|m|C|         |" );                         \
  NEXT_MEMORY_ROW(start);                                           \
  printf( " |%d|%d|%d|%d|%d|%d|%d|%d|         |",                   \
          GET_BIT_FROM_BYTE(cpu.psl, 7),                            \
          GET_BIT_FROM_BYTE(cpu.psl, 6),                            \
          GET_BIT_FROM_BYTE(cpu.psl, 5),                            \
          GET_BIT_FROM_BYTE(cpu.psl, 4),                            \
          GET_BIT_FROM_BYTE(cpu.psl, 3),                            \
          GET_BIT_FROM_BYTE(cpu.psl, 2),                            \
          GET_BIT_FROM_BYTE(cpu.psl, 1),                            \
          GET_BIT_FROM_BYTE(cpu.psl, 0) );                          \
  NEXT_MEMORY_ROW(start);                                           \
  printf( "                           |" );                         \
  NEXT_MEMORY_ROW(start);                                           \
  printf( "Return Address Stack:      |" );                         \
  NEXT_MEMORY_ROW(start);                                           \
  printf( "0:%04X 1:%04X 2:%04X 3:%04X|", cpu.ras[0], cpu.ras[1],   \
          cpu.ras[2], cpu.ras[3] );                                 \
  NEXT_MEMORY_ROW(start);                                           \
  printf( "4:%04X 5:%04X 6:%04X 7:%04X|", cpu.ras[4], cpu.ras[5],   \
          cpu.ras[6], cpu.ras[7] );                                 \
  NEXT_MEMORY_ROW(start);


#endif /* DEBUG_H */
