/* B416K.h - Binary 4-byte + CRC-16/Kermit codec for *ce* util
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
#ifndef __CE_CODEC_B416K_H
#define __CE_CODEC_B416K_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup   ce_codec_B416K B416K
 * @{
 *   @brief      Binary 4-byte + CRC-16/Kermit codec for *ce* util
 *   @details    This implementation will use a *rb* to store or retrieve data,
 *               and will compose the data frame as follows:
 *               start_flag
 *   @ingroup    ce_codec
 *   @author     CieNTi <cienti@cienti.com>
 *   @date       2020
 */

/* C libraries */
#include <stdint.h>
#include <stddef.h>

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Byte used as start-flag in an encoded message
 */
#define CE_CODEC_B416K_START_BYTE 0xEA

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Codec initializer function for *B416K* type *ce* codec
 * @details    Binary 4-byte + CRC-16/Kermit codec
 *
 * @param      codec  Pointer to a codec to initialize
 *
 * @return     One of:
 *             | Value  | Meaning          |
 *             | :----: | :--------------- |
 *             | `== 0` | Ok               |
 *             | `!= 0` | Error            |
 */
int ce_codec_B416K(struct ce_codec *codec);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CE_CODEC_B416K_H */
