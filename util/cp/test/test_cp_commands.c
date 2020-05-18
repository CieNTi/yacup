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

/* Header located near this file, used as an external header in app */
//#include "cp_simple.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define YCP_FORCE_DEBUG
#include "yacup/debug.h"
#undef YCP_NAME
#define YCP_NAME "util/cp/test/test_cp_commands"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* Encode function for test_cmd1 */
int cmd1_val(struct cp_command *command, struct cp_argument *argument[])
{
  /* Configure _dbg() */
  #define YCP_FNAME "cmd1_val"

  /* This specific example command requires only a uint8_t argument */
  if (/* Validate if there is a first argument or not */
      argument[0] == NULL                        ||
      /* Got it, now validate if it is the expected type */
      argument[0]->type != CP_CODEC_DATA_UINT8_T ||
      /* Purfect, now we can do some value check */
      !(*(uint8_t *)argument[0]->data < 251)     ||
      /* And should not be another argument */
      argument[1] != NULL)
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

/* Decode function for test_cmd1 */
int cmd1_par(struct cp_command *command, struct cp_argument *argument[])
{
  /* Configure _dbg() */
  #define YCP_FNAME "cmd1_par"

  _dbg("Hi! from "__FILE__"\n");

  /* Cya! */
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

/* Encode function for test_cmd2 */
int cmd2_val(struct cp_command *command, struct cp_argument *argument[])
{
  /* Configure _dbg() */
  #define YCP_FNAME "cmd2_val"

  /* This specific example requires one uint8_t and one double arguments */
  if (/* Validate if there is a first argument or not */
      argument[0] == NULL                        ||
      /* Got it, now validate if it is the expected type */
      argument[0]->type != CP_CODEC_DATA_UINT8_T ||
      /* Purfect, now we can do some value check */
      !(*(uint8_t *)argument[0]->data < 251)     ||
      /* Validate if there is a second argument or not */
      argument[1] == NULL                        ||
      /* Got it, now validate if it is the expected type */
      argument[1]->type != CP_CODEC_DATA_DOUBLE  ||
      /* Purfect, now we can do some value check */
      !(*(double *)argument[1]->data > -1.234) ||
      /* And should not be another argument */
      argument[2] != NULL)
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

/* Decode function for test_cmd2 */
int cmd2_par(struct cp_command *command, struct cp_argument *argument[])
{
  /* Configure _dbg() */
  #define YCP_FNAME "cmd2_par"

  _dbg("Hi! from "__FILE__"\n");

  /* Cya! */
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

enum command_set1_id
{
  CP_COMMAND_SET1_CMD1 = 0,
  CP_COMMAND_SET1_CMD2 = 1
};

/* List of implemented commands */
struct cp_command *command_set1[] =
{
  /* enum CP_COMMAND_SET1_CMD1 -> test_cmd1 */
  &(struct cp_command)
  {
    .id = 0x01, .name = "test_cmd1", .validate = cmd1_val, .parse = cmd1_par
  },
  /* enum CP_COMMAND_SET1_CMD2 -> test_cmd2 */
  &(struct cp_command)
  {
    .id = 0x02, .name = "test_cmd2", .validate = cmd2_val, .parse = cmd2_par
  },
  NULL
};

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

  /* Compose arguments */
  struct cp_argument *set1_cmd1_args[] =
  {
    &(struct cp_argument)
    { .type = CP_CODEC_DATA_UINT8_T, .data = &(uint8_t){ 250 } },
    NULL
  };

  /* Validate command */
  if (cp_command_validate(command_set1, CP_COMMAND_SET1_CMD1, set1_cmd1_args))
  {
    /* Cannot send, error */
    _dbg("Error when validating CP_COMMAND_SET1_CMD1\n");
    return 1;
  }

  /* Compose arguments */
  struct cp_argument *set1_cmd2_args[] =
  {
    &(struct cp_argument)
    { .type = CP_CODEC_DATA_UINT8_T, .data = &(uint8_t){ 250 } },
    &(struct cp_argument)
    { .type = CP_CODEC_DATA_DOUBLE,  .data = &(double){ -1.233 } },
    NULL
  };

  /* Validate command */
  if (cp_command_validate(command_set1, CP_COMMAND_SET1_CMD2, set1_cmd2_args))
  {
    /* Cannot send, error */
    _dbg("Error when validating CP_COMMAND_SET1_CMD2\n");
    return 1;
  }

  /* Cya! */
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

#undef YCP_NAME
#undef YCP_FORCE_DEBUG
