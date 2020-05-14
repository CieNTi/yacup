/* overwrite.h - Driver for yacup ring-buffers. Overwrite if full
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
#ifndef __RB_DRIVER_OVERWRITE_H
#define __RB_DRIVER_OVERWRITE_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup   rb_driver_overwrite Overwrite
 * @{
 *   @brief      First `rb` driver implementation, overwrite if full
 *   @details    This implementation will overwrite data if full, updating
 *               both head and tail indices without throwing an error.
 *   @ingroup    rb_driver
 *   @author     CieNTi <cienti@cienti.com>
 *   @date       2020
 */

/* C libraries */
#include <stdint.h>
#include <stddef.h>

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Low-level initializer function for `overwrite` RB driver
 * @details    Lowest level checks, variables and operations assignment to `rb`
 * 
 * This set of operations belongs to a first driver implementation, where a
 * ring-buffer tail byte is overwritten if pushing over a full `rb`. This
 * operation is performed without any warning or error.
 * 
 * If it is needed to preserve data under this circumstances, a new
 * driver have to be implemented.
 *
 * @param      rb    Pointer to a `rb` to work with
 *
 * @return     One of:
 *             | Value  | Meaning          |
 *             | :----: | :--------------- |
 *             | `== 0` | Ok               |
 *             | `!= 0` | Error            |
 */
int rb_driver_overwrite(struct rb *rb);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __RB_DRIVER_OVERWRITE_H */
