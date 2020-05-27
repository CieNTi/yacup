/* fire-and-forget.h - A *ce* chat that send/receive data without confirmation
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
 * @defgroup   ce_driver_faf Fire and Forget
 * @{
 *   @brief      A *ce* chat that send/receive data without confirmation
 *   @todo       Write a description/\@details
 *   @ingroup    ce_driver
 *   @author     CieNTi <cienti@cienti.com>
 *   @date       2020
 */

/* C libraries */
#include <stddef.h>
#include <time.h>
#include "yacup/ce.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define CE_DRIVER_FAF_FSM_DELAY_MS 50
#define CE_DRIVER_FAF_SEND_TIMEOUT_MS 1000
#define CE_DRIVER_FAF_RECEIVE_TIMEOUT_MS 1000

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Internal data *ce_driver_faf* will use
 * @todo       If some variable is common to all drivers, migrate it to the
 *             *struct ce_driver*, at the same level as *ce*. Otherwise, it is
 *             just this driver (fsm) dependant.
 */
struct ce_driver_faf_data
{
  /**
   * @brief      Pointer to the *ce* this driver will manage
   */
  struct ce *ce;

  /* Inter-state command links */
  struct ce_command *command;
  struct ce_command_argument **argument;

  /* Timming configurations */
  struct timespec fsm_delay;
  struct timespec send_timeout;
  struct timespec receive_timeout;

  /* Status flags */
  uint8_t request_to_send;
  uint8_t message_sent;

  uint8_t request_to_receive;
  uint8_t message_decoded;

  uint8_t error_invalid_ce;
};

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Driver initializer function for *ce_driver_faf* type CE
 * @details    This chat FSM will control input and output operations on a fire
 *             and forget type protocol, where the data is sent without any
 *             confirmation expectation or timeout, and when data is received
 *             there is no feedback to the remitent. It is the easiest form of
 *             protocol, where everything is supposed to be perfect, with no
 *             communication errors
 *
 * @param      ce    Pointer to a *ce* to work with
 *
 * @return     One of:
 *             | Value  | Meaning          |
 *             | :----: | :--------------- |
 *             | `== 0` | Ok               |
 *             | `!= 0` | Error            |
 */
int ce_driver_faf(struct ce *ce);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CE_CHAT_FIRE_AND_FORGET_H */
