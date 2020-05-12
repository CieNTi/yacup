/* debug.h - Debug functions to ease `rb` development flow
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
#ifndef __RB_DEBUG_H
#define __RB_DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @ingroup debug_functions
 * @{
 */

/* C libraries */
#include "yacup/rb.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Print `rb` information to STDOUT (size, head, tail, ...)
 *
 * @param      rb    Pointer to a ring-buffer previously created with
 *                   rb_create()
 */
void rb_print_info(struct rb *rb);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __RB_DEBUG_H */
