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

#include <sys/time.h>
#include <stdio.h>
#include "os-timer.h"

static struct timeval emu_start;
static struct timeval emu_stop;

void timer_start( void ) {
  gettimeofday( &emu_start, NULL );
}

void timer_stop( void ) {
  gettimeofday( &emu_stop, NULL );
}

void timer_warn( void ) {
  if ( emu_stop.tv_sec - emu_start.tv_sec ) {
    printf( "Emulation lasted longer than one second. "
            "The next line does\n not tell the truth.\n" );
  }
}

double timer_elapsed_microsecs( void ) {
  return emu_stop.tv_usec - emu_start.tv_usec;
}
