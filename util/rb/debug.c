/* debug.c - Debug functions to ease `rb` development flow
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
#include "yacup/rb.h"
#include "yacup/rb/op.h"
#include "yacup/rb/debug.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define YCP_FORCE_DEBUG
#include "yacup/debug.h"
#undef YCP_NAME
#define YCP_NAME "util/rb/debug"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* Print `rb` information to STDOUT.
 * Read `yacup/rb/debug.h` for complete information. */
void rb_print_info(struct rb *rb)
{
  /* Configure _dbg() */
  #define YCP_FNAME "rb_print_info"

  if ((rb == NULL) || (rb->op == NULL) || rb->op->validate(rb))
  {
    _dbg("Provided rb is not valid\n");
    return;
  }

  /* Required vars */
  size_t idx = 0;

  /* Show data */
  _dbg("[s: %3lu, h: %3lu, t: %3lu, of: %1u, len: %3lu][buf:",
         rb->size,
         rb->head,
         rb->tail,
         rb->head_of,
         rb->op->len(rb)
         );
  for (idx = 0; idx < rb->size; idx++)
  {
    PRINTF(" %02X", rb->buffer[idx]);
  }
  PRINTF("]\n");
  fflush(stdout);
  return; 

  /* Free _dbg() config */
  #undef YCP_FNAME
}

#undef YCP_NAME
#undef YCP_FORCE_DEBUG
