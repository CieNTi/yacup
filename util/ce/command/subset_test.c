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
/* List of implemented commands for this subset */
struct ce_command_subset test_command_subset_part_A =
{
  .name = "test_command_subset_part_A",
  .command = (struct ce_command *[])
  {
    /* enum CE_COMMAND_SUBSET_TEST_CMD1 -> test_cmd1 */
    &(struct ce_command)
    {
      .id   = CE_COMMAND_SUBSET_TEST_CMD1,
      .name = "test_cmd1",
      .signature = (enum ce_data_type [])
      {
        CE_DATA_UINT8_T,
        CE_DATA_NULL
      },
      .listener = NULL
    },
    /* enum CE_COMMAND_SUBSET_TEST_CMD2 -> test_cmd2 */
    &(struct ce_command)
    {
      .id   = CE_COMMAND_SUBSET_TEST_CMD2,
      .name = "test_cmd2",
      .signature = (enum ce_data_type [])
      {
        CE_DATA_UINT8_T, CE_DATA_DOUBLE,
        CE_DATA_NULL
      },
      .listener = NULL
    },
    NULL
  }
};

/* List of implemented commands for this subset */
struct ce_command_subset test_command_subset_part_B =
{
  .name = "test_command_subset_part_B",
  .command = (struct ce_command *[])
  {
    /* enum CE_COMMAND_SUBSET_TEST_CMD3 -> test_cmd3 */
    &(struct ce_command)
    {
      .id   = CE_COMMAND_SUBSET_TEST_CMD3,
      .name = "test_cmd3",
      .signature = (enum ce_data_type [])
      {
        CE_DATA_UINT8_T,
        CE_DATA_NULL
      },
      .listener = NULL
    },
    /* enum CE_COMMAND_SUBSET_TEST_CMD4 -> test_cmd4 */
    &(struct ce_command)
    {
      .id   = CE_COMMAND_SUBSET_TEST_CMD4,
      .name = "test_cmd4",
      .signature = (enum ce_data_type [])
      {
        CE_DATA_UINT8_T, CE_DATA_DOUBLE,
        CE_DATA_NULL
      },
      .listener = NULL
    },
    NULL
  }
};

/* Define the example command set compunded by the previous two subsets */
struct ce_command_set test_command_set =
{
  .name = "test_command_set",
  .subset = (struct ce_command_subset *[])
  {
    &test_command_subset_part_A,
    &test_command_subset_part_B,
    NULL
  }
};

#undef YCP_NAME
