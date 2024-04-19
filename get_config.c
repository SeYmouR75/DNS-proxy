#include "get_config.h"

char *get_config(char *filename){
    FILE *conf_file;
    char *variable = NULL;
    size_t variable_size = 0;
    char variable_name[18], *variable_value;
    char *result = NULL;
    
    conf_file = fopen(filename, "r");
    
    if(!errno){
        while(getline(&variable, &variable_size, conf_file) != -1){

            variable_value = malloc(strlen(variable));
            
            if(sscanf(variable, "%[^=]=%[^\n]", variable_name, variable_value) == 2){
                
                
                if(strncmp(variable_name, "UPSTREAM_DNS_ADDR", 17) == 0){
                    UPSTREAM_DNS_ADDR = (char*)malloc(strlen(variable_value) + 1);
                    strcpy(UPSTREAM_DNS_ADDR, variable_value);
                }
                if(strncmp(variable_name, "RESPONSE_BANNED", 15) == 0){ 
                    RESPONSE_BLACKLIST = (char*)malloc(strlen(variable_value) + 1);
                    strcpy(RESPONSE_BLACKLIST, variable_value);
                }
                if(strncmp(variable_name, "BLACKLIST", 9) == 0){
                    BLACKLIST = (char*)malloc(strlen(variable_value) + 1);
                    strcpy(BLACKLIST, variable_value);
                }
            }

            if(variable_value) free(variable_value);
        }
    }

    if(variable) free(variable);

    if(conf_file) fclose(conf_file);

    if(errno != 0){
        printf("%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }else if(!UPSTREAM_DNS_ADDR || !RESPONSE_BLACKLIST || !BLACKLIST){
        printf("Some or all of the settings are incorrect, please check dns_settings.conf\n");
        config_free();
        exit(EXIT_FAILURE);
    }else{
        printf("Configuration has been set successfully\n");
    }

    return result;
}

void config_free(){
    if(UPSTREAM_DNS_ADDR) free(UPSTREAM_DNS_ADDR);

    if(RESPONSE_BLACKLIST) free(RESPONSE_BLACKLIST);

    if(BLACKLIST) free(BLACKLIST);
}

int check_banned(char *domain_name){
    int res = 0;

    char *token = strtok(BLACKLIST, ",");

    while(token != NULL){
        if(strcmp(domain_name, token) == 0){
            res = 1;
        }
        token = strtok(NULL, ",");
    }

    return res;
}
