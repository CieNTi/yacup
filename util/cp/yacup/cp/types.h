/* types.h - Available enums/types for `cp` for yacup project
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
#ifndef __CP_TYPES_H
#define __CP_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup   cp
 * @{
 */

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Data types a `cp` understand
 */
enum cp_data_type
{
  CP_DATA_UINT8_T  = 0, CP_DATA_INT8_T  = 1,
  CP_DATA_UINT16_T = 2, CP_DATA_INT16_T = 3,
  CP_DATA_UINT32_T = 4, CP_DATA_INT32_T = 5,
  CP_DATA_UINT64_T = 6, CP_DATA_INT64_T = 7,
  CP_DATA_FLOAT    = 8, CP_DATA_DOUBLE  = 9,
  CP_DATA_CHAR     = 10
};

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CP_TYPES_H */
