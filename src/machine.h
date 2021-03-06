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

/*
  This file contains definitions that are specific for the hardware
  configuration of the Signetics Instructor 50.
*/

#ifndef MACHINE_H
#define MACHINE_H

#define CLOCK         (3579548)   /* Instructor 50 says 3579545, but the chosen
                                     value allows for correct integer
                                     division. */
#define CPU_CLOCK     (CLOCK / 4) /* = 894887, otherwise it would be
                                     894886.25. */

#endif /* MACHINE_H */
