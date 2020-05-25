/* test_ce_command_validate.c - Check validation over different test commands
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
#include "yacup/ce.h"
#include "yacup/ce/command.h"
#include "yacup/ce/command/subset_test.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define YCP_FORCE_DEBUG
#include "yacup/debug.h"
#undef YCP_NAME
#define YCP_NAME "util/ce/test/test_ce_command_validate"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Test to check `ce` functionality using a single ce
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
int test_ce_command_validate(int argc, const char* argv[])
{
  /* Configure _dbg() */
  #define YCP_FNAME "test_ce_command_validate"

  _dbg("Hi! from "__FILE__"\n");

  /* Define the command set this `ce` will understand how to send/receive */
  struct ce_command_set cmd_set =
  {
    .name = "test_set",
    .subset = (struct ce_command_subset *[])
    {
      &test_command_subset_part_A,
      &test_command_subset_part_B,
      NULL
    }
  };

  /* Compose arguments */
  struct ce_command_argument *cmd1_args[] =
  {
    &(struct ce_command_argument) { .type = CE_DATA_UINT8_T, .data.u8 = 250 },
    NULL
  };

  /* Validate command */
  _dbg("Should validate: Valid 1 argument vs. 1 argument command\n");
  if (ce_command_validate(&cmd_set,
                          CE_COMMAND_SUBSET_TEST_CMD1,
                          cmd1_args) == NULL)
  {
    /* Cannot send, error */
    _dbg("Error when validating CE_COMMAND_SUBSET_TEST_CMD1\n");
    return 1;
  }

  /* Compose arguments */
  struct ce_command_argument *cmd2_args[] =
  {
    &(struct ce_command_argument) { .type = CE_DATA_UINT8_T, .data.u8 = 250  },
    &(struct ce_command_argument) { .type = CE_DATA_DOUBLE,  .data.d  = -1.2 },
    NULL
  };

  /* Validate command */
  _dbg("Should validate: Valid 2 arguments vs. 2 arguments command\n");
  if (ce_command_validate(&cmd_set,
                          CE_COMMAND_SUBSET_TEST_CMD4,
                          cmd2_args) == NULL)
  {
    /* Cannot validate, error */
    _dbg("Error when validating CE_COMMAND_SUBSET_TEST_CMD2\n");
    return 1;
  }

  /* Test invalid command */
  _dbg("Should not validate: Not supported/invalid command\n");
  if (ce_command_validate(&cmd_set,
                          1000,
                          cmd2_args) != NULL)
  {
    /* Validated, error */
    _dbg("Invalid command marked as valid! ERROR!\n");
    return 1;
  }

  /* Test invalid arguments: 1 arg validated against 2 args command */
  _dbg("Should not validate: Invalid 1 argument vs. 2 arguments command\n");
  if (ce_command_validate(&cmd_set,
                          CE_COMMAND_SUBSET_TEST_CMD4,
                          cmd1_args) != NULL)
  {
    /* Validated, error */
    _dbg("Invalid arguments marked as valid! ERROR!\n");
    return 1;
  }

  /* Test invalid arguments: 2 args validated against 1 arg command */
  _dbg("Should not validate: Invalid 2 arguments vs. 1 argument command\n");
  if (ce_command_validate(&cmd_set,
                          CE_COMMAND_SUBSET_TEST_CMD3,
                          cmd2_args) != NULL)
  {
    /* Validated, error */
    _dbg("Invalid arguments marked as valid! ERROR!\n");
    return 1;
  }

  /* Cya! */
  _dbg("If you are reading this, everything went correctly :_)\n");
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

#undef YCP_NAME
#undef YCP_FORCE_DEBUG
