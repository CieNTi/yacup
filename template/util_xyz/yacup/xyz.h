/* xyz.h - XYZ implementation for yacup project
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
#ifndef __XYZ_H
#define __XYZ_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup xyz X Y Z
 * @{
 *   @brief      `xyz` description, seen on `modules` view
 *   @details    `xyz` detailed description, seen once clicked the module
 *   @author     CieNTi <cienti@cienti.com>
 *   @date       2020
 *
 *   @defgroup   xyz_api Interface
 *   @{
 *     @brief      Operations over `xyz` instances
 *     @details    Centralized functions to allow multiple implementations
 *     @author     CieNTi <cienti@cienti.com>
 *     @date       2020
 *   @}
 *
 *   @defgroup   xyz_driver Drivers
 *   @{
 *     @brief      Operations driver for `xyz` instances
 *     @details    Different XYZ implementations interfaces
 *     @author     CieNTi <cienti@cienti.com>
 *     @date       2020
 *   @}
 * @}
 * 
 * @ingroup   xyz_api
 * @{
 */

/* C libraries */
#include <stdint.h>
#include <stddef.h>

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Structure that defines a XYZ
 */
struct xyz
{
  /** 
   * @brief      Pointer to `uint8_t` buffer
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
 * @brief      Configure `xyz` instance
 *
 * @param      xyz     Pointer to a XYZ
 * @param      buffer  The buffer
 * @param[in]  size    The size
 *
 * @return     One of:
 *             | Value  | Meaning          |
 *             | :----: | :--------------- |
 *             | `== 0` | Ok               |
 *             | `!= 0` | Error            |
 */
int xyz_setup(struct xyz *xyz, uint8_t *buffer, size_t size);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __XYZ_H */
