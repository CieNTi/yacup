/* test_cp_commands.c - A simple set of commands for `cp` testing
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
#include "yacup/cp.h"
#include "yacup/cp/command.h"
#include "yacup/cp/command/subset_test.h"

/* Header located near this file, used as an external header in app */
//#include "cp_simple.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define YCP_FORCE_DEBUG
#include "yacup/debug.h"
#undef YCP_NAME
#define YCP_NAME "util/cp/test/test_cp_commands"

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
int test_cp_commands(int argc, const char* argv[])
{
  /* Configure _dbg() */
  #define YCP_FNAME "test_cp_commands"

  _dbg("Hi! from "__FILE__"\n");

  /* Define the command set this `cp` will understand how to send/receive */
  struct cp_command_set cmd_set =
  {
    .name = "test_set",
    .subset = (struct cp_command_subset *[])
    {
      &test_command_subset_part_A,
      &test_command_subset_part_B,
      NULL
    }
  };

  /* Compose arguments */
  struct cp_argument *cmd1_args[] =
  {
    &(struct cp_argument)
    { .type = CP_DATA_UINT8_T, .data.u8 = 250 },
    NULL
  };

  /* Validate command */
  if (cp_command_validate(&cmd_set, CP_COMMAND_SUBSET_TEST_CMD1, cmd1_args))
  {
    /* Cannot send, error */
    _dbg("Error when validating CP_COMMAND_SUBSET_TEST_CMD1\n");
    return 1;
  }

  /* Compose arguments */
  struct cp_argument *cmd2_args[] =
  {
    &(struct cp_argument)
    { .type = CP_DATA_UINT8_T, .data.u8 = 250 },
    &(struct cp_argument)
    { .type = CP_DATA_DOUBLE,  .data.d  = -1.233 },
    NULL
  };

  /* Validate command */
  if (cp_command_validate(&cmd_set, CP_COMMAND_SUBSET_TEST_CMD4, cmd2_args))
  {
    /* Cannot send, error */
    _dbg("Error when validating CP_COMMAND_SUBSET_TEST_CMD2\n");
    return 1;
  }

  /* Test invalid command */
  if (cp_command_validate(&cmd_set, 1000, cmd2_args) == 0)
  {
    /* Cannot send, error */
    _dbg("Invalid command marked as valid! ERROR!\n");
    return 1;
  }

  /* Cya! */
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

#undef YCP_NAME
#undef YCP_FORCE_DEBUG
