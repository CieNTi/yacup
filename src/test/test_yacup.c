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
 *             | `!= 0` | Warning          |
 *
 * @ingroup    template
 * @version    v1.0.0
 */
int test_rb_driver_v1(int argc, const char* argv[]);
int test_rb_simple(int argc, const char* argv[]);
int test_yacup(int argc, const char* argv[])
{
  int _test_rb_driver_v1 = test_rb_driver_v1(argc, argv);
  int _test_rb_simple    = test_rb_simple(argc, argv);
  printf("Result from test_rb_driver_v1() = %i\n", _test_rb_driver_v1);
  printf("Result from test_rb_simple() = %i\n", _test_rb_simple);
  printf("Hi! from "__FILE__"\n");
  return 0;
}
