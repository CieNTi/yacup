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
/* Encodes a defined type data and pushes it into a ring-buffer
 * WARNING: Assumed `cp/cp.c` pre-validation. Not safe as direct call!
 * Read `yacup/cp/codec.h` for complete information. */
static int encode_data(enum cp_codec_data_type type, void *data, struct rb *rb)
{
  /* Configure _dbg() */
  #define YCP_FNAME "encode_data"

  _dbg("Entering!\n");
  rb_push(rb, *(uint8_t *)data);

  /* Ok! */
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

/* Pulls and decodes data from a ring-buffer and saves it into variable
 * WARNING: Assumed `cp/cp.c` pre-validation. Not safe as direct call!
 * Read `yacup/cp/codec.h` for complete information. */
static int decode_data(struct rb *rb, enum cp_codec_data_type type, void *data)
{
  /* Configure _dbg() */
  #define YCP_FNAME "decode_data"

  _dbg("Entering!\n");
  rb_pull(rb, (uint8_t *)data);

  /* Ok! */
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

/* Takes `rb` raw data, encodes it as a message, and puts it back as `rb`
 * WARNING: Assumed `cp/cp.c` pre-validation. Not safe as direct call!
 * Read `yacup/cp/codec.h` for complete information. */
static int encode_message(struct rb *in, struct rb *out)
{
  /* Configure _dbg() */
  #define YCP_FNAME "encode_message"

  _dbg("Entering!\n");

  /* Ok! */
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

/* Read and delete a byte from a comm-protocol tail.
 * WARNING: Assumed `cp/cp.c` pre-validation. Not safe as direct call!
 * Read `yacup/cp/codec.h` for complete information. */
static int decode_message(struct rb *in, struct rb *out)
{
  /* Configure _dbg() */
  #define YCP_FNAME "decode_message"

  _dbg("Entering!\n");

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
