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
/* Validates a `ce_command`
 * Read `yacup/ce/command.h` for complete information. */
struct ce_command *ce_command_validate(struct ce_command_set *cmd_set,
                                       size_t id,
                                       struct ce_command_argument *argument[])
{
  /* Configure _dbg() */
  #define YCP_FNAME "ce_command_validate"

  /* subset index */
  size_t sx = 0;
  /* command index */
  size_t cx = 0;
  /* argument index */
  size_t ax = 0;

  _dbg("Validating command 0x%02lX on set '%s' (%p)\n",
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
      if (cmd_set->subset[sx]->command[cx]->id != id)
      {
        continue;
      }
      _dbg("Command '%s' (subset %lu, id %lu) found, checking arguments\n",
           cmd_set->subset[sx]->command[cx]->name,
           sx,
           cx);

      /* No arguments passed, check if it fits */
      if (argument == NULL)
      {
        if (cmd_set->subset[sx]->command[cx]->signature[0] != CE_DATA_NULL)
        {
          _dbg("Command expects at least 1 argument, none passed\n");

          /* Argument type mismatch, next command */
          continue;
        }

        /* Command found */
        _dbg("Command '%s' (subset %lu, id %lu) is valid (no args)!\n",
             cmd_set->subset[sx]->command[cx]->name,
             sx,
             cx);
        return cmd_set->subset[sx]->command[cx];
      }

      /* Check if command signature is valid */
      for (ax = 0;
           ((argument[ax] != NULL) &&
            (cmd_set->subset[sx]->command[cx]->signature[ax] != CE_DATA_NULL));
           ax++)
      {
        if (cmd_set->subset[sx]->command[cx]->signature[ax] !=
            argument[ax]->type)
        {
          _dbg("Argument type mismatch %lu (%u vs. %u)\n",
               ax,
               argument[ax]->type,
               cmd_set->subset[sx]->command[cx]->signature[ax]);

          /* Argument type mismatch, next command */
          break;
        }
      }

      /* After the last command, both need to be NULL or one has extra arg */
      if ((cmd_set->subset[sx]->command[cx]->signature[ax] != CE_DATA_NULL) ||
          (argument[ax] != NULL))
      {
        _dbg("Extra argument not matched %lu (%u vs. %u)\n",
             ax,
             (argument[ax] == NULL)?CE_DATA_NULL:argument[ax]->type,
             cmd_set->subset[sx]->command[cx]->signature[ax]);

        /* Extra argument not matched, next command */
        continue;
      }

      /* Command found */
      _dbg("Command '%s' (subset %lu, id %lu) is valid!\n",
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

#undef YCP_NAME
