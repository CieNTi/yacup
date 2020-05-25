/* test_ce_command_codec.c - Validates a command codec
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
#include "yacup/ce/command/subset_test.h"
#include "yacup/ce/command_codec.h"
#include "yacup/ce/command/codec/binary.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define YCP_FORCE_DEBUG
#include "yacup/debug.h"
#undef YCP_NAME
#define YCP_NAME "util/ce/test/test_ce_command_codec"

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
int test_ce_command_codec(int argc, const char* argv[])
{
  /* Configure _dbg() */
  #define YCP_FNAME "test_ce_command_codec"

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
    &(struct ce_command_argument) { .type = CE_DATA_UINT8_T, .data.u8 = 1 },
    NULL
  };

  /* Validate command */
  struct ce_command *cmd_to_encode = NULL;
  _dbg("Should validate: Valid 1 argument vs. 1 argument command\n");
  cmd_to_encode = ce_command_validate(&cmd_set,
                                      CE_COMMAND_SUBSET_TEST_CMD1,
                                      cmd1_args);
  if (cmd_to_encode == NULL)
  {
    /* Cannot send, error */
    _dbg("Error when validating CE_COMMAND_SUBSET_TEST_CMD1\n");
    return 1;
  }

  /* Define command codec to use */
  struct ce_codec         ce_codec0      = { 0x00 };
  struct ce_command_codec command_codec0 = { 0x00 };
  _dbg("Should initialize ce_codec\n");
  if (ce_codec_init(&ce_codec0, ce_codec_B416K))
  {
    _dbg("- Cannot initialize the codec. ERROR\n");
    return 1;
  }
  _dbg("- Ok\n");

  _dbg("Should initialize command_codec\n");
  if (ce_command_codec_init(&command_codec0, ce_command_codec_binary))
  {
    _dbg("Oops! Cannot initialize the command codec\n");
    return 1;
  }
  _dbg("- Ok\n");

  /* Prepare a rb for encoding storage */
  #define TEST_CE_COMMAND_CODEC_DATA 512
  uint8_t buffer_data[TEST_CE_COMMAND_CODEC_DATA];
  struct rb rb_data =
  {
    .buffer = buffer_data,
    .size = TEST_CE_COMMAND_CODEC_DATA
  };

  /* Create rb_data using overwrite driver */
  _dbg("Should initialize the 'rb_data' ring-buffer\n");
  if (rb_init(&rb_data, rb_driver_overwrite))
  {
    _dbg("Cannot initialize rb_data\n");
    return 1;
  }

  /* Encode the command */
  _dbg("Should encode a command using '%s' command codec\n",
       command_codec0.name);
  if (command_codec0.encode(&ce_codec0, cmd_to_encode, cmd1_args, &rb_data))
  {
    _dbg("Cannot encode command\n");
    return 1;
  }

  _dbg("Data buffer content:\n");
  rb_print_info(&rb_data);

  /* Cya! */
  _dbg("If you are reading this, everything went correctly :_)\n");
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

#undef YCP_NAME
#undef YCP_FORCE_DEBUG
