/* driver_v1.h - Driver for yacup ring-buffers. First implementation
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
#ifndef __RB_DRIVER_V1_H
#define __RB_DRIVER_V1_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup rb_driver
 * @{
 */

/* C libraries */
#include <stdint.h>
#include <stddef.h>

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Ring-buffer operations driver v1
 * @details    Composes a `rb_op` structure and returns it as a pointer.
 * 
 *             This set of operations belongs to a first driver implementation,
 *             where a ring-buffer tail byte is overwritten if pushing over a
 *             full `rb`. This operation is performed without any warning or
 *             error.
 *             
 *             If it is needed to preserve data under this circumstances, a new
 *             driver have to be implemented.
 *
 * @return     One of:
 *             | Value            | Meaning          |
 *             | :--------------: | :--------------- |
 *             | `struct rb_op *` | Ok               |
 *             | `NULL`           | Error            |
 *
 * @version    v1.0.0
 */
struct rb_op *rb_driver_v1(void);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __RB_DRIVER_V1_H */
