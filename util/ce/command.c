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
int ce_command_validate(struct ce_command_set *cmd_set,
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
      _dbg("Command %lu: Found '%s'\n",
           cx,
           cmd_set->subset[sx]->command[cx]->name);

      /* Check if command signature is valid */
      for (ax = 0;
           cmd_set->subset[sx]->command[cx]->signature[ax] != CE_DATA_NULL;
           ax++)
      {
        _dbg("Looping %lu with val = %u\n", ax,
             cmd_set->subset[sx]->command[cx]->signature[ax]);
      }
      _dbg("Exit loop %lu with val = %u\n", ax,
           cmd_set->subset[sx]->command[cx]->signature[ax]);

      /* Return command validate output */
      //return (cmd_set->subset[sx]->command[cx]->validate(
      //          cmd_set->subset[sx]->command[cx],
      //          argument));
      return 0;
    }
  }

  _dbg("Command not found\n");
  return 1;

  /* Free _dbg() config */
  #undef YCP_FNAME
}

#undef YCP_NAME
