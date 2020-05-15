/* cp.h - CP implementation for yacup project
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
#ifndef __CP_H
#define __CP_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup cp Communications protocols
 * @{
 *   @brief      Yet another communications protocols implementation
 *   @details    Communications protocols made easy (for me xD)
 *   @author     CieNTi <cienti@cienti.com>
 *   @date       2020
 *
 *   @defgroup   cp_api Interface
 *   @{
 *     @brief      Operations over `cp` instances
 *     @details    Centralized functions to allow multiple implementations
 *     @author     CieNTi <cienti@cienti.com>
 *     @date       2020
 *   @}
 *
 *   @defgroup   cp_codec Codecs
 *   @{
 *     @brief      Available codecs for `cp` instances
 *     @details    Different encodings implementations ready to be used
 *     @author     CieNTi <cienti@cienti.com>
 *     @date       2020
 *   @}
 * @}
 * 
 * @ingroup   cp_api
 * @{
 */

/* C libraries */
#include <stdint.h>
#include <stddef.h>
#include "yacup/rb.h"
#include "yacup/fsm.h"
#include "yacup/cp/codec.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Structure that defines a cp channel
 */
struct cp_channel
{
  uint8_t         busy;
  uint8_t         data_ready;
  struct rb       buffer;
  struct fsm      chat;
  struct cp_codec codec;
};

/**
 * @brief      Structure that defines a communication protocol
 */
struct cp
{
  struct cp_channel out;
  struct cp_channel in;
};


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Initializes a `cp`
 * @details    Checks and initializes `cp` common data, then calls the lower
 *             level init function passed by argument. The latter is defined at
 *             each `cp` unit, and it is where the `start` and `stop` states
 *             are really assigned.
 *
 * @param      cp   Pointer to a correctly initialized FSM
 *
 * @return     One of:
 *             | Value  | Meaning          |
 *             | :----: | :--------------- |
 *             | `== 0` | Ok               |
 *             | `!= 0` | Error            |
 */
int cp_init(struct cp *cp, int (*cp_low_level_init)(struct cp *));

int cp_cycle(struct cp *cp);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CP_H */
