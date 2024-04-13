#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

char* get_dns_addr(char* filename);
char* get_response_type(char* filename);
char* get_blacklist(char* filename);
void config_free(char* upstream_dns_addr, char* response_blacklist, char* blacklist);
