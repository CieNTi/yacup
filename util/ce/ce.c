/* ce.c - Command engine API for yacup project
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
#include "yacup/ce.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include "yacup/debug.h"
#undef YCP_NAME
#define YCP_NAME "util/ce/ce"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* Initializes a command engine referenced by a `ce` pointer
 * Read `yacup/ce.h` for complete information. */
int ce_init(struct ce *ce,
            int (*ce_driver_init)(struct ce *),
            int (*ce_codec_driver_init)(struct ce_codec *),
            int (*rb_driver_init)(struct rb *))
{
  /* Configure _dbg() */
  #define YCP_FNAME "ce_init"

  if (/* Invalid ce? */
      (ce == NULL) ||
      /* Invalid driver */
      (ce_driver_init == NULL) ||
      /* Defined codec driver? */
      (ce_codec_driver_init == NULL) ||
      /* Defined buffer driver? */
      (rb_driver_init == NULL) ||
      /* Invalid channels init */
      ce_channel_init(&ce->out, ce_codec_driver_init, rb_driver_init) ||
      ce_channel_init(&ce->in,  ce_codec_driver_init, rb_driver_init) ||
      /* And try to initialize this ce driver */
      ce_driver_init(ce))
  {
    _dbg("Invalid ce or driver init function\n");
    return 1;
  }
      
  /* Assign default name, if not previously set */
  if (ce->name == NULL)
  {
    ce->name = YCP_NAME;
  }

  /* And finish! */
  _dbg("ce '%s' initialized successfully\n", ce->name);
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

/* Validates command if found, encode data into a message and send it
 * Read `yacup/ce.h` for complete information. */
int ce_send_command(struct ce *ce,
                    size_t id,
                    struct ce_command_argument *argument[])
{
  /* Configure _dbg() */
  #define YCP_FNAME "ce_send_command"

  if (/* Invalid ce? */
      (ce == NULL) ||
      /* Invalid command set? */
      (ce->out.command_set == NULL) ||
      /* Invalid command */
      (ce_command_validate(ce->out.command_set, id, argument) == NULL) ||
      /* Invalid send_command() ? */
      (ce->driver.send_command == NULL) ||
      /* Cannot send the command ? */
      ce->driver.send_command(ce, id, argument))
  {
    /* Cannot send, error */
    _dbg("Error when sending the command\n");
    return 1;
  }

  /* Ok! */
  _dbg("Command sent\n");
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

/* Set a command listener, if found in a set
 * Read `yacup/ce.h` for complete information. */
int ce_set_command_listener(struct ce *ce,
                            size_t id,
                            struct ce_command_listener *listener)
{
  /* Configure _dbg() */
  #define YCP_FNAME "ce_set_command_listener"

  if (/* Invalid ce? */
      (ce == NULL) ||
      /* Invalid listener structure? */
      (listener == NULL) ||
      /* Invalid listener function? */
      (listener->listener == NULL) ||
      /* Invalid command set? */
      (ce->in.command_set == NULL) ||
      /* Invalid command */
      (ce_command_validate(ce->in.command_set, id, listener->argument) == NULL))
  {
    /* Cannot send, error */
    _dbg("Error when attaching a listener to a command\n");
    return 1;
  }

  /* Ok! */
  _dbg("Listener attached successfully\n");
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}
#undef YCP_NAME
