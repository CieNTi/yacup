/* test_fsm_simple.c - Test program to check fsm_simple functionality
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
//#include <stdlib.h>
#include <time.h>
#include "yacup/fsm.h"
#include "yacup/fsm/debug.h"

/* This include acts like an external application include, located elsewhere */
#include "fsm_simple.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#undef YCP_NAME
#define YCP_NAME "util/fsm/test/test_fsm_simple"
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
/**
 * @brief      Test to check `fsm` functionality using a single fsm
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
int test_fsm_simple(int argc, const char* argv[])
{
  /* Testbench vars */
  #define MAX_CYCLES 20
  uint32_t current_cycle = MAX_CYCLES;
  struct timespec loop_wait_ms = { .tv_sec = 0, .tv_nsec = 100 * 1000000 };

  /* fsm (fsm_simple.c) */
  struct fsm *fsm_simple0 = fsm_simple_create("fsm_simple0");

  /* Basics: enable + auto-restart + start as soon as possible */
  fsm_enable(fsm_simple0);
  fsm_set_loop(fsm_simple0);
  fsm_request_start(fsm_simple0);

  /* fsm cycles */
  while (current_cycle--)
  {
    /* Start cycle */
    printf("-----------\n"
           " Cycle #%02u\n"
           "-----------\n",
           MAX_CYCLES - current_cycle);

    /* Test the fsm */
    fsm_do_cycle(fsm_simple0);

    /* Finish cycle */
    fsm_print_stats(fsm_simple0);
    printf("\n");

    /* Simulate some time spent on the cycle */
    nanosleep(&loop_wait_ms, NULL);
  }
  return 0;
}

#undef YCP_NAME