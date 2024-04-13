#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "get_config.h"

#define CONFIG_FILE "dns_settings.conf"
#define DNS_PORT 49155
#define MAX_BUFFER 1024

int main(){
    int sock_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char domain_name[MAX_BUFFER];
    unsigned banned = 0;
    char* upstream_dns_addr = get_dns_addr(CONFIG_FILE);
    char* response_blacklist = get_response_type(CONFIG_FILE);
    char* blacklist = get_blacklist(CONFIG_FILE);

    if(errno != 0){
        printf("%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }else if(!upstream_dns_addr || !response_blacklist || !blacklist){
        printf("Some or all of the settings are incorrect, please check dns_settings.conf\n");
        config_free(upstream_dns_addr, response_blacklist, blacklist);
        exit(EXIT_FAILURE);
    }else{
        printf("Configuration has been set successfully\n");
    }

    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

    if(sock_fd == -1){
        printf("socket creation failed\n");
        config_free(upstream_dns_addr, response_blacklist, blacklist);
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));   
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(DNS_PORT);

    if (bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1){
        printf("socket binding failed\n");
        config_free(upstream_dns_addr, response_blacklist, blacklist);
        exit(EXIT_FAILURE);
    }

    addr_size = sizeof(client_addr);

    while(1){
        memset(&domain_name, 0, MAX_BUFFER);

        recvfrom(sock_fd, domain_name, MAX_BUFFER, 0, (struct sockaddr *)&client_addr, &addr_size);

        if(errno != 0){
            perror("recvfrom failed");
            printf("%s\n", strerror(errno));
            break;
        }

        if(domain_name){
            break;
        }
    }

    char* token = strtok(blacklist, ",");

    while(token != NULL){
        if(strcmp(domain_name, token) == 0){
            banned = 1;
        }
        token = strtok(NULL, ",");
    }

    printf("%u\n", banned);

    // get_target_domain();
    // check_domain();
    // connect_to_upstream_dns(upstream_dns_addr);

    if(sock_fd) close(sock_fd);

    config_free(upstream_dns_addr, response_blacklist, blacklist);
}