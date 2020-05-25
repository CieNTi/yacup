/* ce.h - Command engine API for yacup project
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
#ifndef __CE_H
#define __CE_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup ce Command Engine
 * @{
 *   @brief      Yet another command engine implementation
 *   @details    Command engine made easy (for me xD)
 *   @author     CieNTi <cienti@cienti.com>
 *   @date       2020
 *
 *   @defgroup   ce_api Interface
 *   @{
 *     @brief      Operations on `ce` instances
 *     @details    Centralized functions to allow multiple implementations
 *     @author     CieNTi <cienti@cienti.com>
 *     @date       2020
 *   @}
 * @}
 * 
 * @addtogroup   ce_api
 * @{
 */

/* C libraries */
#include <stdint.h>
#include <stddef.h>
#include "yacup/fsm.h"
#include "yacup/ce/types.h"
#include "yacup/ce/driver.h"
#include "yacup/ce/channel.h"
#include "yacup/ce/command.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Structure that defines a command engine
 */
struct ce
{
  /**
   * @brief      ASCII name of this commands engine
   */
  char *name;

  /**
   * @brief      Input/Output chat between parties (protocol)
   */
  struct ce_driver driver;

  /**
   * @brief      Output channel
   */
  struct ce_channel out;

  /**
   * @brief      Input channel
   */
  struct ce_channel in;
};


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Initializes a command engine referenced by a `ce` pointer
 * @details    Checks and initializes `ce` common data, then calls the lower
 *             level init function passed by argument.
 *
 * @param      ce                Pointer to a CE to initialize
 * @param[in]  chat_driver_init  Pointer to a chat initializer function
 *
 * @return     One of:
 *             | Value  | Meaning          |
 *             | :----: | :--------------- |
 *             | `== 0` | Ok               |
 *             | `!= 0` | Error            |
 */
int ce_init(struct ce *ce,
            int (*ce_driver_init)(struct ce *),
            int (*channels_codec_driver_init)(struct ce_codec *),
            int (*channels_rb_driver_init)(struct rb *));

/**
 * @brief      Executes a command engine chat `fsm` cycle. Required if data is
 *             expected to be received and/or parsed
 *
 * @param      ce    Pointer to the command engine to tick
 *
 * @return     One of:
 *             | Value  | Meaning          |
 *             | :----: | :--------------- |
 *             | `== 0` | Ok               |
 *             | `!= 0` | Error            |
 */
int ce_tick(struct ce *ce);

/**
 * @brief      Validates if a command is found in a set, and if it pass the
 *             signature check, then encode its data into a message and send it
 *
 * @param      ce        Pointer to the engine that will handle this command
 * @param      id        Unique command identifier of the command to send
 * @param      argument  Arguments to check against command signature and send
 *
 * @return     One of:
 *             | Value  | Meaning          |
 *             | :----: | :--------------- |
 *             | `== 0` | Ok               |
 *             | `!= 0` | Error            |
 */
int ce_send_command(struct ce *ce,
                    size_t id,
                    struct ce_command_argument *argument[]);

/**
 * @brief      Set a command listener, if found in a set
 *
 * @param      ce        Pointer to the engine that will handle this command
 * @param      id        Unique command identifier of the command to send
 * @param      listener  Incoming command listener
 *
 * @return     One of:
 *             | Value  | Meaning          |
 *             | :----: | :--------------- |
 *             | `== 0` | Ok               |
 *             | `!= 0` | Error            |
 */
int ce_set_command_listener(struct ce *ce,
                            size_t id,
                            struct ce_command_listener *listener);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CE_H */
