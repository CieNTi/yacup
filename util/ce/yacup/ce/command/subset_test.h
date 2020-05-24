/* subset_test.h - Tests commands subset for `ce` for yacup project
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
#ifndef __CE_COMMAND_SUBSET_TEST_H
#define __CE_COMMAND_SUBSET_TEST_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup ce_command_subset
 */

/* C libraries */
#include <stdint.h>
#include <stddef.h>
#include "yacup/ce/command.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
enum command_subset_test_id
{
  CE_COMMAND_SUBSET_TEST_CMD1 = 0xF0,
  CE_COMMAND_SUBSET_TEST_CMD2 = 0xF1,
  CE_COMMAND_SUBSET_TEST_CMD3 = 0xF2,
  CE_COMMAND_SUBSET_TEST_CMD4 = 0xF3
};

extern struct ce_command_subset test_command_subset_part_A;
extern struct ce_command_subset test_command_subset_part_B;

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CE_COMMAND_SUBSET_TEST_H */
