/* channel.c - Command engine channel API for yacup project
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
#include "yacup/ce/channel.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include "yacup/debug.h"
#undef YCP_NAME
#define YCP_NAME "util/ce/channel"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* Initializes a command engine channel using driver initialization functions
 * Read `yacup/ce/channel.h` for complete information. */
int ce_channel_init(struct ce_channel *channel,
                    int (*channels_codec_driver_init)(struct ce_codec *),
                    int (*channels_rb_driver_init)(struct rb *))
{
  /* Configure _dbg() */
  #define YCP_FNAME "ce_channel_init"

  if (/* Invalid channel? */
      (channel == NULL) ||
      /* No commands? */
      (channel->command_set == NULL) ||
      /* Defined buffer driver? */
      (channels_rb_driver_init == NULL) ||
      /* Defined codec driver? */
      (channels_codec_driver_init == NULL) ||
      /* Valid data rb? */
      rb_init(&channel->data, channels_rb_driver_init) ||
      /* Valid message rb? */
      rb_init(&channel->message, channels_rb_driver_init) ||
      /* Valid codec? */
      ce_codec_init(&channel->codec, channels_codec_driver_init))
  {
    _dbg("Invalid ce_channel or driver init function\n");
    return 1;
  }

  /* Ok! */
  _dbg("Channel initialized successfully\n");
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

#undef YCP_NAME
