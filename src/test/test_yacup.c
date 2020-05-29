/* driver_v1.c - Test to check rb's driver_v1 functionality
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
#include <stdio.h>

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define YCP_FORCE_DEBUG
#include "yacup/debug.h"
#undef YCP_NAME
#define YCP_NAME "app/test/test_yacup"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* Pre-declare required tests here (there is no header for them!) */
int test_xyz_testname(int argc, const char* argv[]);
int test_rb_driver_overwrite(int argc, const char* argv[]);
int test_fsm_driver_simple(int argc, const char* argv[]);
int test_ce_codec_B416K(int argc, const char* argv[]);
int test_ce_command_validate(int argc, const char* argv[]);
int test_ce_command_codec_B416K(int argc, const char* argv[]);
int test_ce_initialization(int argc, const char* argv[]);
int test_ce_driver_faf(int argc, const char* argv[]);

/**
 * @brief      The main of the mains
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
 * @ingroup    app_test
 * @version    v1.0.0
 */
int test_yacup(int argc, const char* argv[])
{
  /* Configure _dbg() */
  #define YCP_FNAME "test_yacup"

  _dbg("Hi! from "__FILE__"\n");

  printf("Result from test_xyz_testname() = %i\n", 
         test_xyz_testname(argc, argv));
  printf("Result from test_rb_driver_overwrite() = %i\n", 
         test_rb_driver_overwrite(argc, argv));
  printf("Result from test_fsm_driver_simple() = %i\n", 
         test_fsm_driver_simple(argc, argv));
  printf("Result from test_ce_codec_B416K() = %i\n", 
         test_ce_codec_B416K(argc, argv));
  printf("Result from test_ce_command_validate() = %i\n", 
         test_ce_command_validate(argc, argv));
  printf("Result from test_ce_command_codec_B416K() = %i\n", 
         test_ce_command_codec_B416K(argc, argv));
  printf("Result from test_ce_initialization() = %i\n", 
         test_ce_initialization(argc, argv));
  printf("Result from test_ce_driver_faf() = %i\n", 
         test_ce_driver_faf(argc, argv));
  _dbg("Hi! from "__FILE__"\n");
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

#undef YCP_NAME
#undef YCP_FORCE_DEBUG
