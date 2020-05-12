/* header.h - Brief one-liner explanation of this file inside the project
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
#ifndef __HEADER_H
#define __HEADER_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup template
 * @{
 *   @brief      Template module from template files xD
 *   @details    A more elaborated description with an example:
 *   ```c
 *   struct nice_structure nice_var =
 *   {
 *     .buffer = NULL,
 *     .len    = 0,
 *     .fn_pt  = NULL
 *   };
 *   ```
 *   @author     CieNTi <cienti@cienti.com>
 *   @date       2020
 */

/* C libraries */
#include <stdint.h>
#include <stddef.h>

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      A nice structure briefly described
 */
struct nice_structure
{
  /** 
   * @brief      Pointer to bytes `uint8_t` buffer
   */
  uint8_t *buffer;
  /** 
   * @brief      Some length
   */
  size_t len;
  /**
   * @brief      A pointer to a `main()`-like function
   *
   * @param      argc  Number of arguments. At least 1
   * @param      argv  Program arguments
   *
   * @return     One of:
   *             | Value  | Meaning          |
   *             | :----: | :--------------- |
   *             | `== 0` | Ok               |
   *             | `!= 0` | Error            |
   */
  int (*fn_pt)(int argc, const char* argv[]);
};


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Check if a nice_structure is valid or not
 *
 * @param      nice  The nice structure pointer
 *
 * @return     One of:
 *             | Value  | Meaning          |
 *             | :----: | :--------------- |
 *             | `== 0` | Ok               |
 *             | `!= 0` | Error            |
 */
uint8_t nice_is_not_nice(struct nice_structure *nice);

/**
 * @brief      Initialize a nice structure
 *
 * @param      buffer  The buffer
 * @param[in]  size    The size
 *
 * @return     One of:
 *             | Value  | Meaning          |
 *             | :----: | :--------------- |
 *             | `== 0` | Ok               |
 *             | `!= 0` | Error            |
 */
struct nice_structure *nice_init(uint8_t *buffer, size_t size);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __HEADER_H */
