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
#include <stdlib.h>
#include <yacup/fsm.h>

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
/*                              ~~~~~~~~~~~~~~~~                              *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Private fsm data ]~~~~~~~~~~~~~~~~~~~~~~~~~~~ *
 *                              ~~~~~~~~~~~~~~~~                              */
struct data
{
  uint32_t cycles;
};

/* Ease access from fsm->data */
#define FSM_DATA(x) ((struct data *)(x->data))


/*                                   ~~~~~~                                   *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ States ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ *
 *                                   ~~~~~~                                   */
static uint32_t start(struct fsm *fsm);
static uint32_t state_1(struct fsm *fsm);
static uint32_t stop(struct fsm *fsm);

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ START ]~ */
static uint32_t start(struct fsm *fsm)
{
  _dbg(__func__"@%s\n", fsm->name);

  /* Default next state */
  fsm->next = state_1;

  /* reset counter */
  FSM_DATA(fsm)->cycles = 0;

  return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ STATE_1 ]~ */
static uint32_t state_1(struct fsm *fsm)
{
  _dbg(__func__"@%s\n", fsm->name);

  /* Default next state */
  fsm->next = state_1;

  /* This state will be executed 5 times */
  if (FSM_DATA(fsm)->cycles++ < 4)
  {
    _dbg(">>\n>> Entering at cycle #%u\n>>\n", FSM_DATA(fsm)->cycles);
  }
  else
  {
    _dbg(">>\n>> Stopping at cycle #%u\n>>\n", FSM_DATA(fsm)->cycles);
    fsm->next = stop;
  }
  return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ STOP ]~ */
static uint32_t stop(struct fsm *fsm)
{
  _dbg(__func__"@%s\n", fsm->name);

  /* Default next state */
  /* stop state do not need fsm->next, it's ignored by stepper anyway */

  (void)fsm;
  return 0;
}


/*                     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~                    *
 * ~~~~~~~~~~~~~~~~~~[ fsm constructor for external access ]~~~~~~~~~~~~~~~~~ *
 *                     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~                    */
/* Create and initialize a `fsm_simple` type FSM.
 * Read `yacup/fsm/debug.h` for complete information. */
struct fsm *fsm_simple_create(char *name)
{
  /* Allocate fsm storage */
  struct fsm *fsm = malloc(sizeof(struct fsm));

  /* It was possible to allocate it? */
  if (fsm == NULL)
  {
    _dbg(__func__": Impossible to malloc() a fsm\n");
    return NULL;
  }
  _dbg(__func__": Ok to malloc() a fsm\n");

  struct data *data = malloc(sizeof(struct data));

  /* It was possible to allocate it? */
  if (data == NULL)
  {
    _dbg(__func__": Impossible to malloc() data\n");
    return NULL;
  }
  _dbg(__func__": Ok to malloc() data\n");

  /* Fill the data */
  data->cycles = 0;

  /* Fill the fsm */
  fsm->name = (uint8_t *)name;
  fsm->config = 0;
  fsm->state = FSM_NEW;
  fsm->stats[FSM_NEW] = 0;
  fsm->stats[FSM_PAUSE] = 0;
  fsm->stats[FSM_RUN] = 0;
  fsm->stats[FSM_ERROR] = 0;
  fsm->stats[FSM_ALL] = 0;
  fsm->data = &data;
  fsm->start = start;
  fsm->stop = stop;

  /* Let's go! */
  return fsm;
}

#undef YCP_NAME
