/* driver_v1.c - Driver for yacup ring-buffers. First implementation
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
#include <stdint.h>
#include <stddef.h>
#include "yacup/rb.h"
#include "yacup/rb/op.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#ifdef YACUP_DEBUG
  #include <time.h>
  #include <stdio.h>
  #include <string.h>
  #ifndef _dbg
    #define _dbg(...) printf(__VA_ARGS__)
  #endif
#else
  #ifndef _dbg
    #define _dbg(...)
  #endif
#endif

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* Checks if the ring-buffer is valid or not.
 * Read `yacup/rb/op.h` for complete information. */
static int validate(struct rb *rb)
{
  if (/* rb cannot be null */  
      (rb == NULL) ||
      /* Buffer cannot be null */ 
      (rb->buffer == NULL) ||
      /* Size cannot be 0 */      
      (rb->size == 0) ||
      /* Head has to be valid */  
      (rb->head >= rb->size) ||
      /* Tail has to be valid */  
      (rb->tail >= rb->size) ||
      /* Head >= tail */          
      (((rb->size * rb->head_of) + rb->head) < rb->tail))
  {
    _dbg("!| validate ~~~~~~~~~~~~~~~~~~~~~~\n"
         "!| - rb cannot be null .....: %s\n"
         "!| - Buffer cannot be null .: %s\n"
         "!| - Size cannot be 0 ......: %s\n"
         "!| - Head has to be valid ..: %s\n"
         "!| - Tail has to be valid ..: %s\n"
         "!| - Head >= tail ..........: %s\n"
         "!| ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n",
         (rb == NULL)?"FAIL":"OK",
         (rb->buffer == NULL)?"FAIL":"OK",
         (rb->size == 0)?"FAIL":"OK",
         (rb->head >= rb->size)?"FAIL":"OK",
         (rb->tail >= rb->size)?"FAIL":"OK",
         (((rb->size * rb->head_of) + rb->head) < rb->tail)?"FAIL":"OK"
         );
    _dbg("!| validate: head(%02X) vs size(%02X)\n",
         (unsigned)rb->head,
         (unsigned)rb->size);
    return 1;
  }

  /* Ok */
  return 0;
}

/* Reset a ring-buffer by cleaning its content and making it empty.
 * Read `yacup/rb/op.h` for complete information. */
static void reset(struct rb *rb)
{
  /* It is a void, just return */
  return;
}

/* Add a byte to a ring-buffer head, overwritting if needed.
 * Read `yacup/rb/op.h` for complete information. */
static int push(struct rb *rb, uint8_t byte)
{
  /* Fail */
  return 1;
}

/* Read and delete a byte from a ring-buffer tail.
 * Read `yacup/rb/op.h` for complete information. */
static int pull(struct rb *rb, uint8_t *byte)
{
  /* Fail */
  return 1;
}

/* Write a byte by position on a ring-buffer, without updating head/tail.
 * Read `yacup/rb/op.h` for complete information. */
static int write(struct rb *rb, uint8_t byte, size_t position)
{
  /* Fail */
  return 1;
}

/* Read a byte by position from a ring-buffer, without deleting it.
 * Read `yacup/rb/op.h` for complete information. */
static int read(struct rb *rb, uint8_t *byte, size_t position)
{
  /* Fail */
  return 1;
}

/* Returns max available size of a ring-buffer buffer.
 * Read `yacup/rb/op.h` for complete information. */
static size_t size(struct rb *rb)
{
  /* Fail */
  return 1;
}

/* Returns available data size inside a ring-buffer.
 * Read `yacup/rb/op.h` for complete information. */
static size_t len(struct rb *rb)
{
  /* Fail */
  return 1;
}

/* Check if a ring-buffer is full or not.
 * Read `yacup/rb/op.h` for complete information. */
static uint8_t full(struct rb *rb)
{
  /* Fail */
  return 1;
}

/* Check if a ring-buffer is full or not.
 * Read `yacup/rb/op.h` for complete information. */
struct rb_op *rb_driver_v1(void)
{
  /* Create it static, as it will not change along the execution */
  static struct rb_op rb_driver_v1_op =
  {
    .validate = validate,
    .reset    = reset,
    .push     = push,
    .pull     = pull,
    .write    = write,
    .read     = read,
    .size     = size,
    .len      = len,
    .full     = full
  };

  /* And return it as a pointer */
  return &rb_driver_v1_op;
}