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
 * @defgroup   ce_command Commands
 * @{
 *   @brief      NEED DETAILS Commands definitions, usage and available sets
 *   @details    NEED DETAILS
 *   @author     CieNTi <cienti@cienti.com>
 *   @date       2020
 *   @ingroup    ce
 *
 *   @defgroup   ce_command_cmd How a command
 *   @{
 *     @brief      Operations on `ce` instances
 *     @details    Centralized functions to allow multiple implementations
 *     @author     CieNTi <cienti@cienti.com>
 *     @date       2020
 *   @}
 * @}
 * 
 * @addtogroup ce_command
 * @{
 */

/* C libraries */
#include <stdint.h>
#include <stddef.h>
#include "yacup/ce/types.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Structure that defines a command argument
 */
struct ce_command_argument
{
  /**
   * @brief      One of the supported argument data types
   */
  enum ce_data_type type;

  /**
   * @brief      Data value, as a union type for pre-fixed types check
   */
  union ce_data data;
};

/**
 * @brief      Structure that defines a command listener with its storage
 */
struct ce_command_listener
{
  /**
   * @brief      Incoming command listener. Will be called only if an incoming
   *             message is correctly received and if it pass the signature
   *             validation, so contained values can be trusted in error-free
   *             reception and type. Value itself is the listener duty ;)
   */
  int (*listener)(struct ce_command_argument *argument[]);

  /**
   * @brief      NULL-terminated list of pointers to arguments. It is used for
   *             signature validation before encode and send, and in case of a
   *             listener is defined, it will be used for signature validation
   *             before holding the received values.
   *             
   */
  struct ce_command_argument **argument;
};

/**
 * @brief      Structure that defines a command
 */
struct ce_command
{
  /**
   * @brief      Command unique ID (if duplicated in a set, first one is used)
   */
  size_t id;

  /**
   * @brief      ASCII name of this command
   */
  char *name;

  /**
   * @brief      NULL-terminated list of pointers to arguments. It is used for
   *             signature validation before encode and send, and in case of a
   *             listener is defined, it will be used for signature validation
   *             before holding the received values.
   */
  enum ce_data_type *signature;

  /**
   * @brief      Incoming command listener. Will be called only if an incoming
   *             message is correctly received and if it pass the signature
   *             validation, so contained values can be trusted in error-free
   *             reception and type. Value itself is the listener duty ;)
   */
  struct ce_command_listener *listener;
};

/**
 * @brief      Structure that defines a subset of commands
 */
struct ce_command_subset
{
  /**
   * @brief      ASCII name of this commands subset
   */
  char *name;

  /**
   * @brief      NULL-terminated list of pointers to commands
   */
  struct ce_command **command;
};

/**
 * @brief      Structure that defines a set of commands (composed by subsets)
 */
struct ce_command_set
{
  /**
   * @brief      ASCII name of this commands set
   */
  char *name;

  /**
   * @brief      NULL-terminated list of pointers to subsets of commands
   */
  struct ce_command_subset **subset;
};

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * @brief      Checks if passed command is found on set and has valid arguments
 *
 * @param      cmd_set   Set of commands where to search
 * @param      id        Unique command identifier of the command to validate
 * @param      argument  Arguments to check against command signature
 *
 * @return     
 *             | Value  | Meaning          |
 *             | :----: | :--------------- |
 *             | `== 0` | Ok               |
 *             | `!= 0` | Warning          |
 */
int ce_command_validate(struct ce_command_set *cmd_set,
                        size_t id,
                        struct ce_command_argument *argument[]);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CE_COMMAND_H */
