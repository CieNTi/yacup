/* debug.h - Debug definitions to ease development
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
/* No include guards in this file so each module gets its own version */

/**
 * @ingroup debug_functions
 * @{
 */

#if defined(YACUP_DEBUG) || defined(YCP_FORCE_DEBUG)
  #ifndef PRINTF
    #include <stdio.h>
    /**
     * @brief      Macro used as `printf` replacement by `_dbg` macro, unless
     *             previously defined by the user as a custom function
     */
    #define PRINTF(...) printf(__VA_ARGS__); fflush(stdout)
  #endif
  #ifndef _dbg
    /**
     * @brief      Macro used to take debug messages and send them to stdout,
     *             unless previously defined by the user as a custom function
     *
     * @note       `YCP_NAME` is defined and undefined at a file top and bottom
     *             respectively.
     * @note       `YCP_FNAME` is defined and undefined at a function top and
     *             bottom respectively.
     */
    #define _dbg(...) PRINTF(YCP_NAME"["YCP_FNAME"] "__VA_ARGS__)
  #endif
#else
  #ifndef _dbg
    /**
     * @brief      Macro used to unify debugging messages.
     * @details    This is a configurable macro:
     * 
     * - If `YACUP_DEBUG` is defined, `PRINTF` macro will be used.
     *   - If `PRINTF` is not defined, standard `printf` will be used.
     *   - User can define `PRINTF` as a custom function. As example, instead
     *     of print to stdout, the string is sent through a serial port.
     * - If `YACUP_DEBUG` is not defined, no debug function is used and no
     *   string storage allocation is performed.
     * 
     * @note       Read `yacup/debug.h` for complete information
     */
    #define _dbg(...)
  #endif
#endif

/** @} */
