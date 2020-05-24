/* test_fsm_driver_simple.c - Test to check `fsm_driver_simple` functionality
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
#include "yacup/fsm.h"
#include "yacup/fsm/debug.h"

/* This include acts like an external application include, located elsewhere */
#include "fsm_driver_simple.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define YCP_FORCE_DEBUG
#include "yacup/debug.h"
#undef YCP_NAME
#define YCP_NAME "util/fsm/test/test_fsm_driver_simple"

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
int test_fsm_driver_simple(int argc, const char* argv[])
{
  /* Configure _dbg() */
  #define YCP_FNAME "test_fsm_driver_simple"

  /* Testbench vars */
  #define MAX_CYCLES 20
  uint32_t current_cycle = MAX_CYCLES;

  /* FSM data and instance */
  struct fsm_driver_simple_data fsm_driver_simple0_data;
  struct fsm fsm_driver_simple0 =
  {
    .name = "fsm_driver_simple0",
    .data = &fsm_driver_simple0_data
  };

  /* Initialize fsm found at `fsm_driver_simple.c` */
  _dbg("Initializing the finite-state machine\n");
  if (fsm_init(&fsm_driver_simple0, fsm_driver_simple))
  {
    _dbg("- Cannot initialize the FSM. ERROR\n");
    return 1;
  }
  _dbg("- Ok\n");

  /* Basics: enable + auto-restart + start as soon as possible */
  fsm_enable(&fsm_driver_simple0);
  fsm_set_loop(&fsm_driver_simple0);
  fsm_request_start(&fsm_driver_simple0);

  /* fsm cycles */
  fsm_print_info(&fsm_driver_simple0);
  while (current_cycle--)
  {
    /* Start cycle */
    _dbg("Cycle #%02u\n", MAX_CYCLES - current_cycle);

    /* Test the fsm */
    if (fsm_do_cycle(&fsm_driver_simple0))
    {
      _dbg("Error when executing a fsm cycle\n");
      fsm_print_info(&fsm_driver_simple0);
      fsm_print_stats(&fsm_driver_simple0);
      return 1;
    }

    /* Finish cycle */
    /* Simulate some time spent on the cycle */
    nanosleep(&(struct timespec){ .tv_sec = 0, .tv_nsec = 100*1000000 }, NULL);
  }

  /* Cya! */
  fsm_print_stats(&fsm_driver_simple0);
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

#undef YCP_NAME
#undef YCP_FORCE_DEBUG
