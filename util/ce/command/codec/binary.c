/* binary.c - Binary command codec for `ce` util
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
#include "yacup/ce/command_codec.h"
#include "yacup/ce/command/codec/binary.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include "yacup/debug.h"
#undef YCP_NAME
#define YCP_NAME "util/ce/command/codec/binary"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* Encodes a command as a data-block into a rb
 * WARNING: Assumes pre-validation. Not safe as direct call!
 * Read `yacup/ce/command_codec.h` for complete information. */
static size_t encode_command(struct ce_command *command,
                             struct ce_command_argument *argument[],
                             struct rb *rb_data)
{
  /* Configure _dbg() */
  #define YCP_FNAME "encode_command"

  /* And return with success */
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

/* Decodes a data-block into a validated command with arguments
 * WARNING: Assumes pre-validation. Not safe as direct call!
 * Read `yacup/ce/command_codec.h` for complete information. */
static size_t decode_command(struct rb *rb,
                             struct ce_command *command,
                             struct ce_command_argument *argument[])
{
  /* Configure _dbg() */
  #define YCP_FNAME "decode_command"

  /* And return with success */
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}


/* Initialize a `binary` type comm-protocol codec.
 * Read `yacup/ce/command_codec.h` for complete information. */
int ce_command_codec_binary(struct ce_command_codec *codec)
{
  /* Configure _dbg() */
  #define YCP_FNAME "ce_command_codec_binary"

  /* Valid codec? */
  if (codec == NULL)
  {
    _dbg("Direct calls not recommended, read the doc\n");
    return 1;
  }

  /* Ok assign the operations */
  codec->name   = YCP_NAME;
  codec->encode = encode_command;
  codec->decode = decode_command;

  /* And return with success */
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

#undef YCP_NAME
