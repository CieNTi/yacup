/* debug.c - Debug functions to ease `fsm` development flow
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
#include <stddef.h>
#include <stdio.h>
#include "yacup/fsm.h"
#include "yacup/fsm/driver.h"
#include "yacup/fsm/debug.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define YCP_FORCE_DEBUG
#include "yacup/debug.h"
#undef YCP_NAME
#define YCP_NAME "util/fsm/debug"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* Print `fsm` information to STDOUT.
 * Read `yacup/fsm/debug.h` for complete information. */
void fsm_print_info(struct fsm *fsm)
{
  /* Configure _dbg() */
  #define YCP_FNAME "fsm_print_info"

  if (fsm == NULL) { return; }
  _dbg("name .......: %s\n", fsm->name);
  _dbg("config .....: %u\n", fsm->config);
  _dbg("state ......: %u\n", fsm->state);
  _dbg("driver .....: %p\n", (void *)(size_t)fsm->driver);
  _dbg(" .start ....: %p\n", (void *)(size_t)fsm->driver->start);
  _dbg(" .stop .....: %p\n", (void *)(size_t)fsm->driver->stop);
  _dbg("last .......: %p\n", (void *)(size_t)fsm->last);
  _dbg("now ........: %p\n", (void *)(size_t)fsm->now);
  _dbg("next .......: %p\n", (void *)(size_t)fsm->next);

  /* Free _dbg() config */
  #undef YCP_FNAME
}

/* Print `fsm` stats to STDOUT.
 * Read `yacup/fsm/debug.h` for complete information. */
void fsm_print_stats(struct fsm *fsm)
{
  /* Configure _dbg() */
  #define YCP_FNAME "fsm_print_stats"

  if (fsm == NULL) { return; }
  _dbg("FSM_ALL ...: %lu\n", fsm->stats[FSM_ALL]);
  _dbg("FSM_NEW ...: %lu\n", fsm->stats[FSM_NEW]);
  _dbg("FSM_PAUSE .: %lu\n", fsm->stats[FSM_PAUSE]);
  _dbg("FSM_RUN ...: %lu\n", fsm->stats[FSM_RUN]);
  _dbg("FSM_ERROR .: %lu\n", fsm->stats[FSM_ERROR]);

  /* Free _dbg() config */
  #undef YCP_FNAME
}

#undef YCP_NAME
#undef YCP_FORCE_DEBUG
