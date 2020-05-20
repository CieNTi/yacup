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

  _dbg("Validating command 0x%02lX on set '%s' (%p)\n",
       id,
       cmd_set->name,
       (void *)cmd_set);

  /* Iterate through subsets */
  for (sub_idx = 0; cmd_set->subset[sub_idx] != NULL; sub_idx++)
  {
    _dbg("Subset %lu: '%s' (%p)\n",
         sub_idx,
         cmd_set->subset[sub_idx]->name,
         (void *)cmd_set->subset[sub_idx]);

    /* Check if command is implemented */
    for (cmd_idx = 0;
         cmd_set->subset[sub_idx]->command[cmd_idx] != NULL;
         cmd_idx++)
    {
      if (cmd_set->subset[sub_idx]->command[cmd_idx]->id != id)
      {
        continue;
      }
      _dbg("Command %lu: Found '%s'\n",
           cmd_idx,
           cmd_set->subset[sub_idx]->command[cmd_idx]->name);

      /* Return command validate output */
      return (cmd_set->subset[sub_idx]->command[cmd_idx]->validate(
                cmd_set->subset[sub_idx]->command[cmd_idx],
                argument));
    }
  }

  _dbg("Command not found\n");
  return 1;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

/* Sends a `cp_command`: Put ready-to-send data into a ring-buffer
 * Read `yacup/cp/command.h` for complete information. */
int cp_command_send(struct cp_command_set *cmd_set,
                    size_t id,
                    struct cp_argument *argument[])
{
  /* Configure _dbg() */
  #define YCP_FNAME "cp_command_validate"


  /* Free _dbg() config */
  #undef YCP_FNAME
}

#undef YCP_NAME
