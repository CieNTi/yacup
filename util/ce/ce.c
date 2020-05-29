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

  /* Pointer to validated command */
  struct ce_command *cmd_to_send = NULL;
  
  if (/* Invalid ce? */
      (ce == NULL) ||
      /* Invalid command set? */
      (ce->out.command_set == NULL) ||
      /* Invalid send_command() ? */
      (ce->driver.send_command == NULL))
  {
    /* Cannot send, error */
    _dbg("Error when sending a command: Invalid ce, command set or driver\n");
    return 1;
  }

  /* Look for it, validate and return a pointer if found and valid */
  cmd_to_send = ce_command_validate(ce->out.command_set, id, argument);

  if (/* Invalid command */
      (cmd_to_send == NULL) ||
      /* Cannot send the command ? */
      ce->driver.send_command(ce, cmd_to_send, argument))
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

/* Wait for a command and returns its id and data if success
 * Read `yacup/ce.h` for complete information. */
int ce_wait_command(struct ce *ce,
                    size_t *id,
                    struct ce_command_argument **argument[])
{
  /* Configure _dbg() */
  #define YCP_FNAME "ce_wait_command"

  /* Pointer to validated command */
  struct ce_command *cmd_to_wait = NULL;
  
  if (/* Invalid ce? */
      (ce == NULL) ||
      /* Invalid command ID holder? */
      (id == NULL) ||
      /* Invalid arguments ? */
      (argument == NULL) ||
      /* Invalid send_command() ? */
      (ce->driver.wait_command == NULL))
  {
    /* Cannot send, error */
    _dbg("Error when waiting commands: Invalid ce, id or argument holders\n");
    return 1;
  }

  /* Cannot receive any command ? */
  if (ce->driver.wait_command(ce, id, argument))
  {
    /* Cannot send, error */
    _dbg("Error when receiving the command\n");
    return 1;
  }

  /* Look for it, validate and return a pointer if found and valid */
  cmd_to_wait = ce_command_validate(ce->in.command_set, *id, *argument);
  if (cmd_to_wait == NULL)
  {
    /* Cannot send, error */
    _dbg("Cannot validate command\n");
    return 1;
  }

  /* set id and go */
  *id = cmd_to_wait->id;

  /* Ok! */
  _dbg("Command received\n");
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

#undef YCP_NAME
