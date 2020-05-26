/* set_test.h - Tests commands subset for `ce` for yacup project
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
#ifndef __CE_COMMAND_SET_TEST_H
#define __CE_COMMAND_SET_TEST_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup ce_command_set_test Test commands
 * @{
 *   @brief      Some commands for testing purposes
 *   @ingroup    ce_command
 *   @author     CieNTi <cienti@cienti.com>
 *   @date       2020
 */

/* C libraries */
#include <stdint.h>
#include <stddef.h>
#include "yacup/ce/command.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @name       Unique identifiers
 * @{
 */
/**
 * @brief      *test_cmd1(u8)* identifier. Related to @ref test_cmd1_listener,
 *             @ref test_command_subset_part_A and @ref test_command_set
 */
#define  CE_COMMAND_SET_TEST_CMD1 0xA1
/**
 * @brief      *test_cmd2(u8, d)* identifier. Related to @ref
 *             test_cmd2_listener, @ref test_command_subset_part_A and @ref
 *             test_command_set
 */
#define  CE_COMMAND_SET_TEST_CMD2 0xA2
/**
 * @brief      *test_cmd3(u8)* identifier. Related to @ref
 *             test_command_subset_part_B and @ref test_command_set
 */
#define  CE_COMMAND_SET_TEST_CMD3 0xA3
/**
 * @brief      *test_cmd4(u8, d)* identifier. Related to @ref
 *             test_command_subset_part_B and @ref test_command_set
 */
#define  CE_COMMAND_SET_TEST_CMD4 0xA4
/**
 * @brief      *test_cmd5(void)* identifier. Related to @ref
 *             test_command_subset_part_B and @ref test_command_set
 */
#define  CE_COMMAND_SET_TEST_CMD5 0xA5
/** @} */

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @name       Listeners
 * @{
 */
/**
 * @brief      Das *test_cmd1_listener* struct
 */
extern struct ce_command_listener test_cmd1_listener;
/**
 * @brief      Das *test_cmd2_listener* struct
 */
extern struct ce_command_listener test_cmd2_listener;
/** @} */

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @name       Subsets
 * @{
 */
/**
 * @brief      Das *test_command_subset_part_A* struct
 */
extern struct ce_command_subset test_command_subset_part_A;
/**
 * @brief      Das *test_command_subset_part_B* struct
 */
extern struct ce_command_subset test_command_subset_part_B;
/** @} */

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @name       Sets
 * @{
 */
/**
 * @brief      Das *test_command_set* struct
 */
extern struct ce_command_set test_command_set;
/** @} */

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CE_COMMAND_SET_TEST_H */
