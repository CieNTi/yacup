/* driver.h - Command engine driver API for `ce` util usage
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
#ifndef __CE_DRIVER_H
#define __CE_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup   ce_api
 * @{
 */

/* C libraries */
#include <stdint.h>
#include <stddef.h>
#include "yacup/rb.h"
#include "yacup/ce.h"
#include "yacup/ce/codec.h"
#include "yacup/ce/command.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* Pre-declare fsm struct */
struct ce;

/**
 * @brief      Structure that defines the input/output chat between parties
 *             (communication protocol)
 */
struct ce_driver
{
  /**
   * @brief      Finite state machine controlling data/actions behaviour
   */
  struct fsm fsm;

  /**
   * @brief      Finite state machine controlling data/actions behaviour
   */
  int (*send_command)(struct ce *,
                      struct ce_command *,
                      struct ce_command_argument *[]);
};

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CE_DRIVER_H */
