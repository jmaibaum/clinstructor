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
#include <windows.h>
#include "os-timer.h"

static LARGE_INTEGER emu_start;
static LARGE_INTEGER emu_stop;
static LARGE_INTEGER freq;

void timer_start( void ) {
  QueryPerformanceFrequency( &freq );
  QueryPerformanceCounter( &emu_start );
}

void timer_stop( void ) {
  QueryPerformanceCounter( &emu_stop );
}

double timer_elapsed_microsecs( void ) {
  LARGE_INTEGER elapsed_microsecs;

  elapsed_microsecs.QuadPart = emu_stop.QuadPart - emu_start.QuadPart;

  /*
    We now have the elapsed number of ticks, along with the number of
    ticks-per-second. We use these values to convert the number of elapsed
    microseconds. To guard against loss-of-precision, we convert to microseconds
    *before* dividing by ticks-per-second.
  */

  elapsed_microsecs.QuadPart *= 1000000;
  elapsed_microsecs.QuadPart /= freq.QuadPart;

  return (double) elapsed_microsecs.QuadPart;
}
