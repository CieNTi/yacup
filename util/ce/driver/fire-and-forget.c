/* fire-and-forget.c - A `ce` driver that send/receive data without confirm
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
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include "yacup/rb.h"
#include "yacup/fsm.h"
#include "yacup/fsm/driver.h"
#include "yacup/fsm/debug.h"
#include "yacup/ce.h"
#include "yacup/ce/driver/fire-and-forget.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include "yacup/debug.h"
#undef YCP_NAME
#define YCP_NAME "util/ce/driver/fire-and-forget"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* Ease access from fsm->data */
#define FSM_DATA(x) ((struct ce_driver_faf_data *)((x)->data))

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* States pre-declaration */
/**
 * @addtogroup  ce_driver_faf
 * @{
 *   @name        FSM States
 *   @{
 */
static int start(struct fsm *fsm);
static int state_idle(struct fsm *fsm);
static int state_encode(struct fsm *fsm);
static int state_error(struct fsm *fsm);
static int stop(struct fsm *fsm);
/**  @}
 * @}
 */

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Prepare *extra* variable
 *
 * @param      fsm   Pointer to a FSM. Use dedicated fsm setup function before
 *
 * @return     One of:
 *             | Value  | Meaning          |
 *             | :----: | :--------------- |
 *             | `== 0` | Ok               |
 *             | `!= 0` | Warning          |
 */
static int start(struct fsm *fsm)
{
  /* Configure _dbg() */
  #define YCP_FNAME "start"

  _dbg("%s\n", fsm->name);

  if (FSM_DATA(fsm)->ce == NULL)
  {
    /* Set error source flag */
    FSM_DATA(fsm)->error_invalid_ce = 1;

    /* Default next state */
    fsm->next = state_error;
  }
  else
  {
    /* Reset fsm */
    FSM_DATA(fsm)->command = NULL;
    FSM_DATA(fsm)->argument = NULL;
    FSM_DATA(fsm)->request_to_send = 0;
    FSM_DATA(fsm)->data_ready_to_send = 0;
    FSM_DATA(fsm)->message_sent = 0;
    FSM_DATA(fsm)->request_to_receive = 0;
    FSM_DATA(fsm)->data_ready_to_decode = 0;
    FSM_DATA(fsm)->message_decoded = 0;
    FSM_DATA(fsm)->error_invalid_ce = 0;

    /* Default next state */
    fsm->next = state_idle;
  }

  _dbg("Exit '%s' %s\n", YCP_FNAME, (fsm->next == state_error)?"FAIL":"OK");
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

/**
 * @brief      Stay here during 5 counts of *extra* variable
 *
 * @param      fsm   Pointer to a FSM. Use dedicated fsm setup function before
 *
 * @return     One of:
 *             | Value  | Meaning          |
 *             | :----: | :--------------- |
 *             | `== 0` | Ok               |
 *             | `!= 0` | Warning          |
 */
static int state_idle(struct fsm *fsm)
{
  /* Configure _dbg() */
  #define YCP_FNAME "state_idle"

  _dbg("%s\n", fsm->name);

  /* Default next state */
  fsm->next = state_idle;

  /* This state will be executed 5 times */
  if (FSM_DATA(fsm)->request_to_send == 1)
  {
    fsm->next = state_encode;
  }

  _dbg("Exit '%s' %s\n", YCP_FNAME, (fsm->next == state_error)?"FAIL":"OK");
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

/**
 * @brief      Encode command + data as a message
 *
 * @param      fsm   Pointer to a FSM. Use dedicated fsm setup function before
 *
 * @return     One of:
 *             | Value  | Meaning          |
 *             | :----: | :--------------- |
 *             | `== 0` | Ok               |
 *             | `!= 0` | Warning          |
 */
static int state_encode(struct fsm *fsm)
{
  /* Configure _dbg() */
  #define YCP_FNAME "state_encode"

  _dbg("%s\n", fsm->name);

  /* Default next state */
  fsm->next = stop;

  /* Encode the command */
  _dbg("Should encode a command using '%s' command codec\n",
       FSM_DATA(fsm)->ce->out.codec.name);
  if (FSM_DATA(fsm)->ce->out.codec.encode.command(FSM_DATA(fsm)->command,
                                                  FSM_DATA(fsm)->argument,
                                               &(FSM_DATA(fsm)->ce->out.data)))
  {
    _dbg("Cannot encode command\n");
    return 1;
  }
  _dbg("Ok\n");

  _dbg("Exit '%s' %s\n", YCP_FNAME, (fsm->next == state_error)?"FAIL":"OK");
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

/**
 * @brief      Some error happened. Wops!
 *
 * @param      fsm   Pointer to a FSM. Use dedicated fsm setup function before
 *
 * @return     One of:
 *             | Value  | Meaning          |
 *             | :----: | :--------------- |
 *             | `== 0` | Ok               |
 *             | `!= 0` | Warning          |
 */
static int state_error(struct fsm *fsm)
{
  /* Configure _dbg() */
  #define YCP_FNAME "state_idle"

  _dbg("ERROR in '%s'. Status flags:\n", fsm->name);
  _dbg("- request_to_send .......: %X\n", FSM_DATA(fsm)->request_to_send);
  _dbg("- data_ready_to_send ....: %X\n", FSM_DATA(fsm)->data_ready_to_send);
  _dbg("- message_sent ........  : %X\n", FSM_DATA(fsm)->message_sent);
  _dbg("- request_to_receive ....: %X\n", FSM_DATA(fsm)->request_to_receive);
  _dbg("- data_ready_to_decode ..: %X\n", FSM_DATA(fsm)->data_ready_to_decode);
  _dbg("- message_decoded .......: %X\n", FSM_DATA(fsm)->message_decoded);
  _dbg("- error_invalid_ce ......: %X\n", FSM_DATA(fsm)->error_invalid_ce);

  /* Default next state */
  fsm->next = stop;
  _dbg("Exit '%s' %s\n", YCP_FNAME, (fsm->next == state_error)?"FAIL":"OK");
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

/**
 * @brief      Prepare anything before stopping the fsm
 *
 * @param      fsm   Pointer to a FSM. Use dedicated fsm setup function before
 *
 * @return     One of:
 *             | Value  | Meaning          |
 *             | :----: | :--------------- |
 *             | `== 0` | Ok               |
 *             | `!= 0` | Warning          |
 */
static int stop(struct fsm *fsm)
{
  /* Configure _dbg() */
  #define YCP_FNAME "stop"

  _dbg("%s\n", fsm->name);

  /* Default next state */
  /* stop state do not need fsm->next, it's ignored by stepper anyway */

  (void)fsm;
  _dbg("Exit '%s' %s\n", YCP_FNAME, (fsm->next == state_error)?"FAIL":"OK");
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* Internal ce_driver fsm initializer (fsm_init() compliant) */
static int ce_driver_fsm_driver(struct fsm *fsm)
{
  /* Configure _dbg() */
  #define YCP_FNAME "ce_driver_fsm_driver"

  /* Create it static, as this will not change along the execution */
  static struct fsm_driver this_driver =
  {
    .start = start,
    .stop = stop
  };

  /* Valid fsm? */
  if (fsm == NULL)
  {
    _dbg("Direct calls are not recommended, read the doc\n");
    return 1;
  }

  /* Assign default name, if not previously set */
  if (fsm->name == NULL)
  {
    fsm->name = YCP_NAME;
  }

  /* Assign the essential states */
  fsm->driver = &this_driver;

  /* Let's go! */
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* Initialize a *ce_driver_faf* type *ce_driver*.
 * Read `yacup/ce/driver/fire-and-forget.h` for complete information. */
static int send_command(struct ce *ce,
                        struct ce_command *command,
                        struct ce_command_argument *argument[])
{
  /* Configure _dbg() */
  #define YCP_FNAME "send_command"

  /* Command is already validated, so we can trust on:
   * - arguments type, checked by ce_command_validate()
   * - arguments type, ensured storage as per ce_command_argument declaration
   */
  _dbg("FAF is sending command '%s' (0x%02lX)\n", command->name, command->id);

  struct timespec time_to_finish = { 0x00 };
  struct timespec time_after = { 0x00 };

  /* Calculate when the timeout will happen */
  if(clock_gettime(CLOCK_REALTIME, &time_to_finish))
  {
    time_to_finish.tv_sec = 0;
    time_to_finish.tv_nsec = 0;
  }
  time_to_finish.tv_sec  += FSM_DATA(&ce->driver.fsm)->send_timeout.tv_sec;
  time_to_finish.tv_nsec += FSM_DATA(&ce->driver.fsm)->send_timeout.tv_nsec;
  time_to_finish.tv_sec += time_to_finish.tv_nsec / 1000000000;
  time_to_finish.tv_nsec = time_to_finish.tv_nsec % 1000000000;

  do
  {
    /* Test the fsm */
    if (fsm_do_cycle(&ce->driver.fsm))
    {
      _dbg("Error when executing a fsm cycle\n");
      fsm_print_info(&ce->driver.fsm);
      fsm_print_stats(&ce->driver.fsm);
      return 1;
    }

    /* Simulate some time spent on the cycle */
    nanosleep(&(FSM_DATA(&ce->driver.fsm)->fsm_delay), NULL);
  }
  while ((clock_gettime(CLOCK_REALTIME, &time_after) == 0) &&
         ((time_after.tv_sec  < time_to_finish.tv_sec) ||
          ((time_after.tv_sec == time_to_finish.tv_sec) && 
           (time_after.tv_nsec < time_to_finish.tv_nsec))));

  /* Let's go! */
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* Initialize a command engine
 * Read `yacup/ce/driver/fire-and-forget.h` for complete information. */
int ce_driver_faf(struct ce *ce)
{
  /* Configure _dbg() */
  #define YCP_FNAME "ce_driver_faf"

  if (/* Valid engine? */
      ce == NULL ||
      /* Valid required fsm data */
      ce->driver.fsm.data == NULL)
  {
    _dbg("Invalid command engine or required data\n");
    return 1;
  }

  /* Assign fsm external variables */
  FSM_DATA(&ce->driver.fsm)->ce = ce;

  /* Set cycle delay if not */
  if ((FSM_DATA(&ce->driver.fsm)->fsm_delay.tv_sec == 0) &&
      (FSM_DATA(&ce->driver.fsm)->fsm_delay.tv_nsec == 0))
  {
    FSM_DATA(&ce->driver.fsm)->fsm_delay.tv_sec =
                                 (CE_DRIVER_FAF_FSM_DELAY_MS / 1000);
    FSM_DATA(&ce->driver.fsm)->fsm_delay.tv_nsec =
                                 (CE_DRIVER_FAF_FSM_DELAY_MS % 1000) * 1000000;
  }

  /* Set cycle delay if not */
  if ((FSM_DATA(&ce->driver.fsm)->send_timeout.tv_sec == 0) &&
      (FSM_DATA(&ce->driver.fsm)->send_timeout.tv_nsec == 0))
  {
    FSM_DATA(&ce->driver.fsm)->send_timeout.tv_sec =
                              (CE_DRIVER_FAF_SEND_TIMEOUT_MS / 1000);
    FSM_DATA(&ce->driver.fsm)->send_timeout.tv_nsec =
                              (CE_DRIVER_FAF_SEND_TIMEOUT_MS % 1000) * 1000000;
  }

  /* Set cycle delay if not */
  if ((FSM_DATA(&ce->driver.fsm)->receive_timeout.tv_sec == 0) &&
      (FSM_DATA(&ce->driver.fsm)->receive_timeout.tv_nsec == 0))
  {
    FSM_DATA(&ce->driver.fsm)->receive_timeout.tv_sec =
                           (CE_DRIVER_FAF_RECEIVE_TIMEOUT_MS / 1000);
    FSM_DATA(&ce->driver.fsm)->receive_timeout.tv_nsec =
                           (CE_DRIVER_FAF_RECEIVE_TIMEOUT_MS % 1000) * 1000000;
  }

  /* Once configured/fixed, initialize this driver fsm */
  if (fsm_init(&ce->driver.fsm, ce_driver_fsm_driver))
  {
    _dbg("Cannot initialize this command engine\n");
    return 1;
  }

  /* Assign default name, if not previously set */
  if (ce->name == NULL)
  {
    ce->name = "YCP_NAME";
  }

  /* Assign the external driver-fsm API */
  ce->driver.send_command = send_command;

  /* Basics: enable + auto-restart + start as soon as possible */
  fsm_enable(&ce->driver.fsm);
  fsm_set_loop(&ce->driver.fsm);
  fsm_request_start(&ce->driver.fsm);

  /* fsm cycles */
  fsm_print_info(&ce->driver.fsm);

  /* Let's go! */
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

#undef FSM_DATA
#undef YCP_NAME
