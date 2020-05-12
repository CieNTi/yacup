/* fsm_simple.c - A simple finite state machine for testing purposes
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
#include "yacup/fsm.h"

/* Header located near this file, used as an external header in app */
#include "fsm_simple.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#undef YCP_NAME
#define YCP_NAME "util/fsm/test/fsm_simple"
#ifdef YACUP_DEBUG
  #include <time.h>
  #include <stdio.h>
  #include <string.h>
  #ifndef _dbg
    #define _dbg(...) printf(YCP_NAME" | "__VA_ARGS__)
  #endif
#else
  #ifndef _dbg
    #define _dbg(...)
  #endif
#endif

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* Ease access from fsm->data */
#define FSM_DATA(x) ((struct fsm_simple_data *)(x->data))

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* States pre-declaration */
static int start(struct fsm *fsm);
static int state_1(struct fsm *fsm);
static int stop(struct fsm *fsm);

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Sate `start`: Prepare `cycles` variable
 *
 * @param      fsm   Pointer to a FSM. Use dedicated fsm setup function before
 * @ingroup    fsm_simple
 *
 * @return     One of:
 *             | Value  | Meaning          |
 *             | :----: | :--------------- |
 *             | `== 0` | Ok               |
 *             | `!= 0` | Warning          |
 */
static int start(struct fsm *fsm)
{
  _dbg("start: %s\n", fsm->name);

  /* Default next state */
  fsm->next = state_1;

  /* reset counter */
  FSM_DATA(fsm)->cycles = 0;

  return 0;
}

/**
 * @brief      State `state_1`: Stay here during 5 `cycles` variable counts
 *
 * @param      fsm   Pointer to a FSM. Use dedicated fsm setup function before
 * @ingroup    fsm_simple
 *
 * @return     One of:
 *             | Value  | Meaning          |
 *             | :----: | :--------------- |
 *             | `== 0` | Ok               |
 *             | `!= 0` | Warning          |
 */
static int state_1(struct fsm *fsm)
{
  _dbg("state_1: %s\n", fsm->name);

  /* Default next state */
  fsm->next = state_1;

  /* This state will be executed 5 times */
  if (FSM_DATA(fsm)->cycles++ < 4)
  {
    printf(YCP_NAME" | state_1: Entering cycle #%lu\n", FSM_DATA(fsm)->cycles);
  }
  else
  {
    printf(YCP_NAME" | state_1: Stop at cycle #%lu\n", FSM_DATA(fsm)->cycles);
    fsm->next = stop;
  }
  return 0;
}

/**
 * @brief      State `stop`: Prepare anything before stopping the fsm
 *
 * @param      fsm   Pointer to a FSM. Use dedicated fsm setup function before
 * @ingroup    fsm_simple
 *
 * @return     One of:
 *             | Value  | Meaning          |
 *             | :----: | :--------------- |
 *             | `== 0` | Ok               |
 *             | `!= 0` | Warning          |
 */
static int stop(struct fsm *fsm)
{
  _dbg("stop: %s\n", fsm->name);

  /* Default next state */
  /* stop state do not need fsm->next, it's ignored by stepper anyway */

  (void)fsm;
  return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* Initialize a `fsm_simple` type FSM.
 * Read `yacup/fsm/debug.h` for complete information. */
int fsm_simple_setup(struct fsm *fsm)
{
  /* It was possible to allocate it? */
  if (fsm == NULL)
  {
    _dbg("fsm_simple_create: Invalid fsm\n");
    return 1;
  }

  /* It was possible to allocate it? */
  if (fsm->data == NULL)
  {
    _dbg("fsm_simple_create: Invalid fsm data (fsm = %s)\n", fsm->name);
    return 1;
  }

  /* Fill the data */
  FSM_DATA(fsm)->cycles = 0;

  /* Fill the fsm */
  fsm->config = 0;
  fsm->state = FSM_NEW;
  fsm->stats[FSM_NEW] = 0;
  fsm->stats[FSM_PAUSE] = 0;
  fsm->stats[FSM_RUN] = 0;
  fsm->stats[FSM_ERROR] = 0;
  fsm->stats[FSM_ALL] = 0;
  fsm->start = start;
  fsm->stop = stop;

  /* Let's go! */
  return 0;
}

#undef FSM_DATA
#undef YCP_NAME
