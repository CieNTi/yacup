/* test_rb_driver_overwrite.c - Test to check rb's `overwrite` driver
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
#include <stdio.h>
#include "yacup/rb.h"
#include "yacup/rb/debug.h"
#include "yacup/rb/driver/overwrite.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#undef YCP_NAME
#define YCP_NAME "util/rb/test/test_rb_driver_overwrite"
#include <time.h>
#include <stdio.h>
#include <string.h>
#ifndef _dbg
  #define _dbg(...) printf(YCP_NAME" | "__VA_ARGS__)
#endif

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Tests `overwrite` driver API and functionality
 *
 * @param[in]  argc  The count of arguments
 * @param      argv  The arguments array
 *
 * @return     One of:
 *             | Value  | Meaning          |
 *             | :----: | :--------------- |
 *             | `== 0` | Ok               |
 *             | `!= 0` | Error            |
 *
 * @ingroup    util_test
 * @version    v1.0.0
 */
int test_rb_driver_overwrite(int argc, const char* argv[])
{
  printf("Hi! from "__FILE__"\n");

  /* Variables related to the test itself */
  size_t idx = 0;
  #define RB_TEST_DATA_BUF_LEN 32
  uint8_t data_by_pull[RB_TEST_DATA_BUF_LEN];
  uint8_t data_by_read[RB_TEST_DATA_BUF_LEN];

  /* Allocate buffer space */
  #define SIMPLE_TEST_BUF_LEN 6
  uint8_t rb_test_buf[SIMPLE_TEST_BUF_LEN] = { 0x00 };

  /* Create a rb from it */
  _dbg("Creating ring-buffer\n");
  struct rb *rb0 = rb_create(rb_test_buf, SIMPLE_TEST_BUF_LEN,
                             rb_driver_overwrite);
  if (rb0 == NULL)
  {
    _dbg("Cannot create a rb\n");
    return 1;
  }

  /* Debug it! */
  rb_print_info(rb0);

  /* Push some data */
  _dbg("Pushing data to ring-buffer\n");
  if (rb_push(rb0, 'y')) { _dbg("rb_push('y') fail. ERROR\n"); return 1; }
  rb_print_info(rb0);
  if (rb_push(rb0, 'C')) { _dbg("rb_push('C') fail. ERROR\n"); return 1; }
  rb_print_info(rb0);
  if (rb_push(rb0, 'i')) { _dbg("rb_push('i') fail. ERROR\n"); return 1; }
  rb_print_info(rb0);
  if (rb_push(rb0, 'e')) { _dbg("rb_push('e') fail. ERROR\n"); return 1; }
  rb_print_info(rb0);
  if (rb_push(rb0, 'N')) { _dbg("rb_push('N') fail. ERROR\n"); return 1; }
  rb_print_info(rb0);
  if (rb_push(rb0, 'T')) { _dbg("rb_push('T') fail. ERROR\n"); return 1; }
  rb_print_info(rb0);
  if (rb_push(rb0, 'i')) { _dbg("rb_push('i') fail. ERROR\n"); return 1; }
  rb_print_info(rb0);

  /* Check if full */
  _dbg("Ring-buffer is supposed to be full right now\n");
  if (rb_full(rb0) != 1)
  {
    _dbg("- But is not. ERROR\n");
    return 1;
  }
  _dbg("- Yes it is. OK\n");

  /* Now we have data, we can read it without pull it */
  _dbg("Reading without pull (data is kept, head/tail are not changed)\n");
  for (idx = 0; (idx < rb_len(rb0)) && (idx < RB_TEST_DATA_BUF_LEN); idx++)
  {
    if (rb_read(rb0, &data_by_read[idx], idx))
    {
      printf("read() failed at position %lu\n", idx);
    }
  }
  data_by_read[idx] = 0x00;

  /* Print the data */
  _dbg("Checking read data. What we read: %s\n", data_by_read);
  if (strcmp((char *)data_by_read, "CieNTi") != 0)
  {
    _dbg("- Expected: CieNTi. ERROR\n");
    return 1;
  }
  _dbg("- OK\n");

  /* Now we can write new data without push it */
  _dbg("Writing without push (data is changed, head/tail are not changed)\n");
  if (rb_write(rb0, 'c', 0)) { _dbg("rb_write('c') fail. ERROR\n"); return 1; }
  rb_print_info(rb0);
  if (rb_write(rb0, 'n', 3)) { _dbg("rb_write('n') fail. ERROR\n"); return 1; }
  rb_print_info(rb0);
  if (rb_write(rb0, 't', 4)) { _dbg("rb_write('t') fail. ERROR\n"); return 1; }
  rb_print_info(rb0);

  /* Pull it */
  _dbg("Pulling data from ring-buffer\n");
  for (idx = 0; idx < RB_TEST_DATA_BUF_LEN; idx++)
  {
    if (rb_pull(rb0, &data_by_pull[idx]))
    {
      _dbg("Pulling failed, but it can be empty\n");
      if (rb_len(rb0) == 0)
      {
        _dbg("- Empty. OK\n");
        /* Finish as string */
        data_by_pull[idx] = 0x00;
        break;
      }
      else
      {
        _dbg("- Not empty. ERROR\n");
        return 1;
      }
    }
    rb_print_info(rb0);
  }

  /* Print the data */
  _dbg("Checking pulled data. What we pulled: %s\n", data_by_pull);
  if (strcmp((char *)data_by_pull, "cienti") != 0)
  {
    _dbg("- Expected: cienti. ERROR\n");
    return 1;
  }
  _dbg("- OK\n");

  /* Reset it! */
  rb_reset(rb0);

  /* Debug it! */
  rb_print_info(rb0);

  _dbg("If you are reading this, everything went correctly :_)\n");
  return 0;
}

#undef YCP_NAME
