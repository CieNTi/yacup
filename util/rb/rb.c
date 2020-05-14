/* rb.c - Ring buffers implementation for yacup project
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
#include <stdlib.h>
#include "yacup/rb.h"
#include "yacup/rb/op.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#undef YCP_NAME
#define YCP_NAME "util/rb/rb"
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
/* Create and initialize a ring-buffer.
 * Read `yacup/rb.h` for complete information. */
int rb_init(struct rb *rb, int (*rb_driver_init)(struct rb *))
{
  if (/* Invalid rb? */
      (rb == NULL) ||
      /* Invalid low-level init? */
      (rb_driver_init == NULL) ||
      /* Invalid buffer? */
      (rb->buffer == NULL) ||
      /* Invalid size? */
      (rb->size == 0))
  {
    _dbg("rb_init: Invalid rb, driver, buffer or size\n");
    return 1;
  }

  /* Fill RB common data */
  rb->head = 0;
  rb->tail = 0;
  rb->head_of = 0;

  /* Assign driver operations */
  if (rb_driver_init(rb))
  {
    /* Fail miserably */
    _dbg("rb_init: Impossible to assign rb operations\n");
    return 1;
  }

  /* Clean buffer and put it into a known state */
  rb->op->reset(rb);

  /* Finally, check if driver validates it */
  if (rb->op->validate(rb))
  {
    /* Fail miserably */
    _dbg("rb_init: Invalid rb after initialization\n");
    return 1;
  }
  else
  {
    /* And finish! */
    return 0;
  }
}

/* Reset a ring-buffer by cleaning its content and making it empty.
 * Read `yacup/rb.h` for complete information. */
void rb_reset(struct rb *rb)
{
  /* Validate it */
  if ((rb == NULL) || (rb->op == NULL) || rb->op->validate(rb))
  {
    _dbg("rb_reset: Failed\n");
    return;
  }

  /* Call operation */
  rb->op->reset(rb);

  /* It is a void, just return */
  return;
}

/* Add a byte to a ring-buffer head, overwritting if needed.
 * Read `yacup/rb.h` for complete information. */
int rb_push(struct rb *rb, uint8_t byte)
{
  /* Validate it */
  if ((rb == NULL) || (rb->op == NULL) || rb->op->validate(rb))
  {
    _dbg("rb_push: Invalid\n");
    return 1;
  }

  /* Call operation and return its value */
  return (rb->op->push(rb, byte));
}

/* Read and delete a byte from a ring-buffer tail.
 * Read `yacup/rb.h` for complete information. */
int rb_pull(struct rb *rb, uint8_t *byte)
{
  /* Validate it */
  if ((rb == NULL) || (rb->op == NULL) || rb->op->validate(rb))
  {
    _dbg("rb_pull: Invalid\n");
    return 1;
  }

  /* Call operation and return its value */
  return (rb->op->pull(rb, byte));
}

/* Write a byte by position on a ring-buffer, without updating head/tail.
 * Read `yacup/rb.h` for complete information. */
int rb_write(struct rb *rb, uint8_t byte, size_t position)
{
  /* Validate it */
  if ((rb == NULL) || (rb->op == NULL) || rb->op->validate(rb))
  {
    _dbg("rb_write: Failed\n");
    return 1;
  }

  /* Call operation and return its value */
  return (rb->op->write(rb, byte, position));
}

/* Read a byte by position from a ring-buffer, without deleting it.
 * Read `yacup/rb.h` for complete information. */
int rb_read(struct rb *rb, uint8_t *byte, size_t position)
{
  /* Validate it */
  if ((rb == NULL) || (rb->op == NULL) || rb->op->validate(rb))
  {
    _dbg("rb_read: Failed\n");
    return 1;
  }

  /* Call operation and return its value */
  return (rb->op->read(rb, byte, position));
}

/* Returns max available size of a ring-buffer buffer.
 * Read `yacup/rb.h` for complete information. */
size_t rb_size(struct rb *rb)
{
  /* Validate it */
  if ((rb == NULL) || (rb->op == NULL) || rb->op->validate(rb))
  {
    _dbg("rb_size: Failed\n");
    return 0;
  }

  /* Call operation and return its value */
  return (rb->op->size(rb));
}

/* Returns available data size inside a ring-buffer.
 * Read `yacup/rb.h` for complete information. */
size_t rb_len(struct rb *rb)
{
  /* Validate it */
  if ((rb == NULL) || (rb->op == NULL) || rb->op->validate(rb))
  {
    _dbg("rb_len: Failed\n");
    return 0;
  }

  /* Call operation and return its value */
  return (rb->op->len(rb));
}

/* Check if a ring-buffer is full or not.
 * Read `yacup/rb.h` for complete information. */
uint8_t rb_full(struct rb *rb)
{
  /* Validate it */
  if ((rb == NULL) || (rb->op == NULL) || rb->op->validate(rb))
  {
    _dbg("rb_full: Failed\n");
    return 0;
  }

  /* Call operation and return its value */
  return (rb->op->full(rb));
}

#undef YCP_NAME
