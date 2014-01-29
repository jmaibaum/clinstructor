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

#include "cpu-2650.h"

void init_cpu( Cpu *cpu )
{
  cpu->register_0 = 0;
  cpu->register_1 = 0;
  cpu->register_2 = 0;
  cpu->register_3 = 0;
  cpu->register_4 = 0;
  cpu->register_5 = 0;
  cpu->register_6 = 0;

  cpu->psw.upper = 0;
  cpu->psw.lower = 0;

  cpu->pc = 0x1234; /* This is just for testing purposes! */
}
