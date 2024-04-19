#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

extern char *UPSTREAM_DNS_ADDR;
extern char *RESPONSE_BLACKLIST;
extern char *BLACKLIST;

char *get_config(char *filename);
char *get_response_type(char *filename);
char *get_blacklist(char *filename);
int check_banned(char *domain_name);
void config_free();