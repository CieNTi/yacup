/* driver.h - Finite state machine operations driver for yacup project
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
#ifndef __FSM_DRIVER_H
#define __FSM_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup fsm_api
 * @{
 */

/* C libraries */
#include <stdint.h>
#include <stddef.h>

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* Pre-declare fsm struct */
struct fsm;

/**
 * @brief      Structure that defines valid operations on ring buffers
 */
struct fsm_driver
{
  /**
   * @brief      State function executed to start the FSM
   */
  int (*start)(struct fsm *fsm);

  /**
   * @brief      State function executed at fsm stop, before pause or restart
   */
  int (*stop) (struct fsm *fsm);
};

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __FSM_DRIVER_H */
