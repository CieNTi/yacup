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
#define  CE_COMMAND_SUBSET_TEST_CMD1 0xA1
#define  CE_COMMAND_SUBSET_TEST_CMD2 0xA2
#define  CE_COMMAND_SUBSET_TEST_CMD3 0xA3
#define  CE_COMMAND_SUBSET_TEST_CMD4 0xA4
#define  CE_COMMAND_SUBSET_TEST_CMD5 0xA5

extern struct ce_command_listener test_cmd1_listener;

extern struct ce_command_subset test_command_subset_part_A;
extern struct ce_command_subset test_command_subset_part_B;
extern struct ce_command_set test_command_set;

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CE_COMMAND_SUBSET_TEST_H */
