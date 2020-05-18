/* subset_test.h - Tests commands subset for `cp` for yacup project
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
#ifndef __CP_COMMAND_SUBSET_TEST_H
#define __CP_COMMAND_SUBSET_TEST_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @ingroup cp
 * @{
 *   @addtogroup cp_command_subset
 *   @{
 */

/* C libraries */
#include <stdint.h>
#include <stddef.h>
#include "yacup/cp/command.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
enum command_subset_test_id
{
  CP_COMMAND_SUBSET_TEST_CMD1 = 0,
  CP_COMMAND_SUBSET_TEST_CMD2 = 1
};

extern struct cp_command_subset command_subset_test;

/** @} */
/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CP_COMMAND_SUBSET_TEST_H */
