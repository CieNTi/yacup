/* binary.h - Binary command codec for `ce` util
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
#ifndef __CE_COMMAND_CODEC_BINARY_H
#define __CE_COMMAND_CODEC_BINARY_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup   ce_command_codec_binary Binary
 * @{
 *   @brief      Binary command encoding
 *   @todo       Write a description/\@details
 *   @ingroup    ce_command_codec
 *   @author     CieNTi <cienti@cienti.com>
 *   @date       2020
 */

/* C libraries */
#include <stdint.h>
#include <stddef.h>

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Codec initializer function for `binary` type `ce_command` codec
 *
 * @param      codec  Pointer to a codec to initialize
 *
 * @return     One of:
 *             | Value  | Meaning          |
 *             | :----: | :--------------- |
 *             | `== 0` | Ok               |
 *             | `!= 0` | Error            |
 */
int ce_command_codec_binary(struct ce_command_codec *codec);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CE_COMMAND_CODEC_BINARY_H */
