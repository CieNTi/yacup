/* test_ce_command_codec_B416K.c - Validates a command codec using B416K
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
#include "yacup/rb.h"
#include "yacup/rb/debug.h"
#include "yacup/rb/driver/overwrite.h"
#include "yacup/ce/codec.h"
#include "yacup/ce/codec/B416K.h"
#include "yacup/ce/debug_codec.h"
#include "yacup/ce/command.h"
#include "yacup/ce/command/set_test.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define YCP_FORCE_DEBUG
#include "yacup/debug.h"
#undef YCP_NAME
#define YCP_NAME "util/ce/test/test_ce_command_codec_B416K"

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
int test_ce_command_codec_B416K(int argc, const char* argv[])
{
  /* Configure _dbg() */
  #define YCP_FNAME "test_ce_command_codec_B416K"

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

  /* Define ce codec to use as underlying data encoding layer*/
  struct ce_codec         ce_codec0      = { 0x00 };
  _dbg("Should initialize ce_codec\n");
  if (ce_codec_init(&ce_codec0, ce_codec_B416K))
  {
    _dbg("Cannot initialize the codec. ERROR\n");
    return 1;
  }
  _dbg("Ok\n");

  //////////* Define command codec to use */
  /////////struct ce_command_codec command_codec0 = { 0x00 };
  /////////_dbg("Should initialize command_codec\n");
  /////////if (ce_command_codec_init(&command_codec0, ce_command_codec_binary))
  /////////{
  /////////  _dbg("Oops! Cannot initialize the command codec\n");
  /////////  return 1;
  /////////}
  /////////_dbg("Ok\n");

  /* Prepare a rb for encoding storage */
  #define TEST_CE_COMMAND_CODEC_BINARY_DATA 512
  uint8_t buffer_data[TEST_CE_COMMAND_CODEC_BINARY_DATA];
  struct rb rb_data =
  {
    .buffer = buffer_data,
    .size = TEST_CE_COMMAND_CODEC_BINARY_DATA
  };

  /* Create rb_data using overwrite driver */
  _dbg("Should initialize the 'rb_data' ring-buffer\n");
  if (rb_init(&rb_data, rb_driver_overwrite))
  {
    _dbg("Cannot initialize rb_data\n");
    return 1;
  }
  _dbg("Ok\n");

  /* Pointer to validated command */
  struct ce_command *cmd_to_encode = NULL;
  
  /* Encode 0-arguments command (with NULL argument [not array of])
   */

  /* Compose arguments */
  //struct ce_command_argument *cmd5_args[] =
  //{
  //  NULL
  //};

  /* Validate command */
  _dbg("Should validate: Valid 0 argument vs. 0 argument command\n");
  cmd_to_encode = ce_command_validate(&cmd_set,
                                      CE_COMMAND_SET_TEST_CMD5,
                                      NULL);
  if (cmd_to_encode == NULL)
  {
    /* Cannot validate, error */
    _dbg("Error when validating CE_COMMAND_SET_TEST_CMD5\n");
    return 1;
  }
  _dbg("Ok\n");

  /* Encode the command */
  _dbg("Should encode a command using '%s' command codec\n",
       ce_codec0.name);
  if (ce_codec0.encode.command(cmd_to_encode, NULL, &rb_data))
  {
    _dbg("Cannot encode command\n");
    return 1;
  }
  _dbg("Ok\n");
  rb_print_info(&rb_data);

  /* Encode 1-argument command
   */

  /* Compose arguments */
  struct ce_command_argument *cmd1_args[] =
  {
    &(struct ce_command_argument) { .type = CE_DATA_UINT8_T, .data.u8 = 1 },
    NULL
  };

  /* Validate command */
  _dbg("Should validate: Valid 1 argument vs. 1 argument command\n");
  cmd_to_encode = ce_command_validate(&cmd_set,
                                      CE_COMMAND_SET_TEST_CMD1,
                                      cmd1_args);
  if (cmd_to_encode == NULL)
  {
    /* Cannot validate, error */
    _dbg("Error when validating CE_COMMAND_SET_TEST_CMD1\n");
    return 1;
  }

  /* Encode the command */
  _dbg("Should encode a command using '%s' command codec\n",
       ce_codec0.name);
  if (ce_codec0.encode.command(cmd_to_encode, cmd1_args, &rb_data))
  {
    _dbg("Cannot encode command\n");
    return 1;
  }
  _dbg("Ok\n");
  rb_print_info(&rb_data);

  /* Encode 2-arguments command
   */

  /* Compose arguments */
  struct ce_command_argument *cmd2_args[] =
  {
    &(struct ce_command_argument) { .type = CE_DATA_UINT8_T, .data.u8 = 0x88 },
    &(struct ce_command_argument) { .type = CE_DATA_DOUBLE,  .data.d  = -1.2 },
    NULL
  };

  /* Validate command */
  _dbg("Should validate: Valid 2 arguments vs. 2 arguments command\n");
  cmd_to_encode = ce_command_validate(&cmd_set,
                                      CE_COMMAND_SET_TEST_CMD2,
                                      cmd2_args);
  if (cmd_to_encode == NULL)
  {
    /* Cannot validate, error */
    _dbg("Error when validating CE_COMMAND_SET_TEST_CMD2\n");
    return 1;
  }

  /* Encode the command */
  _dbg("Should encode a command using '%s' command codec\n",
       ce_codec0.name);
  if (ce_codec0.encode.command(cmd_to_encode, cmd2_args, &rb_data))
  {
    _dbg("Cannot encode command\n");
    return 1;
  }
  _dbg("Ok\n");
  rb_print_info(&rb_data);

  /* Set a command listener */
  if (ce_command_set_listener(&cmd_set,
                              CE_COMMAND_SET_TEST_CMD1,
                              &test_cmd1_listener))
  {
    /* Cannot set it, error */
    _dbg("Error when setting listener for CE_COMMAND_SET_TEST_CMD1\n");
    return 1;
  }

  /* Set a command listener */
  if (ce_command_set_listener(&cmd_set,
                              CE_COMMAND_SET_TEST_CMD2,
                              &test_cmd2_listener))
  {
    /* Cannot set it, error */
    _dbg("Error when setting listener for CE_COMMAND_SET_TEST_CMD2\n");
    return 1;
  }

  /* Decode command (overwrite rb = FIFO) */
  _dbg("Should decode a command using '%s' command codec\n",
       ce_codec0.name);
  if (ce_codec0.decode.command(&rb_data, &cmd_set))
  {
    _dbg("Cannot decode command\n");
    return 1;
  }
  _dbg("Ok\n");
  rb_print_info(&rb_data);

  /* Decode command (overwrite rb = FIFO) */
  _dbg("Should decode a command using '%s' command codec\n",
       ce_codec0.name);
  if (ce_codec0.decode.command(&rb_data, &cmd_set))
  {
    _dbg("Cannot decode command\n");
    return 1;
  }
  _dbg("Ok\n");
  rb_print_info(&rb_data);

  /* Decode command (overwrite rb = FIFO) */
  _dbg("Should decode a command using '%s' command codec\n",
       ce_codec0.name);
  if (ce_codec0.decode.command(&rb_data, &cmd_set))
  {
    _dbg("Cannot decode command\n");
    return 1;
  }
  _dbg("Ok\n");
  rb_print_info(&rb_data);

  /* Cya! */
  _dbg("If you are reading this, everything went correctly :_)\n");
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

#undef YCP_NAME
#undef YCP_FORCE_DEBUG
