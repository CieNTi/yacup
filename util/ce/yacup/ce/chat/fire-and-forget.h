/* fire-and-forget.h - A `ce` chat that send/receive data without confirmation
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
#ifndef __CE_CHAT_FIRE_AND_FORGET_H
#define __CE_CHAT_FIRE_AND_FORGET_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup   ce_chat_faf Fire and Forget
 * @{
 *   @brief      A `ce` chat that send/receive data without confirmation
 *   @details    **TODO**
 *   @ingroup    ce_chat_available
 *   @author     CieNTi <cienti@cienti.com>
 *   @date       2020
 */

/* C libraries */
#include <stddef.h>
#include "yacup/rb.h"
#include "yacup/fsm.h"
#include "yacup/ce.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Internal data ce_chat_faf will use
 */
struct ce_chat_faf_data
{
  /**
   * @brief      An extra variable
   */
  size_t extra;

  /**
   * @brief      Pointer to the `ce` this chat will manage
   */
  struct ce *ce;
};

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Low-level initializer function for `ce_chat_faf` type chat FSM
 * @details    This chat FSM will control input and output operations on a fire
 *             and forget type protocol, where the data is sent without any
 *             confirmation expectation or timeout, and when data is received
 *             there is no feedback to the remitent. It is the easiest form of
 *             protocol, where everything is supposed to be perfect, with no
 *             communication errors
 *
 * @param      fsm   Pointer to a `fsm` to work with
 *
 * @return     One of:
 *             | Value  | Meaning          |
 *             | :----: | :--------------- |
 *             | `== 0` | Ok               |
 *             | `!= 0` | Error            |
 */
int ce_chat_faf(struct fsm *fsm);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CE_CHAT_FIRE_AND_FORGET_H */
