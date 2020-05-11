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
#include <yacup/rb.h>
#include <yacup/rb/debug.h>

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#ifdef YACUP_DEBUG
  #include <time.h>
  #include <stdio.h>
  #include <string.h>
  #ifndef _dbg
    #define _dbg(...) printf(__VA_ARGS__)
  #endif
#else
  #ifndef _dbg
    #define _dbg(...)
  #endif
#endif

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* Print `rb` information to STDOUT.
 * Read `yacup/rb/debug.h` for complete information. */
void rb_print_info(struct rb *rb)
{
  size_t idx = 0;

  /* Show data */
  printf("[s: %3lu, h: %3lu, t: %3lu, of: %1u, len: %3lu]"
         "[buf:",
         rb->size,
         rb->head,
         rb->tail,
         rb->head_of,
         rb_len(rb)
         );
  fflush(stdout);

  for (idx = 0; idx < rb->size; idx++)
  {
    printf(" %02X", rb->buffer[idx]);
  }
  printf("]\n");
  return; 
}
