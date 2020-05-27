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
static int s_start(struct fsm *fsm);
static int s_wait_cmd(struct fsm *fsm);
static int s_encode(struct fsm *fsm);
static int s_decode(struct fsm *fsm);
static int s_send(struct fsm *fsm);
static int s_error(struct fsm *fsm);
static int s_stop(struct fsm *fsm);
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
static int s_start(struct fsm *fsm)
{
  /* Configure _dbg() */
  #define YCP_FNAME "s_start"

  if (FSM_DATA(fsm)->ce == NULL)
  {
    /* Set error source flag */
    FSM_DATA(fsm)->error_invalid_ce = 1;

    /* Default next state */
    fsm->next = s_error;
  }
  else
  {
    /* Reset fsm */
    FSM_DATA(fsm)->command = NULL;
    FSM_DATA(fsm)->argument = NULL;
    FSM_DATA(fsm)->request_to_send = 0;
    FSM_DATA(fsm)->message_sent = 0;
    FSM_DATA(fsm)->request_to_receive = 0;
    FSM_DATA(fsm)->message_decoded = 0;
    FSM_DATA(fsm)->error_invalid_ce = 0;

    /* Default next state */
    fsm->next = s_wait_cmd;
  }
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
static int s_wait_cmd(struct fsm *fsm)
{
  /* Configure _dbg() */
  #define YCP_FNAME "s_wait_cmd"

  /* Default next state */
  fsm->next = s_wait_cmd;

  /* Do you want to send? */
  if (FSM_DATA(fsm)->request_to_send == 1)
  {
    FSM_DATA(fsm)->message_sent = 0;
    fsm->next = s_encode;
  }
  /* Or do you want to receive? */
  if (FSM_DATA(fsm)->request_to_receive == 1)
  {
    FSM_DATA(fsm)->message_decoded = 0;
    fsm->next = s_decode;
  }
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
static int s_encode(struct fsm *fsm)
{
  /* Configure _dbg() */
  #define YCP_FNAME "s_encode"

  /* Default next state */
  fsm->next = s_send;

  /* Encode the command */
  if (FSM_DATA(fsm)->ce->out.codec.encode.command(FSM_DATA(fsm)->command,
                                                  FSM_DATA(fsm)->argument,
                                               &(FSM_DATA(fsm)->ce->out.data)))
  {
    fsm->next = s_error;

    _dbg("Cannot encode command\n");
    return 1;
  }

  /* Encoded, so send it now */
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
static int s_decode(struct fsm *fsm)
{
  /* Configure _dbg() */
  #define YCP_FNAME "s_encode"

  /* Default next state */
  fsm->next = s_send;

  /* Encode the command */
  if (FSM_DATA(fsm)->ce->in.codec.decode.command(&(FSM_DATA(fsm)->ce->in.data),
                                             FSM_DATA(fsm)->ce->in.command_set,
                                                 &FSM_DATA(fsm)->command))
  {
    fsm->next = s_error;

    _dbg("Cannot decode command\n");
    return 1;
  }

  /* Decoded, so go back now */
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

/**
 * @brief      Send the message to the outside world
 *
 * @param      fsm   Pointer to a FSM. Use dedicated fsm setup function before
 *
 * @return     One of:
 *             | Value  | Meaning          |
 *             | :----: | :--------------- |
 *             | `== 0` | Ok               |
 *             | `!= 0` | Warning          |
 */
static int s_send(struct fsm *fsm)
{
  /* Configure _dbg() */
  #define YCP_FNAME "s_encode"

  /* Default next state */
  fsm->next = s_stop;

  /* Send the command */
  //
  // Code here to actually send the data, if required
  //
  FSM_DATA(fsm)->message_sent = 1;

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
static int s_error(struct fsm *fsm)
{
  /* Configure _dbg() */
  #define YCP_FNAME "s_error"

  _dbg("ERROR in '%s'. Status flags:\n", fsm->name);
  _dbg("- request_to_send .......: %X\n", FSM_DATA(fsm)->request_to_send);
  _dbg("- message_sent ........  : %X\n", FSM_DATA(fsm)->message_sent);
  _dbg("- request_to_receive ....: %X\n", FSM_DATA(fsm)->request_to_receive);
  _dbg("- message_decoded .......: %X\n", FSM_DATA(fsm)->message_decoded);
  _dbg("- error_invalid_ce ......: %X\n", FSM_DATA(fsm)->error_invalid_ce);

  /* Set next state */
  fsm->next = s_stop;
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
static int s_stop(struct fsm *fsm)
{
  /* Configure _dbg() */
  #define YCP_FNAME "s_stop"

  /* Default next state */
  // 
  // Stop state do not need fsm->next, it's ignored by stepper anyway
  // 

  (void)fsm;
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
    .start = s_start,
    .stop = s_stop
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

  FSM_DATA(&ce->driver.fsm)->message_sent = 0;
  do
  {
    /* Once requests are accepted, put the command and go! */
    if (ce->driver.fsm.next == s_wait_cmd)
    {
      FSM_DATA(&ce->driver.fsm)->command = command;
      FSM_DATA(&ce->driver.fsm)->argument = argument;
      FSM_DATA(&ce->driver.fsm)->request_to_send = 1;
    }
    if (fsm_do_cycle(&ce->driver.fsm))
    {
      _dbg("Error when executing a fsm cycle\n");
      fsm_print_info(&ce->driver.fsm);
      fsm_print_stats(&ce->driver.fsm);
      return 1;
    }
    if ((ce->driver.fsm.now == s_stop) &&
        (ce->driver.fsm.next == s_start))
    {
      if (FSM_DATA(&ce->driver.fsm)->message_sent == 1)
      {
        /* Sent! */
        return 0;
      }
      /* Not sent! */
      _dbg("Cannot send the command\n");
      return 1;
    }

    /* Simulate some time spent on the cycle */
    nanosleep(&(FSM_DATA(&ce->driver.fsm)->fsm_delay), NULL);
  }
  while ((clock_gettime(CLOCK_REALTIME, &time_after) == 0) &&
         ((time_after.tv_sec  < time_to_finish.tv_sec) ||
          ((time_after.tv_sec == time_to_finish.tv_sec) && 
           (time_after.tv_nsec < time_to_finish.tv_nsec))));

  /* Ouch! */
  _dbg("Timeout\n");
  return 1;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* Initialize a *ce_driver_faf* type *ce_driver*.
 * Read `yacup/ce/driver/fire-and-forget.h` for complete information. */
static int wait_command(struct ce *ce,
                        size_t *id,
                        struct ce_command_argument *argument[])
{
  /* Configure _dbg() */
  #define YCP_FNAME "wait_command"

  /* Command is already validated, so we can trust on:
   * - arguments type, checked by ce_command_validate()
   * - arguments type, ensured storage as per ce_command_argument declaration
   */
  _dbg("FAF is waiting commands\n");

  struct ce_command *cmd_to_decode = NULL;
  struct timespec time_to_finish = { 0x00 };
  struct timespec time_after = { 0x00 };

  /* Calculate when the timeout will happen */
  if(clock_gettime(CLOCK_REALTIME, &time_to_finish))
  {
    time_to_finish.tv_sec = 0;
    time_to_finish.tv_nsec = 0;
  }
  time_to_finish.tv_sec  += FSM_DATA(&ce->driver.fsm)->receive_timeout.tv_sec;
  time_to_finish.tv_nsec += FSM_DATA(&ce->driver.fsm)->receive_timeout.tv_nsec;
  time_to_finish.tv_sec += time_to_finish.tv_nsec / 1000000000;
  time_to_finish.tv_nsec = time_to_finish.tv_nsec % 1000000000;

  FSM_DATA(&ce->driver.fsm)->message_decoded = 0;
  do
  {
    if (ce->driver.fsm.next == s_wait_cmd)
    {
      FSM_DATA(&ce->driver.fsm)->command = cmd_to_decode;
      FSM_DATA(&ce->driver.fsm)->argument = argument;
      FSM_DATA(&ce->driver.fsm)->request_to_receive = 1;
    }
    if (fsm_do_cycle(&ce->driver.fsm))
    {
      _dbg("Error when executing a fsm cycle\n");
      fsm_print_info(&ce->driver.fsm);
      fsm_print_stats(&ce->driver.fsm);
      return 1;
    }
    if ((ce->driver.fsm.now == s_stop) &&
        (ce->driver.fsm.next == s_start))
    {
      if (FSM_DATA(&ce->driver.fsm)->message_decoded == 1)
      {
        /* Sent! */
        return 0;
      }
      /* Not sent! */
      _dbg("Cannot decode the command\n");
      return 1;
    }

    /* Simulate some time spent on the cycle */
    nanosleep(&(FSM_DATA(&ce->driver.fsm)->fsm_delay), NULL);
  }
  while ((clock_gettime(CLOCK_REALTIME, &time_after) == 0) &&
         ((time_after.tv_sec  < time_to_finish.tv_sec) ||
          ((time_after.tv_sec == time_to_finish.tv_sec) && 
           (time_after.tv_nsec < time_to_finish.tv_nsec))));

  /* Ouch! */
  _dbg("Timeout\n");
  return 1;

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
  ce->driver.wait_command = wait_command;

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
