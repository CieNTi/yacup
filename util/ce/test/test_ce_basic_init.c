/* test_ce_basic_init.c - Check validation over different test commands
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
#include "yacup/rb/driver/overwrite.h"
#include "yacup/ce.h"
#include "yacup/ce/codec.h"
#include "yacup/ce/codec/B416K.h"
#include "yacup/ce/command.h"
#include "yacup/ce/command/subset_test.h"
#include "yacup/ce/chat/fire-and-forget.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define YCP_FORCE_DEBUG
#include "yacup/debug.h"
#undef YCP_NAME
#define YCP_NAME "util/ce/test/test_ce_basic_init"

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
int test_ce_basic_init(int argc, const char* argv[])
{
  /* Configure _dbg() */
  #define YCP_FNAME "test_ce_basic_init"

  _dbg("Hi! from "__FILE__"\n");

  /* Out first `ce`, prepare the essential data */
  #define CE_TEST_CH_BUF_LEN 256
  struct ce ce0 =
  {
    /* Command engine entity parameters */
    .name = "Super Engine!",

    /* Output channel command set (subset_test.c) */
    .out.command_set = &test_command_set,
    /* Output channel message buffer */
    .out.rb.buffer = (uint8_t [CE_TEST_CH_BUF_LEN]) { 0x00 },
    .out.rb.size = CE_TEST_CH_BUF_LEN,

    /* Input channel command set (subset_test.c) */
    .in.command_set = &test_command_set,
    /* Input channel message buffer */
    .in.rb.buffer = (uint8_t [CE_TEST_CH_BUF_LEN]) { 0x00 },
    .in.rb.size = CE_TEST_CH_BUF_LEN
  };

  /* Initializes first channels, then ce */
  if (ce_channel_init(&ce0.out, ce_codec_B416K, rb_driver_overwrite) ||
      ce_channel_init(&ce0.in, ce_codec_B416K, rb_driver_overwrite) ||
      ce_init(&ce0, ce_driver_faf))
  {
    /* Cannot init, error */
    _dbg("Error when initializing ce0\n");
    return 1;
  }

  /* 
   * Send a command
   */
  /* Compose arguments */
  struct ce_command_argument *cmd1_args[] =
  {
    &(struct ce_command_argument) { .type = CE_DATA_UINT8_T, .data.u8 = 250 },
    NULL
  };
  /* Call for command send */
  if (ce_send_command(&ce0, CE_COMMAND_SUBSET_TEST_CMD1, cmd1_args))
  {
    /* Cannot send, error */
    _dbg("Error when sending CE_COMMAND_SUBSET_TEST_CMD1\n");
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
