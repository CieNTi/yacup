/* fsm_driver_simple.h - A simple `fsm` driver for testing purposes
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
#ifndef __FSM_DRIVER_SIMPLE_H
#define __FSM_DRIVER_SIMPLE_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup   fsm_driver_simple Simple FSM
 * @{
 *   @brief      A simple finite state machine for testing purposes
 *   @details    This FSM just starts, execute state_1 5 times and finish
 *   @ingroup    fsm_driver
 *   @author     CieNTi <cienti@cienti.com>
 *   @date       2020
 */

/* C libraries */
#include <stddef.h>
#include "yacup/fsm.h"
#include "yacup/fsm/driver.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Internal data fsm_driver_simple will use
 */
struct fsm_driver_simple_data
{
  /**
   * @brief      Number of cycles the FSM passed over state_1
   */
  size_t cycles;
};

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Low-level initializer function for `fsm_driver_simple` type FSM
 * @details    This FSM just starts, execute `state_1` 5 times and finish
 *
 * @param      fsm   Pointer to a `fsm` to work with
 *
 * @return     One of:
 *             | Value  | Meaning          |
 *             | :----: | :--------------- |
 *             | `== 0` | Ok               |
 *             | `!= 0` | Error            |
 */
int fsm_driver_simple(struct fsm *fsm);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __FSM_DRIVER_SIMPLE_H */
