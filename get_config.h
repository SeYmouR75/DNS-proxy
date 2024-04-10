#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int load_config(char* filename, char** upstream_dns_addr, char* response_blacklist, char** blacklist);
char* get_dns_addr();
char get_response_type();
char* get_blacklist();
