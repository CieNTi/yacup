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
#include <yacup/fsm.h>
#include <yacup/fsm/debug.h>

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#undef YCP_NAME
#define YCP_NAME "util/fsm/debug"
#include <time.h>
#include <stdio.h>
#include <string.h>
#ifndef _dbg
  #define _dbg(...) printf(YCP_NAME" | "__VA_ARGS__)
#endif

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* Print `fsm` information to STDOUT.
 * Read `yacup/fsm/debug.h` for complete information. */
void fsm_print_info(struct fsm *fsm)
{
  if (fsm == NULL) { return; }
  _dbg("fsm_print_info: name .......: %s\n", fsm->name);
  _dbg("fsm_print_info: config .....: %u\n", fsm->config);
  _dbg("fsm_print_info: state ......: %u\n", fsm->state);
  _dbg("fsm_print_info: start ......: %p\n", (void *)(size_t)fsm->start);
  _dbg("fsm_print_info: stop .......: %p\n", (void *)(size_t)fsm->stop);
  _dbg("fsm_print_info: last .......: %p\n", (void *)(size_t)fsm->last);
  _dbg("fsm_print_info: now ........: %p\n", (void *)(size_t)fsm->now);
  _dbg("fsm_print_info: next .......: %p\n", (void *)(size_t)fsm->next);
  fflush(stdout);
}

/* Print `fsm` stats to STDOUT.
 * Read `yacup/fsm/debug.h` for complete information. */
void fsm_print_stats(struct fsm *fsm)
{
  if (fsm == NULL) { return; }
  _dbg("fsm_print_stats: FSM_ALL ...: %lu\n", fsm->stats[FSM_ALL]);
  _dbg("fsm_print_stats: FSM_NEW ...: %lu\n", fsm->stats[FSM_NEW]);
  _dbg("fsm_print_stats: FSM_PAUSE .: %lu\n", fsm->stats[FSM_PAUSE]);
  _dbg("fsm_print_stats: FSM_RUN ...: %lu\n", fsm->stats[FSM_RUN]);
  _dbg("fsm_print_stats: FSM_ERROR .: %lu\n", fsm->stats[FSM_ERROR]);
  fflush(stdout);
}

#undef YCP_NAME
