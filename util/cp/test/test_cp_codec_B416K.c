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
#include <string.h>
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
int encode_decode_check_by_type(struct cp_codec *codec,
                                enum cp_codec_data_type type,
                                struct rb *rb)
{
  /* Configure _dbg() */
  #define YCP_FNAME "encode_decode_check_by_type"

  /* All data types, source and destination flavours */
  //head      src_head        = 0;              head      dst_head        = 0;
  //tail      src_tail        = 0;              tail      dst_tail        = 0;
  //glue      src_glue        = 0;              glue      dst_glue        = 0;
  char      src_char[128]   = "abcd";         char      dst_char[128]   = "";
  uint8_t   src_uint8_t     = 100;            uint8_t   dst_uint8_t     = 0;
  int8_t    src_int8_t      = -100;           int8_t    dst_int8_t      = 0;
  uint16_t  src_uint16_t    = 300;            uint16_t  dst_uint16_t    = 0;
  int16_t   src_int16_t     = -300;           int16_t   dst_int16_t     = 0;
  uint32_t  src_uint32_t    = 100000;         uint32_t  dst_uint32_t    = 0;
  int32_t   src_int32_t     = -100000;        int32_t   dst_int32_t     = 0;
  uint64_t  src_uint64_t    = 4300000000;     uint64_t  dst_uint64_t    = 0;
  int64_t   src_int64_t     = -4300000000;    int64_t   dst_int64_t     = 0;
  float     src_float       = -1.23456789012; float     dst_float       = 0.0;
  double    src_double      = -1.23456789012; double    dst_double      = 0.0;
  /* Pointers to them, both fashions */
  void      *src_pt         = NULL;           void      *dst_pt         = NULL;
  size_t    len_data        = 0;

  /* Branch on type to assign valid pointers */
  switch(type)
  {
    case CP_CODEC_DATA_HEAD:
      _dbg("Selected data type CP_CODEC_DATA_HEAD = %lu\n", (size_t)type);
      //src_pt = &src_head;     dst_pt = &dst_head;     len_data = 1;
      return 1; // Not implemented yet
      break;
    case CP_CODEC_DATA_TAIL:
      _dbg("Selected data type CP_CODEC_DATA_TAIL = %lu\n", (size_t)type);
      //src_pt = &src_tail;     dst_pt = &dst_tail;     len_data = 1;
      return 1; // Not implemented yet
      break;
    case CP_CODEC_DATA_GLUE:
      _dbg("Selected data type CP_CODEC_DATA_GLUE = %lu\n", (size_t)type);
      //src_pt = &src_glue;     dst_pt = &dst_glue;     len_data = 1;
      return 1; // Not implemented yet
      break;
    case CP_CODEC_DATA_CHAR:
      _dbg("Selected data type CP_CODEC_DATA_CHAR = %lu\n", (size_t)type);
      src_pt = &src_char;     dst_pt = &dst_char;
      /* strlen() counts all but 0x00, so add it here to directly decode it */
      len_data = strlen(src_char) + 1;
      break;
    case CP_CODEC_DATA_UINT8_T:
      _dbg("Selected data type CP_CODEC_DATA_UINT8_T = %lu\n", (size_t)type);
      src_pt = &src_uint8_t;  dst_pt = &dst_uint8_t;  len_data = 1;
      break;
    case CP_CODEC_DATA_INT8_T:
      _dbg("Selected data type CP_CODEC_DATA_INT8_T = %lu\n", (size_t)type);
      src_pt = &src_int8_t;   dst_pt = &dst_int8_t;   len_data = 1;
      break;
    case CP_CODEC_DATA_UINT16_T:
      _dbg("Selected data type CP_CODEC_DATA_UINT16_T = %lu\n", (size_t)type);
      src_pt = &src_uint16_t; dst_pt = &dst_uint16_t; len_data = 1;
      break;
    case CP_CODEC_DATA_INT16_T:
      _dbg("Selected data type CP_CODEC_DATA_INT16_T = %lu\n", (size_t)type);
      src_pt = &src_int16_t;  dst_pt = &dst_int16_t;  len_data = 1;
      break;
    case CP_CODEC_DATA_UINT32_T:
      _dbg("Selected data type CP_CODEC_DATA_UINT32_T = %lu\n", (size_t)type);
      src_pt = &src_uint32_t; dst_pt = &dst_uint32_t; len_data = 1;
      break;
    case CP_CODEC_DATA_INT32_T:
      _dbg("Selected data type CP_CODEC_DATA_INT32_T = %lu\n", (size_t)type);
      src_pt = &src_int32_t;  dst_pt = &dst_int32_t;  len_data = 1;
      break;
    case CP_CODEC_DATA_UINT64_T:
      _dbg("Selected data type CP_CODEC_DATA_UINT64_T = %lu\n", (size_t)type);
      src_pt = &src_uint64_t; dst_pt = &dst_uint64_t; len_data = 1;
      break;
    case CP_CODEC_DATA_INT64_T:
      _dbg("Selected data type CP_CODEC_DATA_INT64_T = %lu\n", (size_t)type);
      src_pt = &src_int64_t;  dst_pt = &dst_int64_t;  len_data = 1;
      break;
    case CP_CODEC_DATA_FLOAT:
      _dbg("Selected data type CP_CODEC_DATA_FLOAT = %lu\n", (size_t)type);
      src_pt = &src_float;    dst_pt = &dst_float;    len_data = 1;
      break;
    case CP_CODEC_DATA_DOUBLE:
      _dbg("Selected data type CP_CODEC_DATA_DOUBLE = %lu\n", (size_t)type);
      src_pt = &src_double;   dst_pt = &dst_double;   len_data = 1;
      break;
    default:
      _dbg("Unrecognized type %lu\n", (size_t)type);
      return 1;
  }

  /* Encode selected variable */
  _dbg("Encoding type %lu from address %p\n", (size_t)type, src_pt);
  if(codec->encode.data(rb, type, src_pt, len_data) < 1)
  {
    _dbg("- Cannot encode the data. ERROR\n");
    return 1;
  }
  _dbg("- Ok\n");

  /* Decode a selected variable */
  _dbg("Decoding type %lu to address %p\n", (size_t)type, dst_pt);
  if(codec->decode.data(rb, type, dst_pt, len_data) < 1)
  {
    _dbg("- Cannot decode the data. ERROR\n");
    return 1;
  }
  _dbg("- Ok\n");

  /* Branch on type to check each returned value */
  uint8_t res = 0;
  switch(type)
  {
    case CP_CODEC_DATA_HEAD:
      _dbg("Checking data type CP_CODEC_DATA_HEAD = %lu\n", (size_t)type);
      //res = (src_head == dst_head);
      //_dbg("%u == %u?\n", src_head, dst_head);
      return 1; // Not implemented yet
      break;
    case CP_CODEC_DATA_TAIL:
      _dbg("Checking data type CP_CODEC_DATA_TAIL = %lu\n", (size_t)type);
      //res = (src_tail == dst_tail);
      //_dbg("%u == %u?\n", src_tail, dst_tail);
      return 1; // Not implemented yet
      break;
    case CP_CODEC_DATA_GLUE:
      _dbg("Checking data type CP_CODEC_DATA_GLUE = %lu\n", (size_t)type);
      //res = (src_glue == dst_glue);
      //_dbg("%u == %u?\n", src_glue, dst_glue);
      return 1; // Not implemented yet
      break;
    case CP_CODEC_DATA_CHAR:
      _dbg("Checking data type CP_CODEC_DATA_CHAR = %lu\n", (size_t)type);
      res = (strcmp(src_char, dst_char) == 0);
      _dbg("%s == %s?\n", src_char, dst_char);
      break;
    case CP_CODEC_DATA_UINT8_T:
      _dbg("Checking data type CP_CODEC_DATA_UINT8_T = %lu\n", (size_t)type);
      res = (src_uint8_t == dst_uint8_t);
      _dbg("%u == %u?\n", src_uint8_t, dst_uint8_t);
      break;
    case CP_CODEC_DATA_INT8_T:
      _dbg("Checking data type CP_CODEC_DATA_INT8_T = %lu\n", (size_t)type);
      res = (src_int8_t == dst_int8_t);
      _dbg("%i == %i?\n", src_int8_t, dst_int8_t);
      break;
    case CP_CODEC_DATA_UINT16_T:
      _dbg("Checking data type CP_CODEC_DATA_UINT16_T = %lu\n", (size_t)type);
      res = (src_uint16_t == dst_uint16_t);
      _dbg("%u == %u?\n", src_uint16_t, dst_uint16_t);
      break;
    case CP_CODEC_DATA_INT16_T:
      _dbg("Checking data type CP_CODEC_DATA_INT16_T = %lu\n", (size_t)type);
      res = (src_int16_t == dst_int16_t);
      _dbg("%i == %i?\n", src_int16_t, dst_int16_t);
      break;
    case CP_CODEC_DATA_UINT32_T:
      _dbg("Checking data type CP_CODEC_DATA_UINT32_T = %lu\n", (size_t)type);
      res = (src_uint32_t == dst_uint32_t);
      _dbg("%u == %u?\n", src_uint32_t, dst_uint32_t);
      break;
    case CP_CODEC_DATA_INT32_T:
      _dbg("Checking data type CP_CODEC_DATA_INT32_T = %lu\n", (size_t)type);
      res = (src_int32_t == dst_int32_t);
      _dbg("%i == %i?\n", src_int32_t, dst_int32_t);
      break;
    case CP_CODEC_DATA_UINT64_T:
      _dbg("Checking data type CP_CODEC_DATA_UINT64_T = %lu\n", (size_t)type);
      res = (src_uint64_t == dst_uint64_t);
      _dbg("%lu == %lu?\n", src_uint64_t, dst_uint64_t);
      break;
    case CP_CODEC_DATA_INT64_T:
      _dbg("Checking data type CP_CODEC_DATA_INT64_T = %lu\n", (size_t)type);
      res = (src_int64_t == dst_int64_t);
      _dbg("%li == %li?\n", src_int64_t, dst_int64_t);
      break;
    case CP_CODEC_DATA_FLOAT:
      _dbg("Checking data type CP_CODEC_DATA_FLOAT = %lu\n", (size_t)type);
      res = (src_float == dst_float);
      _dbg("%f == %f?\n", src_float, dst_float);
      break;
    case CP_CODEC_DATA_DOUBLE:
      _dbg("Checking data type CP_CODEC_DATA_DOUBLE = %lu\n", (size_t)type);
      res = (src_double == dst_double);
      _dbg("%f == %f?\n", src_double, dst_double);
      break;
    default:
      _dbg("What? How did you arrive here bro? SUPER FAIL\n");
      return 1;
  }

  if (res == 1)
  {
    _dbg(":) Valid comparison!\n");
  }
  else
  {
    _dbg(":( Invalid comparison!\n");
    return 1;
  }

  /* Ok! */
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

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
  struct cp_codec codec0 = { 0x00 };
  _dbg("Printing uninitialized 'codec0'\n");
  cp_codec_print_info(&codec0);

  /* Initialize codec found at `B416K.c` */
  _dbg("Initializing the `B416K` codec\n");
  if (cp_codec_init(&codec0, cp_codec_B416K))
  {
    _dbg("- Cannot initialize the codec. ERROR\n");
    return 1;
  }
  _dbg("- Ok\n");
  _dbg("Printing initialized 'codec0', data and message not be NULL\n");
  cp_codec_print_info(&codec0);

  /* Encode/decode and Compare */
  _dbg("Per each type: Encode -> Decode -> Compare\n");

  if(!(encode_decode_check_by_type(&codec0, CP_CODEC_DATA_HEAD, &rb_data))||
     !(encode_decode_check_by_type(&codec0, CP_CODEC_DATA_TAIL, &rb_data))||
     !(encode_decode_check_by_type(&codec0, CP_CODEC_DATA_GLUE, &rb_data))||
     encode_decode_check_by_type(&codec0, CP_CODEC_DATA_CHAR, &rb_data) ||
     encode_decode_check_by_type(&codec0, CP_CODEC_DATA_UINT8_T, &rb_data) ||
     encode_decode_check_by_type(&codec0, CP_CODEC_DATA_INT8_T, &rb_data) ||
     encode_decode_check_by_type(&codec0, CP_CODEC_DATA_UINT16_T, &rb_data) ||
     encode_decode_check_by_type(&codec0, CP_CODEC_DATA_INT16_T, &rb_data) ||
     encode_decode_check_by_type(&codec0, CP_CODEC_DATA_UINT32_T, &rb_data) ||
     encode_decode_check_by_type(&codec0, CP_CODEC_DATA_INT32_T, &rb_data) ||
     encode_decode_check_by_type(&codec0, CP_CODEC_DATA_UINT64_T, &rb_data) ||
     encode_decode_check_by_type(&codec0, CP_CODEC_DATA_INT64_T, &rb_data) ||
     encode_decode_check_by_type(&codec0, CP_CODEC_DATA_FLOAT, &rb_data) ||
     encode_decode_check_by_type(&codec0, CP_CODEC_DATA_DOUBLE, &rb_data) ||
     0)
  {
    _dbg("- A step failed. ERROR\n");
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
