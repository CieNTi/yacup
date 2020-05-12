/* rb.h - Ring buffers implementation for yacup project
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
 * @defgroup rb Ring-buffers
 * @{
 *   @brief      Yet another ring-buffer implementation
 *   @details    Ring buffer made easy (for me xD)
 *   @author     CieNTi <cienti@cienti.com>
 *   @date       2020
 *
 *   @defgroup   rb_api Interface
 *   @{
 *     @brief      Operations over `rb` instances
 *     @details    Centralized functions to allow multiple implementations
 *     @author     CieNTi <cienti@cienti.com>
 *     @date       2020
 *   @}
 *
 *   @defgroup   rb_driver Drivers
 *   @{
 *     @brief      Operations driver for `rb` instances
 *     @details    Different ring buffer implementations interfaces
 *     @author     CieNTi <cienti@cienti.com>
 *     @date       2020
 *   @}
 * @}
 * 
 * @addtogroup   rb_api
 * @{
 */

/* C libraries */
#include <stdint.h>
#include <stddef.h>

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Structure that defines a ring buffer
 */
struct rb
{
  /**
   * @brief      Pointer to real reserved data holder (provided by the user)
   */
  uint8_t *buffer;

  /**
   * @brief      Total amount of space on buffer that we can use
   */
  size_t  size;

  /**
   * @brief      Location inside buffer where to place the next byte
   */
  size_t  head;

  /**
   * @brief      Location inside buffer where the first valid data resides
   */
  size_t  tail;

  /**
   * @brief      Used to mark if head did overflow or not
   */
  uint8_t head_of;

  /**
   * @brief      Pointer to a operations structure
   */
  struct rb_op *op;
};

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Create and initialize a ring-buffer. User needs to previously
 *             reserve a buffer
 *
 * @param      buf     Buffer to store the data, created by the user
 * @param[in]  size    Size in bytes of the buffer
 * @param      driver  Pointer to a driver initializer function
 *
 * @return     One of:
 *             | Value         | Meaning          |
 *             | :-----------: | :--------------- |
 *             | `struct rb *` | Ok               |
 *             | `NULL`        | Error            |
 */
struct rb *rb_create(uint8_t *buf, size_t size, struct rb_op *(*driver)(void));

/**
 * @brief      Destroy a ring-buffer and free its resources. User needs to
 *             destroy the buffer
 *
 * @param      rb    Pointer to a ring-buffer previously created with
 *                   rb_create()
 */
void rb_destroy(struct rb *rb);

/**
 * @brief      Reset a ring-buffer by cleaning its content and making it empty
 *
 * @param      rb    Pointer to a ring-buffer previously created with
 *                   rb_create()
 */
void rb_reset(struct rb *rb);

/**
 * @brief      Add a byte to a ring-buffer head, overwritting if needed
 *
 * @param      rb    Pointer to a ring-buffer previously created with
 *                   rb_create()
 * @param[in]  byte  Byte to be pushed into the ring-buffer
 *
 * @return     One of:
 *             | Value  | Meaning          |
 *             | :----: | :--------------- |
 *             | `== 0` | Ok               |
 *             | `!= 0` | Error            |
 */
int rb_push(struct rb *rb, uint8_t byte);

/**
 * @brief      Read and delete a byte from a ring-buffer tail
 *
 * @param      rb    Pointer to a ring-buffer previously created with
 *                   rb_create()
 * @param      byte  Pointer to byte where to write the pushed value
 *
 * @return     One of:
 *             | Value  | Meaning          |
 *             | :----: | :--------------- |
 *             | `== 0` | Ok               |
 *             | `!= 0` | Error            |
 */
int rb_pull(struct rb *rb, uint8_t *byte);

/**
 * @brief      Write a byte by position on a ring-buffer, without updating
 *             head/tail.
 *
 * @param      rb        Pointer to a ring-buffer previously created with
 *                       create()
 * @param[in]  byte      Byte to be written into the ring-buffer
 * @param[in]  position  Position to read, thinking as if ring-buffer is linear
 *
 * @return     One of:
 *             | Value  | Meaning          |
 *             | :----: | :--------------- |
 *             | `== 0` | Ok               |
 *             | `!= 0` | Error            |
 */
int rb_write(struct rb *rb, uint8_t byte, size_t position);

/**
 * @brief      Read a byte by position from a ring-buffer, without updating
 *             head/tail.
 *
 * @param      rb        Pointer to a ring-buffer previously created with
 *                       rb_create()
 * @param      byte      Pointer to byte where to write the pushed value
 * @param[in]  position  Position to read, thinking as if ring-buffer is linear
 *
 * @return     One of:
 *             | Value  | Meaning          |
 *             | :----: | :--------------- |
 *             | `== 0` | Ok               |
 *             | `!= 0` | Error            |
 */
int rb_read(struct rb *rb, uint8_t *byte, size_t position);

/**
 * @brief      Returns max available size of a ring-buffer buffer
 *
 * @param      rb    Pointer to a ring-buffer previously created with
 *                   rb_create()
 *
 * @return     One of:
 *             | Value  | Meaning          |
 *             | :----: | :--------------- |
 *             | `== 0` | 0 or Error       |
 *             | `!= 0` | Valid size       |
 */
size_t rb_size(struct rb *rb);

/**
 * @brief      Returns available data size inside a ring-buffer
 *
 * @param      rb    Pointer to a ring-buffer previously created with
 *                   rb_create()
 *
 * @return     One of:
 *             | Value  | Meaning          |
 *             | :----: | :--------------- |
 *             | `== 0` | 0 or Error       |
 *             | `!= 0` | Valid size       |
 */
size_t rb_len(struct rb *rb);

/**
 * @brief      Check if a ring-buffer is full or not
 *
 * @param      rb    Pointer to a ring-buffer previously created with
 *                   rb_create()
 *
 * @return     One of:
 *             | Value  | Meaning              |
 *             | :----: | :------------------- |
 *             | `== 0` | Not empty or Error   |
 *             | `!= 0` | Empty                |
 */
uint8_t rb_full(struct rb *rb);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __RB_H */
