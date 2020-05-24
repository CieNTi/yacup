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
int ce_init(struct ce *ce, int (*ce_driver_init)(struct ce *))
{
  /* Configure _dbg() */
  #define YCP_FNAME "ce_init"

  if (/* Invalid ce? */
      (ce == NULL) ||
      /* Invalid driver */
      (ce_driver_init == NULL))
  {
    _dbg("Invalid ce or driver init function\n");
    return 1;
  }

  /* Fill ce common data */
  // Nothing to fill here yet, so this call is right now, just a validator

  /* Now call the low level init function, and go */
  return (ce_driver_init(ce));

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

  /* Validate command */
  if (ce_command_validate(ce->out.command_set, id, argument))
  {
    /* Cannot send, error */
    _dbg("Error when validating CE_COMMAND_SUBSET_TEST_CMD1\n");
    return 1;
  }

  /* Ok! */
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

#undef YCP_NAME
