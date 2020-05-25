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
#include "yacup/rb/driver/overwrite.h"
#include "yacup/ce.h"
#include "yacup/ce/codec.h"
#include "yacup/ce/codec/B416K.h"
#include "yacup/ce/command.h"
#include "yacup/ce/command/subset_test.h"


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

  /* Cya! */
  _dbg("If you are reading this, everything went correctly :_)\n");
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

#undef YCP_NAME
#undef YCP_FORCE_DEBUG
