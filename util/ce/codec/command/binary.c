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
                             struct ce_codec *codec,
                             struct rb *rb_data)
{
  /* Configure _dbg() */
  #define YCP_FNAME "encode_command"

  /* Header: Encode command id as uint16_t */
  if(codec->encode.data(CE_DATA_UINT8_T,
                        &command->id,
                        1,
                        rb_data) == 0)
  {
    _dbg("Cannot encode the command id. ERROR\n");
    return 1;
  }

  if (argument == NULL)
  {
    /* No arguments, stop here with success */
    return 0;
  }

  /* Encode all passed arguments (pre-validated) */
  size_t idx = 0;
  for (idx = 0; argument[idx] != NULL; idx++)
  {
    /* Encode argument */
    if(codec->encode.data(argument[idx]->type,
                          &argument[idx]->data,
                          1,
                          rb_data) == 0)
    {
      _dbg("Cannot encode the data at index %lu. ERROR\n", idx);
      return 1;
    }
    _dbg("Encoded argument: 0x%02lX\n", *(size_t *)&argument[idx]->data);
  }

  /* And return with success */
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

/* Decodes a data-block into a validated command with arguments
 * WARNING: Assumes pre-validation. Not safe as direct call!
 * Read `yacup/ce/command_codec.h` for complete information. */
static size_t decode_command(struct rb *rb_data,
                             struct ce_codec *codec,
                             struct ce_command_set *cmd_set)
{
  /* Configure _dbg() */
  #define YCP_FNAME "decode_command"

  size_t aux_var = 0;

  /* Header: Decode command id as uint16_t */
  if(codec->decode.data(rb_data,
                        CE_DATA_UINT8_T,
                        &aux_var,
                        1) == 0)
  {
    _dbg("Cannot decode the command id. ERROR\n");
    return 1;
  }

  struct ce_command *ref_cmd = ce_command_locate_by_id(cmd_set, aux_var);
  if (ref_cmd == NULL)
  {
    _dbg("Command not found\n");
    return 1;
  }

  /* Decode arguments, following command signature */
  size_t idx = 0;
  void *data_holder = &aux_var;

  /* Decode arguments (mandatory, with or without listener) */
  for (idx = 0; ref_cmd->signature[idx] != CE_DATA_NULL; idx++)
  {
    /* Define data holder (save or destroy) */
    if ((ref_cmd->listener != NULL) &&
        (ref_cmd->listener->argument != NULL) &&
        (ref_cmd->signature[idx] == ref_cmd->listener->argument[idx]->type))
    {
      data_holder = &ref_cmd->listener->argument[idx]->data;
    }

    if(codec->decode.data(rb_data,
                          ref_cmd->signature[idx],
                          data_holder,
                          1) == 0)
    {
      _dbg("Cannot encode the data at index %lu. ERROR\n", idx);
      return 1;
    }
    _dbg("Decoded argument: 0x%02lX\n", *(size_t *)data_holder);
  }

  /* Not aux_var? Then we have a listener ready to be called! */
  if (data_holder != &aux_var)
  {
    ref_cmd->listener->listener(ref_cmd->listener->argument);
  }

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
