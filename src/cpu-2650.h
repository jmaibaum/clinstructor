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

#include <stdint.h>

typedef struct Cpu {
  int8_t register_0;
  int8_t register_1;
  int8_t register_2;
  int8_t register_3;
  int8_t register_4;
  int8_t register_5;
  int8_t register_6;
} Cpu;

/* Function prototypes */
void init_cpu( Cpu *cpu );
void update_register( int8_t *reg, int8_t value );

#endif /* CPU_2650_H */
