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
#include <stdlib.h>
#include <stdint.h>
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
/* Create and initialize a ring-buffer.
 * Read `rb.h` for complete information. */
struct rb *rb_create(uint8_t *buffer, size_t size)
{
  /* Fail */
  return 1;
}

/* Destroy a ring-buffer and free its resources.
 * Read `rb.h` for complete information. */
void rb_destroy(struct rb *rb)
{
  /* Fail */
  return 1;
}

/* Reset a ring-buffer by cleaning its content and making it empty.
 * Read `rb.h` for complete information. */
void rb_reset(struct rb *rb)
{
  /* Fail */
  return 1;
}

/* Add a byte to a ring-buffer head, overwritting if needed.
 * Read `rb.h` for complete information. */
int rb_push(struct rb *rb, uint8_t byte)
{
  /* Fail */
  return 1;
}

/* Read and delete a byte from a ring-buffer tail.
 * Read `rb.h` for complete information. */
int rb_pull(struct rb *rb, uint8_t *byte)
{
  /* Fail */
  return 1;
}

/* Write a byte by position on a ring-buffer, without updating head/tail.
 * Read `rb.h` for complete information. */
int rb_write(struct rb *rb, uint8_t byte, size_t position)
{
  /* Fail */
  return 1;
}

/* Read a byte by position from a ring-buffer, without deleting it.
 * Read `rb.h` for complete information. */
int rb_read(struct rb *rb, uint8_t *byte, size_t position)
{
  /* Fail */
  return 1;
}

/* Returns max available size of a ring-buffer buffer.
 * Read `rb.h` for complete information. */
size_t rb_size(struct rb *rb)
{
  /* Fail */
  return 1;
}

/* Returns available data size inside a ring-buffer.
 * Read `rb.h` for complete information. */
size_t rb_len(struct rb *rb)
{
  /* Fail */
  return 1;
}

/* Check if a ring-buffer is full or not.
 * Read `rb.h` for complete information. */
uint8_t rb_full(struct rb *rb)
{
  /* Fail */
  return 1;
}