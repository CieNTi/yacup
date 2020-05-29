/* debug.h - Debug functions to ease `fsm` development flow
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
#ifndef __FSM_DEBUG_H
#define __FSM_DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup debug_functions
 * @{
 */

/* C libraries */
#include "yacup/fsm.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Print `fsm` information to STDOUT (name, config, state, ...)
 *
 * @param      fsm    Pointer to a valid `fsm`
 */
void fsm_print_info(struct fsm *fsm);

/**
 * @brief      Print `fsm` stats to STDOUT (how many times each run-state has
 *             been executed/cycled)
 *
 * @param      fsm   Pointer to a valid `fsm`
 */
void fsm_print_stats(struct fsm *fsm);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __FSM_DEBUG_H */
