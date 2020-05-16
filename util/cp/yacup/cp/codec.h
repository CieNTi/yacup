/* codec.h - Codec implementation interface for `cp` util usage
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
#ifndef __CP_CODEC_H
#define __CP_CODEC_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @ingroup cp_codec
 * @{
 */

/* C libraries */
#include <stdint.h>
#include <stddef.h>
#include "yacup/rb.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Data types the codec can push or pull
 */
enum cp_codec_data_type
{
  CP_CODEC_DATA_HEAD     = 0,  CP_CODEC_DATA_TAIL      = 1,
  CP_CODEC_DATA_GLUE     = 2,  CP_CODEC_DATA_RAW_BLOCK = 3,
  CP_CODEC_DATA_UINT8_T  = 4,  CP_CODEC_DATA_INT8_T    = 5,
  CP_CODEC_DATA_UINT16_T = 6,  CP_CODEC_DATA_INT16_T   = 7,
  CP_CODEC_DATA_UINT32_T = 8,  CP_CODEC_DATA_INT32_T   = 9,
  CP_CODEC_DATA_UINT64_T = 10, CP_CODEC_DATA_INT64_T   = 11,
  CP_CODEC_DATA_FLOAT    = 12, CP_CODEC_DATA_DOUBLE    = 13,
  CP_CODEC_DATA_CHAR     = 14, CP_CODEC_DATA_STRING    = 15
};

/**
 * @brief      Structure that defines a `cp` codec operations
 */
struct cp_codec
{
  /**
   * @brief      Encoding operations
   */
  struct cp_codec_encoder
  {
    /**
     * @brief      Encodes a defined type data and pushes it into a ring-buffer
     *
     * @param[in]  type  One of `CP_CODEC_DATA_*` data types
     * @param[in]  data  Pointer where the source data to encode is located
     * @param      rb    Pointer to a destination ring-buffer
     *
     * @return     One of:
     *             | Value  | Meaning          |
     *             | :----: | :--------------- |
     *             | `== 0` | Ok               |
     *             | `!= 0` | Error            |
     */
    int (*data)(enum cp_codec_data_type type, void *data, struct rb *rb);

    /**
     * @brief      Takes an input `rb` with raw data, encodes it as a message,
     *             and puts it back into an output `rb`, ready to be decoded
     *
     * @param      in    Pointer to a source ring-buffer containing the data
     * @param      out   Pointer to a destination ring-buffer for the message
     *
     * @return     One of:
     *             | Value  | Meaning          |
     *             | :----: | :--------------- |
     *             | `== 0` | Ok               |
     *             | `!= 0` | Error            |
     */
    int (*message)(struct rb *in, struct rb *out);
  } encode;

  /**
   * @brief      Decoding operations
   */
  struct cp_codec_decoder
  {
    /**
     * @brief      Pulls and decodes a defined type data from a ring-buffer and
     *             saves it into a pointed variable
     *
     * @param[in]  in    Pointer to a source ring-buffer with encoded data
     * @param      type  One of `CP_CODEC_DATA_*` data types
     * @param      data  Pointer to a destination for decoded data
     *
     * @return     One of:
     *             | Value  | Meaning          |
     *             | :----: | :--------------- |
     *             | `== 0` | Ok               |
     *             | `!= 0` | Error            |
     */
    int (*data)(struct rb *rb, enum cp_codec_data_type type, void *data);

    /**
     * @brief      Takes an input `rb` with an encoded message, decodes it,
     *             extract its data packet, and puts into a destination `rb`
     *
     * @param      in    Pointer to a source ring-buffer containing the message
     * @param      out   Pointer to a destination ring-buffer for the data
     *
     * @return     One of:
     *             | Value  | Meaning          |
     *             | :----: | :--------------- |
     *             | `== 0` | Ok               |
     *             | `!= 0` | Error            |
     */
    int (*message)(struct rb *in, struct rb *out);
  } decode;
};

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
int cp_codec_init(struct cp_codec *codec,
                  int (*cp_codec_low_level_init)(struct cp_codec *));

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CP_CODEC_H */
