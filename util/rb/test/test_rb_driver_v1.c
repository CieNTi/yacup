/* test_rb_driver_v1.c - Test to check rb's driver_v1 functionality
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
#include "yacup/rb/driver_v1.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#undef YCP_NAME
#define YCP_NAME "util/rb/test/test_rb_driver_v1"
#include <time.h>
#include <stdio.h>
#include <string.h>
#ifndef _dbg
  #define _dbg(...) printf(YCP_NAME" | "__VA_ARGS__)
#endif

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Tests driver_v1 API and functionality
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
int test_rb_driver_v1(int argc, const char* argv[])
{
  printf("Hi! from "__FILE__"\n");

  /* Variables related to the test itself */
  size_t idx = 0;
  #define RB_TEST_DATA_BUF_LEN 32
  uint8_t data_by_read[RB_TEST_DATA_BUF_LEN];
  uint8_t data_by_pull[RB_TEST_DATA_BUF_LEN];

  /* Allocate buffer space */
  #define SIMPLE_TEST_BUF_LEN 6
  uint8_t rb_test_buf[SIMPLE_TEST_BUF_LEN] = { 0x00 };

  /* Create a rb from it */
  struct rb *rb0 = rb_create(rb_test_buf, SIMPLE_TEST_BUF_LEN, rb_driver_v1);
  if (rb0 == NULL)
  {
    _dbg("Cannot create a rb\n");
    return 1;
  }

  /* Debug it! */
  rb_print_info(rb0);

  return 0;
}

#undef YCP_NAME
