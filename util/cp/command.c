/* command.c - Command API for `cp` for yacup project
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
#include "yacup/cp/command.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include "yacup/debug.h"
#undef YCP_NAME
#define YCP_NAME "util/cp/command"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* Validates a `cp_command`
 * Read `yacup/cp/command.h` for complete information. */
int cp_command_validate(struct cp_command_set *cmd_set,
                        size_t id,
                        struct cp_argument *argument[])
{
  /* Configure _dbg() */
  #define YCP_FNAME "cp_command_validate"

  size_t sub_idx = 0;
  size_t cmd_idx = 0;

  /* Iterate through subsets */
  for (sub_idx = 0; cmd_set->subset[sub_idx] != NULL; sub_idx++)
  {
    _dbg("Subset index %lu, address %p\n", sub_idx, (void *)cmd_set->subset[sub_idx]);

    /* Check if command is implemented */
    for (cmd_idx = 0;
         cmd_set->subset[sub_idx]->command[cmd_idx] != NULL;
         cmd_idx++)
    {
      if (cmd_idx != id)
      {
        continue;
      }
      _dbg("Command found, index %lu, name %s\n",
           cmd_idx,
           cmd_set->subset[sub_idx]->command[cmd_idx]->name);
      if (cmd_set->subset[sub_idx]->command[cmd_idx]->validate(
            cmd_set->subset[sub_idx]->command[cmd_idx],
            argument)
          )
      {
        _dbg("Invalid command\n");
        return 1;
      }
      break;
    }
    break;
  }

  if (cmd_set->subset[sub_idx] == NULL)
  {
    _dbg("Command not found\n");
    return 1;
  }

//  if (cmd_set[cmd_idx] == NULL)
//  {
//    _dbg("Command not found\n");
//    return 1;
//  }
//
  /* Cya! */
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

#undef YCP_NAME
