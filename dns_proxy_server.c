#include "dns_proxy_server.h"

char *UPSTREAM_DNS_ADDR;
char *RESPONSE_BLACKLIST;
char *BLACKLIST;

int main(){
    int sock_fd;

    struct sockaddr_in bind_addr, client_addr, dns_addr;
    socklen_t client_addr_len = 0, response_len = 0;

    struct dns_header_t *dns_h;
    struct dns_question_t *dns_q;

    unsigned char buff[MAX_BUFFER], domain[MIN_BUFFER] = "google.com", *network_domain;
    //unsigned banned = 0;

    srand(time(NULL));

    get_config(CONFIG_FILE);

    sock_fd = create_socket();
    
    memset(&client_addr, 0, sizeof(client_addr));
    memset(&dns_addr, 0, sizeof(dns_addr));
    memset(&bind_addr, 0, sizeof(bind_addr));   

    dns_addr.sin_family = AF_INET;
    dns_addr.sin_port = htons(DNS_PORT);
    inet_pton(AF_INET, UPSTREAM_DNS_ADDR, &(dns_addr.sin_addr));
    
    bind_addr.sin_family = AF_INET;
    bind_addr.sin_port = htons(CLIENT_PORT);
    bind_addr.sin_addr.s_addr = INADDR_ANY;

    bind_socket(sock_fd, bind_addr);

    while(1){
        memset(&domain, 0, MIN_BUFFER);

        ssize_t catch = recvfrom(sock_fd, domain, MIN_BUFFER, 0, (struct sockaddr *)&client_addr, &client_addr_len);

        if(errno != 0){
            perror("recvfrom failed");
            config_free();
            close(sock_fd); 
            exit(EXIT_FAILURE);
        }

        if(catch > 0)
            break;
    }

    dns_h = (struct dns_header_t *)&buff;
    fill_dns_header(dns_h);

    network_domain = (unsigned char *)&buff[sizeof(struct dns_header_t)];
    to_dns_format_domain(network_domain, domain);
    
    dns_q = (struct dns_question_t*)&buff[sizeof(struct dns_header_t) + strlen((const char *)network_domain) + 1];
    dns_q->qtype = htons(1); //1 = A - IPv4 query
    dns_q->qclass = htons(1); //1 = IN - internet 
    size_t buffer_pos = sizeof(struct dns_header_t) + (strlen((const char *)network_domain) + 1) + sizeof(struct dns_question_t);

    printf("Sending query.. ");
    send_message(sock_fd, buff, buffer_pos, dns_addr);

    printf("Recieving response.. ");
    recieve_response(sock_fd, buff, &dns_addr, &response_len);

    printf("Sending response to client.. ");
    send_message(sock_fd, buff, buffer_pos, dns_addr);

    if(sock_fd) close(sock_fd);

    config_free();
}