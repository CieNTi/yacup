/* debug.c - Debug functions to ease `cp` development flow
 * Copyright (C) 2020 CieNTi <cienti@cienti.com>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include "yacup/cp.h"
#include "yacup/cp/debug.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#undef YCP_NAME
#define YCP_NAME "util/cp/debug"
#include <time.h>
#include <stdio.h>
#include <string.h>
#ifndef _dbg
  #define _dbg(...) printf(YCP_NAME" | "__VA_ARGS__)
#endif

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* Print `cp` information to STDOUT.
 * Read `yacup/cp/debug.h` for complete information. */
void cp_print_info(struct cp *cp)
{
  if (cp == NULL) { return; }
  _dbg("cp_print_info: len ........: %lu\n", cp->len);
  fflush(stdout);
}

#undef YCP_NAME
