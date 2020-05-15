/* test_cp_codec_B416K.c - Test to check cp's B416K codec functionality
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
#include "yacup/rb.h"
#include "yacup/rb/debug.h"
#include "yacup/rb/driver/overwrite.h"
#include "yacup/cp/debug.h"
#include "yacup/cp/codec.h"
#include "yacup/cp/codec/B416K.h"

/* This include acts like an external application include, located elsewhere */
//#include "cp_external.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define YCP_FORCE_DEBUG
#include "yacup/debug.h"
#undef YCP_NAME
#define YCP_NAME "util/cp/test/test_cp_codec_B416K"

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
int test_cp_codec_B416K(int argc, const char* argv[])
{
  /* Configure _dbg() */
  #define YCP_FNAME "test_cp_codec_B416K"

  _dbg("Hi! from "__FILE__"\n");

  /* 
   * HIGH-LEVEL: Inside test/app
   */
  /* What a codec needs:
   * - one rb where to push the encoded data
   * - one rb where to save a message
   */
  #define TEST_CP_CODEC_B416K_DATA 512
  uint8_t buffer_data[TEST_CP_CODEC_B416K_DATA];
  struct rb rb_data =
  {
    .buffer = buffer_data,
    .size = TEST_CP_CODEC_B416K_DATA
  };

  /* Create rb_data using overwrite driver */
  _dbg("Initializing the 'rb_data' ring-buffer\n");
  if (rb_init(&rb_data, rb_driver_overwrite))
  {
    _dbg("Cannot initialize rb_data\n");
    return 1;
  }

  #define TEST_CP_CODEC_B416K_MESSAGE 1024
  uint8_t buffer_message[TEST_CP_CODEC_B416K_MESSAGE];
  struct rb rb_message =
  {
    .buffer = buffer_message,
    .size = TEST_CP_CODEC_B416K_MESSAGE
  };

  /* Create rb_message using overwrite driver */
  _dbg("Initializing the 'rb_message' ring-buffer\n");
  if (rb_init(&rb_message, rb_driver_overwrite))
  {
    _dbg("Cannot initialize rb_message\n");
    return 1;
  }

  /* test/app calls `cp_*` functions, not encode/decode. Test here only */

  /* 
   * MID-LOW-LEVEL: Calls to codec functions inside a `cp`
   */
  /* Set by `cp_init` */
  struct cp_codec cp_codec0 = { 0x00 };
  _dbg("Printing uninitialized 'cp_codec0'\n");
  cp_codec_print_info(&cp_codec0);

  /* Initialize codec found at `B416K.c` */
  _dbg("Initializing the `B416K` codec\n");
  if (cp_codec_init(&cp_codec0, cp_codec_B416K))
  {
    _dbg("- Cannot initialize the codec. ERROR\n");
    return 1;
  }
  _dbg("- Ok\n");
  _dbg("Printing initialized 'cp_codec0', data and message not be NULL\n");
  cp_codec_print_info(&cp_codec0);

  /* Encode a `uint8_t` variable */
  uint8_t src_data_u8 = 0xAB;
  uint8_t dst_data_u8 = 0x00;
  _dbg("Encoding a uint8_t = 0x%02X\n", src_data_u8);
  if(cp_codec0.encode.data(CP_CODEC_DATA_UINT8_T, &src_data_u8, &rb_data))
  {
    _dbg("- Cannot encode the data. ERROR\n");
    return 1;
  }
  _dbg("- Ok\n");

  /* Cya! */
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

#undef YCP_NAME
#undef YCP_FORCE_DEBUG
