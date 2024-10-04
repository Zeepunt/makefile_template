#
# Copyright (c) 2024 by Zeepunt, All Rights Reserved. 
#

ROOT_PATH := $(shell pwd)
BUILD_PATH := $(ROOT_PATH)/build

TARGET := $(BUILD_PATH)/example

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

CC_INCLUDES := -I$(ROOT_PATH)/include

export ROOT_PATH BUILD_PATH CC_FLAGS LD_FLAGS CC_INCLUDES

include $(ROOT_PATH)/scripts/Makefile.include

obj-y += lib/
obj-y += src/

lib-y += example.a

PHONY :=
PHONY += all
all: env
	$(Q)$(MAKE) -C ./ $(build) build
	$(CC) $(LD_FLAGS) $(CC_INCLUDES) -o $(TARGET) $(BUILD_PATH)/built-in.o

PHONY += env
env:
	$(Q)if [ ! -d $(BUILD_PATH) ]; then \
		mkdir -p $(BUILD_PATH);         \
	fi

PHONY += clean
clean:
	$(Q)rm -rf $(BUILD_PATH)

.PHONY: $(PHONY)