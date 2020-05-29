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
#include "yacup/rb/driver.h"
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

  if ((rb == NULL) || (rb->driver == NULL) || rb->driver->validate(rb))
  {
    _dbg("Provided rb is not valid\n");
    return;
  }

  /* Show parameters data */
  _dbg("[s: %3lu, h: %3lu, t: %3lu, of: %1u, len: %3lu]\n",
         rb->size,
         rb->head,
         rb->tail,
         rb->head_of,
         rb->driver->len(rb)
         );

  /* Required vars to print a data table */
  size_t idx_byte = 0;
  size_t idx_line = 0;
  #define RB_DBG_LINE_BYTES 24
  #define __RB_DBG_TOTAL ((RB_DBG_LINE_BYTES * 3) + 10)
  char debug_line[__RB_DBG_TOTAL] = { 0x00 };
  char *debug_line_pt = NULL;

  /* Show top row with index */
  debug_line_pt = debug_line;
  for (idx_byte = 0; idx_byte < RB_DBG_LINE_BYTES; idx_byte++)
  {
    sprintf(debug_line_pt, " %02lX", idx_byte);
    debug_line_pt += 3;
  }
  _dbg("[    |%s ]\n", debug_line);

  /* Show row with separator */
  debug_line_pt = debug_line;
  for (idx_byte = 0; idx_byte < RB_DBG_LINE_BYTES; idx_byte++)
  {
    sprintf(debug_line_pt, "~~~");
    debug_line_pt += 3;
  }
  _dbg("[~~~~+%s~]\n", debug_line);

  /* Show rows with data */
  for (idx_line = 0; (idx_line * RB_DBG_LINE_BYTES) < rb->size; idx_line++)
  {
    debug_line_pt = debug_line;
    for (idx_byte = 0; idx_byte < RB_DBG_LINE_BYTES; idx_byte++)
    {
      if ((idx_line * RB_DBG_LINE_BYTES) + idx_byte < rb->size)
      {
        sprintf(debug_line_pt, "%c%02X",
             (((idx_line * RB_DBG_LINE_BYTES) + idx_byte == rb->tail)?'[':
              ((idx_line * RB_DBG_LINE_BYTES) + idx_byte == rb->head)?']':' '),
                rb->buffer[(idx_line * RB_DBG_LINE_BYTES) + idx_byte]);
      }
      else
      {
        sprintf(debug_line_pt, " ~~");
      }
      debug_line_pt += 3;
    }
    _dbg("[ %02lX |%s ]\n", idx_line, debug_line);
  }
  return; 

  /* Free _dbg() config */
  #undef YCP_FNAME
}

#undef YCP_NAME
#undef YCP_FORCE_DEBUG
