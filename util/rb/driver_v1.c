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
/* Checks if the ring-buffer is valid or not.
 * Read `rb.h` for complete information. */
static int validate(struct rb *rb)
{
  /* Fail */
  return 1;
}

/* Reset a ring-buffer by cleaning its content and making it empty.
 * Read `rb.h` for complete information. */
static void reset(struct rb *rb)
{
  /* Fail */
  return 1;
}

/* Add a byte to a ring-buffer head, overwritting if needed.
 * Read `rb.h` for complete information. */
static int push(struct rb *rb, uint8_t byte)
{
  /* Fail */
  return 1;
}

/* Read and delete a byte from a ring-buffer tail.
 * Read `rb.h` for complete information. */
static int pull(struct rb *rb, uint8_t *byte)
{
  /* Fail */
  return 1;
}

/* Write a byte by position on a ring-buffer, without updating head/tail.
 * Read `rb.h` for complete information. */
static int write(struct rb *rb, uint8_t byte, size_t position)
{
  /* Fail */
  return 1;
}

/* Read a byte by position from a ring-buffer, without deleting it.
 * Read `rb.h` for complete information. */
static int read(struct rb *rb, uint8_t *byte, size_t position)
{
  /* Fail */
  return 1;
}

/* Returns max available size of a ring-buffer buffer.
 * Read `rb.h` for complete information. */
static size_t size(struct rb *rb)
{
  /* Fail */
  return 1;
}

/* Returns available data size inside a ring-buffer.
 * Read `rb.h` for complete information. */
static size_t len(struct rb *rb)
{
  /* Fail */
  return 1;
}

/* Check if a ring-buffer is full or not.
 * Read `rb.h` for complete information. */
static uint8_t full(struct rb *rb)
{
  /* Fail */
  return 1;
}

