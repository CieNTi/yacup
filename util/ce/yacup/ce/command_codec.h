/* codec.h - Command engine command codec API for yacup project
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
#ifndef __CE_COMMAND_CODEC_H
#define __CE_COMMAND_CODEC_H

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
#include "yacup/ce/codec.h"
#include "yacup/ce/command.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Structure that defines a `ce_command` codec operations
 */
struct ce_command_codec
{
  /**
   * @brief      ASCII name of this codec
   */
  char *name;

  /**
   * @brief      Encodes a command as a data-block into a rb
   *
   * @param      command   Pointer to a command to be encoded
   * @param      argument  Command arguments data to encode
   * @param      codec     Pointer to a `ce` codec for data encoding operations
   * @param      rb_data   Pointer to a destination data block ring-buffer
   *
   * @return     One of:
   *             | Value  | Meaning          |
   *             | :----: | :--------------- |
   *             | `== 0` | Ok               |
   *             | `!= 0` | Error            |
   */
  size_t (*encode)(struct ce_command *command,
                   struct ce_command_argument *argument[],
                   struct ce_codec *codec,
                   struct rb *rb_data);

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
  size_t (*decode)(struct rb *rb_data,
                   struct ce_codec *codec,
                   struct ce_command_set *cmd_set);
};

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Initializes a `ce_command_codec`
 *
 * @param      codec                         Pointer to a command codec to
 *                                           initialize
 * @param      ce_command_codec_driver_init  The ce command codec driver
 *                                           initializer function
 *
 * @return     One of:
 *             | Value         | Meaning          |
 *             | :-----------: | :--------------- |
 *             | `struct ce *` | Ok               |
 *             | `NULL`        | Error            |
 */
int ce_command_codec_init(struct ce_command_codec *codec,
               int (*ce_command_codec_driver_init)(struct ce_command_codec *));

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CE_COMMAND_CODEC_H */
