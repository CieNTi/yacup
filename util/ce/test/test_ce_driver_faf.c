/* test_ce_driver_faf.c - Test a *fire-and-forget* *ce* driver functionality
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
#include "yacup/fsm.h"
#include "yacup/ce/codec.h"
#include "yacup/ce/codec/B416K.h"
#include "yacup/ce/command/set_test.h"
#include "yacup/ce/driver/fire-and-forget.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define YCP_FORCE_DEBUG
#include "yacup/debug.h"
#undef YCP_NAME
#define YCP_NAME "util/ce/test/test_ce_driver_faf"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Test to check *ce* functionality using a single CE
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
int test_ce_driver_faf(int argc, const char* argv[])
{
  /* Configure _dbg() */
  #define YCP_FNAME "test_ce_driver_faf"

  _dbg("Hi! from "__FILE__"\n");

  /* Out *ce* for driver testing, prepare the essential data */
  #define CE_DRV_FAF_TEST_DATA_BUF_LEN 128
  #define CE_DRV_FAF_TEST_MESSAGE_BUF_LEN 256
  struct ce ce0 =
  {
    /* Command engine entity parameters */
    .name = "CE Engine with driver",

    /* Output channel command set (set_test.c) */
    .out.command_set = &test_command_set,
    /* Output channel data buffer */
    .out.data.buffer = (uint8_t [CE_DRV_FAF_TEST_DATA_BUF_LEN]) { 0x00 },
    .out.data.size = CE_DRV_FAF_TEST_DATA_BUF_LEN,
    /* Output channel message buffer */
    .out.message.buffer = (uint8_t [CE_DRV_FAF_TEST_MESSAGE_BUF_LEN]) { 0x00 },
    .out.message.size = CE_DRV_FAF_TEST_MESSAGE_BUF_LEN,

    /* Input channel command set (set_test.c) */
    .in.command_set = &test_command_set,
    /* Input channel data buffer */
    .in.data.buffer = (uint8_t [CE_DRV_FAF_TEST_DATA_BUF_LEN]) { 0x00 },
    .in.data.size = CE_DRV_FAF_TEST_DATA_BUF_LEN,
    /* Input channel message buffer */
    .in.message.buffer = (uint8_t [CE_DRV_FAF_TEST_MESSAGE_BUF_LEN]) { 0x00 },
    .in.message.size = CE_DRV_FAF_TEST_MESSAGE_BUF_LEN
  };

  /* Initializes the engine */
  _dbg("Should initialize command engine '%s' correctly\n", ce0.name);
  if (ce_init(&ce0, ce_driver_faf, ce_codec_B416K, rb_driver_overwrite))
  {
    /* Cannot init, error */
    _dbg("Error when initializing ce0\n");
    return 1;
  }
  _dbg("Ok\n");

  /* Cya! */
  _dbg("If you are reading this, everything went correctly :_)\n");
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

#undef YCP_NAME
#undef YCP_FORCE_DEBUG
