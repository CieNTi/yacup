/* chat.h - Command engine chat state machine API for `ce` util usage
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
#ifndef __CE_CHAT_H
#define __CE_CHAT_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup   ce_chat I/O Chats (Communication protocol)
 * @{
 *   @brief      NEED DETAILS
 *   @details    NEED DETAILS
 *   @author     CieNTi <cienti@cienti.com>
 *   @date       2020
 *   @ingroup    ce
 * @}
 * 
 * @addtogroup ce_chat
 * @{
 */

/* C libraries */
#include <stdint.h>
#include <stddef.h>
#include "yacup/rb.h"
#include "yacup/ce/codec.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Structure that defines the input/output chat between parties
 *             (communication protocol)
 */
struct ce_chat
{
  /**
   * @brief      Finite state machine controlling data/actions behaviour
   */
  struct fsm fsm;

  /**
   * @brief      Finite state machine controlling data/actions behaviour
   */
  int (*command_send)(int);
};

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Initializes a command engine channel using lower level inits
 * @details    Prepares and initializes the channel: command set, codec and
 *             codec message buffer
 *
 * @param      channel                     Poiner to channel to initialize
 * @param      command_set                 Valid command set for this channel
 * @param      channels_codec_driver_init  Channel codec driver initializer
 * @param      channels_rb_driver_init     Message rb driver initializer
 *
 * @return     One of:
 *             | Value  | Meaning          |
 *             | :----: | :--------------- |
 *             | `== 0` | Ok               |
 *             | `!= 0` | Error            |
 */
int ce_chat_init(struct ce_chat *channel,
                 int (*channels_codec_driver_init)(struct ce_codec *),
                 int (*channels_rb_driver_init)(struct rb *));

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CE_CHAT_H */
