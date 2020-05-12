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
CFLAGS = $(addprefix -I, $(IDIR)) -Wall -pedantic-errors
LDLIBS = -lm

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Targets for 'util' folder
# ~~~~~~~~~~~~~~~~~~~~~~~~~
# Test to check `xyz` template functionality
test_xyz_testname_objs=template/util_xyz/xyz.o                    \
                       template/util_xyz/debug.o                  \
                       template/util_xyz/test/test_xyz_testname.o
test_xyz_testname: $(addprefix $(ODIR)/, $(test_xyz_testname_objs))
	@echo "-----"
	@make test_bin TB_OBJ=$(firstword $(filter %$@.o,$+)) TB_NAME=$@ TB_OBJS="$+"
	@echo "-----"

# Test to check `rb` driver_v1 functionality
test_rb_driver_v1_objs=util/rb/rb.o \
                       util/rb/debug.o \
                       util/rb/driver_v1.o \
                       util/rb/test/test_rb_driver_v1.o
test_rb_driver_v1: $(addprefix $(ODIR)/, $(test_rb_driver_v1_objs))
	@echo "-----"
	@make test_bin TB_OBJ=$(firstword $(filter %$@.o,$+)) TB_NAME=$@ TB_OBJS="$+"
	@echo "-----"

# Test to check `fsm` functionality
test_fsm_simple_objs=util/fsm/fsm.o                  \
                     util/fsm/debug.o                \
                     util/fsm/test/fsm_simple.o      \
                     util/fsm/test/test_fsm_simple.o
test_fsm_simple: $(addprefix $(ODIR)/, $(test_fsm_simple_objs))
	@echo "-----"
	@make test_bin TB_OBJ=$(firstword $(filter %$@.o,$+)) TB_NAME=$@ TB_OBJS="$+"
	@echo "-----"

# Test to check `cp` B420K protocol functionality
test_cp_testname_objs=util/cp/cp.o \
                      util/cp/debug.o \
                      util/cp/test/test_cp_testname.o
test_cp_testname: $(addprefix $(ODIR)/, $(test_cp_testname_objs))
	@echo "-----"
	@make test_bin TB_OBJ=$(firstword $(filter %$@.o,$+)) TB_NAME=$@ TB_OBJS="$+"
	@echo "-----"
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Targets for 'src' folder
# ~~~~~~~~~~~~~~~~~~~~~~~~
# Test app compounding all other tests defined here
test_yacup_objs=$(test_xyz_testname_objs) \
                $(test_rb_driver_v1_objs) \
                $(test_fsm_simple_objs)   \
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
all: clean debug prepare test_yacup \
                         test_xyz_testname \
                         test_rb_driver_v1 \
                         test_fsm_simple \
                         test_cp_testname
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
	@echo "Available targets:"
	@echo "  default ...: Executed if 'make' without target. Default: all"
	@echo "  all .......: Executes all targets in sequence"
	@echo "  clean .....: Deletes generated files after build"
	@echo "  debug .....: Print debug information, like variables"
	@echo "  prepare ...: Creates required folders and files"
	@echo "  help ......: Print this information"
	@echo ""
