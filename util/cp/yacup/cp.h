/* cp.h - CP implementation for yacup project
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
 * @defgroup cp Communications protocols
 * @{
 *   @brief      Yet another communications protocols implementation
 *   @details    Communications protocols made easy (for me xD)
 *   @author     CieNTi <cienti@cienti.com>
 *   @date       2020
 *
 *   @defgroup   cp_api Interface
 *   @{
 *     @brief      Operations over `cp` instances
 *     @details    Centralized functions to allow multiple implementations
 *     @author     CieNTi <cienti@cienti.com>
 *     @date       2020
 *   @}
 *
 *   @defgroup   cp_driver Drivers
 *   @{
 *     @brief      Operations driver for `cp` instances
 *     @details    Different communication protocols implementations interfaces
 *     @author     CieNTi <cienti@cienti.com>
 *     @date       2020
 *   @}
 * @}
 * 
 * @ingroup   cp_api
 * @{
 */

/* C libraries */
#include <stdint.h>
#include <stddef.h>

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Structure that defines a communication protocol
 */
struct cp
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
 * @brief      Configure `cp` instance
 *
 * @param      cp     Pointer to a CP
 * @param      buffer  The buffer
 * @param[in]  size    The size
 *
 * @return     One of:
 *             | Value  | Meaning          |
 *             | :----: | :--------------- |
 *             | `== 0` | Ok               |
 *             | `!= 0` | Error            |
 */
int cp_setup(struct cp *cp, uint8_t *buffer, size_t size);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CP_H */
