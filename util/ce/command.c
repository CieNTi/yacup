/* command.c - Command API for `ce` for yacup project
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
#include "yacup/ce/command.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include "yacup/debug.h"
#undef YCP_NAME
#define YCP_NAME "util/ce/command"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* Locate a command in a set by its unique identifier
 * Read `yacup/ce/command.h` for complete information. */
struct ce_command *ce_command_locate_by_id(struct ce_command_set *cmd_set,
                                           size_t id)
{
  /* Configure _dbg() */
  #define YCP_FNAME "ce_command_locate_by_id"

  /* subset index */
  size_t sx = 0;
  /* command index */
  size_t cx = 0;

  _dbg("Locating command 0x%02lX on set '%s' (%p)\n",
       id,
       cmd_set->name,
       (void *)cmd_set);

  /* Iterate through subsets */
  for (sx = 0; cmd_set->subset[sx] != NULL; sx++)
  {
    _dbg("Subset %lu: '%s' (%p)\n",
         sx,
         cmd_set->subset[sx]->name,
         (void *)cmd_set->subset[sx]);

    /* Check if command is implemented */
    for (cx = 0;
         cmd_set->subset[sx]->command[cx] != NULL;
         cx++)
    {
      /* id found? */
      if (cmd_set->subset[sx]->command[cx]->id != id)
      {
        /* No, next */
        continue;
      }
      _dbg("Command '%s' (subset %lu, id %lu) found\n",
           cmd_set->subset[sx]->command[cx]->name,
           sx,
           cx);
      return cmd_set->subset[sx]->command[cx];
    }
  }

  _dbg("Command not found\n");
  return NULL;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

/* Validates a `ce_command`
 * Read `yacup/ce/command.h` for complete information. */
struct ce_command *ce_command_validate(struct ce_command_set *cmd_set,
                                       size_t id,
                                       struct ce_command_argument *argument[])
{
  /* Configure _dbg() */
  #define YCP_FNAME "ce_command_validate"

  /* argument index */
  size_t ax = 0;

  _dbg("Validating command 0x%02lX on set '%s' (%p)\n",
       id, cmd_set->name, (void *)cmd_set);

  struct ce_command *ref_cmd = ce_command_locate_by_id(cmd_set, id);
  if (ref_cmd == NULL)
  {
    _dbg("Command not found\n");
    return NULL;
  }

  _dbg("Command '%s' (0x%02lX) found, checking arguments\n",
       ref_cmd->name, ref_cmd->id);

  /* No arguments passed, check if it fits */
  if (argument == NULL)
  {
    if (ref_cmd->signature[0] != CE_DATA_NULL)
    {
      _dbg("Command expects at least 1 argument, none passed\n");

      /* Argument mismatch */
      return NULL;
    }

    /* Command found */
    _dbg("Command '%s' (0x%02lX), without arguments, is valid\n",
         ref_cmd->name, ref_cmd->id);
    return ref_cmd;
  }

  /* Check if command signature is valid */
  for (ax = 0;
       ((argument[ax] != NULL) &&
        (ref_cmd->signature[ax] != CE_DATA_NULL));
       ax++)
  {
    if (ref_cmd->signature[ax] !=
        argument[ax]->type)
    {
      _dbg("Argument type mismatch %lu (%u vs. %u)\n",
           ax, argument[ax]->type, ref_cmd->signature[ax]);

      /* Argument type mismatch */
      return NULL;
    }
  }

  /* After the last command, both need to be NULL or one has extra arg */
  if ((ref_cmd->signature[ax] != CE_DATA_NULL) ||
      (argument[ax] != NULL))
  {
    _dbg("Extra argument not matched %lu (%u vs. %u)\n",
         ax,
         (argument[ax] == NULL)?CE_DATA_NULL:argument[ax]->type,
         ref_cmd->signature[ax]);

    /* Extra argument not matched, next command */
    return NULL;
  }

  /* Command found */
  _dbg("Command '%s' (0x%02lX) is valid\n", ref_cmd->name, ref_cmd->id);
  return ref_cmd;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

/* Set a command listener, if found in a set
 * Read `yacup/ce/command.h` for complete information. */
int ce_command_set_listener(struct ce_command_set *cmd_set,
                            size_t id,
                            struct ce_command_listener *listener)
{
  /* Configure _dbg() */
  #define YCP_FNAME "ce_command_set_listener"

  if (/* Invalid command set? */
      (cmd_set == NULL) ||
      /* Invalid listener structure? */
      (listener == NULL)
      /* Removed listener->listener check as we maybe just want the data
       * and not the full callback+data. To be checked where executed */)
  {
    /* Cannot send, error */
    _dbg("Invalid data when attaching a listener to a command\n");
    return 1;
  }

  struct ce_command *ref_cmd = NULL;
  ref_cmd = ce_command_validate(cmd_set, id, listener->argument);

  /* Invalid command ? */
  if (ref_cmd == NULL)
  {
    /* Cannot send, error */
    _dbg("Cannot attach, unknown or invalid command\n");
    return 1;
  }

  /* Attach! */
  ref_cmd->listener = listener;

  /* Ok! */
  _dbg("Listener attached successfully\n");
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

#undef YCP_NAME
