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
IDIR = $(addprefix $(MFDIR)/, $(wildcard util/*/yacup))
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

# Wildcard target that look for .c file based on .o name
$(ODIR)/%.o: $(SDIR)/%.c
	@echo "-----"
	@echo "Compiling | << $<\n          | >> $@"
	$(MKDIR) -p $(@D)
	$(CC) -c $< $(CFLAGS) -o $@
	@echo "-----"

# Targets ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Targets for 'util' folder ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Test to check rb's driver_v1 functionality
test_rb_driver_v1_objs=util/rb/test/driver_v1.o
test_rb_driver_v1: $(addprefix $(ODIR)/, $(test_rb_driver_v1_objs))
	@echo "-----\nSetting '$@()' as the new 'main()'"
	$(OBJCOPY) --redefine-sym $@=main $^
	@echo "\nLinking | << $^\n        | >> $(BDIR)/$@"
	$(CC) $^ $(CFLAGS) $(LDLIBS) -o $(BDIR)/$@
	@echo "\nExecuting '$@': $(BDIR)/$@\n-----"
	@$(BDIR)/$@
	@echo "-----"

# Simple test for `rb`
test_rb_simple_objs=util/rb/test/simple.o
test_rb_simple: $(addprefix $(ODIR)/, $(test_rb_simple_objs))
	@echo "-----\nSetting '$@()' as the new 'main()'"
	$(OBJCOPY) --redefine-sym $@=main $^
	@echo "\nLinking | << $^\n        | >> $(BDIR)/$@"
	$(CC) $^ $(CFLAGS) $(LDLIBS) -o $(BDIR)/$@
	@echo "\nExecuting '$@': $(BDIR)/$@\n-----"
	@$(BDIR)/$@
	@echo "-----"

# Targets for 'src' folder ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Test app compounding all other tests defined here
test_yacup_objs=$(test_rb_driver_v1_objs) \
                $(test_rb_simple_objs)    \
                src/test_yacup.o
test_yacup: $(addprefix $(ODIR)/, $(test_yacup_objs))
	@echo "-----\nSetting '$@()' as the new 'main()'"
	$(OBJCOPY) --redefine-sym $@=main $(lastword $^)
	@echo "\nLinking | << $^\n        | >> $(BDIR)/$@"
	$(CC) $^ $(CFLAGS) $(LDLIBS) -o $(BDIR)/$@
	@echo "\nExecuting '$@': $(BDIR)/$@\n-----"
	@$(BDIR)/$@
	@echo "-----"
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# My Little Phonies
.PHONY: all
all: clean debug prepare test_yacup test_rb_simple test_rb_driver_v1
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
