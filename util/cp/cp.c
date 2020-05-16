/* cp.c - Communications protocols API for yacup project
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
#include <stdlib.h>
#include "yacup/cp.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include "yacup/debug.h"
#undef YCP_NAME
#define YCP_NAME "util/cp/cp"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
int cp_init(struct cp *cp, int (*cp_low_level_init)(struct cp *))
{
  /* Configure _dbg() */
  #define YCP_FNAME "cp_init"

  if (/* Invalid cp? */
      (cp == NULL) ||
      /* Invalid low-level init? */
      (cp_low_level_init == NULL))
  {
    _dbg("Invalid cp or low-level init function\n");
    return 1;
  }

  /* Fill cp common data */
  // Nothing to fill here yet, so this call is right now, just a validator

  /* Now call the low level init function, and go */
  return (cp_low_level_init(cp));

  /* Free _dbg() config */
  #undef YCP_FNAME
}

#undef YCP_NAME
