/* B416K.c - Binary 4-byte + CRC-16/Kermit codec for `cp` util
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
#include "yacup/cp.h"
#include "yacup/cp/codec.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include "yacup/debug.h"
#undef YCP_NAME
#define YCP_NAME "util/cp/codec/B416K"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
static size_t codec_sizeof(enum cp_codec_data_type type)
{
  /* Configure _dbg() */
  #define YCP_FNAME "codec_sizeof"

   switch(type)
  {
    case CP_CODEC_DATA_CHAR:
      _dbg("Selected data type CP_CODEC_DATA_CHAR\n");
      return (sizeof(char));
      break;
    case CP_CODEC_DATA_UINT8_T:
      _dbg("Selected data type CP_CODEC_DATA_UINT8_T\n");
      return (sizeof(uint8_t));
      break;
    case CP_CODEC_DATA_INT8_T:
      _dbg("Selected data type CP_CODEC_DATA_INT8_T\n");
      return (sizeof(int8_t));
      break;
    case CP_CODEC_DATA_UINT16_T:
      _dbg("Selected data type CP_CODEC_DATA_UINT16_T\n");
      return (sizeof(uint16_t));
      break;
    case CP_CODEC_DATA_INT16_T:
      _dbg("Selected data type CP_CODEC_DATA_INT16_T\n");
      return (sizeof(int16_t));
      break;
    case CP_CODEC_DATA_UINT32_T:
      _dbg("Selected data type CP_CODEC_DATA_UINT32_T\n");
      return (sizeof(uint32_t));
      break;
    case CP_CODEC_DATA_INT32_T:
      _dbg("Selected data type CP_CODEC_DATA_INT32_T\n");
      return (sizeof(int32_t));
      break;
    case CP_CODEC_DATA_UINT64_T:
      _dbg("Selected data type CP_CODEC_DATA_UINT64_T\n");
      return (sizeof(uint64_t));
      break;
    case CP_CODEC_DATA_INT64_T:
      _dbg("Selected data type CP_CODEC_DATA_INT64_T\n");
      return (sizeof(int64_t));
      break;
    case CP_CODEC_DATA_FLOAT:
      _dbg("Selected data type CP_CODEC_DATA_FLOAT\n");
      return (sizeof(float));
      break;
    case CP_CODEC_DATA_DOUBLE:
      _dbg("Selected data type CP_CODEC_DATA_DOUBLE\n");
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

/* Encodes a defined type data and pushes it into a ring-buffer
 * WARNING: Assumed `cp/cp.c` pre-validation. Not safe as direct call!
 * Read `yacup/cp/codec.h` for complete information. */
static size_t encode_data(struct rb *rb,
                          enum cp_codec_data_type type,
                          void *data, size_t num_data)
{
  /* Configure _dbg() */
  #define YCP_FNAME "encode_data"

  size_t idx_data = 0;
  size_t len_bytes = 0;
  size_t idx_byte = 0;
  uint8_t *data_pt = NULL;

  /* TBD / TODO: Can be a codec configuration */
  uint8_t big_endian = 1;

  len_bytes = codec_sizeof(type);
  for (idx_data = 0; idx_data < num_data; idx_data++)
  {
    _dbg("Pushing %lu/%lu data\n", idx_data + 1, num_data); 
    for (idx_byte = 0; idx_byte < len_bytes; idx_byte++)
    {
      /* Select endianess */
      if (big_endian)
      {
        data_pt = (uint8_t *)data + (idx_data * len_bytes) + idx_byte;
        _dbg("Pushing %lu/%lu bytes. Source: %p = %u\n",
             idx_byte + 1, len_bytes, data_pt, *data_pt);
        if (rb_push(rb, *data_pt))
        {
          /* We expected that bytes to be here, should be error or warning? */
          return idx_data;
        }
      }
    }
  }

  /* Ok! */
  return idx_data;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

/* Pulls and decodes data from a ring-buffer and saves it into variable
 * WARNING: Assumed `cp/cp.c` pre-validation. Not safe as direct call!
 * Read `yacup/cp/codec.h` for complete information. */
static size_t decode_data(struct rb *rb,
                          enum cp_codec_data_type type,
                          void *data, size_t num_data)
{
  /* Configure _dbg() */
  #define YCP_FNAME "decode_data"

  size_t idx_data = 0;
  size_t len_bytes = 0;
  size_t idx_byte = 0;
  uint8_t *data_pt = NULL;

  /* TBD / TODO: Can be a codec configuration */
  uint8_t big_endian = 1;

  len_bytes = codec_sizeof(type);
  for (idx_data = 0; idx_data < num_data; idx_data++)
  {
    _dbg("Pulling %lu/%lu data\n", idx_data + 1, num_data); 
    for (idx_byte = 0; idx_byte < len_bytes; idx_byte++)
    {
      /* Select endianess */
      if (big_endian)
      {
        data_pt = (uint8_t *)data + (idx_data * len_bytes) + idx_byte;
        if (rb_pull(rb, data_pt))
        {
          /* We expected that bytes to be here, should be error or warning? */
          return idx_data;
        }
        _dbg("Pulling %lu/%lu bytes. Target: %p = %u\n",
             idx_byte + 1, len_bytes, data_pt, *data_pt);
      }
    }
  }

  /* Ok! */
  return idx_data;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

/* Takes `rb` raw data, encodes it as a message, and puts it back as `rb`
 * WARNING: Assumed `cp/cp.c` pre-validation. Not safe as direct call!
 * Read `yacup/cp/codec.h` for complete information. */
static int encode_message(struct rb *rb_in, struct rb *rb_out)
{
  /* Configure _dbg() */
  #define YCP_FNAME "encode_message"

  uint8_t data_holder = 0;

  /* Push header */
  if (rb_push(rb_out, 0xEA) ||
      rb_push(rb_out, (uint8_t)(rb_len(rb_in) >> 8)) ||
      rb_push(rb_out, (uint8_t)(rb_len(rb_in)))
      )
  {
    /* Cannot push, error */
    return 1;
  }

  /* Move data */
  while (rb_pull(rb_in, &data_holder) == 0)
  {
    if (rb_push(rb_out, data_holder))
    {
      /* Fial! Out of destination space */
      return 1;
    }
  }

  /* Ok! */
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

/* Read and delete a byte from a comm-protocol tail.
 * WARNING: Assumed `cp/cp.c` pre-validation. Not safe as direct call!
 * Read `yacup/cp/codec.h` for complete information. */
static int decode_message(struct rb *rb_in, struct rb *rb_out)
{
  /* Configure _dbg() */
  #define YCP_FNAME "decode_message"

  uint8_t data_holder = 0;
  size_t data_len = 0;

  /* Pull header */
  if (rb_pull(rb_in, &data_holder) ||
      (data_holder != 0xEA)        ||
      rb_pull(rb_in, &data_holder))
  {
    /* Cannot push, error */
    return 1;
  }

  /* Compose data length */
  data_len = data_holder;
  if (rb_pull(rb_in, &data_holder))
  {
    /* Cannot push, error */
    return 1;
  }
  data_len <<= 8;
  data_len += data_holder;
  _dbg("We need to read %lu bytes of data packet\n", data_len);

  /* Move data */
  while (rb_pull(rb_in, &data_holder) == 0)
  {
    if (rb_push(rb_out, data_holder))
    {
      /* Fial! Out of destination space */
      return 1;
    }
  }

  /* Ok! */
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

/* Initialize a `B416K` type comm-protocol codec.
 * Read `yacup/cp/codec.h` for complete information. */
int cp_codec_B416K(struct cp_codec *codec)
{
  /* Configure _dbg() */
  #define YCP_FNAME "cp_codec_B416K"

  /* Valid codec? */
  if (codec == NULL)
  {
    _dbg("Direct calls not recommended, read the doc\n");
    return 1;
  }

  /* Ok assign the operations */
  codec->encode.data    = encode_data;
  codec->encode.message = encode_message;
  codec->decode.data    = decode_data;
  codec->decode.message = decode_message;

  /* And return with success */
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

#undef YCP_NAME
