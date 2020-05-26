/* doxygen-groups.h - Define Doxygen groups structure, not real header
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
#ifndef __DOXYGEN_GROUPS_H
#define __DOXYGEN_GROUPS_H

/* This file covers that groups that are not defined in a header files */

/**
 * @defgroup    util Utilities
 * @{
  *   @brief    Available utilities and implementations documentation
 * @}
 *
 * @defgroup    test Tests
 * @{
 *   @brief     This module contains all available tests and all available
 *              debug functions published by the developer
 *   @details   In order to include tests here, use *ingroup* as shown on
 *              template files
 *   @author    CieNTi <cienti@cienti.com>
 *   @date      2020
 *
 *   @defgroup    app_test Application tests
 *   @{
 *     @brief     Available tests for applications (*src* folder)
 *     @details   Applications are found inside *src* folder and it will
 *                normally depends on something found on *util* folder (but it
 *                is not mandatory)
 *     @author    CieNTi <cienti@cienti.com>
 *     @date      2020
 *   @}
 *
 *   @defgroup    util_test Utilities tests
 *   @{
 *     @brief     Available tests for utilities (*util* folder)
 *     @details   Utilities are found inside *util* folder and it will depends
 *                only on foreign libraries or something found inside *util*
 *                folder, but not from *src* one (as this is an application)
 *     @author    CieNTi <cienti@cienti.com>
 *     @date      2020
 *   @}
 * @}
 *
 * @defgroup    debug Debug and development
 * @{
 *   @defgroup    debug_functions Debug functions
 *   @{
 *     @brief     Debugging helper functions to ease the development flow
 *     @details   Each *util* or *app* is responsible of create or not a debug
 *                function, but it is recommended to invest a bit of time to
 *                create them, and the more the verbose, the better
 *     @author    CieNTi <cienti@cienti.com>
 *     @date      2020
 *   @}
 * @}
 */

#endif /* __DOXYGEN_GROUPS_H */
