/* command.h - Command API for `ce` util usage
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
#ifndef __CE_COMMAND_H
#define __CE_COMMAND_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup ce_command
 * @{
 */

/* C libraries */
#include <stdint.h>
#include <stddef.h>
#include "yacup/ce/types.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
struct ce_argument
{
  enum ce_data_type type;
  union ce_data data;
};

struct ce_command
{
  size_t id;
  char *name;
  int (*validate)(struct ce_command *command, struct ce_argument *argument[]);
  int (*parse)(struct ce_command *command, struct ce_argument *argument[]);
};

struct ce_command_subset
{
  char *name;
  struct ce_command **command;
};

struct ce_command_set
{
  char *name;
  struct ce_command_subset **subset;
};

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
int ce_command_validate(struct ce_command_set *cmd_set,
                        size_t id,
                        struct ce_argument *argument[]);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CE_COMMAND_H */
