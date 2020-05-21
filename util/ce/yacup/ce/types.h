/* types.h - Available enums/types for `ce` for yacup project
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
#ifndef __CE_TYPES_H
#define __CE_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup   ce
 * @{
 */

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Data types a `ce` understand
 */
enum ce_data_type
{
  CE_DATA_UINT8_T  = 0, CE_DATA_INT8_T  = 1,
  CE_DATA_UINT16_T = 2, CE_DATA_INT16_T = 3,
  CE_DATA_UINT32_T = 4, CE_DATA_INT32_T = 5,
  CE_DATA_UINT64_T = 6, CE_DATA_INT64_T = 7,
  CE_DATA_FLOAT    = 8, CE_DATA_DOUBLE  = 9,
  CE_DATA_CHAR     = 10
};

union ce_data
{
  uint8_t  u8;
  int8_t   i8;
  uint16_t u16;
  int16_t  i16;
  uint32_t u32;
  int32_t  i32;
  uint64_t u64;
  int64_t  i64;
  float    f;
  double   d;
  char     c;
};

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CE_TYPES_H */
