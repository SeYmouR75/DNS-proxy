#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#include "get_config.h"

struct dns_header_t {
    uint16_t id;

    uint16_t rd :1;
    uint16_t tc :1;
    uint16_t aa :1;
    uint16_t opcode :4;
    uint16_t qr :1;

    uint16_t rcode :4;
    uint16_t cd :1;
    uint16_t ad :1;
    uint16_t z :1;
    uint16_t ra :1;

    uint16_t q_count;
    uint16_t ans_count; 
    uint16_t auth_count;
    uint16_t add_count;
};

struct dns_question_t {
    uint16_t qtype;
    uint16_t qclass;
};

struct dns_r_data_t
{
	uint16_t type;
	uint16_t _class;
	uint16_t ttl;
	uint16_t data_len;
};

int create_socket();
void bind_socket(int sock_fd, struct sockaddr_in addr);
void to_dns_format_domain(unsigned char *buff, unsigned char *domain);
void fill_dns_header(struct dns_header_t *dns_h);
void send_message(int sock_fd, unsigned char *buff, size_t buf_size, struct sockaddr_in addr);
void recieve_response(int sock_fd, unsigned char *buff, struct sockaddr_in *dns_addr, socklen_t *response_len);
