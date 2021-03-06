/* debug_codec.h - Debug functions to ease `ce_codec` development flow
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
#ifndef __CE_DEBUG_CODEC_H
#define __CE_DEBUG_CODEC_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup debug_functions
 * @{
 */

/* C libraries */
#include "yacup/ce/codec.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Print `ce_codec` information to STDOUT (encode/decode functions)
 *
 * @param      codec  Pointer to a valid `ce_codec`
 */
void ce_codec_print_info(struct ce_codec *codec);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CE_DEBUG_CODEC_H */
