#include "get_config.h"

int load_config(char* filename, char** upstream_dns_addr, char* response_blacklist, char** blacklist){
    int no_error = 0;
    FILE* conf_file;
    conf_file = fopen(filename, "r");
    if(errno){
        printf("%s\n", strerror(errno));
    }else{
        *blacklist = "asdasd"; // get_blacklist();
        *response_blacklist = '0'; // get_response():
        *upstream_dns_addr = get_dns_addr(conf_file);// get_dns_addr();
        no_error = 1;
    }
    
    if(conf_file) fclose(conf_file);

    return no_error;
}

char* get_dns_addr(FILE* conf_file){
    char* variable;
    size_t variable_size = 0;
    char variable_name[18], variable_value[16];
    char* result;
    
    do{
        if(getline(&variable, &variable_size, conf_file) != -1){
            if(sscanf(variable, "%[^=]=%[^\n]", variable_name, variable_value) == 2){
                result = (char*)malloc(strlen(variable_value) + 1);
                strcpy(result, variable_value);
            }

        }
    

    }while(strncmp(variable_name, "UPSTREAM_DNS_ADDR", 17) != 0);

    if(variable){
        free(variable);
    }

    return result;
}

// char* get_blacklist(FILE* conf_file){

// }