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
test_xyz_testname_o=template/util_xyz/xyz.o                    \
                    template/util_xyz/test/test_xyz_testname.o \
                    template/util_xyz/debug.o
test_xyz_testname: $(addprefix $(ODIR)/, $(test_xyz_testname_o))
	@echo "-----"
	@make test_bin TB_OBJ=$(firstword $(filter %$@.o,$^)) TB_NAME=$@ TB_OBJS="$^"
	@echo "-----"

# test_rb_driver_overwrite: Test to check `rb` overwrite driver functionality
test_rb_driver_overwrite_o=util/rb/rb.o                            \
                           util/rb/driver/overwrite.o              \
                           util/rb/test/test_rb_driver_overwrite.o \
                           util/rb/debug.o
test_rb_driver_overwrite: $(addprefix $(ODIR)/, $(test_rb_driver_overwrite_o))
	@echo "-----"
	@make test_bin TB_OBJ=$(firstword $(filter %$@.o,$^)) TB_NAME=$@ TB_OBJS="$^"
	@echo "-----"

# test_fsm_driver_simple: Test to check `fsm` functionality
test_fsm_driver_simple_o=util/fsm/fsm.o                         \
                         util/fsm/driver/simple.o               \
                         util/fsm/test/test_fsm_driver_simple.o \
                         util/fsm/debug.o
test_fsm_driver_simple: $(addprefix $(ODIR)/, $(test_fsm_driver_simple_o))
	@echo "-----"
	@make test_bin TB_OBJ=$(firstword $(filter %$@.o,$^)) TB_NAME=$@ TB_OBJS="$^"
	@echo "-----"

# test_ce_codec_B416K: Test to check `ce` B416K codec functionality
test_ce_codec_B416K_o=util/rb/rb.o                       \
                      util/rb/driver/overwrite.o         \
                      util/rb/debug.o                    \
                      util/ce/codec.o                    \
                      util/ce/codec/B416K.o              \
                      util/ce/command.o                  \
                      util/ce/test/test_ce_codec_B416K.o \
                      util/ce/debug_codec.o
test_ce_codec_B416K: $(addprefix $(ODIR)/, $(test_ce_codec_B416K_o))
	@echo "-----"
	@make test_bin TB_OBJ=$(firstword $(filter %$@.o,$^)) TB_NAME=$@ TB_OBJS="$^"
	@echo "-----"

# test_ce_command_validate: Test to check `ce` commands functionality
test_ce_command_validate_o=util/ce/command.o                       \
                           util/ce/command/set_test.o              \
                           util/ce/test/test_ce_command_validate.o
test_ce_command_validate: $(addprefix $(ODIR)/, $(test_ce_command_validate_o))
	@echo "-----"
	@make test_bin TB_OBJ=$(firstword $(filter %$@.o,$^)) TB_NAME=$@ TB_OBJS="$^"
	@echo "-----"

# test_ce_command_codec_B416K: Test to check `ce` commands functionality
test_ce_command_codec_B416K_o=util/rb/rb.o                               \
                              util/rb/driver/overwrite.o                 \
                              util/rb/debug.o                            \
                              util/ce/codec.o                            \
                              util/ce/codec/B416K.o                      \
                              util/ce/command.o                          \
                              util/ce/command/set_test.o                 \
                              util/ce/test/test_ce_command_codec_B416K.o
test_ce_command_codec_B416K: $(addprefix $(ODIR)/, \
																						 $(test_ce_command_codec_B416K_o))
	@echo "-----"
	@make test_bin TB_OBJ=$(firstword $(filter %$@.o,$^)) TB_NAME=$@ TB_OBJS="$^"
	@echo "-----"

# test_ce_initialization: Test to check `ce` commands functionality
test_ce_initialization_o=util/rb/rb.o                          \
                         util/rb/driver/overwrite.o            \
                         util/fsm/fsm.o                        \
                         util/ce/ce.o                          \
                         util/ce/codec.o                       \
                         util/ce/codec/B416K.o                 \
                         util/ce/channel.o                     \
                         util/ce/command.o                     \
                         util/ce/command/set_test.o            \
                         util/ce/driver/fire-and-forget.o      \
                         util/ce/test/test_ce_initialization.o
test_ce_initialization: $(addprefix $(ODIR)/, $(test_ce_initialization_o))
	@echo "-----"
	@make test_bin TB_OBJ=$(firstword $(filter %$@.o,$^)) TB_NAME=$@ TB_OBJS="$^"
	@echo "-----"

# test_ce_driver_faf: Test to check `ce` commands functionality
test_ce_driver_faf_o=util/ce/test/test_ce_driver_faf.o
test_ce_driver_faf: $(addprefix $(ODIR)/, $(test_ce_driver_faf_o))
	@echo "-----"
	@make test_bin TB_OBJ=$(firstword $(filter %$@.o,$^)) TB_NAME=$@ TB_OBJS="$^"
	@echo "-----"
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Targets for 'src' folder
# ~~~~~~~~~~~~~~~~~~~~~~~~
# Test app compounding all other tests defined here
test_yacup_o=$(test_xyz_testname_o)            \
             $(test_rb_driver_overwrite_o)     \
             $(test_fsm_driver_simple_o)       \
             $(test_ce_codec_B416K_o)          \
             $(test_ce_command_validate_o)     \
             $(test_ce_command_codec_B416K_o)  \
             $(test_ce_initialization_o)       \
             $(test_ce_driver_faf_o)           \
             src/test/test_yacup.o
test_yacup: $(addprefix $(ODIR)/, $(test_yacup_o))
	@echo "-----"
	make test_bin TB_OBJ=$(firstword $(filter %$@.o,$^)) TB_NAME=$@ TB_OBJS="$^"
	@echo "-----"

# Normal app (main() function is there)
an_app_o=some/object/file.o
an_app: $(addprefix $(ODIR)/, $(an_app_o))
	@echo "-----"
	@echo "\nLinking | << $^\n        | >> $(BDIR)/$@"
	$(CC) $^ $(CFLAGS) $(LDLIBS) -o $(BDIR)/$@
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
	@if [ "$(TB_OBJ)"  = "" -o "$(TB_OBJS)" = "" -o "$(TB_NAME)" = "" ]; \
	then                                                                 \
	  echo "-----";                                                      \
	  echo ":::::::::::::::::::::::::::::::::::::::::::::::::::::";      \
	  echo ":: This is not supposed to be called this way, son ::";      \
	  echo ":::::::::::::::::::::::::::::::::::::::::::::::::::::";      \
	  echo ":: TB_OBJ .........: $(TB_OBJ)";                             \
	  echo ":: TB_OBJS ........: $(TB_OBJS)";                            \
	  echo ":: TB_NAME ........: $(TB_NAME)";                            \
	  echo ":::::::::::::::::::::::::::::::::::::::::::::::::::::";      \
	  echo "-----";                                                      \
	  exit 1;                                                            \
  fi
	@echo "-----\nSetting '$(TB_NAME)()' as the new 'main()'"
	$(OBJCOPY) --redefine-sym $(TB_NAME)=main $(TB_OBJ)
	@echo "\nLinking | << $(TB_OBJS)\n        | >> $(BDIR)/$(TB_NAME)"
	$(CC) $(TB_OBJS) $(CFLAGS) $(LDLIBS) -o $(BDIR)/$(TB_NAME)
	@echo "\nExecuting '$(TB_NAME)': $(BDIR)/$(TB_NAME)\n-----"
	@$(BDIR)/$(TB_NAME)
	@echo "-----"

.PHONY: all
all: clean debug prepare test_yacup                  \
                         test_xyz_testname           \
                         test_rb_driver_overwrite    \
                         test_fsm_driver_simple      \
                         test_ce_codec_B416K         \
                         test_ce_command_validate    \
                         test_ce_command_codec_B416K \
                         test_ce_initialization      \
                         test_ce_driver_faf
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
	@echo "  make <target>"
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
	@echo "  - test_xyz_testname"
	@echo "    'xyz' template tests as a guideline for development purposes"
	@echo ""
	@echo "  - test_rb_driver_overwrite"
	@echo "    'rb' module tests on 'overwrite' driver implementation"
	@echo ""
	@echo "  - test_fsm_driver_simple"
	@echo "    'fsm' module tests on 'simple' driver implementation"
	@echo ""
	@echo "  - test_ce_codec_B416K"
	@echo "    'ce_codec' module tests, 'B416K' codec implementation"
	@echo ""
	@echo "  - test_ce_command_validate"
	@echo "    'ce_command' validation flows tests and checks"
	@echo ""
	@echo "  - test_ce_command_codec_B416K"
	@echo "    'ce_command_codec' tests using 'binary' codec implementation"
	@echo ""
	@echo "  - test_ce_initialization"
	@echo "    'ce' basic initialize and usage tests (partial, devel mostly)"
	@echo ""
	@echo "  - test_ce_driver_faf"
	@echo "    'ce' API basic tests: All previous tests features as a compund"
	@echo ""
	@echo ""
	@echo "Available targets related to application tests:"
	@echo "  - test_yacup"
	@echo "    Example application test that runs all other utils tests in a row"
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
