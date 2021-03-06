/* fsm.c - Finite state machine API for yacup project
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
#include "yacup/fsm.h"
#include "yacup/fsm/driver.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include "yacup/debug.h"
#undef YCP_NAME
#define YCP_NAME "util/fsm/fsm"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* Configuration flags */
#define FSM_CONFIG_ENABLED      (uint32_t)(1 << 0)
#define FSM_CONFIG_AUTO_RESTART (uint32_t)(1 << 1)
#define FSM_CONFIG_STARTED      (uint32_t)(1 << 2)

/* Initializes a `fsm` common data, then lower level init, passed by argument.
 * Read `yacup/fsm.h` for complete information. */
int fsm_init(struct fsm *fsm, int (*fsm_driver_init)(struct fsm *))
{
  /* Configure _dbg() */
  #define YCP_FNAME "fsm_init"

  if (/* Invalid fsm? */
      (fsm == NULL) ||
      /* Invalid driver init? */
      (fsm_driver_init == NULL))
  {
    _dbg("Invalid fsm or driver init function\n");
    return 1;
  }

  /* Fill FSM common data */
  fsm->config = 0;
  fsm->state = FSM_NEW;
  fsm->stats[FSM_NEW] = 0;
  fsm->stats[FSM_PAUSE] = 0;
  fsm->stats[FSM_RUN] = 0;
  fsm->stats[FSM_ERROR] = 0;
  fsm->stats[FSM_ALL] = 0;

  /* Now call the driver init function, and go */
  if (fsm_driver_init(fsm))
  {
    _dbg("Failed fsm initialization\n");
    return 1;
  }

  /* Assign default name, if not previously set */
  if (fsm->name == NULL)
  {
    fsm->name = YCP_NAME;
  }

  /* Ok! */
  _dbg("fsm '%s' initialized successfully\n", fsm->name);
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

/* Sets the enable bit, allowing this `fsm` to perform actions
 * Read `yacup/fsm.h` for complete information. */
void fsm_enable(struct fsm *fsm)
{
  if (fsm == NULL) { return; }
  fsm->config |= FSM_CONFIG_ENABLED;
}

/* Unsets the enable bit, disallowing this `fsm` to perform further actions
 * Read `yacup/fsm.h` for complete information. */
void fsm_disable(struct fsm *fsm)
{
  if (fsm == NULL) { return; }
  fsm->config &= ~FSM_CONFIG_ENABLED;
}

/* Unsets the auto-restart bit, making this `fsm` to stop once completed
 * Read `yacup/fsm.h` for complete information. */
void fsm_set_single(struct fsm *fsm)
{
  if (fsm == NULL) { return; }
  fsm->config &= ~FSM_CONFIG_AUTO_RESTART;
}

/* Sets the auto-restart bit, making this `fsm` to start again once completed
 * Read `yacup/fsm.h` for complete information. */
void fsm_set_loop(struct fsm *fsm)
{
  if (fsm == NULL) { return; }
  fsm->config |= FSM_CONFIG_AUTO_RESTART;
}

/* Sets the started bit, making this `fsm` to start the next valid cycle
 * Read `yacup/fsm.h` for complete information. */
void fsm_request_start(struct fsm *fsm)
{
  if (fsm == NULL) { return; }
  fsm->config |= FSM_CONFIG_STARTED;
}

/* Unsets the started bit, making this `fsm` to stop the next valid cycle
 * Read `yacup/fsm.h` for complete information. */
void fsm_request_stop(struct fsm *fsm)
{
  if (fsm == NULL) { return; }
  fsm->config &= ~FSM_CONFIG_STARTED;
}

/* Stepper function (single cycle and exit, need outside controller loop)
 * Read `yacup/fsm.h` for complete information. */
int fsm_do_cycle(struct fsm *fsm)
{
  /* Configure _dbg() */
  #define YCP_FNAME "fsm_do_cycle"

  if (fsm == NULL)
  {
    _dbg("fsm is NULL. ERROR\n");

    /* Totally wrong, return dramatically */
    return 1;
  }

  if (!(fsm->config & FSM_CONFIG_ENABLED))
  {
    _dbg("%s@disabled\n", fsm->name);

    /* Disabled, return silently */
    return 0;
  }

  /* Record FSM_ALL stat */
  fsm->stats[FSM_ALL]++;

  /* Behavior */
  switch (fsm->state)
  {
    /* This should be a 1-pass state only, only initialization and checks */
    case FSM_NEW:
      _dbg("%s@FSM_NEW\n", fsm->name);
      _dbg("fsm has been created. Lets configure it\n");

      /* Record FSM_NEW stat */
      fsm->stats[FSM_NEW]++;

      /* Checks */
      if (fsm->driver->start == NULL)
      {
        _dbg("'%s' has no start. Ooops! Breaking here now ...\n",
             fsm->name);

        /* Exits inmediately */
        fsm->stats[FSM_ERROR]++;
        return 1;        
      }

      if (fsm->driver->stop == NULL)
      {
        _dbg("'%s' has no stop. FSM_CONFIG_AUTO_RESTART set\n",
             fsm->name);

        /* Infinite loop for non-stoppable fsm */
        fsm->config |= FSM_CONFIG_AUTO_RESTART;
      }

      /* Configure */
      fsm->next = fsm->driver->start;

      /* Pause, if rearm is set it'll run automagically in 2 cycles */
      fsm->state = FSM_PAUSE;
      break;

    /* 'Nothing to do' state. fsm possibly ended and no rearm bit was found */
    case FSM_PAUSE:
      _dbg("%s@FSM_PAUSE\n", fsm->name);

      /* Record FSM_PAUSE stat */
      fsm->stats[FSM_PAUSE]++;

      /* Check if it should be ran */
      if ((fsm->config & FSM_CONFIG_STARTED) &&
          ((fsm->next == fsm->driver->start) ||
           (fsm->config & FSM_CONFIG_AUTO_RESTART)))
      {
        _dbg("'%s' fsm is ready/restart bit is set. Run it!\n",
             fsm->name);

        /* Armed fsm, run it again */
        fsm->next = fsm->driver->start;
        fsm->state = FSM_RUN;
      }
      break;

    /* Machine core, where the things happens */
    case FSM_RUN:
      _dbg("%s@FSM_RUN\n", fsm->name);

      /* Record FSM_RUN stat */
      fsm->stats[FSM_RUN]++;

      /* fsm was ran and finished, and it also was rearmed */
      if ((fsm->driver->stop != NULL) && (fsm->now == fsm->driver->stop))
      {
        _dbg("'%s' has been restarted\n", fsm->name);

        /* Ensure a valid start point */
        fsm->next = fsm->driver->start;
      }

      /* Evaluate next state validity */
      if (fsm->next == NULL)
      {
        _dbg("'%s' fsm has no 'next' state\n", fsm->name);

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
        _dbg("'%s' executed, but something wrong happened\n",
             fsm->name);

        /* @todo Error for now */
        fsm->state = FSM_ERROR;
        return 1;
      }

      /* Capture if this fsm is terminated */
      if ((fsm->driver->stop != NULL) && (fsm->now == fsm->driver->stop))
      {
        fsm->state = FSM_PAUSE;
      }
      break;

    /* You're in a little trouble if you are here */
    case FSM_ERROR:
      _dbg("%s@FSM_ERROR\n", fsm->name);
      _dbg("'%s' fsm entered error state\n", fsm->name);
      _dbg("- fsm->last .: %p\n", (void *)(size_t)fsm->last);
      _dbg("- fsm->now ..: %p\n", (void *)(size_t)fsm->now);
      _dbg("- fsm->next .: %p\n", (void *)(size_t)fsm->next);
      _dbg("App needs to rearm it before continue\n");

      /* Record FSM_ERROR stat */
      fsm->stats[FSM_ERROR]++;
      break;

    /* You're in a big trouble if you are here */
    default:
      /* No stats here (Resultant is 'all' - 'sum of all of the rest') */
      _dbg("'%s' went crazy, it shouldn't be here\n", fsm->name);

      /* @todo Error for now */
      fsm->state = FSM_ERROR;
      return 1;
      break;
  }

  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

#undef YCP_NAME
