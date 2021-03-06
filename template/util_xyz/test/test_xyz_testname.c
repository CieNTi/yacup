/* test_xyz_testname.c - Test to check xyz's xyz_simple functionality
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
#include "yacup/xyz.h"
#include "yacup/xyz/debug.h"

/* This include acts like an external application include, located elsewhere */
//#include "xyz_external.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define YCP_FORCE_DEBUG
#include "yacup/debug.h"
#undef YCP_NAME
#define YCP_NAME "util/xyz/test/test_xyz_testname"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Test to check `xyz` functionality using a single xyz
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
int test_xyz_testname(int argc, const char* argv[])
{
  /* Configure _dbg() */
  #define YCP_FNAME "test_xyz_testname"

  _dbg("Hi! from "__FILE__"\n");

  /* Testbench vars */
  #define TEST_XYZ_TESTNAME_BUFFER_SIZE 20
  uint8_t buffer[TEST_XYZ_TESTNAME_BUFFER_SIZE];
  struct xyz xyz_testname0;

  /* Setup xyz */
  _dbg("Setting up the xyz\n");
  if (xyz_setup(&xyz_testname0, buffer, TEST_XYZ_TESTNAME_BUFFER_SIZE))
  {
    _dbg("- Cannot setup the XYZ. ERROR\n");
    return 1;
  }
  _dbg("- Ok\n");

  /* Cya! */
  xyz_print_info(&xyz_testname0);
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

#undef YCP_NAME
#undef YCP_FORCE_DEBUG
