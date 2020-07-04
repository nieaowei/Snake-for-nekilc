CC		:= gcc
CFLAGS	:= -Wall -Wextra -g

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib
OBJ 	:= obj

LIBRARIES	:= pthread

ifeq ($(OS),Windows_NT)
EXECUTABLE	:= main.exe
SOURCEDIRS	:= $(SRC)
INCLUDEDIRS	:= $(INCLUDE)
LIBDIRS		:= $(LIB)
else
EXECUTABLE	:= main
SOURCEDIRS	:= $(shell find $(SRC) -type d)
INCLUDEDIRS	:= $(shell find $(INCLUDE) -type d)
LIBDIRS		:= $(shell find $(LIB) -type d)
OBJDIRS		:= $(shell find $(OBJ) -type d)
endif

OBJDIRS		= $(subst $(SRC),$(OBJ),$(SOURCEDIRS))

CINCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))
CLIBS		:= $(patsubst %,-L%, $(LIBDIRS:%/=%))

SOURCES		:= $(wildcard $(patsubst %,%/*.c, $(SOURCEDIRS)))
OBJECTS		:= $(subst $(SRC),$(OBJ),$(patsubst %.c,%.o,  $(SOURCES)))

all:  clean $(OBJDIRS) $(BIN)/$(EXECUTABLE) 


.PHONY: clean

driver:
	make all -C driver

test:
	- @echo '$(SOURCES)'
	- @echo '$(SOURCEDIRS)'
	- @echo '$(OBJECTS)'
	- @echo '$(OBJDIRS)'

clean:
	- make clean -C driver
	-$(RM) -r $(OBJ)/*


run: all
	./$(BIN)/$(EXECUTABLE)

$(OBJDIRS):
	mkdir -p $@

$(BIN)/$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(CINCLUDES) $(CLIBS) $^ -o $@ -l$(LIBRARIES)

$(OBJECTS):$(OBJ)/%.o:$(SRC)/%.c
	- $(CC) $(CFLAGS) $(CINCLUDES) $(CLIBS) -c -o $@ $< -l$(LIBRARIES)
