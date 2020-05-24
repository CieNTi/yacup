/* command.h - Command API for `ce` util usage
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
#ifndef __CE_CHANNEL_H
#define __CE_CHANNEL_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup ce_command
 * @{
 */

/* C libraries */
#include <stdint.h>
#include <stddef.h>
#include "yacup/rb.h"
#include "yacup/ce/types.h"
#include "yacup/ce/command.h"
#include "yacup/ce/codec.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Structure that defines a command engine channel
 */
struct ce_channel
{
  /**
   * @brief      Available commands set for this channel
   */
  struct ce_command_set *command_set;

  /**
   * @brief      Codec used to encode/decode channel data/messages
   */
  struct ce_codec       codec;

  /**
   * @brief      Ring-buffer for codec messages (links with low level I/O)
   */
  struct rb             rb;
};

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Checks if passed command is found on set and has valid arguments
 *
 * @param      cmd_set   Set of commands where to search
 * @param      id        Unique command identifier of the command to validate
 * @param      argument  Arguments to check against command signature
 *
 * @return     
 *             | Value  | Meaning          |
 *             | :----: | :--------------- |
 *             | `== 0` | Ok               |
 *             | `!= 0` | Warning          |
 */
int ce_channel_init(struct ce_channel *channel,
                    struct ce_command_set *command_set,
                    int (*channels_codec_driver_init)(struct ce_codec *),
                    int (*channels_rb_driver_init)(struct rb *));

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CE_CHANNEL_H */
