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
#ifndef __RB_H
#define __RB_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup fsm_available
 * @{
 */

/* C libraries */
//#include <stdint.h>
//#include <stddef.h>

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Create and initialize a `fsm_simple` type FSM
 * @details    This FSM just starts, execute state_1 5 times and stop
 *
 * @param      name  FSM name (data is not saved, only the pointer)
 *
 * @return     One of:
 *             | Value          | Meaning          |
 *             | :------------: | :--------------- |
 *             | `struct fsm *` | Ok               |
 *             | `NULL`         | Error            |
 */
struct fsm *fsm_simple_create(char *name);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __RB_H */
