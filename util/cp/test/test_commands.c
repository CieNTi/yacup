/* test_commands.c - A simple set of commands for `cp` testing
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
#include "yacup/cp/codec.h"

/* Header located near this file, used as an external header in app */
//#include "cp_simple.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define YCP_FORCE_DEBUG
#include "yacup/debug.h"
#undef YCP_NAME
#define YCP_NAME "util/cp/test/test_commands"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
struct cp_argument
{
  enum cp_codec_data_type type;
  void *data;
};

struct cp_command
{
  uint32_t id;
  char *name;
  int (*encode)(struct cp_argument *argument[]);
  int (*decode)(struct cp_argument *argument[]);
};

/* Encode function for test_cmd1 */
int cmd1_efn(struct cp_argument *argument[])
{
  /* Ok! */
  return 0;
}

/* Decode function for test_cmd1 */
int cmd1_dfn(struct cp_argument *argument[])
{
  /* Ok! */
  return 0;
}

/* Encode function for test_cmd2 */
int cmd2_efn(struct cp_argument *argument[])
{
  /* Ok! */
  return 0;
}

/* Decode function for test_cmd2 */
int cmd2_dfn(struct cp_argument *argument[])
{
  /* Ok! */
  return 0;
}

enum test_commands
{
  test_cmd1 = 0,
  test_cmd2 = 1
};

/* List of implemented commands */
struct cp_command test_commands[] =
{
  /* enum test_commands -> test_cmd1 */
  {
    .id = 0x01, .name = "test_cmd1", .encode = cmd1_efn, .decode = cmd1_dfn
  },
  /* enum test_commands -> test_cmd2 */
  {
    .id = 0x02, .name = "test_cmd2", .encode = cmd2_efn, .decode = cmd2_dfn
  }
};

#undef YCP_NAME
#undef YCP_FORCE_DEBUG
