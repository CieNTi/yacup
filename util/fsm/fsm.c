/* fsm.c - Finite state machine implementation for yacup project
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
#include "yacup/fsm.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#undef YCP_NAME
#define YCP_NAME "util/fsm/fsm"
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
/* Configuration flags */
#define FSM_CONFIG_ENABLED      (uint32_t)(1 << 0)
#define FSM_CONFIG_AUTO_RESTART (uint32_t)(1 << 1)
#define FSM_CONFIG_STARTED      (uint32_t)(1 << 2)

/**/
void fsm_enable(struct fsm *fsm)
{
  if (fsm == NULL) { return; }
  fsm->config |= FSM_CONFIG_ENABLED;
}

/**/
void fsm_disable(struct fsm *fsm)
{
  if (fsm == NULL) { return; }
  fsm->config &= ~FSM_CONFIG_ENABLED;
}

/**/
void fsm_set_single(struct fsm *fsm)
{
  if (fsm == NULL) { return; }
  fsm->config &= ~FSM_CONFIG_AUTO_RESTART;
}

/**/
void fsm_set_loop(struct fsm *fsm)
{
  if (fsm == NULL) { return; }
  fsm->config |= FSM_CONFIG_AUTO_RESTART;
}

/**/
void fsm_request_start(struct fsm *fsm)
{
  if (fsm == NULL) { return; }
  fsm->config |= FSM_CONFIG_STARTED;
}

/**/
void fsm_request_stop(struct fsm *fsm)
{
  if (fsm == NULL) { return; }
  fsm->config &= ~FSM_CONFIG_STARTED;
}

/* Stepper function (single cycle and exit, need outsider loop */
uint32_t fsm_do_cycle(struct fsm *fsm)
{
  if (fsm == NULL)
  {
    _dbg("fsm_do_cycle: fsm is NULL. ERROR\n");

    /* Totally wrong, return dramatically */
    return 1;
  }

  if (!(fsm->config & FSM_CONFIG_ENABLED))
  {
    _dbg("fsm_do_cycle: %s@disabled\n", fsm->name);

    /* Disabled, return silently */
    return 0;
  }

  /* Record FSM_ALL stat */
  fsm->stats[FSM_ALL]++;

  /* Behavior */
  switch (fsm->state)
  {
    /* This should be a 1-pass state only, just for initialization and checks */
    case FSM_NEW:
      _dbg("fsm_do_cycle: %s@FSM_NEW\n", fsm->name);
      fsm_print_info(fsm);
      _dbg("fsm_do_cycle: fsm has been created. Lets configure it\n\n");

      /* Record FSM_NEW stat */
      fsm->stats[FSM_NEW]++;

      /* Checks */
      if (fsm->start == NULL)
      {
        _dbg("fsm_do_cycle: '%s' has no start. Ooops! Breaking here now ...\n", fsm->name);

        /* Exits inmediately */
        fsm->stats[FSM_ERROR]++;
        return 1;        
      }

      if (fsm->stop == NULL)
      {
        _dbg("fsm_do_cycle: '%s' has no stop, enabling FSM_CONFIG_AUTO_RESTART\n", fsm->name);

        /* Infinite loop for non-stoppable fsm */
        fsm->config |= FSM_CONFIG_AUTO_RESTART;
      }

      /* Configure */
      fsm->next = fsm->start;

      /* Pause, if rearm is set it'll run automagically in 2 cycles */
      fsm->state = FSM_PAUSE;
      break;

    /* 'Nothing to do' state. fsm possibly ended and no rearm bit was found */
    case FSM_PAUSE:
      _dbg("fsm_do_cycle: %s@FSM_PAUSE\n", fsm->name);

      /* Record FSM_PAUSE stat */
      fsm->stats[FSM_PAUSE]++;

      /* Check if it should be ran */
      if ((fsm->config & FSM_CONFIG_STARTED) &&
          ((fsm->next == fsm->start) ||
           (fsm->config & FSM_CONFIG_AUTO_RESTART)))
      {
        _dbg("fsm_do_cycle: '%s' fsm is ready or restart bit is set. Run it now!\n", fsm->name);

        /* Armed fsm, run it again */
        fsm->next = fsm->start;
        fsm->state = FSM_RUN;
      }
      break;

    /* Machine core, where the things happens */
    case FSM_RUN:
      _dbg("fsm_do_cycle: %s@FSM_RUN\n", fsm->name);

      /* Record FSM_RUN stat */
      fsm->stats[FSM_RUN]++;

      /* fsm was ran and finished, and it also was rearmed */
      if ((fsm->stop != NULL) && (fsm->now == fsm->stop))
      {
        _dbg("fsm_do_cycle: '%s' has been restarted\n", fsm->name);

        /* Ensure a valid start point */
        fsm->next = fsm->start;
      }

      /* Evaluate next state validity */
      if (fsm->next == NULL)
      {
        _dbg("fsm_do_cycle: '%s' fsm has no 'next' state\n", fsm->name);

        /* Error, try last? */
        /* @todo Error for now */
        fsm->state = FSM_ERROR;
        return 1;
      }

      /* Shift states and run next (only if new state) */
      if (fsm->next != fsm->now)
      {
        fsm->last = fsm->now;
        fsm->now = fsm->next;
      }

      /* Ensure executed state set a valid 'next' state before return */
      fsm->next = NULL;

      /* Executes state function */
      if (fsm->now(fsm))
      {
        /* Error, break */
        _dbg("fsm_do_cycle: '%s' executed state but something wrong happened\n", fsm->name);

        /* @todo Error for now */
        fsm->state = FSM_ERROR;
        return 1;
      }

      /* Capture if this fsm is terminated */
      if ((fsm->stop != NULL) && (fsm->now == fsm->stop))
      {
        fsm->state = FSM_PAUSE;
      }
      break;

    /* You're in a little trouble if you are here */
    case FSM_ERROR:
      _dbg("fsm_do_cycle: %s@FSM_ERROR\n", fsm->name);
      _dbg("fsm_do_cycle: '%s' fsm entered error state\n", fsm->name);
      _dbg("fsm_do_cycle: - fsm->last .: %p\n", (void *)(size_t)fsm->last);
      _dbg("fsm_do_cycle: - fsm->now ..: %p\n", (void *)(size_t)fsm->now);
      _dbg("fsm_do_cycle: - fsm->next .: %p\n", (void *)(size_t)fsm->next);
      _dbg("fsm_do_cycle: App needs to rearm it before continue\n");

      /* Record FSM_ERROR stat */
      fsm->stats[FSM_ERROR]++;
      break;

    /* You're in a big trouble if you are here */
    default:
      /* No stats here (Resultant is 'all' - 'sum of all of the rest') */
      _dbg("fsm_do_cycle: '%s' went crazy, it shouldn't be here\n", fsm->name);

      /* @todo Error for now */
      fsm->state = FSM_ERROR;
      return 1;
      break;
  }

  return 0;
}

#undef YCP_NAME
