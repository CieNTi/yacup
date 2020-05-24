/* fire-and-forget.c - A `ce` chat that send/receive data without confirmation
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
#include "yacup/rb.h"
#include "yacup/fsm.h"
#include "yacup/fsm/driver.h"
#include "yacup/ce.h"
#include "yacup/ce/chat/fire-and-forget.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include "yacup/debug.h"
#undef YCP_NAME
#define YCP_NAME "util/ce/chat/fire-and-forget"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* States pre-declaration */
static int start(struct fsm *fsm);
static int state_1(struct fsm *fsm);
static int stop(struct fsm *fsm);

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Sate `start`: Prepare `extra` variable
 *
 * @param      fsm   Pointer to a FSM. Use dedicated fsm setup function before
 * @ingroup    ce_chat_faf
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

  /* Default next state */
  fsm->next = state_1;

  /* reset counter */
  //FSM_DATA(fsm)->extra = 0;

  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

/**
 * @brief      State `state_1`: Stay here during 5 `extra` variable counts
 *
 * @param      fsm   Pointer to a FSM. Use dedicated fsm setup function before
 * @ingroup    ce_chat_faf
 *
 * @return     One of:
 *             | Value  | Meaning          |
 *             | :----: | :--------------- |
 *             | `== 0` | Ok               |
 *             | `!= 0` | Warning          |
 */
static int state_1(struct fsm *fsm)
{
  /* Configure _dbg() */
  #define YCP_FNAME "state_1"

  _dbg("%s\n", fsm->name);

  /* Default next state */
  fsm->next = state_1;

//  /* This state will be executed 5 times */
//  if (FSM_DATA(fsm)->extra++ < 4)
//  {
//    printf(YCP_NAME" | state_1: Entering cycle #%lu\n", FSM_DATA(fsm)->extra);
//  }
//  else
//  {
//    printf(YCP_NAME" | state_1: Stop at cycle #%lu\n", FSM_DATA(fsm)->extra);
//    fsm->next = stop;
//  }
  fsm->next = stop;
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

/**
 * @brief      State `stop`: Prepare anything before stopping the fsm
 *
 * @param      fsm   Pointer to a FSM. Use dedicated fsm setup function before
 * @ingroup    ce_chat_faf
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
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

/**
 * @brief      Internal ce_chat fsm initializer (fsm_init() compliant)
 *
 * @param      fsm   Pointer to a `fsm` to work with
 *
 * @return     One of:
 *             | Value  | Meaning          |
 *             | :----: | :--------------- |
 *             | `== 0` | Ok               |
 *             | `!= 0` | Error            |
 */
static int ce_chat_fsm_driver(struct fsm *fsm)
{
  /* Configure _dbg() */
  #define YCP_FNAME "ce_chat_fsm_driver"

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

  /* Assign the essential states */
  fsm->driver = &this_driver;

  /* Let's go! */
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* Initialize a `ce_chat_faf` type `ce_chat`.
 * Read `yacup/ce/chat/fire-and-forget.h` for complete information. */
static int command_send(struct ce *ce,
                        size_t id,
                        struct ce_command_argument *argument[])
{
  /* Configure _dbg() */
  #define YCP_FNAME "command_send"

  /* Let's go! */
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* Initialize a command engine
 * Read `yacup/ce/chat/fire-and-forget.h` for complete information. */
int ce_driver_faf(struct ce *ce)
{
  /* Configure _dbg() */
  #define YCP_FNAME "ce_chat_faf"

  if (/* Valid engine? */
      ce == NULL ||
      /* Valid chat? */
      &ce->chat == NULL ||
      /* Initialize chat fsm */
      fsm_init(&ce->chat.fsm, ce_chat_fsm_driver))
  {
    _dbg("Cannot initialize this chat\n");
    return 1;
  }

  /* Assign the external chat-fsm API */
  ce->chat.command_send = command_send;

  /* Let's go! */
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

#undef FSM_DATA
#undef YCP_NAME
