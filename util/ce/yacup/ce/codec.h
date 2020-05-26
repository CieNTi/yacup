/* codec.h - Command engine codec API for yacup project
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
#ifndef __CE_CODEC_H
#define __CE_CODEC_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup   ce_api
 * @{
 */

/* C libraries */
#include <stdint.h>
#include <stddef.h>
#include "yacup/rb.h"
#include "yacup/ce/types.h"
#include "yacup/ce/command.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Structure that defines a `ce` codec encoder operations
 */
struct ce_codec_encoder
{
  /**
   * @brief      Encodes a defined type data and pushes it into a ring-buffer
   *
   * @param      type      One of `CE_DATA_*` data types
   * @param      data      Pointer where the source data to encode is located
   * @param      num_data  Number of data entities to encode
   * @param      rb        Pointer to a destination ring-buffer
   *
   * @return     One of:
   *             | Value  | Meaning                         |
   *             | :----: | :------------------------------ |
   *             | `== 0` | No encoded data                 |
   *             | `>  0` | Number of encoded data entities |
   */
  size_t (*data)(enum ce_data_type type,
                 void *data, size_t num_data,
                 struct rb *rb);

  /**
   * @brief      Encodes a command as a data-block into a rb
   *
   * @param      command   Pointer to a command to be encoded
   * @param      argument  Command arguments data to encode
   * @param      rb_data   Pointer to a destination data block ring-buffer
   *
   * @return     One of:
   *             | Value  | Meaning          |
   *             | :----: | :--------------- |
   *             | `== 0` | Ok               |
   *             | `!= 0` | Error            |
   */
  size_t (*command)(struct ce_command *command,
                    struct ce_command_argument *argument[],
                    struct rb *rb_data);

  /**
   * @brief      Takes an input `rb` with raw data, encodes it as a message,
   *             and puts it back into an output `rb`, ready to be decoded
   *
   * @param      rb_data  Pointer to a ring-buffer containing the data
   * @param      rb_msg   Pointer to a ring-buffer to save the message in
   *
   * @return     One of:
   *             | Value  | Meaning          |
   *             | :----: | :--------------- |
   *             | `== 0` | Ok               |
   *             | `!= 0` | Error            |
   */
  int (*message)(struct rb *rb_data, struct rb *rb_msg);
};

/**
 * @brief      Structure that defines a `ce` codec encoder operations
 */
struct ce_codec_decoder
{
  /**
   * @brief      Pulls and decodes a defined type data from a ring-buffer and
   *             saves it into a pointed variable
   *
   * @param      rb        Pointer to a source ring-buffer with encoded data
   * @param      type      One of `CE_DATA_*` data types
   * @param      data      Pointer to a destination for decoded data
   * @param      num_data  Number of data entities to decode
   *
   * @return     One of:
   *             | Value  | Meaning                         |
   *             | :----: | :------------------------------ |
   *             | `== 0` | No decoded data                 |
   *             | `>  0` | Number of decoded data entities |
   */
  size_t (*data)(struct rb *rb,
                 enum ce_data_type type,
                 void *data, size_t num_data);

  /**
   * @brief      Decodes a data-block into a validated command with arguments
   * @todo       Is this the parser to listener call?
   *
   * @param      rb_data   Pointer to a destination data block ring-buffer
   * @param      codec     Pointer to a `ce` codec for data decoding operations
   * @param      cmd_set   Set of commands where to search for commands
   *
   * @return     One of:
   *             | Value  | Meaning          |
   *             | :----: | :--------------- |
   *             | `== 0` | Ok               |
   *             | `!= 0` | Error            |
   */
  size_t (*command)(struct rb *rb_data,
                    struct ce_command_set *cmd_set);

  /**
   * @brief      Takes an input `rb` with an encoded message, decodes it,
   *             extract its data packet, and puts into a destination `rb`
   *
   * @param      rb_msg   Pointer to a ring-buffer containing the message
   * @param      rb_data  Pointer to a ring-buffer to save the data in
   *
   * @return     One of:
   *             | Value  | Meaning          |
   *             | :----: | :--------------- |
   *             | `== 0` | Ok               |
   *             | `!= 0` | Error            |
   */
  int (*message)(struct rb *rb_msg, struct rb *rb_data);
} ;
  
/**
 * @brief      Structure that defines a `ce` codec operations
 */
struct ce_codec
{
  /**
   * @brief      ASCII name of this codec
   */
  char *name;

  /**
   * @brief      Bytes the codec will use to store/retrieve a type
   * 
   * @param      type      One of *ce_data_type*'s `CE_DATA_*` data types
   * 
   * @return     One of:
   *             | Value  | Meaning                               |
   *             | :----: | :------------------------------------ |
   *             | `== 0` | Invalid type or not supported         |
   *             | `>  0` | Length in bytes of the requested data |
   */
  size_t (*codec_sizeof)(enum ce_data_type type);

  /**
   * @brief      Encoding operations
   */
  struct ce_codec_encoder encode;

  /**
   * @brief      Decoding operations
   */
  struct ce_codec_decoder decode;
};

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Initializes a `ce_codec`
 * @details    Checks and initializes `ce_codec` common data, then calls the
 *             lower level init function passed by argument. The latter is
 *             defined at each `ce_codec` unit, and it is where the encoding and
 *             decoding functions are really assigned.
 *
 * @param      codec                 Pointer to a codec to initialize
 * @param      ce_codec_driver_init  The ce codec driver initializer function
 *
 * @return     One of:
 *             | Value  | Meaning          |
 *             | :----: | :--------------- |
 *             | `== 0` | Ok               |
 *             | `!= 0` | Error            |
 */
int ce_codec_init(struct ce_codec *codec,
                  int (*ce_codec_driver_init)(struct ce_codec *));

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CE_CODEC_H */
