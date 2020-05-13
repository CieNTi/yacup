/* fsm.h - Finite state machine implementation for yacup project
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
#ifndef __FSM_H
#define __FSM_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup fsm Finite state machines
 * @{
 *   @brief      Yet another finite-state machine implementation
 *   @details    FSM made easy (for me xD)
 *   @author     CieNTi <cienti@cienti.com>
 *   @date       2020
 *
 *   @defgroup   fsm_api Interface
 *   @{
 *     @brief      Operations over `fsm` instances
 *     @details    Centralized functions to allow different FSM coexistence
 *     @author     CieNTi <cienti@cienti.com>
 *     @date       2020
 *   @}
 *
 *   @defgroup   fsm_available Available FSM
 *   @{
 *     @brief      Already made and tested FSM for different purposes
 *     @details    Each FSM found here can be instantiated by calling its
 *                 constructor function. It can be duplicated and/or combinated,
 *                 as all required storage is dinamically allocated and cannot
 *                 ends in any kind of clash.
 *     @author     CieNTi <cienti@cienti.com>
 *     @date       2020
 *   @}
 * @}
 * 
 * @ingroup   fsm_api
 * @{
 */

/* C libraries */
#include <stdint.h>
#include <stddef.h>

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Valid states that a finite state machine can be in
 */
enum fsm_state
{
  /**
   * @brief      single-pass state only, just for initialization and checks
   */
  FSM_NEW   = 0,
  
  /**
   * @brief      'Nothing to do' state. FSM possibly ended and no rearm bit was
   *             found
   */
  FSM_PAUSE = 1,
  
  /**
   * @brief      FSM core, where the magic happens
   */
  FSM_RUN   = 2,
  
  /**
   * @brief      You're in a little trouble if you are here
   */
  FSM_ERROR = 3,
  
  /**
   * @brief      Not a real state, just for stats as a cycle counter
   */
  FSM_ALL   = 4
};

/**
 * @brief      Structure that defines a finite state machine
 */
struct fsm
{
  /**
   * @brief      Name of the finite state machine, useful to track many of them
   */
  char *name;

  /**
   * @brief      Saves finite state machine configuration (enabled, auto, ...)
   */
  uint8_t config;

  /**
   * @brief      Current state of the FSM
   */
  enum fsm_state state;

  /**
   * @brief      Hold each state stats as a count of passed cycles for each one
   */
  size_t stats[5];

  /**
   * @brief      Internal data as a pointer to void, managed by the FSM itself
   */
  void *data;

  /**
   * @brief      State function executed to start the FSM
   * @warning    It is mandatory, otherwise the FSM will fail miserably
   */
  int (*start)(struct fsm *fsm);

  /**
   * @brief      State function executed to stop, before pause or restart
   */
  int (*stop) (struct fsm *fsm);

  /**
   * @brief      Saves previously executed state
   */
  int (*last) (struct fsm *fsm);

  /**
   * @brief      Current FSM state, in execution
   */
  int (*now)  (struct fsm *fsm);

  /**
   * @brief      Next state to be executed
   */
  int (*next) (struct fsm *fsm);
};

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Initializes a `fsm`
 * @details    Checks and initializes `fsm` common data, then calls the lower
 *             level init function passed by argument. The latter is defined at
 *             each `fsm` unit, and it is where the `start` and `stop` states
 *             are really assigned.
 *
 * @param      fsm   Pointer to a correctly initialized FSM
 *
 * @return     One of:
 *             | Value  | Meaning          |
 *             | :----: | :--------------- |
 *             | `== 0` | Ok               |
 *             | `!= 0` | Error            |
 */
int fsm_init(struct fsm *fsm, int (*fsm_low_level_init)(struct fsm *));

/**
 * @brief      Sets the enable bit, allowing this `fsm` to perform actions
 *
 * @param      fsm   Pointer to a FSM to initialize
 */
void fsm_enable(struct fsm *fsm);

/**
 * @brief      Unsets the enable bit, disallowing this `fsm` to perform further
 *             actions
 *
 * @param      fsm   Pointer to a correctly initialized FSM
 */
void fsm_disable(struct fsm *fsm);

/**
 * @brief      Unsets the auto-restart bit, making this `fsm` to stop once
 *             completed
 *
 * @param      fsm   Pointer to a correctly initialized FSM
 */
void fsm_set_single(struct fsm *fsm);

/**
 * @brief      Sets the auto-restart bit, making this `fsm` to start again once
 *             completed
 *
 * @param      fsm   Pointer to a correctly initialized FSM
 */
void fsm_set_loop(struct fsm *fsm);

/**
 * @brief      Sets the started bit, making this `fsm` to start the next valid
 *             cycle
 *
 * @param      fsm   Pointer to a correctly initialized FSM
 */
void fsm_request_start(struct fsm *fsm);

/**
 * @brief      Unsets the started bit, making this `fsm` to stop the next valid
 *             cycle
 *
 * @param      fsm   Pointer to a correctly initialized FSM
 */
void fsm_request_stop(struct fsm *fsm);

/**
 * @brief      Stepper function (single cycle and exit, need outside controller
 *             loop)
 *
 * @param      fsm   Pointer to a correctly initialized FSM
 *
 * @return     One of:
 *             | Value  | Meaning          |
 *             | :----: | :--------------- |
 *             | `== 0` | Ok               |
 *             | `!= 0` | Error            |
 */
int fsm_do_cycle(struct fsm *fsm);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __FSM_H */
