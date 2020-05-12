/* fsm_simple.h - A simple finite state machine for testing purposes
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
#ifndef __FSM_SIMPLE_H
#define __FSM_SIMPLE_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup fsm_available
 * @{
 *   @defgroup   fsm_simple Simple FSM
 *   @{
 *     @brief      A simple finite state machine for testing purposes
 *     @details    This FSM just starts, execute state_1 5 times and finish
 *     @author     CieNTi <cienti@cienti.com>
 *     @date       2020
 *   @}
 * @}
 *
 * @ingroup fsm_simple
 * @{
 */

/* C libraries */
#include <stddef.h>
#include "yacup/fsm.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Internal data fsm_simple will use
 */
struct fsm_simple_data
{
  /**
   * @brief      Number of cycles the FSM passed over state_1
   */
  size_t cycles;
};

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Create and initialize a `fsm_simple` type FSM
 * @details    This FSM just starts, execute `state_1` 5 times and finish
 *
 * @param      fsm   fsm pointer to work with. Valid if returns without errors
 *
 * @return     One of:
 *             | Value  | Meaning          |
 *             | :----: | :--------------- |
 *             | `== 0` | Ok               |
 *             | `!= 0` | Error            |
 */
int fsm_simple_setup(struct fsm *fsm);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __FSM_SIMPLE_H */
