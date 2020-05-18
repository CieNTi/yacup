#  Makefile - Makefile for setting up yacup project builds
#  Copyright (C) 2020 CieNTi <cienti@cienti.com>
#  
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU Affero General Public License as published
#  by the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#  
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU Affero General Public License for more details.
#  
#  You should have received a copy of the GNU Affero General Public License
#  along with this program.  If not, see <https://www.gnu.org/licenses/>.

# Define default target
.PHONY: default
default: all

# Makefile absolute path
MFDIR = $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
# Remove trailing slash
MFDIR := $(MFDIR:/=)

# Base input folders
IDIR = template/util_xyz $(addprefix $(MFDIR)/, $(wildcard util/*))
SDIR = $(MFDIR)

# Base output folders
OUTD = $(MFDIR)/out
BDIR = $(OUTD)/bin
LDIR = $(OUTD)/lib
ODIR = $(OUTD)/obj

# Command mapping
MKDIR = mkdir
LS = ls -al
CP = cp
RM = rm -rf
CC = gcc
OBJCOPY = objcopy

# Flags, libs, ...
CFLAGS = $(addprefix -I, $(IDIR)) -Wall -Werror -pedantic-errors
LDLIBS = -lm

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Targets for 'util' folder
# ~~~~~~~~~~~~~~~~~~~~~~~~~
# test_xyz_testname: Test to check `xyz` template functionality
test_xyz_testname_objs=template/util_xyz/xyz.o                    \
                       template/util_xyz/test/test_xyz_testname.o \
                       template/util_xyz/debug.o
test_xyz_testname: $(addprefix $(ODIR)/, $(test_xyz_testname_objs))
	@echo "-----"
	@make test_bin TB_OBJ=$(firstword $(filter %$@.o,$+)) TB_NAME=$@ TB_OBJS="$+"
	@echo "-----"

# test_rb_driver_overwrite: Test to check `rb` overwrite driver functionality
test_rb_driver_overwrite_objs=util/rb/rb.o                            \
                              util/rb/driver/overwrite.o              \
                              util/rb/test/test_rb_driver_overwrite.o \
                              util/rb/debug.o
test_rb_driver_overwrite: $(addprefix $(ODIR)/, $(test_rb_driver_overwrite_objs))
	@echo "-----"
	@make test_bin TB_OBJ=$(firstword $(filter %$@.o,$+)) TB_NAME=$@ TB_OBJS="$+"
	@echo "-----"

# test_fsm_simple: Test to check `fsm` functionality
test_fsm_simple_objs=util/fsm/fsm.o                  \
                     util/fsm/test/fsm_simple.o      \
                     util/fsm/test/test_fsm_simple.o \
                     util/fsm/debug.o
test_fsm_simple: $(addprefix $(ODIR)/, $(test_fsm_simple_objs))
	@echo "-----"
	@make test_bin TB_OBJ=$(firstword $(filter %$@.o,$+)) TB_NAME=$@ TB_OBJS="$+"
	@echo "-----"

# test_cp_codec_B416K: Test to check `cp` B416K protocol functionality
test_cp_codec_B416K_objs=util/rb/rb.o                       \
                         util/rb/driver/overwrite.o         \
                         util/rb/debug.o                    \
                         util/cp/cp.o                       \
                         util/cp/codec.o                    \
                         util/cp/codec/B416K.o              \
                         util/cp/test/test_cp_codec_B416K.o \
                         util/cp/debug.o
test_cp_codec_B416K: $(addprefix $(ODIR)/, $(test_cp_codec_B416K_objs))
	@echo "-----"
	@make test_bin TB_OBJ=$(firstword $(filter %$@.o,$+)) TB_NAME=$@ TB_OBJS="$+"
	@echo "-----"

# test_cp_commands: Test to check `cp` commands functionality
test_cp_commands_objs=util/rb/rb.o                       \
                      util/rb/driver/overwrite.o         \
                      util/rb/debug.o                    \
                      util/fsm/fsm.o                     \
                      util/fsm/debug.o                   \
                      util/cp/cp.o                       \
                      util/cp/codec.o                    \
                      util/cp/command.o                  \
                      util/cp/codec/B416K.o              \
                      util/cp/test/test_cp_commands.o    \
                      util/cp/debug.o
test_cp_commands: $(addprefix $(ODIR)/, $(test_cp_commands_objs))
	@echo "-----"
	@make test_bin TB_OBJ=$(firstword $(filter %$@.o,$+)) TB_NAME=$@ TB_OBJS="$+"
	@echo "-----"
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Targets for 'src' folder
# ~~~~~~~~~~~~~~~~~~~~~~~~
# Test app compounding all other tests defined here
test_yacup_objs=$(test_xyz_testname_objs)        \
                $(test_rb_driver_overwrite_objs) \
                $(test_fsm_simple_objs)          \
                $(test_cp_codec_B416K_objs)      \
                src/test/test_yacup.o
test_yacup: $(addprefix $(ODIR)/, $(test_yacup_objs))
	@echo "-----"
	make test_bin TB_OBJ=$(firstword $(filter %$@.o,$+)) TB_NAME=$@ TB_OBJS="$+"
	@echo "-----"

# Normal app (main() function is there)
an_app_objs=some/object/file.o
an_app: $(addprefix $(ODIR)/, $(an_app_objs))
	@echo "-----"
	@echo "\nLinking | << $+\n        | >> $(BDIR)/$@"
	$(CC) $+ $(CFLAGS) $(LDLIBS) -o $(BDIR)/$@
	@echo "\nExecuting '$@': $(BDIR)/$@\n-----"
	@$(BDIR)/$@
	@echo "-----"
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# Wildcard target that look for .c file based on .o name
$(ODIR)/%.o: $(SDIR)/%.c
	@echo "-----"
	@echo "Compiling | << $<\n          | >> $@"
	$(MKDIR) -p $(@D)
	$(CC) -c $< $(CFLAGS) -o $@
	@echo "-----"

# My Little Phonies
.PHONY: test_bin
test_bin:
	@if [ "$(TB_OBJ)"  = "" -o "$(TB_OBJS)" = "" -o "$(TB_NAME)" = "" ];  \
	then                                                                        \
	  echo "-----";                                                             \
	  echo ":::::::::::::::::::::::::::::::::::::::::::::::::::::";             \
	  echo ":: This is not supposed to be called this way, son ::";             \
	  echo ":::::::::::::::::::::::::::::::::::::::::::::::::::::";             \
	  echo ":: TB_OBJ .........: $(TB_OBJ)";                                    \
	  echo ":: TB_OBJS ........: $(TB_OBJS)";                                   \
	  echo ":: TB_NAME ........: $(TB_NAME)";                                   \
	  echo ":::::::::::::::::::::::::::::::::::::::::::::::::::::";             \
	  echo "-----";                                                             \
	  exit 1;                                                                   \
  fi
	@echo "-----\nSetting '$(TB_NAME)()' as the new 'main()'"
	$(OBJCOPY) --redefine-sym $(TB_NAME)=main $(TB_OBJ)
	@echo "\nLinking | << $(TB_OBJS)\n        | >> $(BDIR)/$(TB_NAME)"
	$(CC) $(TB_OBJS) $(CFLAGS) $(LDLIBS) -o $(BDIR)/$(TB_NAME)
	@echo "\nExecuting '$(TB_NAME)': $(BDIR)/$(TB_NAME)\n-----"
	@$(BDIR)/$(TB_NAME)
	@echo "-----"

.PHONY: all
all: clean debug prepare test_yacup               \
                         test_xyz_testname        \
                         test_rb_driver_overwrite \
                         test_fsm_simple          \
                         test_cp_codec_B416K      \
                         test_cp_commands
	@echo "-----"
	@echo "Success after 'make $@' ('make $^')"
	@echo ""
	@echo "Pick your binaries at '$(BDIR)'"
	@$(LS) $(BDIR)
	@echo "-----"

.PHONY: prepare
prepare:
	@echo "-----"
	@echo "Preparing environment ..."
	@echo "Creating | '$(BDIR)'\n         | '$(LDIR)'\n         | '$(ODIR)'"
	@$(MKDIR) -p $(BDIR)
	@$(MKDIR) -p $(LDIR)
	@$(MKDIR) -p $(ODIR)
	@echo "-----"

.PHONY: debug
debug:
	$(eval CFLAGS += -DYACUP_DEBUG)
	@echo "-----"
	@echo "Variables:"
	@echo "  MFDIR ....: $(MFDIR)"
	@echo "  IDIR .....: $(IDIR)"
	@echo "  SDIR .....: $(SDIR)"
	@echo "  BDIR .....: $(BDIR)"
	@echo "  LDIR .....: $(LDIR)"
	@echo "  ODIR .....: $(ODIR)"
	@echo "  MKDIR ....: $(MKDIR)"
	@echo "  LS .......: $(LS)"
	@echo "  CP .......: $(CP)"
	@echo "  RM .......: $(RM)"
	@echo "  CC .......: $(CC)"
	@echo "  CFLAGS ...: $(CFLAGS)"
	@echo "  LDLIBS ...: $(LDLIBS)"
	@echo "-----"

.PHONY: clean
clean:
	@echo "-----"
	@echo "Cleaning environment ..."
	$(RM) *~ $(BDIR) $(LDIR) $(ODIR) $(OUTD) $(addsuffix /*~, $(IDIR))
	@echo "-----"

.PHONY: help
help:
	@echo "Usage:"
	@echo "  make target"
	@echo ""
	@echo "Available targets related to common tasks:"
	@echo "  default ..: Executed if 'make' without target. Default: all"
	@echo "  all ......: Executes all targets in sequence"
	@echo "  clean ....: Deletes generated files after build"
	@echo "  debug ....: Defines YACUP_DEBUG flag and print debug information"
	@echo "  prepare ..: Creates required folders and files"
	@echo "  help .....: Print this information"
	@echo ""
	@echo "Available targets related to utilities tests:"
	@echo "  test_xyz_testname .........: Example 'xyz' template functionality"
	@echo "  test_rb_driver_overwrite ..: 'rb' ring-buffer 'overwrite' driver"
	@echo "  test_fsm_simple ...........: 'fsm' basic FSM functionality"
	@echo "  test_cp_codec_B416K .......: 'cp' B416K codec functionality"
	@echo "  test_cp_commands ..........: 'cp' commands functionality"
	@echo ""
	@echo "Available targets related to application tests:"
	@echo "  test_yacup ..: Example application test that runs all other utils"
	@echo "                 tests in a row"
	@echo ""
	@echo "Example:"
	@echo "  - Prepare a clean environment, enable debug and print a brief"
	@echo "    > make clean debug prepare"
	@echo ""
	@echo "  - Clean, prepare, build and execute 'test_xyz_testname' with debug"
	@echo "    > make clean debug prepare test_xyz_testname"
	@echo ""
	@echo "NOTE:"
	@echo "  If YACUP_DEBUG define/flag is defined, it will enable '_dbg()'"
	@echo "  function along all the utilities and applications, so a lot of"
	@echo "  internal information will be printed to STDOUT, formatted as:"
	@echo "  > some/module/path | function_name: message"
	@echo "  This will ease development and debug flows"
	@echo ""
