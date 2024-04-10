CC=gcc
CFLAGS=-Wall -Werror -Wextra

BUILD_DIR=build

ifeq ($(wildcard $(BUILD_DIR)), )
  $(shell mkdir $(BUILD_DIR))
endif

SRC=$(wildcard *.c)
OBJ=$(addprefix $(BUILD_DIR)/,$(SRC:%.c=%.o))
HDR=$(wildcard *.h)

TARGET=proxy.exe


all:$(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(HDR) -o $(BUILD_DIR)/$@

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: clean $(TARGET)
	./$(BUILD_DIR)/$(TARGET)

clean_obj:
	rm -rf $(BUILD_DIR)/*.o

clean_exec:
	rm -rf $(BUILD_DIR)/*.exe

clean: clean_obj clean_exec