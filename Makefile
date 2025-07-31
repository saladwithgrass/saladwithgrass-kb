
ARMGNU ?= arm-none-eabi

XCPU = -mcpu=cortex-m0

AOPS = --warn --fatal-warnings $(XCPU)
CFLAGS = -Wall -O2 -ffreestanding $(XCPU) -nostartfiles 
LDFLAGS = -nostdlib

TARGET = keyboard

# key directories
BUILD_DIR = build
SRC_DIR = src
BIN_DIR = bin
RP2040_DIR = $(SRC_DIR)/RP2040
KEYBOARD_DIR = $(SRC_DIR)/keyboard
DEBUG_MATRIX_DIR = $(SRC_DIR)/debug_matrix

# source files
KEYBOARD_SRC =  $(wildcard $(KEYBOARD_DIR)/*.c)
RP2040_SRC = $(wildcard $(RP2040_DIR)/*.c) $(wildcard $(RP2040_DIR)/*/*.c)
MAKEU2F_SRC = $(SRC_DIR)/makeuf2f.c
BOOTLOADER_SRC = $(SRC_DIR)/start.s
MEMMAP_SRC = $(SRC_DIR)/memmap.ld
DEBUG_MATRIX_SRC = $(wildcard $(DEBUG_MATRIX_DIR)/*.c)

RP2040_OBJS = $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(RP2040_SRC))
KEYBOARD_OBJS = $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(KEYBOARD_SRC))
DEBUG_MATRIX_OBJS = $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(DEBUG_MATRIX_SRC))
BOOTLOADER_OBJ = $(BIN_DIR)/start.o
# ALL_OBJS = $(RP2040_OBJS) $(KEYBOARD_OBJS) $(DEBUG_MATRIX_OBJS) $(BOOTLOADER_OBJ)

all : build

build: clean
	@echo ""
	@echo "----------------------------------"
	@echo "STARTING BUILD"
	@echo "----------------------------------"
	mkdir $(BUILD_DIR)
	cp -r $(SRC_DIR) $(BUILD_DIR)
	cp Makefile $(BUILD_DIR)
	$(MAKE) $(TARGET).uf2 -C $(BUILD_DIR) 


clean:
	@echo ""
	@echo "----------------------------------"
	@echo "CLEANING UP"
	rm -f *.bin
	rm -f *.o
	rm -f *.elf
	rm -f *.list
	rm -f *.uf2
	rm -f makeuf2f
	rm -rf $(BUILD_DIR)
	
# build target
$(TARGET).uf2 : $(TARGET).bin makeuf2f
	./makeuf2f $(TARGET).bin $@

# build bootloader
$(BOOTLOADER_OBJ) : $(BOOTLOADER_SRC)
	@echo "----------------------------------"
	@echo "BUIDING BOOTLOADER: $@"
	mkdir -p $(@D)
	$(ARMGNU)-as $(AOPS) $(BOOTLOADER_SRC) -o $@

# build objects from C files
$(BIN_DIR)/%.o : $(SRC_DIR)/%.c
	@echo "----------------------------------"
	@echo "BUIDING $@ from $^"
	mkdir -p $(@D)
	$(ARMGNU)-gcc $(CFLAGS) -mthumb -c $^ -o $@

# build binary
$(TARGET).bin : $(MEMMAP_SRC) $(BOOTLOADER_OBJ) $(KEYBOARD_OBJS) $(RP2040_OBJS) $(DEBUG_MATRIX_OBJS)
	@echo ""
	@echo "----------------------------------"
	@echo "BUIDING TARGET BINARY"
	$(ARMGNU)-ld $(LDFLAGS) -T $^ -o $(TARGET).elf
	$(ARMGNU)-objdump -D $(TARGET).elf > $(TARGET).list
	$(ARMGNU)-objcopy -O binary $(TARGET).elf $(TARGET).bin
	@echo "----------------------------------"

makeuf2f : $(MAKEU2F_SRC)
	gcc -O2 $(MAKEU2F_SRC) -o makeuf2f

##-------------------------------------------------------------------------
##
## Copyright (c) 2021 David Welch dwelch@dwelch.com
##
## Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
##
## The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
##
## THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
##
##-------------------------------------------------------------------------
