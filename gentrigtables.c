/* Generate trigonometric function tables. */
/*
 *  GRUB  --  GRand Unified Bootloader
 *  Copyright (C) 2008, 2009  Free Software Foundation, Inc.
 *
 *  GRUB is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  GRUB is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with GRUB.  If not, see <http://www.gnu.org/licenses/>.
 */

#define _GNU_SOURCE 1

#include <grub/trig.h>
#include <math.h>
#include <stdio.h>

int
main ()
{
  int i;

  printf ("#include <grub/types.h>\n"
	  "#include <grub/symbol.h>\n"
	  "GRUB_EXPORT(grub_trig_costab);\n"
	  "GRUB_EXPORT(grub_trig_sintab);\n");

#define TAB(op) \
  printf ("grub_int16_t grub_trig_" #op "tab[] =\n{"); \
  for (i = 0; i < GRUB_TRIG_ANGLE_MAX; i++) \
    { \
      double x = i * 2 * M_PI / GRUB_TRIG_ANGLE_MAX; \
      if (i % 10 == 0) \
	printf ("\n    "); \
      printf ("%d,", (int) (round (op (x) * GRUB_TRIG_FRACTION_SCALE))); \
    } \
  printf ("\n};\n")

  TAB(sin);
  TAB(cos);

  return 0;
}
