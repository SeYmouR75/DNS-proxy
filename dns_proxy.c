#include "dns_proxy.h"

int main(){
    char* upstream_dns_addr = get_dns_addr(CONFIG_FILE);
    int response_blacklist = get_response_type(CONFIG_FILE);
    char* blacklist = get_blacklist(CONFIG_FILE);
    printf("%s %d %s\n", upstream_dns_addr, response_blacklist, blacklist);



    // get_target_domain();
    // check_domain();
    // connect_to_upstream_dns(upstream_dns_addr);


    if(upstream_dns_addr) free(upstream_dns_addr);
    if(blacklist) free(blacklist);

}