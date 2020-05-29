/* B416K.c - Binary 4-byte + CRC-16/Kermit codec for `ce` util
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
#include "yacup/ce/codec.h"
#include "yacup/ce/codec/B416K.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include "yacup/debug.h"
#undef YCP_NAME
#define YCP_NAME "util/ce/codec/B416K"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* Calculate this encoding size of a specified type, in bytes
 * Read `yacup/ce/codec.h` for complete information. */
static size_t codec_sizeof(enum ce_data_type type)
{
  /* Configure _dbg() */
  #define YCP_FNAME "codec_sizeof"

   switch(type)
  {
    case CE_DATA_UINT8_T:
      _dbg("Selected data type CE_DATA_UINT8_T\n");
      return (sizeof(uint8_t));
      break;
    case CE_DATA_INT8_T:
      _dbg("Selected data type CE_DATA_INT8_T\n");
      return (sizeof(int8_t));
      break;
    case CE_DATA_UINT16_T:
      _dbg("Selected data type CE_DATA_UINT16_T\n");
      return (sizeof(uint16_t));
      break;
    case CE_DATA_INT16_T:
      _dbg("Selected data type CE_DATA_INT16_T\n");
      return (sizeof(int16_t));
      break;
    case CE_DATA_UINT32_T:
      _dbg("Selected data type CE_DATA_UINT32_T\n");
      return (sizeof(uint32_t));
      break;
    case CE_DATA_INT32_T:
      _dbg("Selected data type CE_DATA_INT32_T\n");
      return (sizeof(int32_t));
      break;
    case CE_DATA_UINT64_T:
      _dbg("Selected data type CE_DATA_UINT64_T\n");
      return (sizeof(uint64_t));
      break;
    case CE_DATA_INT64_T:
      _dbg("Selected data type CE_DATA_INT64_T\n");
      return (sizeof(int64_t));
      break;
    case CE_DATA_FLOAT:
      _dbg("Selected data type CE_DATA_FLOAT\n");
      return (sizeof(float));
      break;
    case CE_DATA_DOUBLE:
      _dbg("Selected data type CE_DATA_DOUBLE\n");
      return (sizeof(double));
      break;
    default:
      _dbg("Unrecognized type %lu\n", (size_t)type);
      break;
  }

  /* Invalid size */
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

/**
 * @brief      Calculate CRC-16/KERMIT (According to https://crccalc.com/)
 *
 * @warning    Assumed safe environment, all pre-checks already done
 *
 * @param      rb    Ring-buffer to use for read data (not pulled)
 * @param      skip  Amount of bytes to skip before start the computations
 * @param      len   Amount of bytes to use for computations
 * @param      crc   Pointer to calculated CRC holder
 *
 * @return     One of:
 *             | Value  | Meaning          |
 *             | :----: | :--------------- |
 *             | `== 0` | Ok               |
 *             | `!= 0` | Error            |
 */
static int crc16_kermit(struct rb *rb, size_t skip, size_t len, uint16_t *crc)
{
  /* Configure _dbg() */
  #define YCP_FNAME "crc16_kermit"

  size_t i;
  uint8_t bit;
  uint8_t carry;
  uint8_t data_holder;
  *crc = 0;
  for (i = 0; i < len; i++)
  {
    if (rb_read(rb, &data_holder, i + skip))
    {
      /* Cannot read */
      _dbg("Cannot read data\n");
      return 1;
    }
    *crc ^= data_holder;
    for (bit = 0; bit < 8; bit++)
    {
      carry = *crc & 1;
      *crc >>= 1;
      if (carry)
      {
        *crc ^= 0x8408;
      }
    }
  }
  _dbg("Calculated CRC: %04X (skips %lu, uses %lu)\n", *crc, skip, len);
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

/* Encodes a defined type data and pushes it into a ring-buffer
 * WARNING: Assumes pre-validation. Not safe as direct call!
 * Read `yacup/ce/codec.h` for complete information. */
static size_t encode_data(enum ce_data_type type,
                          void *data, size_t num_data,
                          struct rb *rb)
{
  /* Configure _dbg() */
  #define YCP_FNAME "encode_data"

  size_t idx_data = 0;
  size_t len_bytes = 0;
  size_t idx_byte = 0;
  uint8_t *data_pt = NULL;

  /* TBD / TODO: Can be a codec configuration */
  uint8_t big_endian = 0;

  len_bytes = codec_sizeof(type);
  for (idx_data = 0; idx_data < num_data; idx_data++)
  {
    for (idx_byte = 0; idx_byte < len_bytes; idx_byte++)
    {
      /* Select endianess */
      if (big_endian)
      {
        data_pt = (uint8_t *)data +
                  (idx_data * len_bytes) +
                  idx_byte;
      }
      else
      {
        data_pt = (uint8_t *)data +
                  (idx_data * len_bytes) +
                  (len_bytes - (idx_byte + 1));
      }
      if (rb_push(rb, *data_pt))
      {
        /* We expected that bytes to be here, should be error or warning? */
        _dbg("WARNING [Cannot push (data %lu, byte %lu). No space?]\n",
             idx_data,
             idx_byte);
        return idx_data;
      }
    }
  }

  /* Ok! */
  return idx_data;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

/* Pulls and decodes data from a ring-buffer and saves it into variable
 * WARNING: Assumes pre-validation. Not safe as direct call!
 * Read `yacup/ce/codec.h` for complete information. */
static size_t decode_data(struct rb *rb,
                          enum ce_data_type type,
                          void *data, size_t num_data)
{
  /* Configure _dbg() */
  #define YCP_FNAME "decode_data"

  size_t idx_data = 0;
  size_t len_bytes = 0;
  size_t idx_byte = 0;
  uint8_t *data_pt = NULL;

  /* TBD / TODO: Can be a codec configuration */
  uint8_t big_endian = 0;

  len_bytes = codec_sizeof(type);
  for (idx_data = 0; idx_data < num_data; idx_data++)
  {
    for (idx_byte = 0; idx_byte < len_bytes; idx_byte++)
    {
      /* Select endianess */
      if (big_endian)
      {
        data_pt = (uint8_t *)data +
                  (idx_data * len_bytes) +
                  idx_byte;
      }
      else
      {
        data_pt = (uint8_t *)data +
                  (idx_data * len_bytes) +
                  (len_bytes - (idx_byte + 1));
      }
      if (rb_pull(rb, data_pt))
      {
        /* We expected that bytes to be here, should be error or warning? */
        _dbg("WARNING [Cannot pull (data %lu, byte %lu). No space?]\n",
             idx_data,
             idx_byte);
        return idx_data;
      }
    }
  }

  /* Ok! */
  return idx_data;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

/* Encodes a command as a data-block into a rb
 * WARNING: Assumes pre-validation. Not safe as direct call!
 * Read `yacup/ce/codec.h` for complete information. */
static size_t encode_command(struct ce_command *command,
                             struct ce_command_argument *argument[],
                             struct rb *rb_data)
{
  /* Configure _dbg() */
  #define YCP_FNAME "encode_command"

  /* Header: Encode command id as uint16_t */
  if(encode_data(CE_DATA_UINT8_T, &command->id, 1, rb_data) == 0)
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
    if(encode_data(argument[idx]->type, &argument[idx]->data, 1, rb_data) == 0)
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
 * Read `yacup/ce/codec.h` for complete information. */
static size_t decode_command(struct rb *rb_data,
                             struct ce_command_set *cmd_set,
                             struct ce_command **command)
{
  /* Configure _dbg() */
  #define YCP_FNAME "decode_command"

  size_t aux_var = 0;

  /* Header: Decode command id as uint16_t */
  if(decode_data(rb_data, CE_DATA_UINT8_T, &aux_var, 1) == 0)
  {
    _dbg("Cannot decode the command id. ERROR\n");
    return 1;
  }

  *command = ce_command_locate_by_id(cmd_set, aux_var);
  if (*command == NULL)
  {
    _dbg("Command not found\n");
    return 1;
  }

  /* Decode arguments, following command signature */
  size_t idx = 0;
  void *data_holder = &aux_var;

  /* Decode arguments (mandatory, with or without listener) */
  for (idx = 0; (*command)->signature[idx] != CE_DATA_NULL; idx++)
  {
    /* Define data holder (save or destroy) */
    if (((*command)->listener != NULL) &&
        ((*command)->listener->argument != NULL) &&
        ((*command)->signature[idx] == (*command)->listener->argument[idx]->type))
    {
      data_holder = &(*command)->listener->argument[idx]->data;
    }

    if(decode_data(rb_data, (*command)->signature[idx], data_holder, 1) == 0)
    {
      _dbg("Cannot decode the data at index %lu. ERROR\n", idx);
      *command = NULL;
      return 1;
    }
    _dbg("Decoded argument: 0x%02lX\n", *(size_t *)data_holder);
  }

//  /* Not aux_var? Then we have a listener ready to be called! */
//  if (data_holder != &aux_var)
//  {
//    command->listener->listener(command->listener->argument);
//  }

  /* And return with success */
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

/* Takes `rb` raw data, encodes it as a message, and puts it back as `rb`
 * WARNING: Assumes pre-validation. Not safe as direct call!
 * Read `yacup/ce/codec.h` for complete information. */
static int encode_message(struct rb *rb_data, struct rb *rb_msg)
{
  /* Configure _dbg() */
  #define YCP_FNAME "encode_message"

  uint8_t data_holder = 0;
  uint16_t crc_holder = 0;
  size_t msg_len = rb_len(rb_msg);

  /* Push header */
  if (rb_push(rb_msg, CE_CODEC_B416K_START_BYTE) ||
      rb_push(rb_msg, (uint8_t)(rb_len(rb_data) >> 8)) ||
      rb_push(rb_msg, (uint8_t)(rb_len(rb_data)))
      )
  {
    /* Cannot push, error */
    _dbg("Error when pushing message header\n");
    return 1;
  }

  /* Move data */
  while (rb_pull(rb_data, &data_holder) == 0)
  {
    if (rb_push(rb_msg, data_holder))
    {
      /* Fial! Out of destination space */
      _dbg("Error when moving data packet to message buffer\n");
      return 1;
    }
  }

  /* Calculate and save CRC */
  if (crc16_kermit(rb_msg, msg_len + 1, rb_len(rb_msg) - msg_len - 1,
                   &crc_holder)                                       ||
      rb_push(rb_msg, (uint8_t)(crc_holder >> 8))                     ||
      rb_push(rb_msg, (uint8_t)(crc_holder)))
  {
    /* Fial! Out of destination space */
    _dbg("Error when pushing message CRC\n");
    return 1;
  }

  /* Ok! */
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

/* Read and delete a byte from a comm-protocol tail.
 * WARNING: Assumes pre-validation. Not safe as direct call!
 * Read `yacup/ce/codec.h` for complete information. */
static int decode_message(struct rb *rb_msg, struct rb *rb_data)
{
  /* Configure _dbg() */
  #define YCP_FNAME "decode_message"

  uint8_t data_holder = 0;
  uint16_t crc_holder[2] = { 0 };
  size_t data_len = 0;

  /* Seek for the header, discarding any other data found */
  while (rb_len(rb_msg)                               &&
         (rb_read(rb_msg, &data_holder, 0) == 0)      &&
         (data_holder != CE_CODEC_B416K_START_BYTE))
  {
    if (rb_pull(rb_msg, &data_holder) || (rb_len(rb_msg) == 0))
    {
      /* Input buffer exhausted without any header */
      _dbg("No message header found on buffer\n");
      return 1;
    }
  }

  /* Pre-read length, but not removing it as it is needed for CRC */
  data_len = 0;
  if (rb_read(rb_msg, (uint8_t *)&data_len + 1, 1) ||
      rb_read(rb_msg, (uint8_t *)&data_len    , 2))
  {
    /* Cannot push, error */
    _dbg("Error when pre-reading message length\n");
    return 1;
  }

  /* Calculate and save CRC (all message but start flag and crc bytes) */
  if (crc16_kermit(rb_msg, 1, 2 + data_len, &crc_holder[0]))
  {
    /* Error when calculating CRC */
    _dbg("Error when calculating message CRC\n");
    return 1;
  }

  /* Read received CRC and compare it with calculated one */
  if (rb_read(rb_msg, (uint8_t *)&crc_holder[1] + 1, 3 + data_len + 0) ||
      rb_read(rb_msg, (uint8_t *)&crc_holder[1]    , 3 + data_len + 1))
  {
    /* Cannot push, error */
    _dbg("Error when reading message CRC\n");
    return 1;
  }

  if (crc_holder[0] != crc_holder[1])
  {
    _dbg("CRC mismatch (Calculated: %04X vs. Received %04X)\n",
         crc_holder[0], crc_holder[1]);
    return 1;
  }

  /* Once the message is validated, we can start to extract data */
  /* Pull Header, MSB + LSB of data length */
  data_len = 0;
  if (rb_pull(rb_msg, &data_holder) ||
      rb_pull(rb_msg, (uint8_t *)&data_len + 1) ||
      rb_pull(rb_msg, (uint8_t *)&data_len))
  {
    /* Cannot push, error */
    _dbg("Error when pulling message length\n");
    return 1;
  }

  /* Move data */
  while ((data_len > 0) && (rb_pull(rb_msg, &data_holder) == 0))
  {
    if (rb_push(rb_data, data_holder))
    {
      /* Fial! Out of destination space */
      _dbg("Cannot push when moving data from message to data buffer\n");
      return 1;
    }
    data_len--;
  }

  /* Pull CRC bytes */
  if (rb_pull(rb_msg, &data_holder) ||
      rb_pull(rb_msg, &data_holder)
      )
  {
    /* Cannot push, error */
    _dbg("Error when pulling CRC\n");
    return 1;
  }

  /* Ok! */
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

/* Initialize a `B416K` type comm-protocol codec.
 * Read `yacup/ce/codec.h` for complete information. */
int ce_codec_B416K(struct ce_codec *codec)
{
  /* Configure _dbg() */
  #define YCP_FNAME "ce_codec_B416K"

  /* Valid codec? */
  if (codec == NULL)
  {
    _dbg("Direct calls not recommended, read the doc\n");
    return 1;
  }

  /* Ok assign the operations */
  codec->name           = YCP_NAME;
  codec->codec_sizeof   = codec_sizeof;
  codec->encode.command = encode_command;
  codec->encode.data    = encode_data;
  codec->encode.message = encode_message;
  codec->decode.command = decode_command;
  codec->decode.data    = decode_data;
  codec->decode.message = decode_message;

  /* And return with success */
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

#undef YCP_NAME
