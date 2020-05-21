/* subset_test.c - Tests commands subset for `ce` for yacup project
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
#include <stddef.h>
#include "yacup/ce.h"
#include "yacup/ce/command.h"
#include "yacup/ce/command/subset_test.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include "yacup/debug.h"
#undef YCP_NAME
#define YCP_NAME "util/ce/command/subset_test"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* Validate function for test_cmd1 */
static int test_cmd1_val(struct ce_command *cmd, struct ce_argument *arg[])
{
  /* Configure _dbg() */
  #define YCP_FNAME "cmd1_val"

  /* This specific example command requires only a uint8_t argument */
  if (/* Validate if there is a first argument or not */
      arg[0] == NULL                  ||
      /* Got it, now validate if it is the expected type */
      arg[0]->type != CE_DATA_UINT8_T ||
      /* Purfect, now we can do some value check */
      !(arg[0]->data.u8 < 251)        ||
      /* And should not be another argument */
      arg[1] != NULL)
  {
    _dbg("Invalid argument. Expecting (uint8_t < 251)\n");
    return 1;
  }
  _dbg("Valid, ready to send\n");

  /* Cya! */
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

/* Parse function for test_cmd1 */
static int test_cmd1_par(struct ce_command *cmd, struct ce_argument *arg[])
{
  /* Configure _dbg() */
  #define YCP_FNAME "cmd1_par"

  _dbg("Hop!\n");
  //struct ce_argument *arga[] =
  //{
  //  &(struct ce_argument)
  //  { .type = CE_DATA_UINT8_T, .data.u8 = 0 },
  //  NULL
  //};

  /* Cya! */
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

/* Validate function for test_cmd2 */
static int test_cmd2_val(struct ce_command *cmd, struct ce_argument *arg[])
{
  /* Configure _dbg() */
  #define YCP_FNAME "cmd2_val"

  /* This specific example requires one uint8_t and one double arguments */
  if (/* Validate if there is a first argument or not */
      arg[0] == NULL                  ||
      /* Got it, now validate if it is the expected type */
      arg[0]->type != CE_DATA_UINT8_T ||
      /* Purfect, now we can do some value check */
      !(arg[0]->data.u8 < 251)        ||
      /* Validate if there is a second argument or not */
      arg[1] == NULL                  ||
      /* Got it, now validate if it is the expected type */
      arg[1]->type != CE_DATA_DOUBLE  ||
      /* Purfect, now we can do some value check */
      !(arg[1]->data.d > -1.234)      ||
      /* And should not be another argument */
      arg[2] != NULL)
  {
    _dbg("Invalid argument. Expecting (uint8_t < 251, double > -1.234)\n");
    return 1;
  }
  _dbg("Valid, ready to send\n");

  /* Cya! */
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

/* Parse function for test_cmd2 */
static int test_cmd2_par(struct ce_command *cmd, struct ce_argument *arg[])
{
  /* Configure _dbg() */
  #define YCP_FNAME "cmd2_par"

  _dbg("Hi! from "__FILE__"\n");

  /* Cya! */
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

/* List of implemented commands for this subset */
struct ce_command_subset test_command_subset_part_A =
{
  .name = "test_subset_part_A",
  .command = (struct ce_command *[])
  {
    /* enum CE_COMMAND_SUBSET_TEST_CMD1 -> test_cmd1 */
    &(struct ce_command)
    {
      .id   = CE_COMMAND_SUBSET_TEST_CMD1, .validate = test_cmd1_val,
      .name = "test_cmd1",                 .parse    = test_cmd1_par
    },
    /* enum CE_COMMAND_SUBSET_TEST_CMD2 -> test_cmd2 */
    &(struct ce_command)
    {
      .id   = CE_COMMAND_SUBSET_TEST_CMD2, .validate = test_cmd2_val,
      .name = "test_cmd2",                 .parse    = test_cmd2_par
    },
    NULL
  }
};

/* List of implemented commands for this subset */
struct ce_command_subset test_command_subset_part_B =
{
  .name = "test_subset_part_B",
  .command = (struct ce_command *[])
  {
    /* enum CE_COMMAND_SUBSET_TEST_CMD1 -> test_cmd1 */
    &(struct ce_command)
    {
      .id   = CE_COMMAND_SUBSET_TEST_CMD3, .validate = test_cmd1_val,
      .name = "test_cmd3",                 .parse    = test_cmd1_par
    },
    /* enum CE_COMMAND_SUBSET_TEST_CMD2 -> test_cmd2 */
    &(struct ce_command)
    {
      .id   = CE_COMMAND_SUBSET_TEST_CMD4, .validate = test_cmd2_val,
      .name = "test_cmd4",                 .parse    = test_cmd2_par
    },
    NULL
  }
};

#undef YCP_NAME
