/* debug.c - Debug functions to ease `ce` development flow
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
#include "yacup/ce.h"
#include "yacup/ce/codec.h"
#include "yacup/ce/debug.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define YCP_FORCE_DEBUG
#include "yacup/debug.h"
#undef YCP_NAME
#define YCP_NAME "util/ce/debug"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* Print `ce` information to STDOUT.
 * Read `yacup/ce/debug.h` for complete information. */
void ce_print_info(struct ce *ce)
{
  /* Configure _dbg() */
  #define YCP_FNAME "ce_print_info"

  _dbg("Entering\n");

  /* Free _dbg() config */
  #undef YCP_FNAME
}

/* Print `ce_codec` information to STDOUT.
 * Read `yacup/ce/debug.h` for complete information. */
void ce_codec_print_info(struct ce_codec *codec)
{
  /* Configure _dbg() */
  #define YCP_FNAME "ce_codec_print_info"

  /* Print codec information */
  if (codec == NULL) { return; }
  _dbg("codec ...........: %p\n",      (void *)codec);
  _dbg("- encode ........: %p\n",      (void *)&codec->encode);
  _dbg("  - data ........: %p (%p)\n", (void *)&codec->encode.data,
                                       (void *)(size_t)codec->encode.data);
  _dbg("  - message .....: %p (%p)\n", (void *)&codec->encode.message,
                                       (void *)(size_t)codec->encode.message);
  _dbg("- decode ........: %p\n",      (void *)&codec->decode);
  _dbg("  - data ........: %p (%p)\n", (void *)&codec->decode.data,
                                       (void *)(size_t)codec->decode.data);
  _dbg("  - message .....: %p (%p)\n", (void *)&codec->decode.message,
                                       (void *)(size_t)codec->decode.message);
  return;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

#undef YCP_NAME
#undef YCP_FORCE_DEBUG
