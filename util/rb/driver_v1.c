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
#undef YCP_NAME
#define YCP_NAME "util/rb/driver_v1"
#ifdef YACUP_DEBUG
  #include <time.h>
  #include <stdio.h>
  #include <string.h>
  #ifndef _dbg
    #define _dbg(...) printf(YCP_NAME" | "__VA_ARGS__)
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
    _dbg("validate ~~~~~~~~~~~~~~~~~~~~~~\n");
    _dbg("- rb cannot be null .....: %4s\n",
         (rb == NULL)?"FAIL":"OK");
    _dbg("- Buffer cannot be null .: %4s\n",
         (rb->buffer == NULL)?"FAIL":"OK");
    _dbg("- Size cannot be 0 ......: %4s\n",
         (rb->size == 0)?"FAIL":"OK");
    _dbg("- Head has to be valid ..: %4s\n",
         (rb->head >= rb->size)?"FAIL":"OK");
    _dbg("- Tail has to be valid ..: %4s\n",
         (rb->tail >= rb->size)?"FAIL":"OK");
    _dbg("- Head >= tail ..........: %4s\n",
         (((rb->size * rb->head_of) + rb->head) < rb->tail)?"FAIL":"OK");
    _dbg("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    return 1;
  }

  /* Ok */
  return 0;
}

/* Reset a ring-buffer by cleaning its content and making it empty.
 * WARNING: Assumed `rb/rb.c` pre-validation. Not safe as direct call!
 * Read `yacup/rb/op.h` for complete information. */
static void reset(struct rb *rb)
{
  /* Put properties to reset state */
  rb->head = 0;
  rb->tail = 0;
  rb->head_of = 0;

  /* Clear data */
  for (rb->head = 0; rb->head < rb->size; rb->head++)
  {
    rb->buffer[rb->head] = 0x00;
  }
  rb->head = 0;

  /* It is a void, just return */
  return;
}

/* Add a byte to a ring-buffer head, overwritting if needed.
 * WARNING: Assumed `rb/rb.c` pre-validation. Not safe as direct call!
 * Read `yacup/rb/op.h` for complete information. */
static int push(struct rb *rb, uint8_t byte)
{
  /* Add the data, overwritting if needed */
  rb->buffer[rb->head] = byte;

  if (rb->op->full(rb))
  {
    rb->tail++;
  }
  rb->head++;

  /* Normalize head index */
  if (rb->head >= rb->size)
  {
    rb->head -= rb->size;
    rb->head_of = 1;
  }

  /* Normalize tail index */
  if (rb->tail >= rb->size)
  {
    rb->tail -= rb->size;
  }

  /* Ok! */
  return 0;
}

/* Read and delete a byte from a ring-buffer tail.
 * WARNING: Assumed `rb/rb.c` pre-validation. Not safe as direct call!
 * Read `yacup/rb/op.h` for complete information. */
static int pull(struct rb *rb, uint8_t *byte)
{
  if (rb->op->len(rb) == 0)
  {
    _dbg("pull: Pulling from empty rb not allowed\n");
    return 1;
  }

  /* Extract the data */
  *byte = rb->buffer[rb->tail];
  rb->buffer[rb->tail] = 0x00;
  rb->tail++;

  /* Normalize tail index */
  if (rb->tail >= rb->size)
  {
    rb->tail -= rb->size;
    rb->head_of = 0;
  }

  /* Ok! */
  return 0;
}

/* Write a byte by position on a ring-buffer, without updating head/tail.
 * WARNING: Assumed `rb/rb.c` pre-validation. Not safe as direct call!
 * Read `yacup/rb/op.h` for complete information. */
static int write(struct rb *rb, uint8_t byte, size_t position)
{
  /* Use position as index over tail, with overflow management */
  rb->buffer[(rb->tail + position) % rb->size] = byte;

  /* Ok! */
  return 0;
}

/* Read a byte by position from a ring-buffer, without deleting it.
 * WARNING: Assumed `rb/rb.c` pre-validation. Not safe as direct call!
 * Read `yacup/rb/op.h` for complete information. */
static int read(struct rb *rb, uint8_t *byte, size_t position)
{
  /* Use position as index over tail, with overflow management */
  *byte = rb->buffer[(rb->tail + position) % rb->size];

  /* Ok! */
  return 0;
}

/* Returns max available size of a ring-buffer buffer.
 * WARNING: Assumed `rb/rb.c` pre-validation. Not safe as direct call!
 * Read `yacup/rb/op.h` for complete information. */
static size_t size(struct rb *rb)
{
  return rb->size;
}

/* Returns available data size inside a ring-buffer.
 * WARNING: Assumed `rb/rb.c` pre-validation. Not safe as direct call!
 * Read `yacup/rb/op.h` for complete information. */
static size_t len(struct rb *rb)
{
  return (((rb->size * rb->head_of) + rb->head) - rb->tail);
}

/* Check if a ring-buffer is full or not.
 * WARNING: Assumed `rb/rb.c` pre-validation. Not safe as direct call!
 * Read `yacup/rb/op.h` for complete information. */
static uint8_t full(struct rb *rb)
{
  return ((rb->head_of == 1) && (rb->head == rb->tail));
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

#undef YCP_NAME
