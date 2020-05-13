/* test_cp_codec_B416K.c - Test to check cp's cp_simple functionality
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
#include <time.h>
#include "yacup/cp.h"
#include "yacup/cp/debug.h"

/* This include acts like an external application include, located elsewhere */
//#include "cp_external.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#undef YCP_NAME
#define YCP_NAME "util/cp/test/test_cp_codec_B416K"
#include <time.h>
#include <stdio.h>
#include <string.h>
#ifndef _dbg
  #define _dbg(...) printf(YCP_NAME" | "__VA_ARGS__)
#endif

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Test to check `cp` functionality using a single cp
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
int test_cp_codec_B416K(int argc, const char* argv[])
{
  printf("Hi! from "__FILE__"\n");

  /* Testbench vars */
  #define TEST_CP_TESTNAME_BUFFER_SIZE 20
  uint8_t buffer[TEST_CP_TESTNAME_BUFFER_SIZE];
  struct cp cp_codec_B416K0;

  /* Setup cp */
  _dbg("Setting up the cp\n");
  if (cp_setup(&cp_codec_B416K0, buffer, TEST_CP_TESTNAME_BUFFER_SIZE))
  {
    _dbg("- Cannot setup the CP. ERROR\n");
    return 1;
  }
  _dbg("- Ok\n");

  /* Cya! */
  cp_print_info(&cp_codec_B416K0);
  return 0;
}

#undef YCP_NAME
