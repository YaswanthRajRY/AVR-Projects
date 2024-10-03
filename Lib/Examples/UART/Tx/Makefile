# AVR Makefile
#
# Written by Yaswanth Raj R Y (https://github.com/YaswanthRajRY)

# Targets:
#		
#		all: Compile all the file
#		
#		flash: flash the program code to MCU
#
#		clean: remove all the .o .hex .elf files
#		

# Micro-controller name
MCU=atmega328p
MCU2=ATMEGA328P

# CPU clock frequency. For ATMega328P - 16Mhz
F_CPU=16000000UL

# Hardware serial port 
PORT=/dev/ttyUSB0

# Program source files
TARGET=main
SRCS=main.c

# where to look for external libraries (consisting of .c/.cpp files and .h files)
FREERTOS_LIB = Source Source/include
EXTC := $(foreach dir, $(FREERTOS_LIB), $(wildcard $(dir)/*.c))
INCLUDE := $(foreach dir, $(FREERTOS_LIB), -I$(dir))

# Generate object file names from C source files
OBJ := $(SRCS:.c=.o) $(notdir $(EXTC:.c=.o))

all:

# 	Compile all .c files
	avr-gcc -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU) $(INCLUDE) -c $(SRCS) $(EXTC)

#	Link all the oblect files in one file
	avr-gcc -mmcu=$(MCU) -o $(TARGET).elf $(OBJ)

#	Convert the linker file into .hex file
	avr-objcopy -O ihex -R .eeprom $(TARGET).elf $(TARGET).hex

        
flash:

#	Flash program (.hex) to MCU
	avrdude -F -V -c arduino -p $(MCU2) -P $(PORT) -b 115200 -U flash:w:$(TARGET).hex
        
clean:

#	Remove compiled files (.o .hex .elf)
	rm -f *.o *.hex *.elf

env: all flash clean
