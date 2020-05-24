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
 * @brief      Supported data types in a command engine
 */
enum ce_data_type
{
  CE_DATA_NULL,
  CE_DATA_UINT8_T,
  CE_DATA_INT8_T,
  CE_DATA_UINT16_T,
  CE_DATA_INT16_T,
  CE_DATA_UINT32_T,
  CE_DATA_INT32_T,
  CE_DATA_UINT64_T,
  CE_DATA_INT64_T,
  CE_DATA_FLOAT,
  CE_DATA_DOUBLE
};

/**
 * @brief      Storage and namings for supported data types in a command engine
 */
union ce_data
{
  /**
   * @brief      Reference to a uint8_t (matches with CE_DATA_UINT8_T)
   */
  uint8_t  u8;
  
  /**
   * @brief      Reference to a int8_t (matches with CE_DATA_INT8_T)
   */
  int8_t   i8;
  
  /**
   * @brief      Reference to a uint16_t (matches with CE_DATA_UINT16_T)
   */
  uint16_t u16;
  
  /**
   * @brief      Reference to a int16_t (matches with CE_DATA_INT16_T)
   */
  int16_t  i16;
  
  /**
   * @brief      Reference to a uint32_t (matches with CE_DATA_UINT32_T)
   */
  uint32_t u32;
  
  /**
   * @brief      Reference to a int32_t (matches with CE_DATA_INT32_T)
   */
  int32_t  i32;
  
  /**
   * @brief      Reference to a uint64_t (matches with CE_DATA_UINT64_T)
   */
  uint64_t u64;
  
  /**
   * @brief      Reference to a int64_t (matches with CE_DATA_INT64_T)
   */
  int64_t  i64;
  
  /**
   * @brief      Reference to a float (matches with CE_DATA_FLOAT)
   */
  float    f;
  
  /**
   * @brief      Reference to a double (matches with CE_DATA_DOUBLE)
   */
  double   d;
  
  /**
   * @brief      Reference to a char (matches with CE_DATA_CHAR)
   */
  char     c;
};

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CE_TYPES_H */
