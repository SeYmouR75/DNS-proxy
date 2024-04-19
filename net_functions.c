#include "net_functions.h"

int create_socket(){
    int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

    if(sock_fd == -1){
        printf("UDP socket creation failed\n");
        config_free();
        exit(EXIT_FAILURE);
    }else{
        printf("UDP socket created\n");
    }

    return sock_fd;
}

void bind_socket(int sock_fd, struct sockaddr_in addr){
    printf("Binding a UDP socket.. ");
    if (bind(sock_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1){
        printf("UDP socket binding failed\n");
        config_free();
        if(sock_fd) close(sock_fd);
        exit(EXIT_FAILURE);
    }else{
        printf("UDP socket bound\n");
    } 
}

void to_dns_format_domain(unsigned char *network, unsigned char *host){
    int lock = 0;
    unsigned char *tmp_ptr = network; 

    strcat((char*)host,".");
    
    for(int i = 0; i < (int)strlen((char*)host); i++){

        if(host[i] == '.'){
			*tmp_ptr++ = i - lock;
            
            for(;lock < i; lock++){
                *tmp_ptr++ = host[lock];
            }
            lock++;
        }
    }
    *tmp_ptr = '\0';

}

void fill_dns_header(struct dns_header_t *dns_h){
    dns_h->id = htons(rand() % (UINT16_MAX + 1)); //query id
    dns_h->qr = 0; //query = 0 response = 1
    dns_h->opcode = 0; //query type(0 - standart)
    dns_h->aa = 0; //not authoritative
    dns_h->tc = 0; //not truncated
    dns_h->rd = 0; //recursion not desired
    dns_h->ra = 0; //recursion not available
    dns_h->z = 0; //reserved thats should be 0
    dns_h->ad = 0; //1 if response was authentic 0 if its not
    dns_h->cd = 0; //If set to 1 this indicates that the client has requested that data authentication be disabled
    dns_h->rcode = 0; //successful query - 0, format error - 1, server not found - 2, response rejection - 3, etc
    dns_h->q_count = htons(1); //number of questions(1)
    dns_h->ans_count = 0; //number of answers
    dns_h->auth_count = 0; //number of authoritative records
    dns_h->add_count = 0; //number of additional records
}

void send_message(int sock_fd, unsigned char *buff, size_t buf_size, struct sockaddr_in addr){
    if(sendto(sock_fd, buff, buf_size, 0, (struct sockaddr *)&addr, sizeof(addr)) < 0){
        printf("%s\n", strerror(errno));
        config_free();
        if(sock_fd) close(sock_fd);
        exit(EXIT_FAILURE);
    }
    printf("Done\n");
}

void recieve_response(int sock_fd, unsigned char *buff, struct sockaddr_in *addr, socklen_t *len){
    if(recvfrom(sock_fd, buff, sizeof buff, 0, (struct sockaddr *)&addr, len) < 0){
        printf("%s\n", strerror(errno));
        config_free();
        if(sock_fd) close(sock_fd);
        exit(EXIT_FAILURE);
    }
    printf("Done\n");
}