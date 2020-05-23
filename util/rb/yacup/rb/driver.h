/* driver.h - Ring buffers operations driver for yacup project
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
#ifndef __RB_DRIVER_H
#define __RB_DRIVER_H

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
/* Pre-declare rb struct */
struct rb;

/**
 * @brief      Structure that defines valid operations on ring buffers
 */
struct rb_driver
{
  /**
   * @brief      Checks if the ring-buffer is valid or not
   *
   * @param      rb    Pointer to a ring-buffer previously created with create()
   *
   * @return     One of:
   *             | Value  | Meaning          |
   *             | :----: | :--------------- |
   *             | `== 0` | Ok               |
   *             | `!= 0` | Error            |
   */
  int (*validate)(struct rb *rb);

  /**
   * @brief      Reset a ring-buffer by cleaning its content and making it empty
   *
   * @param      rb    Pointer to a ring-buffer previously created with create()
   */
  void (*reset)(struct rb *rb);

  /**
   * @brief      Add a byte to a ring-buffer head, overwritting if needed
   *
   * @param      rb    Pointer to a ring-buffer previously created with create()
   * @param[in]  byte  Byte to be pushed into the ring-buffer
   *
   * @return     One of:
   *             | Value  | Meaning          |
   *             | :----: | :--------------- |
   *             | `== 0` | Ok               |
   *             | `!= 0` | Error            |
   */
  int (*push)(struct rb *rb, uint8_t byte);

  /**
   * @brief      Read and delete a byte from a ring-buffer tail
   *
   * @param      rb    Pointer to a ring-buffer previously created with create()
   * @param      byte  Pointer to byte where to write the pushed value
   *
   * @return     One of:
   *             | Value  | Meaning          |
   *             | :----: | :--------------- |
   *             | `== 0` | Ok               |
   *             | `!= 0` | Error            |
   */
  int (*pull)(struct rb *rb, uint8_t *byte);

  /**
   * @brief      Write a byte by position on a ring-buffer, without updating
   *             head/tail.
   *
   * @param      rb        Pointer to a ring-buffer previously created with
   *                       create()
   * @param[in]  byte      Byte to be written into the ring-buffer
   * @param[in]  position  Position to read, thinking as if ring-buffer is
   *                       linear
   *
   * @return     One of:
   *             | Value  | Meaning          |
   *             | :----: | :--------------- |
   *             | `== 0` | Ok               |
   *             | `!= 0` | Error            |
   */
  int (*write)(struct rb *rb, uint8_t byte, size_t position);

  /**
   * @brief      Read a byte by position from a ring-buffer, without updating
   *             head/tail.
   *
   * @param      rb        Pointer to a ring-buffer previously created with
   *                       create()
   * @param      byte      Pointer to byte where to write the pushed value
   * @param[in]  position  Position to read, thinking as if ring-buffer is
   *                       linear
   *
   * @return     One of:
   *             | Value  | Meaning          |
   *             | :----: | :--------------- |
   *             | `== 0` | Ok               |
   *             | `!= 0` | Error            |
   */
  int (*read)(struct rb *rb, uint8_t *byte, size_t position);

  /**
   * @brief      Returns max available size of a ring-buffer buffer
   *
   * @param      rb    Pointer to a ring-buffer previously created with create()
   *
   * @return     One of:
   *             | Value  | Meaning          |
   *             | :----: | :--------------- |
   *             | `== 0` | 0 or Error       |
   *             | `!= 0` | Valid size       |
   */
  size_t (*size)(struct rb *rb);

  /**
   * @brief      Returns available data size inside a ring-buffer
   *
   * @param      rb    Pointer to a ring-buffer previously created with create()
   *
   * @return     One of:
   *             | Value  | Meaning          |
   *             | :----: | :--------------- |
   *             | `== 0` | 0 or Error       |
   *             | `!= 0` | Valid size       |
   */
  size_t (*len)(struct rb *rb);

  /**
   * @brief      Check if a ring-buffer is full or not
   *
   * @param      rb    Pointer to a ring-buffer previously created with create()
   *
   * @return     One of:
   *             | Value  | Meaning              |
   *             | :----: | :------------------- |
   *             | `== 0` | Not empty or Error   |
   *             | `!= 0` | Empty                |
   */
  uint8_t (*full)(struct rb *rb);
};

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __RB_DRIVER_H */
