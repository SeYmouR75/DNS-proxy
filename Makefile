CC=gcc
CFLAGS=-Wall -Wextra #-Werror

BUILD_DIR=build

ifeq ($(wildcard $(BUILD_DIR)), )
  $(shell mkdir $(BUILD_DIR))
endif

SRC=$(wildcard *.c)
OBJ=$(addprefix $(BUILD_DIR)/,$(SRC:%.c=%.o))
HDR=$(wildcard *.h)

TARGET=proxy.exe


all: clean $(TARGET)

client: client_clear
	$(CC) $(CFLAGS) Test_client/test.c -o $(BUILD_DIR)/client.exe
	./$(BUILD_DIR)/client.exe

client_clear:
	rm -rf $(BUILD_DIR)/client.exe

server: server_clear
	$(CC) $(CFLAGS) dns_proxy_server.c get_config.c net_functions.c dns_proxy_server.h get_config.h net_functions.h -o $(BUILD_DIR)/server.exe
	valgrind --tool=memcheck --leak-check=yes -s ./$(BUILD_DIR)/server.exe

server_clear:
	rm -rf 	$(BUILD_DIR)/server.exe

instance: instance_clear
	$(CC) $(CFLAGS) Test_client/heheh.c -o $(BUILD_DIR)/instance.exe
	./$(BUILD_DIR)/instance.exe

instance_clear:
	rm -rf $(BUILD_DIR)/instance.exe

query: query_clear
	$(CC) $(CFLAGS) dns_query.c dns_query.h -o $(BUILD_DIR)/query.exe
	./$(BUILD_DIR)/query.exe

query_clear:
	rm -rf $(BUILD_DIR)/query.exe





$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(HDR) -o $(BUILD_DIR)/$@

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: clean $(TARGET)
	./$(BUILD_DIR)/$(TARGET)
#	valgrind --tool=memcheck --leak-check=yes -s ./$(BUILD_DIR)/$(TARGET)

clean_obj:
	rm -rf $(BUILD_DIR)/*.o

clean_exec:
	rm -rf $(BUILD_DIR)/*.exe

clean: clean_obj clean_exec