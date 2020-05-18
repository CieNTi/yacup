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
int cp_command_validate(struct cp_command *command_set[],
                        size_t id,
                        struct cp_argument *argument[])
{
  /* Configure _dbg() */
  #define YCP_FNAME "cp_command_validate"

  size_t idx = 0;

  /* Check if command is implemented */
  for (idx = 0; command_set[idx] != NULL; idx++)
  {
    if (idx != id)
    {
      continue;
    }
    _dbg("Command found, index %lu, name %s\n", idx, command_set[idx]->name);
    if (command_set[idx]->validate(command_set[idx], argument))
    {
      _dbg("Invalid command\n");
      return 1;
    }
    break;
  }

  if (command_set[idx] == NULL)
  {
    _dbg("Command not found\n");
    return 1;
  }

  /* Cya! */
  return 0;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

#undef YCP_NAME
