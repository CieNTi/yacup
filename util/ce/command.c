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

#undef YCP_NAME
