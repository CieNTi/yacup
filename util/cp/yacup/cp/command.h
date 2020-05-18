/* command.h - Command API for `cp` util usage
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
#ifndef __CP_COMMAND_H
#define __CP_COMMAND_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup cp
 * @{
 */

/* C libraries */
#include <stdint.h>
#include <stddef.h>
#include "yacup/cp/codec.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
struct cp_argument
{
  enum cp_codec_data_type type;
  void *data;
};

struct cp_command
{
  size_t id;
  char *name;
  int (*validate)(struct cp_command *command, struct cp_argument *argument[]);
  int (*parse)(struct cp_command *command, struct cp_argument *argument[]);
};

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
int cp_command_validate(struct cp_command *command_set[],
                        size_t id,
                        struct cp_argument *argument[]);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CP_COMMAND_H */
