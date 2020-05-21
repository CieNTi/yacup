/* ce.h - CP implementation for yacup project
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
 * @defgroup ce Communications protocols
 * @{
 *   @brief      Yet another communications protocols implementation
 *   @details    Communications protocols made easy (for me xD)
 *   @author     CieNTi <cienti@cienti.com>
 *   @date       2020
 *
 *   @defgroup   ce_api Interface
 *   @{
 *     @brief      Operations over `ce` instances
 *     @details    Centralized functions to allow multiple implementations
 *     @author     CieNTi <cienti@cienti.com>
 *     @date       2020
 *   @}
 *
 *   @defgroup   ce_codec Codecs
 *   @{
 *     @brief      Available codecs for `ce` instances
 *     @details    Different encodings implementations ready to be used
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
#include "yacup/rb.h"
#include "yacup/fsm.h"
#include "yacup/ce/types.h"
#include "yacup/ce/codec.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Structure that defines a communication protocol
 */
struct ce
{
  struct fsm chat;
  struct ce_channel
  {
    uint8_t         busy;
    struct rb       buffer;
    struct ce_codec codec;
  } out, in;
};


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Initializes a `ce`
 * @details    Checks and initializes `ce` common data, then calls the lower
 *             level init function passed by argument. The latter is defined at
 *             each `ce` unit, and it is where the `start` and `stop` states
 *             are really assigned.
 *
 * @param      ce   Pointer to a correctly initialized FSM
 *
 * @return     One of:
 *             | Value  | Meaning          |
 *             | :----: | :--------------- |
 *             | `== 0` | Ok               |
 *             | `!= 0` | Error            |
 */
int ce_init(struct ce *ce, int (*ce_low_level_init)(struct ce *));

int ce_cycle(struct ce *ce);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CP_H */
