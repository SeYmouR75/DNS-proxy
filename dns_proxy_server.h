#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "get_config.h"
#include "net_functions.h"

#define CONFIG_FILE "dns_settings.conf"
#define DNS_PORT 53
#define CLIENT_PORT 49155
#define MIN_BUFFER 100
#define MAX_BUFFER 65536