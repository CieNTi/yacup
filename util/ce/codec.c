/* codec.c - Command engine codec API for yacup project
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
#include "yacup/ce/codec.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include "yacup/debug.h"
#undef YCP_NAME
#define YCP_NAME "util/ce/codec"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* Initializes a `ce_codec`
 * Read `yacup/ce/codec.h` for complete information. */
int ce_codec_init(struct ce_codec *codec,
                  int (*ce_codec_driver_init)(struct ce_codec *))
{
  /* Configure _dbg() */
  #define YCP_FNAME "ce_codec_init"

  if (/* Invalid codec? */
      (codec == NULL) ||
      /* Invalid driver init? */
      (ce_codec_driver_init == NULL))
  {
    _dbg("Invalid codec or driver init function\n");
    return 1;
  }

  /* Presets */
  codec->encode.command = NULL;
  codec->encode.data = NULL;
  codec->encode.message = NULL;
  codec->decode.command = NULL;
  codec->decode.data = NULL;
  codec->decode.message = NULL;

  /* Now call the driver init function, and go */
  if (ce_codec_driver_init(codec))
  {
    _dbg("Failed channel initialization\n");
    return 1;
  }

  /* Assign default name, if not previously set */
  if (codec->name == NULL)
  {
    codec->name = YCP_NAME;
  }

  /* Ok! */
  _dbg("Codec '%s' initialized successfully\n", codec->name);
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

#undef YCP_NAME
