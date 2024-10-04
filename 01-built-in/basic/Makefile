#
# Copyright (c) 2024 by Zeepunt, All Rights Reserved. 
#

ROOT_PATH := $(shell pwd)

TARGET := example

CC_PREFIX :=
AS        := $(CC_PREFIX)as
CC        := $(CC_PREFIX)gcc
CPP       := $(CC_PREFIX)g++
LD        := $(CC_PREFIX)ld
NM        := $(CC_PREFIX)nm
AR        := $(CC_PREFIX)ar
OBJCOPY   := $(CC_PREFIX)objcopy
OBJDUMP   := $(CC_PREFIX)objdump
SIZE      := $(CC_PREFIX)size
STRIP     := $(CC_PREFIX)strip

CC_FLAGS := -g
LD_FLAGS :=

CC_INCLUDES := -I$(ROOT_PATH)/lib/func_a/ \
               -I$(ROOT_PATH)/lib/func_b/

export ROOT_PATH CC_FLAGS LD_FLAGS CC_INCLUDES

SUB_DIR := lib \
           src

PHONY := all
all: $(SUB_DIR)
	$(CC) $(LD_FLAGS) $(CC_INCLUDES) -o $(TARGET) lib/built-in.o src/built-in.o

PHONY += $(SUB_DIR)
$(SUB_DIR):
	$(MAKE) -C $@ -f $(ROOT_PATH)/scripts/Makefile.build build

PHONY += clean
clean:
	@rm -f $(shell find -name "*.o")
	@rm -f $(shell find -name "*.d")
	@rm -f $(TARGET)

.PHONY: $(PHONY)