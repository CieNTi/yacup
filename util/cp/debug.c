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
#include "yacup/cp/codec.h"
#include "yacup/cp/debug.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define YCP_FORCE_DEBUG
#include "yacup/debug.h"
#undef YCP_NAME
#define YCP_NAME "util/cp/debug"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* Print `cp` codec information to STDOUT.
 * Read `yacup/cp/debug.h` for complete information. */
void cp_codec_print_info(struct cp_codec *codec)
{
  /* Configure _dbg() */
  #define YCP_FNAME "cp_codec_print_info"

  /* Print codec information */
  if (codec == NULL) { return; }
  _dbg("codec ........: %p\n", (void *)&codec);
  _dbg("- encode .....: %p\n", (void *)&codec->encode);
  _dbg("  - data .....: %p\n", (void *)&codec->encode.data);
  _dbg("  - message ..: %p\n", (void *)&codec->encode.message);
  _dbg("- decode .....: %p\n", (void *)&codec->decode);
  _dbg("  - data .....: %p\n", (void *)&codec->decode.data);
  _dbg("  - message ..: %p\n", (void *)&codec->decode.message);
  fflush(stdout);
  return;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

/* Print `cp` information to STDOUT.
 * Read `yacup/cp/debug.h` for complete information. */
void cp_print_info(struct cp *cp)
{
  if (cp == NULL) { return; }
  _dbg("cp_print_info: len ........: %lu\n", cp->len);
  fflush(stdout);
}

#undef YCP_NAME
#undef YCP_FORCE_DEBUG
