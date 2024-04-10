#include "dns_proxy.h"

int main(){
    char* upstream_dns_addr;
    char response_blacklist;
    char* blacklist;
    if(load_config("dns_settings.conf", &upstream_dns_addr, &response_blacklist, &blacklist)){
        printf("%s %c %s\n", upstream_dns_addr, response_blacklist, blacklist);
    }

    // get_target_domain();
    // check_domain();
    // connect_to_upstream_dns(upstream_dns_addr);


    free(upstream_dns_addr);

}